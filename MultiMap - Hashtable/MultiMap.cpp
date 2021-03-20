#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


int MultiMap::h(TKey k, int i) const
{
	// the key must be positive for hashing
	if (k < 0)
		k = -k;

	// to be sure of obtaining permutations, c1=c2=0.5, m starts as a power of 2 
	//													(so it will remain power of to when resizing by doubling the capacity)
	return (int(k % m + 0.5 * i + 0.5 * i * i) % m);
}


// Complexity: theta(m)
//			AC = BC = WC
//   * Special case when map is empty -> theta(1)
int MultiMap::getKeyRange() const
{
	TKey min = 111111;
	TKey max = -111111;

	if (this->nrElems == 0)
		return -1;

	for (int i = 0; i < m; i++)
	{
		if (this->elements[i] != EMPTY && this->elements[i] != DELETED)
		{
			if (this->elements[i].first > max)
				max = this->elements[i].first;
			if (this->elements[i].first < min)
				min = this->elements[i].first;
		}
	}

	return max - min;
}


// Complexity: theta(m)
//				AC = BC = WC = theta(m) (array is initialised with empty positions)
MultiMap::MultiMap() {

	this->m = 8;
	this->elements = new TElem[this->m];
	this->nrElems = 0;
	for (int i = 0; i < m; i++)
		this->elements[i] = EMPTY;
}


// Complexity: O(m) -overall
//			BC: theta(1) - h(k,0) is empty or deleted 
//			WC: theta(m) - when all h(k,i), i<m are occupied
//			AC: theta(1) - load factor=n/m has upper bound 1 so it's constant
//       Special case, when resize is needed, the complexity becomes that of the resize function
void MultiMap::add(TKey c, TValue v) {

	TElem element;
	element.first = c;
	element.second = v;

	// we hash positions, increasing the 'i' parameter until an EMPTY or DELETED position is found
	int i = 0;
	int pos = h(c, i);
	while (i < this->m && this->elements[pos] != EMPTY && this->elements[pos] != DELETED)   // BC = theta (1) -first found position is free
	{																						// WC = theta (m) -no empty spots	
		i++;
		pos = this->h(c, i);
	}

	// if we reach the capacity, we stop and it means there are no more empty spots
	// resize is needed, and after that rehashing needs to be done, so 're-add' the element
	if (i == this->m)
	{
		this->resize();
		this->add(c, v);        // when 're-adding' resize will definitely won't be needed, so it doesn't become recursve
	}

	else
	{
		this->elements[pos] = element;
		this->nrElems++;
	}
}


// Complexity: O(m) -overall
//			BC: theta(1) - h(k,0) is empty or it stores the searched element
//			WC: theta(m) - when all h(k,i), i<m are occupied, but the searched element is not in the map
//			AC: theta(1) - load factor=n/m has upper bound 1 so it's constant
bool MultiMap::remove(TKey c, TValue v) {

	TElem element;
	element.first = c;
	element.second = v;

	int i = 0;
	int pos = h(c, i);

	while (i<this->m && this->elements[pos] != element && this->elements[pos] != EMPTY)
	{
		// we keep calculating position until we found the one having the element that need to be rmeoved
		i++;
		pos = this->h(c, i);
	}

	if (this->elements[pos] == element)
	{
		// if the element is found, it is marked as deleted
		this->nrElems--;
		this->elements[pos] = DELETED;
		return true;
	}
	
	return false;
}


// Complexity: O(m) -overall
//			BC: theta(1) - h(k,0) is empty
//			WC: theta(m) - when all h(k,i), i<m are occupied
//			AC: theta(1) - load factor=n/m has upper bound 1 so it's constant
vector<TValue> MultiMap::search(TKey c) const {

	vector<TValue> values;

	int i = 0;
	int pos = this->h(c, i);

	while (i < this->m)
	{
		// if we found an element with key=c we save it
		if (this->elements[pos].first == c)
			values.push_back(this->elements[pos].second);

		// when empty position is reached, there are no more elements with this key
		if (this->elements[pos] == EMPTY)
			break;

		i++;
		pos = this->h(c, i);
	}

	return values;
}


// Complexity: theta(1)
int MultiMap::size() const {

	return this->nrElems;
}


// Complexity: theta(1)
bool MultiMap::isEmpty() const {

	return this->nrElems == 0;
}


MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


// Complexity: theta(1)
MultiMap::~MultiMap() {

	delete[] this->elements;
}


// Complexity: O(m^2)     -> given by the worst case
//				BC: theta(m)
//				AC: theta(m)
//				WC: theta(m^2) -> when add functions take the worst complexity
void MultiMap::resize()
{
	TElem* copy = new TElem[this->m];

	for (int i = 0; i < nrElems; i++)      // nrElems steps
		copy[i] = this->elements[i];

	this->m *= 2;
	delete[] this->elements;

	this->elements = new TElem[this->m];
	this->nrElems = 0;
	for (int i = 0; i < this->m; i++)      // m steps   (m will be here 2*nrElems)
		this->elements[i] = EMPTY;

	for (int i = 0; i < this->m / 2; i++)
		if (copy[i] != EMPTY && copy[i] != DELETED)
			this->add(copy[i].first, copy[i].second);    // for this add, resize won't be needed, so it doesn't become recursive
		// we add each element in the new array because position needs rehashing
		// for the add operation, on average complexity is theta(1), but wors case can be theta(m)

	delete[] copy;
}
