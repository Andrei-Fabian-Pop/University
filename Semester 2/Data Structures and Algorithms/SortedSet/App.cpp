#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>

using namespace std;

// A2
// 8.ADT SortedSet–using a DLL where elements are ordered based on a relation between the elements.

int main() {
	testAll();
	testAllExtended();

	cout << "Test end" << endl;
	system("pause");
}