import 'package:flutter/foundation.dart';
import 'package:nonnative/news_widget.dart';
import 'news_entity.dart';

class NewsRepository with ChangeNotifier {
  final List<NewsCard> _items = [];

  List<NewsCard> get items => _items;

  void addNews(NewsItem item) {
    NewsCard newsCard = NewsCard(entity: item);
    _items.add(newsCard);
    notifyListeners(); // Notify listeners when the data changes
  }

  void deleteNews(int index) {
    _items.removeAt(index);
    notifyListeners();
  }

  void updateNews(int index, NewsItem item) {
    // Implement the update logic here
    NewsCard newsCard = NewsCard(entity: item);
    _items.elementAt(index);
    _items.insert(index, newsCard);
    notifyListeners();
  }

  NewsCard getNews(int index) {
    return _items.elementAt(index);
  }

  List<NewsCard> getAllNews() {
    return _items;
  }

  int getLength() {
    return _items.length;
  }
}
