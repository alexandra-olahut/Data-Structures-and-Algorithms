#pragma once
//DO NOT INCLUDE SORTEDMAPITERATOR

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
#include <utility>
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -11111
#define NULL_TPAIR pair<TKey, TValue>(-11111, -11111);
class SMIterator;
typedef bool(*Relation)(TKey, TKey);


struct Node
{
	TElem info;
	Node* next;
};

class SortedMap {
	friend class SMIterator;
private:
	Node* head;
	Relation relation;

public:

	// implicit constructor
	SortedMap(Relation r);

	// adds a pair (key,value) to the map
	//if the key already exists in the map, then the value associated to the key is replaced by the new value and the old value is returned
	//if the key SMes not exist, a new pair is added and the value null is returned
	TValue add(TKey c, TValue v);

	//searches for the key and returns the value associated with the key if the map contains the key or null: NULL_TELEM otherwise
	TValue search(TKey c) const;


	//removes a key from the map and returns the value associated with the key if the key existed ot null: NULL_TELEM otherwise
	TValue remove(TKey c);

	//returns the number of pairs (key,value) from the map
	int size() const;

	//checks whether the map is empty or not
	bool isEmpty() const;

	// return the iterator for the map
	// the iterator will return the keys following the order given by the relation
	SMIterator iterator();

	// destructor
	~SortedMap();

private:

	// searches the node with a given key
	// if the key is found, kNode will be a pointer to the node with that key
	//						and prevNode will be the previous of that node
	// if the key is not found, kNode will be null
	//							and prevNode will be the node after which the kNode should be in order
	std::pair<Node*, Node*> search_node(TKey k);

};
