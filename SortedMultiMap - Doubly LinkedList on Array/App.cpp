#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

#include "SortedMultiMap.h"

bool r(TKey a, TKey b)
{
	return true;
}

int main() {

	testAll();
	testAllExtended();

	std::cout << "Finished SMM Tests!" << std::endl;
	system("pause");
}
