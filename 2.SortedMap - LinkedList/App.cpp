#include "ExtendedTest.h"
#include "ShortTest.h"

#include "SortedMap.h"
#include "SMIterator.h"

#include <assert.h>
#include <iostream>
using namespace std;

int main() {
    
    test_extra();

    testAll();
	testAllExtended();

	cout << "That's all!" << endl;
	system("pause");
	return 0;
}

