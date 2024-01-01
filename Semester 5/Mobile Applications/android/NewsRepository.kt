package com.example.newsapp

import androidx.compose.runtime.mutableStateListOf

class NewsRepository {
    private val items = mutableStateListOf<NewsItem>()

    fun getItems(): List<NewsItem> {
        return items
    }

    fun addItem(item: NewsItem) {
        items.add(item)
    }

    fun deleteItem(item: NewsItem) {
        items.remove(item);
    }

    fun updateItem(item: NewsItem, newItem: NewsItem) {
        val index: Int = items.indexOf(item)
        if (index != -1) {
            items[index] = newItem;
        }
    }
}