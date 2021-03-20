#pragma once
#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator {
	friend class SortedMap;
private:
	SortedMap& map;
	SMIterator( SortedMap& mapionar);

	Node* current;

public:
	void first();
	void next();
	bool valid() const;
	TElem getCurrent() const;


	//removes and returns the current pair from the iterator
	//after the operation the current pair from the Iterator is the next pair from the SortedMap, or, if the removed pair was the last one, the iterator is invalid
	//throws exception if the iterator is invalid
	TElem remove();
};

