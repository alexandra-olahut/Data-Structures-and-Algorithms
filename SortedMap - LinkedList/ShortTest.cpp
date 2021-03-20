#include <assert.h>

#include "SortedMap.h"
#include "SMIterator.h"
#include "ShortTest.h"
#include <exception>
#include <iostream>
using namespace std;


bool rel(TKey cheie1, TKey cheie2) {
    if (cheie1 <= cheie2) {
        return true;
    }
    else {
        return false;
    }
}

void test_extra()
{
    std::cout << "Test extra" << endl<<endl;
    SortedMap sm(rel);
    for (int i = 1; i < 10; i++)
        sm.add(i, i);

    SMIterator it = sm.iterator();
    // remove all elements from iterator
    while (it.valid())
    {
        TElem current = it.getCurrent();
        // the removed element is returned (the current)
        assert(current == it.remove());
    }

    // the iterator becomes invalid
    assert(!it.valid());

    // remove function throws exception if iterator is invalid
    try {
        it.remove();
        assert(false);
    }
    catch (exception&) {
        assert(true);
    }

    // everything was removed
    assert(sm.isEmpty());
}




bool relatie1(TKey cheie1, TKey cheie2) {
    if (cheie1 <= cheie2) {
        return true;
    }
    else {
        return false;
    }
}



void testAll() {
    SortedMap sm(relatie1);
    assert(sm.size() == 0);
    assert(sm.isEmpty());
    sm.add(1, 2);
    assert(sm.size() == 1);
    assert(!sm.isEmpty());
    assert(sm.search(1) != NULL_TVALUE);
    TValue v = sm.add(1, 3);
    assert(v == 2);
    assert(sm.search(1) == 3);
    SMIterator it = sm.iterator();
    it.first();
    while (it.valid()) {
        TElem e = it.getCurrent();
        assert(e.second != NULL_TVALUE);
        it.next();
    }
    assert(sm.remove(1) == 3);
    assert(sm.isEmpty());
}

