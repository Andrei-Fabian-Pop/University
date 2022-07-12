//#include "Bag.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>

using namespace std;

// 7. ADT  Bag–using  a  hashtable  with  separate  chaining  in  which  (unique  element,  frequency) pairs are stored.

int main() {

	testAll();
	cout << "Short tests over" << endl;
	testAllExtended();
	cout << "All test over" << endl;

    return 0;
}