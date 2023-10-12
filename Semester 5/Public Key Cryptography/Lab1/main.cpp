#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <algorithm>

#define ULL unsigned long long

ULL euclidean_gcd(ULL a, ULL b) {
    while (b) {
        ULL temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate the GCD using the Binary GCD algorithm
ULL binary_gcd(ULL a, ULL b) {
    if (a == 0) {
        return b;
    }
    if (b == 0) {
        return a;
    }

    ULL shift;
    for (shift = 0; ((a | b) & 1) == 0; ++shift) {
        a >>= 1;
        b >>= 1;
    }

    while ((a & 1) == 0) {
        a >>= 1;
    }

    do {
        while ((b & 1) == 0) {
            b >>= 1;
        }

        if (a > b) {
            ULL temp = a;
            a = b;
            b = temp;
        }

        b = b - a;
    } while (b != 0);

    return a << shift;
}

// Recursive GCD Algorithm using subtractions
ULL normal_gcd(ULL a, ULL b) {
	for (ULL i = std::min(a, b); i > 0; --i) {
		if (a % i == 0 && b % i == 0) {
			return i;
		}
	}
}

int main() {
    // Seed for random number generation
    srand(time(NULL));

    // Hardcoded test inputs with ULL values
    ULL test_inputs[10][2] = {
            {1234567890123456789ULL, 9876543210987654321ULL},
            {1111ULL,                2222ULL},
            {999999999999ULL,        123456789012345ULL},
            {9876543210ULL,          1234567890ULL},
            {100000000000000ULL,     200000000000000ULL},
            {123456789ULL,           987654321ULL},
            {123ULL,                 456ULL},
            {77777777ULL,            99999999ULL},
            {123ULL,                 789ULL},
            {12345ULL,               54321ULL}
    };

    // Measure execution time for each algorithm
    for (ULL i = 0; i < 10; i++) {
        ULL a = test_inputs[i][0];
        ULL b = test_inputs[i][1];

        clock_t start_time, end_time;
        double cpu_time_used;

        // Euclidean Algorithm
        start_time = clock();
        ULL euclidean_result = euclidean_gcd(a, b);
        end_time = clock();
        cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
        printf("Euclidean GCD of (%llu, %llu) is %llu. Time taken: %f seconds\n", a, b, euclidean_result, cpu_time_used);

        // Recursive GCD Algorithm
        start_time = clock();
        ULL recursive_result = normal_gcd(a, b);
        end_time = clock();
        cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
        printf("Normal GCD of (%llu, %llu) is %llu. Time taken: %f seconds\n", a, b, recursive_result, cpu_time_used);

        // Brute Force GCD Algorithm
        start_time = clock();
        ULL binary_result = binary_gcd(a, b);
        end_time = clock();
        cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
        printf("Binary GCD of (%llu, %llu) is %llu. Time taken: %f seconds\n\n", a, b, binary_result, cpu_time_used);
    }

    return 0;
}
