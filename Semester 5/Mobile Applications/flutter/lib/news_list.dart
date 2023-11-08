import 'package:flutter/material.dart';
import 'news_entity.dart';
import 'news_widget.dart';

class NewsList extends StatefulWidget {
  const NewsList({super.key});

  @override
  NewsListState createState() => NewsListState();
}

class NewsListState extends State<NewsList> {
  List<NewsItem> newsItems = [];

  @override
  Widget build(BuildContext context) {
    return ListView.builder(
      itemCount: newsItems.length,
      itemBuilder: (context, index) {
        final newsItem = newsItems[index];
        return NewsCard(entity: newsItem);
      },
    );
  }

  void addNewsItem(NewsItem newsItem) {
    setState(() {
      newsItems.add(newsItem);
    });
  }

  void deleteNewsItem(NewsItem newsItem) {
    setState(() {
      newsItems.remove(newsItem);
    });
  }

  void updateNewsItem(NewsItem newsItem) {
    // Implement the update logic here
    setState(() {
      // Update the news item
    });
  }
}
