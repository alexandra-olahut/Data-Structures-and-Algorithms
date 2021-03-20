#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
	//TODO - Implementation
	this->relation = r;
	this->capacity = INIT_CAPACITY;
	this->nrElems = 0;

	this->head = -1;
	this->tail = -1;
	this->firstEmpty = 0;

	this->nodes = new Node[this->capacity];
	for (int i = 0; i < this->capacity - 1; i++)
	{
		nodes[i].next = i + 1;
		nodes[i].prev = i - 1;
	}
	nodes[capacity - 1].next = -1;
	nodes[capacity - 1].prev = capacity - 2;

}

void SortedMultiMap::add(TKey c, TValue v) {
	//TODO - Implementation

	TElem new_element;
	new_element.first = c;
	new_element.second = v;

	int new_index = allocate();

	if (new_index == -1)
	{
		resize();
		new_index = allocate();
	}

	this->nodes[new_index].info = new_element;
	// for now, info=elem, next=-1, prev=-1
	this->nrElems++;


	if (this->nrElems == 1)
	{
		// we add the first element in an empty map
		this->head = new_index;
		this->tail = new_index;
		return;
	}

	if (this->relation(c, nodes[head].info.first))
	{
		// we add it as head
		this->nodes[new_index].next = this->head;
		this->nodes[this->head].prev = new_index;
		this->head = new_index;
		return;
	}

	// we must find the position to maintain the relation
	int current = this->head;
	while (current != -1 && this->relation(nodes[current].info.first, c))
	{
		current = this->nodes[current].next;
	}

	if (current == -1)
	{
		// we reached the end, we add it as tail
		this->nodes[new_index].prev = this->tail;
		this->nodes[this->tail].next = new_index;
		this->tail = new_index;
		return;
	}

	// we add it before 'current'
	int prev_index = this->nodes[current].prev;

	this->nodes[prev_index].next = new_index;
	this->nodes[new_index].prev = prev_index;

	this->nodes[new_index].next = current;
	this->nodes[current].prev = new_index;
}

vector<TValue> SortedMultiMap::search(TKey c) const {
	//TODO - Implementation
	vector<TValue> values;
	
	int current_index = this->head;
	while (current_index != -1)
	{
		if (nodes[current_index].info.first == c)
			values.push_back(nodes[current_index].info.second);
		current_index = nodes[current_index].next;
	}
	return values;
}

bool SortedMultiMap::remove(TKey c, TValue v) {
	//TODO - Implementation
	TElem element;
	element.first = c;
	element.second = v;

	int current_index = this->head;
	while (current_index != -1 && this->nodes[current_index].info != element)
	{
		current_index = this->nodes[current_index].next;
	}

	if(current_index == -1)
		return false;
	
	int prev = this->nodes[current_index].prev;
	int next = this->nodes[current_index].next;

	if (prev == -1)  // current == head
	{
		// we remove the head
		this->head = this->nodes[this->head].next;
	}
	if (next == -1)   // current == tail
	{
		// we remove the tail
		this->tail = this->nodes[this->tail].prev;
	}
	if (prev != -1)
	{
		this->nodes[prev].next = next;
	}
	if (next != -1)
	{
		this->nodes[next].prev = prev;
	}

	free(current_index);
	this->nrElems--;
	return true;
}


int SortedMultiMap::size() const {
	//TODO - Implementation
	return this->nrElems;
}

bool SortedMultiMap::isEmpty() const {
	//TODO - Implementation
	return this->nrElems == 0;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
	//TODO - Implementation
	delete[] this->nodes;
}


void SortedMultiMap::resize()
{
	Node* aux = new Node[this->capacity * 2];

	for (int i = 0; i < this->capacity; i++)
		aux[i] = this->nodes[i];
	
	for (int i = this->capacity; i < 2 * this->capacity; i++)
	{
		aux[i].next = i + 1;
		aux[i].prev = i - 1;
	}
	aux[this->capacity * 2 - 1].next = -1;
	aux[this->capacity].prev = -1;

	this->firstEmpty = this->capacity;
	this->capacity *= 2;

	delete[] this->nodes;

	this->nodes = aux;
}

int SortedMultiMap::allocate()
{
	int new_position = this->firstEmpty;
	if (new_position != -1)
	{
		this->firstEmpty = nodes[firstEmpty].next;
		if (this->firstEmpty != -1)
			this->nodes[this->firstEmpty].prev = -1;

		this->nodes[new_position].next = -1;
		this->nodes[new_position].prev = -1;
	}
	return new_position;
}

void SortedMultiMap::free(int position)
{
	this->nodes[position].next = this->firstEmpty;
	this->nodes[position].prev = -1;

	if (this->firstEmpty != -1)
		this->nodes[firstEmpty].prev = position;
	this->firstEmpty = position;
}
