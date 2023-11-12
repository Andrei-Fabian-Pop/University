class NewsItem {
  final String title;
  final String content;
  final DateTime date;
  final String source;
  final String category;
  final String image;

  NewsItem({
    required this.title,
    required this.content,
    required this.date,
    required this.source,
    required this.category,
    this.image = "No Image"
  });
}
