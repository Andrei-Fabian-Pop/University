package com.example.newsapp

import android.annotation.SuppressLint
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.heightIn
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.text.BasicTextField
import androidx.compose.material3.Button
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.navigation.NavController
import androidx.navigation.compose.rememberNavController
import com.example.newsapp.ui.theme.NewsAppTheme
import java.text.SimpleDateFormat
import java.util.Date

@SuppressLint("SimpleDateFormat")
@Composable
fun AddPage(
    navController: NavController,
    viewModel: MainViewModel
) {
//    val newNewsItem: NewsItem by remember { mutableStateOf(NewsItem()) }
    var title: String by remember { mutableStateOf("") }
    var content: String by remember { mutableStateOf("") }
    var source: String by remember { mutableStateOf("") }
    var category: String by remember { mutableStateOf("") }

    Column(
        modifier = Modifier.fillMaxSize(),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(text = "Title: ")
        BasicTextField(
            value = title,
            onValueChange = { title = it },
            modifier = Modifier
                .padding(16.dp)
                .fillMaxWidth()
                .background(
                    color = Color.LightGray,
                    shape = RoundedCornerShape(8.dp)
                )
                .padding(16.dp)
                .heightIn(min = 28.dp),
            textStyle = TextStyle(color = Color.Black)
        )

        Text(text = "Content:")
        BasicTextField(
            value = content,
            onValueChange = { newText ->
                content = newText
            },
            modifier = Modifier
                .padding(16.dp)
                .fillMaxWidth()
                .background(
                    color = Color.LightGray,
                    shape = RoundedCornerShape(8.dp)
                )
                .padding(16.dp)
                .heightIn(min = 48.dp),
            textStyle = TextStyle(color = Color.Black)
        )

        Text(text = "Source:")
        BasicTextField(
            value = source,
            onValueChange = { newText ->
                source = newText
            },
            modifier = Modifier
                .padding(16.dp)
                .fillMaxWidth()
                .background(
                    color = Color.LightGray,
                    shape = RoundedCornerShape(8.dp)
                )
                .padding(16.dp)
                .heightIn(min = 28.dp),
            textStyle = TextStyle(color = Color.Black)
        )

        Text(text = "Category:")
        BasicTextField(
            value = category,
            onValueChange = { newText ->
                category = newText
            },
            modifier = Modifier
                .padding(16.dp)
                .fillMaxWidth()
                .background(
                    color = Color.LightGray,
                    shape = RoundedCornerShape(8.dp)
                )
                .padding(16.dp)
                .heightIn(min = 28.dp),
            textStyle = TextStyle(color = Color.Black)
        )

        Spacer(modifier = Modifier.height(166.dp))

        Button(
            onClick = {
                val newNewsItem = NewsItem(
                    title = title,
                    content = content,
                    source = source,
                    category = category
                )
                val formatter = SimpleDateFormat("yyyy-MM-dd")
                val date = Date()
                val current = formatter.format(date)
                newNewsItem.date = current
                viewModel.addItem(newNewsItem)
                navController.navigate(Pages.MainPage.name)
            }
        ) {
            Text("Add")
        }

        Button(
            onClick = {
                navController.navigate(Pages.MainPage.name)
            }
        ) {
            Text("Back")
        }
    }
}

@Preview(showBackground = true)
@Composable
fun InputPagePreview() {
    NewsAppTheme {
        AddPage(navController = rememberNavController(), viewModel = MainViewModel())
    }
}
