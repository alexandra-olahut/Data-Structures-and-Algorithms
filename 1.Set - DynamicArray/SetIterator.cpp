#include "SetIterator.h"
#include "Set.h"

#include<exception>
using namespace std;

//Complexity: theta(1)
SetIterator::SetIterator(const Set& m) : set(m)
{
	// index is initialized with 0 
	this->index = 0;
}

//Complexity: theta(1)
void SetIterator::first() {
	// index is given the firs position:0
	this->index = 0;
}


//Complexity: theta(1)
void SetIterator::next() {
	// if index reached the end of the set, exception is thrown
	if (valid() == false)
		throw exception();
	// otherwise index is increased
	this->index++;
}


//Complexity: theta(1)
TElem SetIterator::getCurrent()
{
	// if index reached the end of the set, exception is thrown
	if (valid() == false)
		throw exception();
	// otherwise the element on position=index is returned
	return set.elements[this->index];
}

//Complexity: theta(1)
bool SetIterator::valid() const {
	// if the index reached the size of the set (the number of elements), it returnes False (not valid)
	// otherwise valid, true is returned
	if (this->index >= set.NrElem || this->index < 0)
		return false;
	// otherwise valid, true is returned
	return true;
}

void SetIterator::jumpBackward(int k)
{
	if (k <= 0)
		throw exception();
	this->index -= k;
	if (!valid())
		throw exception();
}
// Complexity: theta(1)

/*
	algorithm jumpBackwards(setIterator, k)
		if k<=0 then
			@throw exception
		SetIterator.index <- SetIterator.index - k
		if valid( SetIterator ) = false then
			@throw exception
	end-algorithm
*/