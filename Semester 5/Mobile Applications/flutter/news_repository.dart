import 'package:nonnative/news_widget.dart';
import 'package:flutter/widgets.dart';

import 'news_database.dart';
import 'news_entity.dart';

class NewsRepository with ChangeNotifier {
  final List<NewsCard> _items = [];
  final NewsDatabase _newsDatabase = NewsDatabase();

  List<NewsCard> get items => _items;

  NewsRepository() {
    initDatabase();
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
      final NewsItem newsItem = NewsItem(
          id: id,
          title: title,
          content: content,
          date: date,
          source: source,
          category: category,
          image: image);
      NewsCard newsCard = NewsCard(entity: newsItem);
      _items.add(newsCard);
    }
    notifyListeners();
  }

  void addNews(NewsItem item) {
    _newsDatabase.insertNews(item);
    NewsCard newsCard = NewsCard(entity: item);
    _items.add(newsCard);
    notifyListeners(); // Notify listeners when the data changes
  }

  void deleteNewsByIndex(int index) {
    NewsCard card = _items.removeAt(index);
    _newsDatabase.deleteNews(card.entity.id);
    notifyListeners();
  }

  void deleteNewsByInstance(NewsCard newsCard) {
    items.remove(newsCard);
    _newsDatabase.deleteNews(newsCard.entity.id);
    notifyListeners();
  }

  void updateNews(NewsCard oldCard, NewsItem newItem) {
    NewsCard newsCard = NewsCard(entity: newItem);
    _items[_items.indexOf(oldCard)] =
        newsCard; // Update the item at the specified index
    _newsDatabase.updateNews(oldCard.entity.id, newItem);
    notifyListeners();
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
