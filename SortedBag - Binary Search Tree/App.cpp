#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"

#include <assert.h>

using namespace std;

bool rel(TComp e1, TComp e2) {
	return e1 >= e2;
}


int main() {

//	testExtra();
	testAll();
	testAllExtended();
	
	cout << "Test over" << endl;
	system("pause");
}
