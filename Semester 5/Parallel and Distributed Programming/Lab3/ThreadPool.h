#ifndef LAB3_THREADPOOL_H
#define LAB3_THREADPOOL_H

#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

class ThreadPool {
public:
	explicit ThreadPool(size_t numThreads);
	~ThreadPool();

	void addTask(const std::function<void(int)>& task, int arg);
	void wait();

private:
	std::vector<std::thread> threads;
	std::queue<std::pair<std::function<void(int)>, int>> tasks;
	std::mutex queueMutex;
	std::condition_variable condition;
	bool stop = false;
	int id = 0;
};



#endif //LAB3_THREADPOOL_H
