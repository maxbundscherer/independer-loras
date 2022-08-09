import config as conf

import psycopg2

import string
import random

from flask import Flask, request

app = Flask(__name__)

def get_random_string(length):
    letters = string.ascii_lowercase
    result_str = ''.join(random.choice(letters) for i in range(length))
    return result_str

def get_db_connection():
    conn = psycopg2.connect(
        host=conf.getDbConfigHost(),
        database=conf.getDbConfigDatabase(),
        user=conf.getDbConfigUser(),
        password=conf.getDbConfigPassword(),
        port=conf.getDbConfigPort())
    return conn


@app.route('/v1/msg/<receiverId>')
def routeGetMessages(receiverId):
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute(
        "SELECT * FROM messages WHERE active is true AND receiver = '" + receiverId + "';")
    messages = cur.fetchall()
    cur.close()
    conn.close()

    retDict = {}

    for i, messageWrapper in enumerate(messages):
        e = {"receiver": messageWrapper[1],
             "author": messageWrapper[2], "msg": messageWrapper[3]}
        retDict[i] = e

    return retDict

@app.route('/v1/clearmsg/<receiverId>')
def routeClearMessages(receiverId):
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute(
        "UPDATE messages SET active = false WHERE receiver = '" + receiverId + "';")
    conn.commit()
    cur.close()
    conn.close()

    return "OK"


@app.route('/v1/msg', methods=['POST'])
def routeWriteMessage():

    content_type = request.headers.get('Content-Type')
    if (content_type == 'application/json'):
        json = request.json

        conn = get_db_connection()
        cur = conn.cursor()
        cur.execute('INSERT INTO messages (receiver, author, msg, active)'
                    'VALUES (%s, %s, %s, %s)',
                    (json["receiver"],
                     json["author"],
                        json["msg"],
                        True)
                    )
        conn.commit()
        cur.close()
        conn.close()

        return "OK"
    else:
        return 'Content-Type not supported!'

@app.route('/v1/register', methods=['POST'])
def routRegister():

    content_type = request.headers.get('Content-Type')
    if (content_type == 'application/json'):
        json = request.json

        t_app_id = json["id"]
        t_app_secret = json["secret"]

        # Auth Check
        conn = get_db_connection()
        cur = conn.cursor()
        cur.execute("SELECT * FROM users WHERE active is true AND appid = '" + t_app_id + "' AND secret = '" + t_app_secret + "';")
        data = cur.fetchall()
        cur.close()
        conn.close()

        if (len(data) > 0):

            # Disable old devices
            conn = get_db_connection()
            cur = conn.cursor()
            cur.execute("UPDATE devices SET active = false WHERE appid = '" + t_app_id + "';")
            conn.commit()
            cur.close()
            conn.close()

            rand_token = get_random_string(20)

            # Register new device
            conn = get_db_connection()
            cur = conn.cursor()
            cur.execute('INSERT INTO devices (appid, token, active)'
                        'VALUES (%s, %s, %s)',
                        (t_app_id,
                            rand_token,
                            True)
                        )
            conn.commit()
            cur.close()
            conn.close()

            return "OK-" + rand_token
        else:
            return "No User Found"
    else:
        return 'Content-Type not supported!'

import os
if __name__ == "__main__":
  app.run(host="0.0.0.0", port=int(os.environ.get("PORT", 5000)))