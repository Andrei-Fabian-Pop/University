import 'package:flutter/material.dart';
import 'package:nonnative/news_repository.dart';
import 'package:provider/provider.dart';

import 'add_page.dart';
import 'news_entity.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return ChangeNotifierProvider(
      create: (context) => NewsRepository(),
      child: MaterialApp(
        title: 'News App',
        theme: ThemeData(
          colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
          useMaterial3: true,
        ),
        home: const MyHomePage(title: 'News App'),
      ),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({super.key, required this.title});

  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  void _openAddPage() {
    Navigator.push(
      context,
      MaterialPageRoute(
        builder: (context) => AddPage(repository: Provider.of<NewsRepository>(context, listen: false)),
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    NewsItem newsEntity = NewsItem(
      title: 'Sample Title',
      content:
      'Sample Contenta jknad dnlad  adkn adbnjlkda kadbn adjl dajk adn jadcn kmadcn lkadcnk ad nkmad km',
      date: DateTime.now(),
      source: 'Sample Source',
      category: 'Sample Category',
      image: 'Sample Image',
    );
    Provider.of<NewsRepository>(context, listen: false).addNews(newsEntity);
    NewsItem newsEntity2 = NewsItem(
      title: 'Sample Title 2',
      content:
      'Sample Contenta jknad dnlad  adkn adbnjlkda kadbn adjl dajk adn jadcn kmadcn lkadcnk ad nkmad km',
      date: DateTime.now(),
      source: 'Sample Source 2',
      category: 'Sample Category',
      image: 'Sample Image',
    );
    Provider.of<NewsRepository>(context, listen: false).addNews(newsEntity2);
    NewsItem newsEntity3 = NewsItem(
      title: 'Sample Title 3',
      content:
      'Sample Contenta jknad dnlad  adkn adbnjlkda kadbn adjl dajk adn jadcn kmadcn lkadcnk ad nkmad km',
      date: DateTime.now(),
      source: 'Sample Source',
      category: 'Sample Category',
      image: 'Sample Image',
    );
    Provider.of<NewsRepository>(context, listen: false).addNews(newsEntity3);

    return Scaffold(
      appBar: AppBar(
        backgroundColor: Theme.of(context).colorScheme.inversePrimary,
        title: Text(widget.title),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Expanded(child:
                Consumer<NewsRepository>(builder: (context, repository, child) {
              return ListView.builder(
                itemCount: repository.getLength(),
                itemBuilder: (context, index) {
                  return repository.getNews(index);
                },
              );
            })),
          ],
        ),
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: _openAddPage,
        tooltip: 'Increment',
        child: const Icon(Icons.plus_one),
      ),
    );
  }
}
