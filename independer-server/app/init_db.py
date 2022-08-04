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

# Execute a command: this creates a new table
# cur.execute('DROP TABLE IF EXISTS messages;')
cur.execute('CREATE TABLE  IF NOT EXISTS messages (id serial PRIMARY KEY,'
            'receiver varchar (5) NOT NULL,'
            'author varchar (5) NOT NULL,'
            'msg text,'
            'active boolean,'
            'date_added date DEFAULT CURRENT_TIMESTAMP);'
            )

# Insert data into the table

# cur.execute('INSERT INTO messages (receiver, author, msg, active)'
#             'VALUES (%s, %s, %s, %s)',
#             ('0xM2',
#              '0xMB',
#              'Hello world!',
#              True)
#             )

# cur.execute('INSERT INTO messages (receiver, author, msg, active)'
#             'VALUES (%s, %s, %s, %s)',
#             ('0xM2',
#              '0xMB',
#              'Hello world 2!',
#              False)
#             )

# cur.execute('INSERT INTO messages (receiver, author, msg, active)'
#             'VALUES (%s, %s, %s, %s)',
#             ('0xMB',
#              '0xM2',
#              'Hello world 3!',
#              True)
#             )

conn.commit()

cur.close()
conn.close()

print("Finished Init DB")
