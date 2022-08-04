import config as conf

import psycopg2
from flask import Flask, request

app = Flask(__name__)


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

import os
if __name__ == "__main__":
  app.run(host="0.0.0.0", port=int(os.environ.get("PORT", 5000)))