import 'package:flutter/cupertino.dart';
import 'package:path/path.dart';
import 'package:sqflite_common_ffi/sqflite_ffi.dart';
import 'package:path_provider/path_provider.dart';
import 'news_entity.dart';
import 'dart:io';

class NewsDatabase {
  static Database? _database;
  final String _tableName = "news";

  NewsDatabase() {
    initDatabase();
  }

  Future<Database> get database async {
    _database ??= await initDatabase();
    return _database!;
  }

  Future<Database> initDatabase() async {
    WidgetsFlutterBinding.ensureInitialized();
    final Directory appDocumentsDir = await getApplicationDocumentsDirectory();

    // Get the path to the database
    String path =
        join(appDocumentsDir.path, "databases", "news_database.sqlite");
    // print("PATH ==================== $path");

    sqfliteFfiInit();

    var databaseFactory = databaseFactoryFfi;
    var db = await databaseFactory.openDatabase(path);
    await db.execute('''
      CREATE TABLE IF NOT EXISTS news (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT,
            content TEXT,
            date DATETIME,
            source TEXT,
            category TEXT,
            image TEXT
          );
    ''');

    return db;
  }

  Future<List<Map<String, Object?>>> getAllItems() async {
    var db = await database;
    return db.query(_tableName);
  }

  Future<void> insertNews(NewsItem item) async {
    final db = await database;
    db.insert(_tableName, {
      "title": item.title,
      "content": item.content,
      "date": item.date.toString(),
      "source": item.source,
      "category": item.category,
      "image": item.image
    });
  }

  Future<void> deleteNews(int index) async {
    if (index == -1) {
      // TREAT ERROR
    } else {
      final db = await database;
      db.delete(_tableName, where: "id=$index");
    }
  }

  Future<void> updateNews(int index, NewsItem item) async {
    if (index == -1) {
      // TREAT ERROR
    } else {
      final db = await database;
      db.update(_tableName, {
        "title": item.title,
        "content": item.content,
        "date": item.date.toString(),
        "source": item.source,
        "category": item.category,
        "image": item.image
      }, where: "id=$index");
    }
  }
}
