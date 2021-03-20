#include "MultiMapIterator.h"
#include "MultiMap.h"


// Complexity: O(m)
//             BC = theta(1) - first position is occupied
//			   WC = theta(m) - go through all position without finding elements
//			   AC = theta(m)
MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {

	this->current = 0;

	while (this->current < col.m && (col.elements[this->current] == EMPTY || col.elements[this->current] == DELETED))
	{
		this->current++;
	}
}


// Complexity: theta(1)
TElem MultiMapIterator::getCurrent() const{

	if (!this->valid())
		throw exception();

	return col.elements[this->current];
}


// Complexity: theta(1)
bool MultiMapIterator::valid() const {

	return this->current < col.m;
}

// Complexity: O(m)
//             BC = theta(1) - next position is occupied
//			   WC = theta(m) - go through all position without finding elements
//			   AC = theta(m)
void MultiMapIterator::next() {

	if (!this->valid())
		throw exception();
	
	this->current++;

	while (this->current < col.m && (col.elements[this->current] == EMPTY || col.elements[this->current] == DELETED))
	{
		this->current++;
	}
}


// Complexity: O(m)
//             BC = theta(1) - first position is occupied
//			   WC = theta(m) - go through all position without finding elements
//			   AC = theta(m)
void MultiMapIterator::first() {

	this->current = 0;

	while (this->current < col.m && (col.elements[this->current] == EMPTY || col.elements[this->current] == DELETED))
	{
		this->current++;
	}
}

