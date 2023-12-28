#include <iostream>
#include <chrono>
#include <vector>
#include <cassert>
#include <algorithm>
#include <mpi/mpi.h>

#define POLY_SIZE 1000

using namespace std;

void print_vector(const vector<int>& poly, int rank = -1) {
	if (rank != -1) {
		cout << "Process " << rank << ": ";
	}
	for (auto p: poly) {
		cout << p << " ";
	}
	cout << "\n";
}

static int mod(int L) {
	if (L >= 1000000009) {
		return L % 1000000009;
	} else if (L < 0) {
		return ((L % 1000000009) + 1000000009) % 1000000009;
	} else {
		return L;
	}
}

//static void multiplyPoly(const vector<int>& A, const vector<int>& B, vector<int>& prod, int start, int end) {
//	size_t n = A.size();
//
//	for (int i = start; i < end; i++) {
//		for (int j = 0; j < n; j++) {
//			prod[i + j] = mod(prod[i + j] + A[i] * B[j]);
//		}
//	}
//}

//vector<int> karatsuba(const vector<int>& a, const vector<int>& b, int rank, int size) {
//	size_t n = a.size();
//	size_t k = n / 2;
//
//	vector<int> z(2 * n, 0);
//
//	if (n <= 32) {
//		vector<int> prod(2 * n, 0);
//		multiplyPoly(a, b, prod, rank * k / size, (rank + 1) * k / size);
//
//		MPI_Allreduce(prod.data(), z.data(), (int) (2 * n), MPI_INT, MPI_SUM, MPI_COMM_WORLD);
//
//		return z;
//	} else {
//		vector<int> aR(k), bL(k), bR(k), aL(k);
//		vector<int> aLaR(k), bLbR(k);
//
//		for (int i = 0; i < k; ++i) {
//			aL[i] = a[i];
//			aR[i] = a[i + k];
//			bL[i] = b[i];
//			bR[i] = b[i + k];
//
//			aLaR[i] = mod(aL[i] + aR[i]);
//			bLbR[i] = mod(bL[i] + bR[i]);
//		}
//
//		vector<int> p1 = karatsuba(aL, bL, rank, size);
//		vector<int> p2 = karatsuba(aR, bR, rank, size);
//		vector<int> p3 = karatsuba(aLaR, bLbR, rank, size);
//
//		vector<long> productMiddle(n, 0);
//
//		for (int j = 0; j < n - 1; ++j) {
//			productMiddle[j] = mod(p3[j] - p1[j] - p2[j]);
//		}
//
//		for (size_t j = 0, middleOffset = k; j < n - 1; ++j) {
//			z[j] = mod(z[j] + p1[j]);
//			z[j + n] = mod(z[j + n] + p2[j]);
//			z[j + middleOffset] = mod((int) (z[j + middleOffset] + productMiddle[j]));
//		}
//
//		return z;
//	}
//}
//
//void old() {
////	MPI_Init(&argc, &argv);
//
//	int size, rank;
//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//	vector<int> poly1, poly2;
//
//	if (rank == 0) {
//		// Initialize polynomials on the root process
//		for (int i = 0; i < POLY_SIZE; ++i) {
//			poly1.push_back((int) (random()) % 1000);
//			poly2.push_back((int) (random()) % 1000);
//		}
//	}
//
//	MPI_Bcast(poly1.data(), POLY_SIZE, MPI_INT, 0, MPI_COMM_WORLD);
//	MPI_Bcast(poly2.data(), POLY_SIZE, MPI_INT, 0, MPI_COMM_WORLD);
//
//	MPI_Barrier(MPI_COMM_WORLD);
//
//	auto start = chrono::high_resolution_clock::now();
//	auto res = karatsuba(poly1, poly2, rank, size);
//	auto stop = chrono::high_resolution_clock::now();
//	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
//
//	if (rank == 0) {
//		cout << "Time taken by karatsuba parallel: " << duration.count() << " microseconds\n";
//
////		auto checkVector = checkMultiply(poly1, poly2);
////		cout << res.size() << " " << checkVector.size() << "\n";
////		assert(checkVector.size() == res.size());
////		for (int i = 0; i < res.size(); ++i) {
////			cout << res[i] << " " << checkVector[i] << "\n";
//
////			assert(res[i] == checkVector[i]);
////		}
////		print_vector(res, rank);
//	}
//
//	MPI_Finalize();
//}

std::vector<int> multiplicationMasterProcess(const vector<int>& poly1, const vector<int>& poly2, int procSize) {
	int start = 0, finish = 0;
	vector<int> result(poly1.size() + poly2.size() - 1, 0);
	int len = (procSize != 1) ? ((int) (poly1.size())) / (procSize - 1) : 1;

	for (int i = 1; i < procSize; ++i) {
		// create the range
		start = finish;
		finish += len;

		if (i == procSize - 1) {
			finish = (int) (poly1.size());
		}

		MPI_Send(poly1.data(), POLY_SIZE, MPI_INT, i, 0, MPI_COMM_WORLD);
		MPI_Send(poly2.data(), POLY_SIZE, MPI_INT, i, 0, MPI_COMM_WORLD);

		MPI_Send(&start, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
		MPI_Send(&finish, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
	}

	int result_size = poly1.size() + poly2.size();
	vector<vector<int>> results(procSize - 1, vector<int>(result_size));
	for (int i = 1; i < procSize; ++i) {
		MPI_Recv(results[i - 1].data(), result_size, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

	for (int i = 0; i < result.size(); ++i) {
		for (auto& item: results) {
			result[i] += item[i];
		}
	}

	return result;
}

vector<int> multiplyNaive(const vector<int>& poly1, const vector<int>& poly2, int begin, int end) {
	size_t degree1 = poly1.size() - 1;
	size_t degree2 = poly2.size() - 1;

	// Degree of the result polynomial
	size_t resultDegree = degree1 + degree2;

	// Initialize result polynomial with zeros
	vector<int> result(resultDegree + 1, 0);

	for (int i = begin; i < end; ++i) {
		for (int j = 0; j < poly2.size(); ++j) {
			result[i + j] += mod(poly1[i] * poly2[j]);
		}
	}

	return result;
}

vector<int> checkMultiply(const vector<int>& poly1, const vector<int>& poly2) {
	size_t degree1 = poly1.size() - 1;
	size_t degree2 = poly2.size() - 1;

	// Degree of the result polynomial
	size_t resultDegree = degree1 + degree2;

	// Initialize result polynomial with zeros
	vector<int> result(resultDegree + 1, 0);

	// Multiply each term of poly1 with each term of poly2
	for (int i = 0; i <= degree1; ++i) {
		for (int j = 0; j <= degree2; ++j) {
			result[i + j] += mod(poly1[i] * poly2[j]);
		}
	}

	return result;
}

void naiveChildProcess([[maybe_unused]] int rank) {
	int begin = 0;
	int end = 0;

	vector<int> poly1(POLY_SIZE);
	vector<int> poly2(POLY_SIZE);

	MPI_Recv(poly1.data(), POLY_SIZE, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	MPI_Recv(poly2.data(), POLY_SIZE, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	MPI_Recv(&begin, POLY_SIZE, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	MPI_Recv(&end, POLY_SIZE, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	vector<int> result = multiplyNaive(poly1, poly2, begin, end);

	MPI_Send(result.data(), (int) (result.size()), MPI_INT, 0, 0, MPI_COMM_WORLD);
}

static std::vector<int> multiplyPoly(vector<int> A, vector<int> B, int n) {
	std::vector<int> prod(2 * n - 1, 0);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			prod[i + j] = mod(prod[i + j] + A[i] * B[j]);
		}
	}
	return prod;
}


std::vector<int> karatsuba(const std::vector<int>& a, const std::vector<int>& b, int begin, int end) {
	size_t sz = a.size();
	size_t mid = sz / 2;

	std::vector<int> result(2 * sz - 1, 0);
	// TODO: the begin/end does not work, try to change all elements to 0, except the ones between begin and end, this might fix smth

	if (sz < 512) {
		result = multiplyNaive(a, b, begin, end);
		return result;
	} else {
		std::vector<int> aR(mid), bL(mid), bR(mid), aL(mid);
		std::vector<int> aLaR(mid), bLbR(mid);

		for (int i = 0; i < mid; ++i) {
			aL[i] = a[i];
			aR[i] = a[i + mid];
			bL[i] = b[i];
			bR[i] = b[i + mid];

			aLaR[i] = mod(aL[i] + aR[i]);
			bLbR[i] = mod(bL[i] + bR[i]);
		}

		vector<int> p1 = karatsuba(aL, bL, begin, end);
		vector<int> p2 = karatsuba(aR, bR, begin, end);
		vector<int> p3 = karatsuba(aLaR, bLbR, begin, end);

		std::vector<int> productMiddle(sz, 0);

		for (int i = 0; i < sz - 1; ++i) {
			productMiddle[i] = mod(p3[i] - p1[i] - p2[i]);
		}

		for (size_t i = 0; i < sz - 1; ++i) {
			result[i] = mod(result[i] + p1[i]);
			result[i + sz] = mod(result[i + sz] + p2[i]);
			result[i + mid] = mod(result[i + mid] + productMiddle[i]);
		}
		return result;
	}
}

void karatsubaChildProcess([[maybe_unused]] int rank) {
	int begin = 0;
	int end = 0;

	vector<int> poly1(POLY_SIZE);
	vector<int> poly2(POLY_SIZE);

	MPI_Recv(poly1.data(), POLY_SIZE, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	MPI_Recv(poly2.data(), POLY_SIZE, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	MPI_Recv(&begin, POLY_SIZE, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	MPI_Recv(&end, POLY_SIZE, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	vector<int> result = karatsuba(poly1, poly2, begin, end);

	MPI_Send(result.data(), (int) (result.size()), MPI_INT, 0, 0, MPI_COMM_WORLD);
}

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);

	int procSize, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &procSize);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		std::cout << "Procs: " << procSize << "\n";
	}

	vector<int> poly1, poly2;
	poly1.resize(POLY_SIZE);
	poly2.resize(POLY_SIZE);
	srandom(11);

	if (rank == 0) {
		// master process
		for (int i = 0; i < POLY_SIZE; ++i) {
			poly1[i] = (int) (random()) % 1000;
			poly2[i] = (int) (random()) % 1000;
		}

//		print_vector(poly1);
//		print_vector(poly2);

//		vector<int> x = multiplicationMasterProcess(poly1, poly2, procSize);
		vector<int> x = karatsuba(poly1, poly2, 0, poly1.size());
		vector<int> y = checkMultiply(poly1, poly2);

		cout << x.size() << " " << y.size() << "\n";
		assert(x.size() == y.size());
		for (int i = 0; i < (int) (x.size()); ++i) {
			assert(x[i] == y[i]);
//			cout << i << ": " << x[i] << " = " <<  y[i] << "\n";
		}
		std::cout << "The computations are correct!\n";
	} else {
		// child process
//		naiveChildProcess(rank);
		karatsubaChildProcess(rank);
	}

	MPI_Finalize();

	return 0;
}
