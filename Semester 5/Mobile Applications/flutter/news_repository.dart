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

  void deleteNewsByIndex(int index) {
    _items.removeAt(index);
    notifyListeners();
  }

  void deleteNewsByInstance(NewsCard newsCard) {
    items.remove(newsCard);
    notifyListeners();
  }

  void updateNews(NewsCard oldCard, NewsItem newItem) {
    // Implement the update logic here
    NewsCard newsCard = NewsCard(entity: newItem);
    _items[_items.indexOf(oldCard)] = newsCard; // Update the item at the specified index
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
