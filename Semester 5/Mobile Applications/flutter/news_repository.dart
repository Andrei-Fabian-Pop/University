import 'package:nonnative/news_widget.dart';
import 'package:flutter/widgets.dart';
import 'package:nonnative/server_communication.dart';

import 'news_database.dart';
import 'news_entity.dart';

class NewsRepository with ChangeNotifier {
  final List<NewsCard> _items = [];
  final NewsDatabase _newsDatabase = NewsDatabase();
  bool initialUpdateCompleted = false;
  static final ServerCommunication _serverCommunication = ServerCommunication();

  List<NewsCard> get items => _items;

  NewsRepository() {
    initDatabase();
    if (!initialUpdateCompleted) {
      initialUpdateCompleted = true;
      updateDbIfPossible().then((value) => null);
    }
  }

  initDatabase() async {
    var res = await _newsDatabase.getAllItems();
    for (final item in res) {
      int id = int.parse(item["id"].toString());
      String title = item["title"].toString();
      String content = item["content"].toString();
      DateTime date = DateTime.parse(item["date"].toString());
      String source = item["source"].toString();
      String category = item["category"].toString();
      String image = item["image"].toString();
      DateTime timestamp = DateTime.parse(item["timestamp"].toString());

      final NewsItem newsItem = NewsItem(
          id: id,
          title: title,
          content: content,
          date: date,
          source: source,
          category: category,
          image: image,
          timestamp: timestamp);
      NewsCard newsCard = NewsCard(entity: newsItem);
      _items.add(newsCard);
    }
    notifyListeners();
  }

  Map<String, Object?>? _getElementFromLocalDB(
      int id, List<Map<String, Object?>> localDatabase) {
    for (final entity in localDatabase) {
      if (entity['id'] == id) {
        return entity;
      }
    }
    return null; // Return null if the element with the specified ID is not found
  }

  Map<String, dynamic>? _getElementFromServerDB(
      int id, List<Map<String, dynamic>> serverDatabase) {
    for (final entity in serverDatabase) {
      if (entity['id'] == id) {
        return entity;
      }
    }
    return null; // Return null if the element with the specified ID is not found
  }

  Future<void> synchronizeDatabases(List<Map<String, dynamic>> serverDatabase,
      List<Map<String, Object?>> localDatabase) async {
    // go through all elements from the local db and send them to the server if
    // they are not already there.
    for (final localEntry in localDatabase) {
      int id = int.parse(localEntry["id"].toString());
      final serverEntity = _getElementFromServerDB(id, serverDatabase);
      if (serverEntity == null) {
        print("sending local id $id");
        Map<String, dynamic> dynamicMap = localEntry.cast<String, dynamic>();
        _serverCommunication.sendDataToServer(dynamicMap);
      }
    }

    // go through all elements received from the server
    for (final serverEntity in serverDatabase) {
      final id = serverEntity["id"];
      final localEntity = _getElementFromLocalDB(id, localDatabase);
      if (localEntity == null) {
        // if local db does not have this entry, just insert it
        NewsItem item = NewsItem(
            id: id,
            title: serverEntity["title"].toString(),
            content: serverEntity["content"].toString(),
            date: DateTime.parse(serverEntity["date"]),
            source: serverEntity["source"].toString(),
            category: serverEntity["category"].toString(),
            timestamp: DateTime.parse(serverEntity["timestamp"]));
        print("Received object with id $id");
        addNews(item, addToCloud: false);
      } else {
        // if local db has the entry then we might have conflicting entities,
        // update the correct db
        if (DateTime.parse(serverEntity["timestamp"])
            .isAfter(DateTime.parse(localEntity["timestamp"].toString()))) {
          // server object is after local object, update local
          print("Updating local object with id $id");
          final String title = serverEntity["title"].toString();
          final String content = serverEntity["content"].toString();
          final DateTime date = DateTime.parse(serverEntity["date"]);
          final String source = serverEntity["source"].toString();
          final String category = serverEntity["category"].toString();
          final DateTime timestamp = DateTime.parse(serverEntity["timestamp"]);
          NewsItem item = NewsItem(
              title: title,
              content: content,
              date: date,
              source: source,
              category: category,
              timestamp: timestamp);

          updateNewsByIndex(id, item);
        } else if (DateTime.parse(serverEntity["timestamp"])
            .isBefore(DateTime.parse(localEntity["timestamp"].toString()))) {
          // local object is after server object, update server
          print("Updating upstream object with id $id");
          Map<String, dynamic> dynamicMap = localEntity.cast<String, dynamic>();
          _serverCommunication.updateDataOnServer(id, dynamicMap);
        } else {
          print("synchronized $id");
        }
      }
    }
  }

  Future<void> updateDbIfPossible() async {
    bool canConnect = await _serverCommunication.checkServerConnection();
    if (canConnect) {
      var serverData = await _serverCommunication.fetchDataFromServer();
      var localData = await _newsDatabase.getAllItems();
      await synchronizeDatabases(serverData, localData);
    }
  }

  void addNews(NewsItem item, {bool addToCloud = true}) {
    _newsDatabase.insertNews(item);
    NewsCard newsCard = NewsCard(entity: item);
    _items.add(newsCard);
    if (addToCloud) {
      _serverCommunication.sendDataToServer(item.toDynamicMap());
    }
    notifyListeners(); // Notify listeners when the data changes
  }

  void deleteNewsByIndex(int index, {bool addToCloud = true}) {
    NewsCard card = _items.removeAt(index);
    _newsDatabase.deleteNews(card.entity.id);
    if (addToCloud) {
      _serverCommunication.deleteDataOnServer(index);
    }
    notifyListeners();
  }

  void deleteNewsByInstance(NewsCard newsCard, {bool addToCloud = true}) {
    items.remove(newsCard);
    _newsDatabase.deleteNews(newsCard.entity.id);
    if (addToCloud) {
      _serverCommunication.deleteDataOnServer(newsCard.entity.id);
    }
    notifyListeners();
  }

  void updateNews(NewsCard oldCard, NewsItem newItem,
      {bool addToCloud = true}) {
    NewsCard newsCard = NewsCard(entity: newItem);
    _items[_items.indexOf(oldCard)] =
        newsCard; // Update the item at the specified index
    _newsDatabase.updateNews(oldCard.entity.id, newItem);
    if (addToCloud) {
      _serverCommunication.updateDataOnServer(
          oldCard.entity.id, newItem.toDynamicMap());
    }
    notifyListeners();
  }

  void updateNewsByIndex(int id, NewsItem newItem, {bool addToCloud = true}) {
    NewsCard newsCard = NewsCard(entity: newItem);
    _items[_getIndexFromId(id)] =
        newsCard; // Update the item at the specified index
    _newsDatabase.updateNews(id, newItem);
    if (addToCloud) {
      _serverCommunication.updateDataOnServer(id, newItem.toDynamicMap());
    }
    notifyListeners();
  }

  int _getIndexFromId(int id) {
    for (int i = 0; i < _items.length; ++i) {
      if (_items[i].entity.id == id) {
        return i;
      }
    }

    return -1;
  }

  NewsCard getNews(int index) {
    return _items[index];
  }

  List<NewsCard> getAllNews() {
    return _items;
  }

  int getLength() {
    return _items.length;
  }
}
