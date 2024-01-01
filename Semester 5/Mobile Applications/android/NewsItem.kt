package com.example.newsapp

data class NewsItem(
    var title: String = "",
    var content: String = "",
    var date: String = "",
    var source: String = "",
    var category: String = "",
    var image: String? = ""
)
