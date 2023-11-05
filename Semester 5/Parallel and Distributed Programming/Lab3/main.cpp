#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "ThreadPool.h"

#define MATRIX_SIZE 100
#define THREAD_COUNT 4

const std::vector<std::vector<int>> matrixA(MATRIX_SIZE, std::vector<int>(MATRIX_SIZE, 9));
const std::vector<std::vector<int>> matrixB(MATRIX_SIZE, std::vector<int>(MATRIX_SIZE, 5));
std::vector<std::vector<int>> result(MATRIX_SIZE, std::vector<int>(MATRIX_SIZE, 0));

int compute_item(int x, int y) {
	int res = 0;
	for (int i = 0; i < MATRIX_SIZE; ++i) {
		res += matrixA[i][x] * matrixB[y][i];
	}
	return res;
}

void strategy1(int id) {
	for (int i = id; i < MATRIX_SIZE; i += THREAD_COUNT) {
		for (int j = 0; j < MATRIX_SIZE; ++j) {
			result[i][j] = compute_item(i, j);
		}
	}
}

void strategy2(int id) {
	for (int i = id; i < MATRIX_SIZE; i += THREAD_COUNT) {
		for (int j = 0; j < MATRIX_SIZE; ++j) {
			result[j][i] = compute_item(j, i);
		}
	}
}

void strategy3(int id) {
	int row = 0;
	int col = id;
	while (true) {
		if (col >= MATRIX_SIZE) {
			col -= MATRIX_SIZE;
			row++;
		}
		if (row >= 9) {
			break;
		}
		result[row][col] = compute_item(row, col);
		col += THREAD_COUNT;
	}
}

void task_per_thread_solution(const std::function<void(int)>& function) {
	std::vector<std::thread> threads(THREAD_COUNT);

	for (int i = 0; i < THREAD_COUNT; ++i) {
		threads[i] = std::thread(function, i);
	}

	for (int i = 0; i < THREAD_COUNT; ++i) {
		threads[i].join();
	}
}

void thread_pool_solution(const std::function<void(int)>& function) {
	ThreadPool pool(THREAD_COUNT);

	for (int i = 0; i < THREAD_COUNT; ++i) {
		pool.addTask(function, i);
	}

	pool.wait();  // Wait for all tasks to complete
}

int main() {
	auto start = std::chrono::high_resolution_clock::now();
	task_per_thread_solution(strategy1);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Time taken by strategy1-task: " << duration.count() << " microseconds" << std::endl;

	start = std::chrono::high_resolution_clock::now();
	task_per_thread_solution(strategy2);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Time taken by strategy2-task: " << duration.count() << " microseconds" << std::endl;

	start = std::chrono::high_resolution_clock::now();
	task_per_thread_solution(strategy3);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Time taken by strategy3-task: " << duration.count() << " microseconds" << std::endl;



	start = std::chrono::high_resolution_clock::now();
	thread_pool_solution(strategy1);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Time taken by strategy1-threadpool: " << duration.count() << " microseconds" << std::endl;

	start = std::chrono::high_resolution_clock::now();
	thread_pool_solution(strategy2);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Time taken by strategy2-threadpool: " << duration.count() << " microseconds" << std::endl;

	start = std::chrono::high_resolution_clock::now();
	thread_pool_solution(strategy3);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Time taken by strategy3-threadpool: " << duration.count() << " microseconds" << std::endl;

//	for (int i = 0; i < MATRIX_SIZE; ++i) {
//		for (int j = 0; j < MATRIX_SIZE; ++j) {
//			std::cout << result[i][j] << " ";
//		}
//		std::cout << "\n";
//	}

	return 0;
}

/*
100x100 - 4 threads
Time taken by strategy1-task: 4597 microseconds
Time taken by strategy2-task: 4487 microseconds
Time taken by strategy3-task: 491 microseconds
Time taken by strategy1-threadpool: 5259 microseconds
Time taken by strategy2-threadpool: 4789 microseconds
Time taken by strategy3-threadpool: 891 microseconds

1000x1000 - 4 threads
Time taken by strategy1-task: 3862520 microseconds
Time taken by strategy2-task: 5231766 microseconds
Time taken by strategy3-task: 29396 microseconds
Time taken by strategy1-threadpool: 3741259 microseconds
Time taken by strategy2-threadpool: 3894145 microseconds
Time taken by strategy3-threadpool: 31606 microseconds

1000x1000 - 16 threads
Time taken by strategy1-task: 3917425 microseconds
Time taken by strategy2-task: 3910910 microseconds
Time taken by strategy3-task: 35069 microseconds
Time taken by strategy1-threadpool: 3932884 microseconds
Time taken by strategy2-threadpool: 4073078 microseconds
Time taken by strategy3-threadpool: 35132 microseconds
*/
