#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"

// 3. ADT SortedBag–using a BST with linked representation with dynamic allocation. If an element appears multiple times,
// it will be stored multiple times in the BST

using namespace std;

int main() {
	testAll();
	testAllExtended();
	
	cout << "Test over" << endl;
}
