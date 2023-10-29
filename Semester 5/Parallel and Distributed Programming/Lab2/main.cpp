#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

std::vector<int> vector1;
std::vector<int> vector2;
std::vector<int> result;

std::mutex mutex;
std::condition_variable producer_cv;
std::condition_variable consumer_cv;
bool producer_ready = true;
bool consumer_ready = false;
long long int scalar_product = 0;

void producer() {
	for (int i = 0; i < vector1.size(); ++i) {
		std::unique_lock<std::mutex> lock(mutex);

		producer_cv.wait(lock, []() { return producer_ready; });

		result.push_back(vector1[i] * vector2[i]);

		consumer_ready = true;
		producer_ready = false;
		consumer_cv.notify_one();
		std::cout << "Notify producer\n";
	}
}

void consumer() {
	for (int i = 0; i < vector1.size(); ++i) {
		std::unique_lock<std::mutex> lock(mutex);

		consumer_cv.wait(lock, []() { return consumer_ready; });

		scalar_product += result.back();
		result.pop_back();

		if (result.empty()) {
			consumer_ready = false;
			producer_ready = true;
			producer_cv.notify_one();
			std::cout << "Notify consumer\n";
		}
	}
}

int main() {
	for (int i = 0; i < 100000; ++i) {
		vector1.push_back(i % 10);
		vector2.push_back(10 - i % 10);
	}

	std::thread consumer_thread(consumer);
	std::thread producer_thread(producer);

	consumer_thread.join();
	producer_thread.join();

	std::cout << "Result: " << scalar_product << "\n";

	return 0;
}
