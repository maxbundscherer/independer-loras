import config as conf

import psycopg2

print("Started Init DB")

conn = psycopg2.connect(
    host=conf.getDbConfigHost(),
    database=conf.getDbConfigDatabase(),
    user=conf.getDbConfigUser(),
    password=conf.getDbConfigPassword(),
    port=conf.getDbConfigPort())

# Open a cursor to perform database operations
cur = conn.cursor()

cur.execute('CREATE TABLE  IF NOT EXISTS users (id serial PRIMARY KEY,'
            'appid varchar (5) NOT NULL UNIQUE,'
            'secret varchar (50) NOT NULL,'
            'active boolean NOT NULL,'
            'date_added timestamp DEFAULT CURRENT_TIMESTAMP NOT NULL);'
            )
conn.commit()

cur.execute('CREATE TABLE  IF NOT EXISTS messages (id serial PRIMARY KEY,'
            'receiver varchar (5) NOT NULL references users(appid),'
            'author varchar (5) NOT NULL references users(appid),'
            'msg text NOT NULL,'
            'active boolean NOT NULL,'
            'date_added timestamp DEFAULT CURRENT_TIMESTAMP NOT NULL);'
            )
conn.commit()

cur.execute('CREATE TABLE  IF NOT EXISTS actors (id serial PRIMARY KEY,'
            'appid varchar (5) NOT NULL references users(appid),'
            'token varchar (50) NOT NULL UNIQUE,'
            'version varchar (50) NOT NULL,'
            'active boolean NOT NULL,'
            'date_added timestamp DEFAULT CURRENT_TIMESTAMP NOT NULL);'
            )
conn.commit()

cur.execute('CREATE TABLE  IF NOT EXISTS gateways (id serial PRIMARY KEY,'
            'appid varchar (5) NOT NULL references users(appid),'
            'gatewayid varchar (5) NOT NULL,'
            'active boolean NOT NULL,'
            'date_added timestamp DEFAULT CURRENT_TIMESTAMP NOT NULL);'
            )
conn.commit()

cur.execute('CREATE TABLE  IF NOT EXISTS history (id serial PRIMARY KEY,'
            'appid varchar (5) NOT NULL references users(appid),'
            'token varchar (50) NOT NULL references actors(token),'
            'url varchar (50) NOT NULL,'
            'date_added timestamp DEFAULT CURRENT_TIMESTAMP NOT NULL);'
            )
conn.commit()

cur.execute('CREATE TABLE  IF NOT EXISTS autosync (id serial PRIMARY KEY,'
            'appid varchar (5) NOT NULL references users(appid),'
            'token varchar (50) NOT NULL references actors(token),'
            'tx_version varchar (50) NOT NULL,'
            'tx_time_before_sync bigint NOT NULL,'
            'tx_time_after_sync bigint NOT NULL,'
            'tx_battery integer NOT NULL,'
            'tx_dev_mode boolean NOT NULL,'
            'tx_is_actor boolean NOT NULL,'
            'date_added timestamp DEFAULT CURRENT_TIMESTAMP NOT NULL);'
            )
conn.commit()

cur.execute('CREATE TABLE  IF NOT EXISTS systemdata (id serial PRIMARY KEY,'
            'key varchar (10) NOT NULL UNIQUE,'
            'value varchar (500) NOT NULL'
            )
conn.commit()

cur.execute('INSERT INTO systemdata (key, value)'
            'VALUES (%s, %s)',
            ('act_version',
             'v.0.0.1')
            )
conn.commit()

cur.execute('INSERT INTO systemdata (key, value)'
            'VALUES (%s, %s)',
            ('status_msg',
             '')
            )
conn.commit()

cur.close()
conn.close()

print("Finished Init DB")
