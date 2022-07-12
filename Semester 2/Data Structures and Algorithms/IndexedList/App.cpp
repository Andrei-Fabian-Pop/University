#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"

#include "IndexedList.h"

using namespace std;

// 23.ADT List(interface with TPozition = Integer,  IndexedList) –using a SLLA

int main(){
    testAll();
    testAllExtended();

    cout<<"Finished LI Tests!"<<endl;
}