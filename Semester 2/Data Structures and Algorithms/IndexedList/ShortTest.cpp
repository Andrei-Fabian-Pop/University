#include <cassert>
#include <exception>

#include "ShortTest.h"
#include "IndexedList.h"
#include "ListIterator.h"




void testAll() {
    IndexedList list = IndexedList();
    assert(list.isEmpty());
    list.addToEnd(1);
    assert(list.size() == 1);
    list.addToPosition(0,2);
    assert(list.size() == 2);
    ListIterator it = list.iterator();
    assert(it.valid());
    it.next();
    assert(it.getCurrent() == 1);
    it.first();
    assert(it.getCurrent() == 2);
    assert(list.search(1) == 1);
    assert(list.setElement(1,3) == 1);
    assert(list.getElement(1) == 3);
    assert(list.remove(0) == 2);
    assert(list.size() == 1);

    // extra functionality
    IndexedList list2 = IndexedList();
    list2.addToEnd(1);
    list2.addToEnd(2);
    list2.addToEnd(3);
    ListIterator it2 = list2.iterator();
    assert(list2.size() == 3);
    assert(it2.remove() == 1);
    assert(list2.size() == 2);
    assert(it2.getCurrent() == 2);
}
