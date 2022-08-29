echo "[Init DB]"
python init_db.py

echo
echo "[Start App]"
#python app.py
uwsgi --ini uwsgi.ini
