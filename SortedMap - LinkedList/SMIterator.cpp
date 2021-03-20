#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

// theta(1)
SMIterator::SMIterator(SortedMap& m) : map(m) {

	this->current = map.head;
}

// theta(1)
void SMIterator::first() {

	this->current = map.head;
}

// theta(1)
void SMIterator::next() {

	if (!this->valid())
		throw exception();
	this->current = this->current->next;
}

// theta(1)
bool SMIterator::valid() const {

	if (this->current == nullptr)
		return false;
	return true;
}

// theta(1)
TElem SMIterator::getCurrent() const {

	if (!this->valid())
		throw exception();
	return this->current->info;
}

TElem SMIterator::remove()
{
	if (!this->valid())
		throw exception();

	// this is the current node that must be removed
	TElem to_be_removed = this->current->info;
	// the current becomes the next element
	this->current = current->next;
	
	// the current element is removed by its key
	this->map.remove(to_be_removed.first);

	// the removed node is returned
	return to_be_removed;

} // complexity: = complexity of SortedMap.remove
	// O (number of nodes)              BC: theta (1)                             - if current is at head
	//									WC: theta (number of nodes)		          - if current is at tail
	//									AC: theta (number of nodes)

