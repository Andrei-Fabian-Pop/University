import 'package:flutter/material.dart';
import 'package:nonnative/news_entity.dart';
import 'package:nonnative/news_repository.dart';
import 'package:provider/provider.dart';

class AddPage extends StatefulWidget {
  const AddPage({super.key, required this.repository});

  final NewsRepository repository;

  @override
  AddPageState createState() => AddPageState();
}

class AddPageState extends State<AddPage> {
  final TextEditingController titleController = TextEditingController();
  final TextEditingController contentController = TextEditingController();
  final TextEditingController dateController = TextEditingController();
  final TextEditingController sourceController = TextEditingController();
  final TextEditingController categoryController = TextEditingController();
  final TextEditingController imageController = TextEditingController();

  void _saveToRepository() {
    NewsItem newsItem = NewsItem(
      title: titleController.text,
      content: contentController.text,
      date: DateTime.parse(dateController.text),
      source: sourceController.text,
      category: categoryController.text,
      image: imageController.text,
    );
    Provider.of<NewsRepository>(context, listen: false).addNews(newsItem);

    // widget.repository.addNews(newItem);

    // You can also navigate back to the main page or perform any other actions as needed.
    Navigator.pop(context);
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Add Page'),
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
              onPressed: _saveToRepository,
              child: const Text('Save'),
            ),
          ],
        ),
      ),
    );
  }
}
