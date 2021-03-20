#pragma once
//DO NOT INCLUDE SETITERATOR

//DO NOT CHANGE THIS PART
#define NULL_TELEM -11111
typedef int TElem;
class SetIterator;

class Set {
    //DO NOT CHANGE THIS PART
    friend class SetIterator;

private:
    //TODO - Representation
    int NrElem;        // number of elements currently in set
    int capacity;      // maximum number of elements the set can store
    TElem* elements;   // dynamic array of elements of type TElem

public:
    //implicit constructor
    Set();

    //adds an element to the set
    bool add(TElem e);

    //removes an element from the set
    bool remove(TElem e);

    //checks whether an element belongs to the set or not
    bool search(TElem elem) const;

    //returns the number of elements;
    int size() const;

    //check whether the set is empty or not;
    bool isEmpty() const;

    //return an iterator for the set
    SetIterator iterator() const;

    // destructor
    ~Set();



private:
    // Additional function that resizes the dynamic vector with a bigger capacity
    // by allocating new memory, copying the elements and deallocating old memory
    void resize();
};

