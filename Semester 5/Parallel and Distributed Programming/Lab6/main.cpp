#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <random>
#include <algorithm>
#include <atomic>

#define VERTICES_COUNT 10000
#define STARTING_NODE 0

using namespace std;

std::vector<std::vector<int>> matrix(VERTICES_COUNT, std::vector<int>());
std::vector<int> nodes(VERTICES_COUNT);
std::vector<int> result(VERTICES_COUNT);
std::vector<int> path;
std::atomic_bool x;
std::mutex mtx;
static std::atomic_int cnt = 0;

void generate_hamiltonian_cycle() {
	for (int i = 0; i < VERTICES_COUNT; ++i) {
		nodes[i] = i;
	}
	std::random_device rd;
	std::default_random_engine rng(rd());
	std::shuffle(nodes.begin(), nodes.end(), rng);

	for (int i = 1; i < nodes.size(); i++) {
		matrix[nodes[i - 1]].push_back(nodes[i]);
	}
	matrix[nodes[nodes.size() - 1]].push_back(nodes[0]);

	for (int i = 0; i < VERTICES_COUNT / 2; i++) {
		int src = rand() % VERTICES_COUNT;
		int dest = rand() % VERTICES_COUNT;

		matrix[src].push_back(dest);
	}
}

void find_cycle(int node) {
	path.push_back(node);

	if (!x.load()) {
		if (path.size() == matrix.size()) {
			auto neighbours = matrix[node];
			if (std::find(neighbours.begin(), neighbours.end(), STARTING_NODE) != neighbours.end()) {
				// found a cycle
				x.store(true);
				std::lock_guard<std::mutex> guard(mtx);
				result.clear();
				result.insert(result.end(), path.begin(), path.end());
			}
			return;
		}

		auto neighbours = matrix[node];

		for (auto neighbour: neighbours) {
			if (std::find(path.begin(), path.end(), neighbour) == path.end()) {
				find_cycle(neighbour);
			}
		}
	}
}

template<typename Func, typename... Args>
void time(Func func, Args&& ... args) {
	auto start_time = std::chrono::high_resolution_clock::now();
	func(args...);
	auto end_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;
}

void print_result() {
	std::cout << "total cycle size: " << result.size() << "\n";
	for (int i: result) { std::cout << i << " "; }
}

void find_cycle_threaded(int node, std::vector<int> current_path = std::vector<int>()) {
	current_path.push_back(node);

	if (!x.load()) {
		auto& neighbours = matrix[node];
		if (current_path.size() == matrix.size()) {

			if (std::find(neighbours.begin(), neighbours.end(), STARTING_NODE) != neighbours.end()) {
				// found a cycle
				x.store(true);
				std::lock_guard<std::mutex> guard(mtx);
				result.clear();
				result.insert(result.end(), current_path.begin(), current_path.end());
			}
			return;
		}

		std::vector<std::thread> threads;

		for (auto neighbour: neighbours) {
			if (std::find(path.begin(), path.end(), neighbour) == path.end()) {
				if ((current_path.size()-1) % 2500 == 0) {
					threads.emplace_back(find_cycle_threaded, neighbour, current_path);
				} else {
					find_cycle_threaded(neighbour, current_path);
				}
			}
		}

		for (auto &thread: threads) {
			thread.join();
		}
	}
}

void restart_test() {
	path.clear();
	result.clear();
	x.store(false);
}

int main() {
	generate_hamiltonian_cycle();
	x.store(false);

	time(find_cycle_threaded, STARTING_NODE, std::vector<int>());
//	time(find_cycle, STARTING_NODE);

	return 0;
}
