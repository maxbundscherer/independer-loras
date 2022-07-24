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


@app.route('/')
def index():
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute('SELECT * FROM messages WHERE active is true;')
    messages = cur.fetchall()
    cur.close()
    conn.close()

    retDict = {}

    for i, messageWrapper in enumerate(messages):
        e = {"receiver": messageWrapper[1],
             "author": messageWrapper[2], "msg": messageWrapper[3]}
        retDict[i] = e

    return retDict


@app.route('/msg', methods=['POST'])
def process_json():
    content_type = request.headers.get('Content-Type')
    if (content_type == 'application/json'):
        json = request.json

        print(json["receiver"])
        print(json["author"])
        print(json["msg"])

        return "OK"
    else:
        return 'Content-Type not supported!'
