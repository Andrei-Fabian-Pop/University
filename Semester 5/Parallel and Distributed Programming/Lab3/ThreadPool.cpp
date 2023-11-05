#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t numThreads)  {
	for (size_t i = 0; i < numThreads; ++i) {
		threads.emplace_back([this]() {
			while (true) {
				std::function<void(int)> task;
				int arg;
				{
					std::unique_lock<std::mutex> lock(queueMutex);
					condition.wait(lock, [this]() {
						return !tasks.empty() || stop;
					});

					if (stop && tasks.empty()) {
						return;
					}

					task = tasks.front().first;
					arg = tasks.front().second;
					tasks.pop();
				}
				task(arg);
			}
		});
	}
}

ThreadPool::~ThreadPool() {
	wait();
}

void ThreadPool::addTask(const std::function<void(int)>& task, int arg) {
	std::unique_lock<std::mutex> lock(queueMutex);
	tasks.emplace(task, arg);
	condition.notify_one();
}

void ThreadPool::wait() {
	{
		std::unique_lock<std::mutex> lock(queueMutex);
		stop = true;
	}
	condition.notify_all();
	for (std::thread& thread : threads) {
		if (thread.joinable()) {
			thread.join();
		}
	}
}
