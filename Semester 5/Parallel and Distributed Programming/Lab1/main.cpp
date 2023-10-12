//Goal
//		The goal of this lab is to refresh the knowledge regarding threads and mutexes.
//
//The programs to be written will demonstrate the usage of threads to do non-cooperative work on shared data. The access to the shared data must be protected by using mutexes.
//
//Common requirements
//The problems will require to execute a number of independent operations, that operate on shared data.
//There shall be several threads launched at the beginning, and each thread shall execute a lot of operations. The operations to be executed are to be randomly chosen, and with randomly chosen parameters.
//The main thread shall wait for all other threads to end and, then, it shall check that the invariants are obeyed.
//The operations must be synchronized in order to operate correctly. Write, in a documentation, the rules (which mutex what invariants it protects).
//You shall play with the number of threads and with the granularity of the locking, in order to assess the performance issues. Document what tests have you done, on what hardware platform, for what size of the data, and what was the time consumed.

//Supermarket inventory:
//There are several types of products, each having a known, constant, unit price. In the beginning, we know the quantity of each product.
//We must keep track of the quantity of each product, the amount of money (initially zero), and the list of bills, corresponding to sales. Each bill is a list of items and quantities sold in a single operation, and their total price.
//We have sale operations running concurrently, on several threads. Each sale decreases the amounts of available products (corresponding to the sold items), increases the amount of money, and adds a bill to a record of all sales.
//From time to time, as well as at the end, an inventory check operation shall be run. It shall check that all the sold products and all the money are justified by the recorded bills.
//Two sales involving distinct products must be able to update their quantities independently (without having to wait for the same mutex).



#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <random>

std::default_random_engine randomGenerator(std::random_device{}());

struct Product {
	std::string name{"No Name"};
	int quantity{0};
	double unitPrice{0};

	std::mutex mutex;
};

struct Bill {
	// list of <product, quantity>
	std::vector<std::pair<std::string, int>> items;
	double total{0};

	std::mutex mutex;
};

std::vector<Product *> g_products;
std::vector<Bill *> g_bills;
std::vector<std::thread> g_threads;
double g_total_money = 0.0;

void finishThreads() {
	// Join threads
	for (std::thread &thread: g_threads) {
		thread.join();
	}
}

void cleanup() {
	for (auto *product: g_products) {
		delete product;
	}

	for (auto *bill: g_bills) {
		delete bill;
	}
}

void generateBill(int thread_id, int bill_number) {
	std::uniform_int_distribution<int> productDistribution(0, (int) (g_products.size()) - 1);
	std::uniform_int_distribution<int> quantityDistribution(1, 10);
	auto *bill = new Bill();
	int items_on_bill = productDistribution(randomGenerator);
	for (int i = 0; i < items_on_bill; ++i) {
		int item_index = productDistribution(randomGenerator);
		Product *product = g_products[item_index];
		product->mutex.lock();
		std::string product_name = product->name;
		int item_quantity = std::min(quantityDistribution(randomGenerator), product->quantity);
		if (item_quantity == 0) {
			product->mutex.unlock();
			continue;
		}

		product->quantity -= item_quantity;

		bill->mutex.lock();
		bill->items.emplace_back(product->name, item_quantity);

		double added_sum = product->unitPrice * item_quantity;
		product->mutex.unlock();

		bill->total += added_sum;
		bill->mutex.unlock();

		std::cout << "Thread " << thread_id << " added to bill " << bill_number << " item " << product_name
				  << " in quantity " << item_quantity << " for $" << added_sum << "\n";
	}

	bill->mutex.lock();
	if (bill->total == 0) {
		bill->mutex.unlock();

		std::cout << "Thread " << thread_id << " created empty bill (num: " << bill_number << ")" << "\n";

		delete bill;
		return;
	}
	g_total_money += bill->total;
	g_bills.push_back(bill);
	std::cout << "Thread " << thread_id << " created bill " << bill_number << " with a total price of "
			  << bill->total << "\n";
	bill->mutex.unlock();
}

void inventoryCheck() {
	double calculated_total = 0.0;
	for (auto *bill: g_bills) {
		bill->mutex.lock();
		double bill_total = 0.0;

		for (const auto &item: bill->items) {
			const std::string &productName = item.first;
			int quantity = item.second;
			double unitPrice = 0.0;

			for (const Product *product: g_products) {
				if (product->name == productName) {
					unitPrice = product->unitPrice;
					break;
				}
			}

			bill_total += quantity * unitPrice;
		}

		if (bill->total != bill_total) {
			std::cerr << "Bill check failed. Total money mismatch. (" << bill->total << " != " << bill_total << ")"
					  << "\n";
		}

		bill->mutex.unlock();
		calculated_total += bill_total;
	}

	if (calculated_total == g_total_money) {
		std::cout << "Inventory check passed. Total money matches." << "\n";
	} else {
		std::cerr << "Inventory check failed. Total money mismatch. (" << calculated_total << " != "
				  << g_total_money
				  << ")" << "\n";
	}
}


auto main() -> int {
	// Initialize products
	auto *productA = new Product();
	productA->name = "Product A", productA->quantity = 100, productA->unitPrice = 5.0;
	auto *productB = new Product();
	productB->name = "Product B", productB->quantity = 50, productB->unitPrice = 10.0;
	auto *productC = new Product();
	productC->name = "Product C", productC->quantity = 200, productC->unitPrice = 2.5;

	g_products.push_back(productA);
	g_products.push_back(productB);
	g_products.push_back(productC);

	int numThreads = 4;

	g_threads.reserve(numThreads);
	for (int i = 0; i < numThreads; ++i) {
		g_threads.emplace_back([i]() -> void {
			for (int j = 0; j < 100; ++j) {
				generateBill(i, j);
			}
		});
	}

	finishThreads();
	inventoryCheck();
	cleanup();

	return 0;
}
