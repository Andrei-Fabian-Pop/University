import 'package:flutter/material.dart';
import 'package:nonnative/news_entity.dart';
import 'package:nonnative/update_page.dart';
import 'package:provider/provider.dart';

import 'news_repository.dart';

class NewsCard extends StatefulWidget {
  final NewsItem entity;

  const NewsCard({super.key, required this.entity});

  @override
  NewsCardState createState() => NewsCardState();
}

class NewsCardState extends State<NewsCard> {
  bool isExpanded = false;

  void _openUpdatePage() {
    Navigator.push(
      context,
      MaterialPageRoute(
        builder: (context) => UpdatePage(repository: Provider.of<NewsRepository>(context, listen: false), newsCard: widget),
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Card(
      elevation: 3,
      margin: const EdgeInsets.all(10),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: <Widget>[
          Row(
            children: [
              Expanded(
                child: ListTile(
                  title: Text(
                    widget.entity.title,
                    style: const TextStyle(
                      fontWeight: FontWeight.bold,
                      fontSize: 18,
                    ),
                  ),
                  subtitle: Text(
                    "Date: ${widget.entity.date.toLocal()}",
                    style: const TextStyle(
                      fontSize: 14,
                    ),
                  ),
                ),
              ),
              ElevatedButton(
                onPressed: () {
                  setState(() {
                    isExpanded = !isExpanded;
                  });
                },
                child: Text(isExpanded ? "Collapse" : "Expand"),
              ),
            ],
          ),
          if (isExpanded)
            Padding(
              padding: const EdgeInsets.all(10),
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  Text(
                    widget.entity.content,
                    style: const TextStyle(fontSize: 16),
                  ),
                  ListTile(
                    leading: const Icon(Icons.source),
                    title: Text("Source: ${widget.entity.source}"),
                  ),
                  ListTile(
                    leading: const Icon(Icons.category),
                    title: Text("Category: ${widget.entity.category}"),
                  ),
                  ListTile(
                    leading: const Icon(Icons.image),
                    title: Text("Image: ${widget.entity.image}"),
                  ),
                  Row(
                    mainAxisAlignment: MainAxisAlignment.spaceBetween,
                    children: [
                      ElevatedButton(
                        onPressed: () {
                          _openUpdatePage();
                        },
                        child: const Text("Update"),
                      ),
                      ElevatedButton(
                        onPressed: () {
                          Provider.of<NewsRepository>(context, listen: false).deleteNewsByInstance(widget);
                        },
                        style: ElevatedButton.styleFrom(
                          backgroundColor: Colors.red,
                        ),
                        child: const Text("Delete"),
                      ),
                    ],
                  ),
                ],
              ),
            ),
        ],
      ),
    );
  }
}
