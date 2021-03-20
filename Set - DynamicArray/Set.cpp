#include "Set.h"
#include "SetITerator.h"


/*
	Complexity: theta(1)
*/
Set::Set() {
	// initialize the number of elements with 0
	this->NrElem = 0;
	this->capacity = 10;

	// allocate memory for as many elements the set cand hold for now
	this->elements = new TElem[this->capacity];
}


/*
	Complexity: O( NrElem )				 *BC: theta(1)
(details in .txt file)					 *WC: theta(2*NrElem) ~ theta(NrElem)
										 *AC: theta(NrElem)
*/
bool Set::add(TElem elem) {
	// if the element is already in the set, it cannot be added
	if (search(elem) == true)
		return false;

	// it the maximum capacity was reached, the set must be resized
	if (this->NrElem == this->capacity)
		resize();

	// the new element is added and the number of elements is increased by 1
	this->elements[this->NrElem] = elem;
	this->NrElem++;

	return true;
}

/*
	Complexity: theta( NrElem )           *BC: theta(NrElem)
(details in .txt file)  				  *WC: theta(2*NrElem) ~ theta(NrElem)
   										  *AC: theta(NrElem)
*/
bool Set::remove(TElem elem) {
	// it the element is not in the set, it cannot be removed
	if (search(elem) == false)
		return false;

	// we search the element to know its position
	for (int i = 0; i < this->NrElem; i++)
	{
		if (this->elements[i] == elem)
		{
			// in order to eliminate the element all elements after it are shifted, one position to the left
			for (int j = i; j < this->NrElem - 1; j++)
				this->elements[j] = this->elements[j + 1];
			break;
		}
	}
	// the number of elements is decreased by 1
	this->NrElem--;

	return true;
}


/*
	Complexity:  O ( NrElem )  
					BC : theta(1)      - element found on first position
					WC : theta(NrElem) - element found on las position
					AC : theta(NrElem)           ~(1/n)*n(n+1)/2 = (n+1)/2 ~n
*/
bool Set::search(TElem elem) const {
	// all elements are parsed until the needed element is found, moment when the loop is stopped
	for (int index = 0; index < this->NrElem; index++)
		if (this->elements[index] == elem)
			return true;

	// if the element was not found, function returns false
	return false;
}


/*
	Complexity:  theta(1)
*/
int Set::size() const {
	// returns the number of elements
	return this->NrElem;
}

/*
	Complexity:  theta(1)
*/
bool Set::isEmpty() const {
	// returns true if there are 0 elements, false otherwise
	return (this->NrElem == 0);
}


/*
	Complexity:  theta(1)
*/
Set::~Set() {
	// deallocates the vector of elements
	delete[] this->elements;
}


SetIterator Set::iterator() const {
	return SetIterator(*this);
} //Complexity: theta(1)


/*
	Complexity:  theta( NrElem )
*/
void Set::resize()
{
	// the capacity is doubled
	this->capacity *= 2;

	// a new vector with the new capacity is allocated
	TElem* auxiliary = new TElem[this->capacity];
	// the elements from the set are copied to the new memory space
	for (int i = 0; i < this->NrElem; i++)
		auxiliary[i] = this->elements[i];

	// the old memory is deallocated
	delete[] this->elements;
	this->elements = auxiliary;
}
