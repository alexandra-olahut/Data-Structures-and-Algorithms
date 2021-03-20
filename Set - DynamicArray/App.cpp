#include "Set.h"
#include "SetIterator.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <stack>
#include <iostream>
using namespace std;


int main() {

	testAll();
	testAllExtended();

	cout << "That's all!" << endl;
	system("pause");


//	testExtra();

/*
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

	while (it.valid())
	{
		cout << it.getCurrent() << " ";
		try {
			it.jumpBackward(3);
		}
		catch (exception&)
		{
		};
	}
*/
}


