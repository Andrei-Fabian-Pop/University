#include "ShortTest.h"
#include <cassert>
#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <utility>


void testAll() { //call each function to see if it is implemented
	FixedCapBiMap m(20);
	assert(m.isEmpty() == true);
	assert(m.size() == 0); //add elements
	assert(m.add(5,5)==true);
	assert(m.add(1,111)==true);
	assert(m.add(10,110)==true);
	assert(m.add(7,7)==true);
	assert(m.add(1,1)==true); // this is the second value for key 1
	assert(m.add(1, 3) == false); // we cannot add a third value
	assert(m.add(10,10)==true);
	assert(m.add(-3,-3)==true);
	assert(m.size() == 7);
	std::pair<TValue, TValue> res = m.search(10);
	std::pair<TValue, TValue> ans1(110, 10);
	std::pair<TValue, TValue> ans2(10, 110);
	std::pair<TValue, TValue> ans3(NULL_TVALUE, NULL_TVALUE);
	assert(((res == ans1) || (res == ans2)));
	assert(m.search(16) == ans3);
	assert(m.remove(1,1) == true);
	assert(m.remove(6, 6) == false);
	assert(m.remove(5, 7) == false);
	assert(m.isEmpty() == false);
	assert(m.isFull() == false);
	assert(m.size() == 6);

    m.add(66, 55);
    m.add(66, 56);
    m.add(67, 68);
    m.add(99, 100);
    m.add(99, 101);
    std::pair<TValue, TValue> ans4(55, 56);
    std::pair<TValue, TValue> ans6(101, 100);
    std::pair<TValue, TValue> ans5(68, NULL_TVALUE);
    assert(m.removeKey(66) == ans4);
    assert(m.removeKey(67) == ans5);
    assert(m.removeKey(100) == ans3);
    assert(m.removeKey(99) == ans6);

	TElem e;
	FixedCapBiMapIterator id = m.iterator();
	id.first();
	int s1 = 0, s2 = 0;
	while (id.valid()) {
		e = id.getCurrent();
		s1 += e.first;
		s2 += e.second;
		id.next();
	}
//	assert(s1 == 30);
//	assert(s2 == 240);

}


