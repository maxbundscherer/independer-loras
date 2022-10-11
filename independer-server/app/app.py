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

def i_check_auth(appid, token):
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute('SELECT * FROM actors WHERE active is true AND appid = %s AND token = %s;', (appid, token))
    
    if cur.rowcount == 1:
        cur.close()
        conn.close()
        return True
    else:
        cur.close()
        conn.close()
        return False

def i_write_history(appid, token, url):
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute('INSERT INTO history (appid, token, url)'
                        'VALUES (%s, %s, %s)',
                        (appid, token, url)
                        )
    conn.commit()
    cur.close()
    conn.close()

# content_type = request.headers.get('Content-Type')
# if (content_type == 'application/json'):
#     json = request.json
#     if i_check_auth(json["auth-id"], json["auth-token"]):
#         # Auth passed
#         pass
#     else:
#         # Auth not passed
#         return "Unauthorized"

@app.route('/v1/getmsgs', methods=['POST'])
def routeGetMessages():

    content_type = request.headers.get('Content-Type')
    if (content_type == 'application/json'):
        json = request.json
        if i_check_auth(json["auth-id"], json["auth-token"]):
            # Auth passed
            i_write_history(json["auth-id"], json["auth-token"], "/v1/getmsgs")
            conn = get_db_connection()
            cur = conn.cursor()
            cur.execute('SELECT * FROM messages WHERE active is true AND receiver = %s;', (json["auth-id"],))
            messages = cur.fetchall()
            cur.close()
            conn.close()

            retDict = {}

            for i, messageWrapper in enumerate(messages):
                e = {"receiver": messageWrapper[1],
                    "author": messageWrapper[2], "msg": messageWrapper[3]}
                retDict[i] = e

            return retDict
        else:
            # Auth not passed
            return "Unauthorized"    

@app.route('/v1/clearmsgs', methods=['POST'])
def routeClearMessages():

    content_type = request.headers.get('Content-Type')
    if (content_type == 'application/json'):
        json = request.json
        if i_check_auth(json["auth-id"], json["auth-token"]):
            # Auth passed
            i_write_history(json["auth-id"], json["auth-token"], "/v1/clearmsgs")
            conn = get_db_connection()
            cur = conn.cursor()
            cur.execute('UPDATE messages SET active = false WHERE receiver = %s;', (json["auth-id"],))
            conn.commit()
            cur.close()
            conn.close()        

            return "OK"
        else:
            # Auth not passed
            return "Unauthorized"

@app.route('/v1/writemsg', methods=['POST'])
def routeWriteMessage():

    content_type = request.headers.get('Content-Type')
    if (content_type == 'application/json'):
        json = request.json
        if i_check_auth(json["auth-id"], json["auth-token"]):
            # Auth passed
            i_write_history(json["auth-id"], json["auth-token"], "/v1/writemsg")
            conn = get_db_connection()
            cur = conn.cursor()
            cur.execute('INSERT INTO messages (receiver, author, msg, active)'
                        'VALUES (%s, %s, %s, %s)',
                        (json["receiver"],
                        json["auth-id"],
                            json["msg"],
                            True)
                        )
            conn.commit()
            cur.close()
            conn.close()

            return "OK"
        else:
            # Auth not passed
            return "Unauthorized"

@app.route('/v1/register', methods=['POST'])
def routRegister():

    content_type = request.headers.get('Content-Type')
    if (content_type == 'application/json'):
        json = request.json

        t_app_id = json["id"]
        t_app_secret = json["secret"]
        t_app_version = json["version"]

        # Auth Check
        conn = get_db_connection()
        cur = conn.cursor()
        cur.execute('SELECT * FROM users WHERE active is true AND appid = %s AND secret = %s;', (t_app_id, t_app_secret))
        data = cur.fetchall()
        cur.close()
        conn.close()

        if (len(data) > 0):

            # Disable old devices
            conn = get_db_connection()
            cur = conn.cursor()
            cur.execute("UPDATE actors SET active = false WHERE appid = %s;", (t_app_id,))
            conn.commit()
            cur.close()
            conn.close()

            rand_token = get_random_string(20)

            # Register new device
            conn = get_db_connection()
            cur = conn.cursor()
            cur.execute('INSERT INTO actors (appid, token, version, active)'
                        'VALUES (%s, %s, %s, %s)',
                        (t_app_id,
                            rand_token,
                            t_app_version,
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

@app.route('/v1/gatewayregister', methods=['POST'])
def routeGatewayRegister():

    content_type = request.headers.get('Content-Type')
    if (content_type == 'application/json'):
        json = request.json
        if i_check_auth(json["auth-id"], json["auth-token"]):
            # Auth passed
            i_write_history(json["auth-id"], json["auth-token"], "/v1/gatewayregister")
            conn = get_db_connection()
            cur = conn.cursor()
            cur.execute('SELECT * FROM gateways WHERE active is true AND appid = %s AND gatewayid = %s;', (json["auth-id"], json["gateway-id"]))

            if cur.rowcount == 1:
                cur.close()
                conn.close()
                return "OK"
            else:
                cur.close()
                conn.close()
                return "Failure"
        else:
            # Auth not passed
            return "Unauthorized"

@app.route('/v1/autosync', methods=['POST'])
def routeAutoSync():

    content_type = request.headers.get('Content-Type')
    if (content_type == 'application/json'):
        json = request.json
        if i_check_auth(json["auth-id"], json["auth-token"]):
            # Auth passed
            i_write_history(json["auth-id"], json["auth-token"], "/v1/autosync")
            conn = get_db_connection()
            cur = conn.cursor()
            cur.execute('INSERT INTO autosync (appid, token, tx_version, tx_battery, tx_time_before_sync, tx_time_after_sync, tx_dev_mode, tx_is_actor)'
                        'VALUES (%s, %s, %s, %s, %s, %s, %s, %s)',
                        (json["auth-id"],
                        json["auth-token"],
                            json["version"],
                            json["battery"],
                            json["time_before_sync"],
                            json["time_after_sync"],
                            json["dev_mode"],
                            json["is_actor"])
                        )
            conn.commit()
            cur.close()
            conn.close()

            return "OK"
        else:
            # Auth not passed
            return "Unauthorized"

#import os
#if __name__ == "__main__":
#  app.run(host="0.0.0.0", port=int(os.environ.get("PORT", 5000)))

application = app

