import 'dart:convert';
import 'dart:io';
import 'package:http/http.dart' as http;

class ServerCommunication {
  final String serverUrl = 'http://127.0.0.1:8080';

  // ServerCommunication(this.serverUrl);

  Future<bool> checkServerConnection() async {
    try {
      final response = await http.get(Uri.parse('$serverUrl/items'));
      return response.statusCode == 200;
    } catch (e) {
      print('Error checking server connection: $e');
      return false;
    }
  }

  Future<List<Map<String, dynamic>>> fetchDataFromServer() async {
    try {
      final response = await http.get(Uri.parse('$serverUrl/items'));
      if (response.statusCode == 200) {
        final dynamic jsonData = json.decode(response.body);
        if (jsonData is List) {
          return List<Map<String, dynamic>>.from(jsonData);
        } else {
          print('Unexpected data format from server');
          return [];
        }
      } else {
        print(
            'Failed to fetch data from server. Status code: ${response.statusCode}');
        return [];
      }
    } catch (e) {
      print('Error fetching data from server: $e');
      return [];
    }
  }

  Future<void> sendDataToServer(Map<String, dynamic> data) async {
    try {
      final response = await http.post(
        Uri.parse('$serverUrl/items/add'),
        headers: {'Content-Type': 'application/json'},
        body: json.encode(data),
      );

      if (response.statusCode != 200) {
        print(
            'Failed to send data to server. Status code: ${response.statusCode}');
      }
    } catch (e) {
      print('Error sending data to server: $e');
    }
  }

  Future<void> updateDataOnServer(int id, Map<String, dynamic> newData) async {
    try {
      final response = await http.post(
        Uri.parse('$serverUrl/items/update'),
        headers: {'Content-Type': 'application/json'},
        body: json.encode({'id': id, ...newData}),
      );

      if (response.statusCode != 200) {
        print(
            'Failed to update data on server. Status code: ${response.statusCode}');
      }
    } catch (e) {
      print('Error updating data on server: $e');
    }
  }

  Future<void> deleteDataOnServer(int id) async {
    try {
      final response = await http.post(
        Uri.parse('$serverUrl/items/delete'),
        headers: {'Content-Type': 'application/json'},
        body: json.encode({'id': id}),
      );

      if (response.statusCode != 200) {
        print(
            'Failed to delete data on server. Status code: ${response.statusCode}');
      }
    } catch (e) {
      print('Error deleting data on server: $e');
    }
  }
}
