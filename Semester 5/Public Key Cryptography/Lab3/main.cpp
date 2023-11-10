#include <iostream>
#include <cstdlib>
#include <ctime>

// POLLARD

std::uint64_t gcd(std::uint64_t a, std::uint64_t b) {
	while (b != 0) {
		std::uint64_t temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

std::uint64_t pollardsRho(std::uint64_t n, std::uint64_t (* function)(std::uint64_t, std::uint64_t)) {
	if (n % 2 == 0) return 2;

	std::uint64_t x = rand() % (n - 1) + 1;
	std::uint64_t y = x;
	std::uint64_t d = 1;

	while (d == 1) {
		x = function(x, n);
		y = function(function(y, n), n);
		d = gcd(std::abs((int64_t)(x) - (int64_t)(y)), n);
	}

	return d;
}

// Default function f(x) = x^2 + 1
std::uint64_t defaultFunction(std::uint64_t x, std::uint64_t num) {
	return (x * x + 1) % num;
}

int main() {
	// Seed for random number generation
	srand(static_cast<unsigned int>(time(nullptr)));

	// Input: Number to be factored
	std::uint64_t num;
	std::cout << "Enter a number to factorize: ";
	std::cin >> num;

//	auto function = [](std::uint64_t x, std::uint64_t num) {
//		return (x * x + 2 * x + 1) % num;
//	};

	std::uint64_t factor = pollardsRho(num, defaultFunction);

	if (factor == num) {
		std::cout << "Unable to find a non-trivial factor. " << num << " is probably prime." << std::endl;
	} else {
		std::cout << "A non-trivial factor of " << num << " is: " << factor << std::endl;
	}

	return 0;
}
