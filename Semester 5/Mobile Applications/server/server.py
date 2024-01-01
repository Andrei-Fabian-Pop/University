from datetime import datetime

from flask import Flask, request, jsonify
import sqlite3
import threading

app = Flask(__name__)
db_lock = threading.Lock()

# SQLite database initialization
conn = sqlite3.connect('/home/andrew/android_development/nonnative/python_server/example.db', check_same_thread=False)
cursor = conn.cursor()
cursor.execute('''
    CREATE TABLE IF NOT EXISTS news (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT,
            content TEXT,
            date DATETIME,
            source TEXT,
            category TEXT,
            image TEXT,
            timestamp DATETIME
          );
''')
conn.commit()


# Function to log requests
def log_request(action, data):
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    log_entry = f"{timestamp} - {action}: {data}\n"
    with open('log.txt', 'a') as log_file:
        log_file.write(log_entry)


# Routes
@app.route('/items', methods=['GET'])
def get_items():
    log_request('GET', '/items')
    cursor.execute('PRAGMA table_info(news)')  # Get column names
    column_names = [col[1] for col in cursor.fetchall()]

    db_lock.acquire(True)
    cursor.execute('SELECT * FROM news')
    items = cursor.fetchall()
    db_lock.release()

    # Map items to dictionaries with column names
    mapped_items = [dict(zip(column_names, item)) for item in items]

    return jsonify(mapped_items)


@app.route('/items/add', methods=['POST'])
def add_item():
    data = request.get_json()
    log_request('POST', f'/items/add - {data}')
    data_id = data['id']
    title = data['title']
    content = data['content']
    date = data['date']
    source = data['source']
    category = data['category']
    image = data["image"]
    timestamp = data["timestamp"]

    db_lock.acquire(True)
    if data_id == '-1':
        print("add -1")
        cursor.execute('INSERT INTO news (title, content, date, source, category, image, timestamp) VALUES (?, ?, ?, ?, ?, ?, ?)', (title, content, date, source, category, image, timestamp))
    else:
        print("Adding data with id", data_id)
        cursor.execute('INSERT INTO news (id, title, content, date, source, category, image, timestamp) VALUES (?, ?, ?, ?, ?, ?, ?, ?)', (data_id, title, content, date, source, category, image, timestamp))

    conn.commit()
    db_lock.release()

    return 'Item added successfully'


@app.route('/items/update', methods=['POST'])
def update_item():
    data = request.get_json()
    log_request('POST', f'/items/update - {data}')
    id = data['id']
    title = data['title']
    content = data['content']
    date = data['date']
    source = data['source']
    category = data['category']
    image = data["image"]

    db_lock.acquire(True)
    cursor.execute('UPDATE news '
                   'SET title=?, content=?, date=?, '
                   'source=?, category=?, image=? WHERE id=?',
                   (title, content, date, source, category, image, id))
    conn.commit()
    db_lock.release()

    return 'Item added successfully'


@app.route('/items/delete', methods=['POST'])
def delete_item():
    data = request.get_json()
    log_request('POST', f'/items/delete - {data}')
    id = data['id']

    db_lock.acquire(True)
    cursor.execute('DELETE FROM news WHERE id=?', (id,))
    conn.commit()
    db_lock.release()

    return 'Item added successfully'


if __name__ == '__main__':
    app.run(debug=True, port=8080)

