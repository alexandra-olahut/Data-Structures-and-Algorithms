#include "ShortTest.h"
#include <assert.h>
#include "Set.h"
#include "SetIterator.h"
#include <exception>
using namespace std;
#include <iostream>

void testExtra()
{
	Set set1;
	SetIterator it = set1.iterator();

	set1.add(1);
	set1.add(2);
	set1.add(3);
	set1.add(4);
	set1.add(5);
	set1.add(6);
	set1.add(7);
	set1.add(8);
	set1.add(9);

	while (it.valid())
		it.next();
	it.jumpBackward(1);
	int element = 9;
	while (it.valid())
	{
		assert(it.getCurrent() == element);
		element -= 3;
		try {
			it.jumpBackward(3);
		}
		catch (exception&)
		{
		};
	}
}



void testAll() {
	Set s;
	assert(s.isEmpty() == true);
	assert(s.size() == 0);
	assert(s.add(5) == true);
	assert(s.add(1) == true);
	assert(s.add(10) == true);
	assert(s.add(7) == true);
	assert(s.add(1) == false);
	assert(s.add(10) == false);
	assert(s.add(-3) == true);
	assert(s.size() == 5);
	assert(s.search(10) == true);
	assert(s.search(16) == false);
	assert(s.remove(1) == true);
	assert(s.remove(6) == false);
	assert(s.size() == 4);


	SetIterator it = s.iterator();
	it.first();
	int sum = 0;
	while (it.valid()) {
		TElem e = it.getCurrent();
		sum += e;
		it.next();
	}
	assert(sum == 19);

}

