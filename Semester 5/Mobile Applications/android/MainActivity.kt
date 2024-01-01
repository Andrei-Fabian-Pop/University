package com.example.newsapp

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.material3.ElevatedButton
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import com.example.newsapp.ui.theme.NewsAppTheme
import androidx.compose.ui.unit.dp
import androidx.compose.foundation.lazy.items
import androidx.compose.material3.Button
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.ui.text.style.TextAlign
import androidx.navigation.NavController
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider


enum class Pages {
    MainPage,
    AddPage,
    UpdatePage
}

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val viewModel = ViewModelProvider(this)[MainViewModel::class.java]
        for (index in 1..10) {
            viewModel.addItem(
                NewsItem(
                    "Title $index",
                    "fvgbhdsajk dsbjkadb sjkasdbj,kasbhdas dasjkdnbsjdkjasnkda",
                    "10.10.2023",
                    "www.yess.com",
                    "Sports",
                    ""
                )
            )
        }

        setContent {
            NewsAppTheme {
                MyApp(viewModel)
            }
        }
    }
}


class MainViewModel : ViewModel() {
    private val itemRepository = NewsRepository()

    fun getItems() = itemRepository.getItems()

    fun addItem(item: NewsItem) {
        itemRepository.addItem(item)
    }

    fun updateItem(item: NewsItem, newItem: NewsItem) {
        itemRepository.updateItem(item = item, newItem = newItem)
    }

    fun deleteItem(item: NewsItem) {
        itemRepository.deleteItem(item);
    }
}


@Composable
fun MyApp(
    viewModel: MainViewModel
) {
    val navController = rememberNavController()
    val newsList: MainViewModel = viewModel
    val currentIndex: Int by remember { mutableIntStateOf(-1) }

    NavHost(
        navController = navController,
        startDestination = Pages.MainPage.name
    ) {
        composable(route = Pages.MainPage.name) {
            MainPage(navController = navController, viewModel = newsList)
        }
        composable(route = Pages.AddPage.name) {
            AddPage(navController = navController, viewModel = newsList)
        }
        composable(route = Pages.UpdatePage.name) {
            UpdatePage(navController = navController, viewModel = newsList, index = currentIndex)
        }
    }
}

@Composable
fun MainPage(
    modifier: Modifier = Modifier,
    navController: NavController,
    viewModel: MainViewModel
) {
    Column(modifier = Modifier.fillMaxWidth()) {
        Button(modifier = Modifier
            .fillMaxWidth()
            .padding(vertical = 4.dp, horizontal = 8.dp),
            onClick = { navController.navigate(Pages.AddPage.name) })
        {
            Text(text = "Add new Entry")
        }
        LazyColumn(modifier = modifier.padding(vertical = 4.dp)) {
            items(items = viewModel.getItems()) { currentNewsItem ->
                NewsBar(
                    item = currentNewsItem,
                    viewModel = viewModel,
                    navController = navController
                )
            }
        }
    }
}

@Composable
fun NewsBar(
    item: NewsItem,
    modifier: Modifier = Modifier,
    viewModel: MainViewModel,
    navController: NavController,
) {
    val expanded = remember { mutableStateOf(false) }
    val height = if (expanded.value) 300.dp else 0.dp

    Surface(
        color = MaterialTheme.colorScheme.primary,
        modifier = modifier.padding(vertical = 4.dp, horizontal = 8.dp)
    ) {
        Column(modifier = modifier) {
            Row(modifier = modifier.padding(24.dp)) {
                Column(
                    modifier = modifier
                        .weight(1f)
                ) {
                    Text(text = "Hello, ")
                    Text(text = item.title)
                }
                ElevatedButton(onClick = { expanded.value = !expanded.value }) {
                    Text(text = if (expanded.value) "Show less" else "Show more")
                }
            }
            Surface(
                modifier = modifier
                    .height(height)
                    .fillMaxWidth(), color = MaterialTheme.colorScheme.primary
            ) {
                Column(modifier = modifier) {
                    Text(text = "Posted " + item.date, textAlign = TextAlign.Right)
                    Text(text = "Category " + item.category, textAlign = TextAlign.Right)
                    Spacer(modifier = modifier.height(8.dp))
                    Text(text = item.content, textAlign = TextAlign.Center)
                    Spacer(modifier = modifier.height(8.dp))
                    Text(text = "Source: " + item.source, textAlign = TextAlign.Left)
                    ElevatedButton(onClick = { navController.navigate(Pages.UpdatePage.name) }) {
                        Text(text = "Update")
                    }
                    ElevatedButton(onClick = { viewModel.deleteItem(item) }) {
                        Text(text = "Delete")
                    }
                }
            }
        }
    }
}

@Preview(showBackground = true, widthDp = 320)
@Composable
fun NewsPreview() {
    NewsAppTheme {
        val viewModel = MainViewModel()
        for (index in 1..3) {
            viewModel.addItem(NewsItem("Title $index", "", "", "", "", ""))
        }
        MainPage(navController = rememberNavController(), viewModel = viewModel)
    }
}
