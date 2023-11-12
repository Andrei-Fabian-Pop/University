import 'package:flutter/material.dart';
import 'package:nonnative/news_entity.dart';
import 'package:nonnative/news_repository.dart';
import 'package:nonnative/news_widget.dart';
import 'package:provider/provider.dart';

class UpdatePage extends StatefulWidget {
  const UpdatePage({super.key, required this.repository, required this.newsCard});

  final NewsRepository repository;
  final NewsCard newsCard;

  @override
  UpdatePageState createState() => UpdatePageState();
}

class UpdatePageState extends State<UpdatePage> {
  late TextEditingController titleController;
  late TextEditingController contentController;
  late TextEditingController dateController;
  late TextEditingController sourceController;
  late TextEditingController categoryController;
  late TextEditingController imageController;

  @override
  void initState() {
    super.initState();

    // Initialize controllers with existing data
    titleController = TextEditingController(text: widget.newsCard.entity.title);
    contentController = TextEditingController(text: widget.newsCard.entity.content);
    dateController =
        TextEditingController(text: widget.newsCard.entity.date.toIso8601String());
    sourceController = TextEditingController(text: widget.newsCard.entity.source);
    categoryController = TextEditingController(text: widget.newsCard.entity.category);
    imageController = TextEditingController(text: widget.newsCard.entity.image);
  }

  void _updateInRepository() {
    NewsItem updatedItem = NewsItem(
      title: titleController.text,
      content: contentController.text,
      date: DateTime.parse(dateController.text),
      source: sourceController.text,
      category: categoryController.text,
      image: imageController.text,
    );

    // Remove the old item and add the updated one
    Provider.of<NewsRepository>(context, listen: false).updateNews(widget.newsCard, updatedItem);
    // widget.repository.updateNews(widget.newsCard, updatedItem);
    // widget.repository.removeNews(widget.newsItem);
    // widget.repository.addNews(updatedItem);

    // You can also navigate back to the main page or perform any other actions as needed.
    Navigator.pop(context);
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Update Page'),
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            TextField(
              controller: titleController,
              decoration: const InputDecoration(labelText: 'Title'),
            ),
            TextField(
              controller: contentController,
              decoration: const InputDecoration(labelText: 'Content'),
            ),
            TextField(
              controller: dateController,
              decoration: const InputDecoration(labelText: 'Date (YYYY-MM-DD)'),
            ),
            TextField(
              controller: sourceController,
              decoration: const InputDecoration(labelText: 'Source'),
            ),
            TextField(
              controller: categoryController,
              decoration: const InputDecoration(labelText: 'Category'),
            ),
            TextField(
              controller: imageController,
              decoration: const InputDecoration(labelText: 'Image (Optional)'),
            ),
            const SizedBox(height: 16),
            ElevatedButton(
              onPressed: _updateInRepository,
              child: const Text('Update'),
            ),
          ],
        ),
      ),
    );
  }
}
