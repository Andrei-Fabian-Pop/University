class NewsItem {
  final int id;
  final String title;
  final String content;
  final DateTime date;
  final String source;
  final String category;
  final String image;
  final DateTime timestamp;

  NewsItem({
    this.id = -1,
    required this.title,
    required this.content,
    required this.date,
    required this.source,
    required this.category,
    required this.timestamp,
    this.image = "No Image"
  });

  Map<String, dynamic> toDynamicMap() {
    return {
      'id': id,
      'title': title,
      'content': content,
      'date': date.toIso8601String(),
      'source': source,
      'category': category,
      'image': image,
      'timestamp': timestamp.toIso8601String(),
    };
  }
}
