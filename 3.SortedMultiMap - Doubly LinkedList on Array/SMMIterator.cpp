#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
	//TODO - Implementation
	this->current = map.head;
}

void SMMIterator::first() {
	//TODO - Implementation
	this->current = map.head;
}

void SMMIterator::next() {
	//TODO - Implementation
	if (this->current == -1)
		throw exception();

	this->current = map.nodes[current].next;
}

bool SMMIterator::valid() const {
	//TODO - Implementation
	if (this->current == -1)
		return false;
	return true;
}

TElem SMMIterator::getCurrent() const {
	//TODO - Implementation
	if (this->current == -1)
		throw exception();

	return map.nodes[this->current].info;
}

