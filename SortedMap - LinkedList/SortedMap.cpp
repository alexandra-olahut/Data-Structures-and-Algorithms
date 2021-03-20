#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

// theta(1)
SortedMap::SortedMap(Relation r) {
	this->relation = r;
	this->head = nullptr;
}


// O (number of nodes)				BC: theta (1)  - element needs to be added first (becomes the head)
//									WC: theta (n)  - element needs to be added last (becomes tail)
//									AC: theta (n)
//   n = number of nodes in list
TValue SortedMap::add(TKey k, TValue v) {

	Node* new_node = new Node;
	new_node->info.first = k;
	new_node->info.second = v;
	new_node->next = nullptr; 

	if (this->head == nullptr)
	{
		this->head = new_node;
		return NULL_TVALUE;
	}

	else if (this->relation(k, this->head->info.first))
	{
		if (k != this->head->info.first)
		{
			new_node->next = this->head;
			this->head = new_node;
			return NULL_TVALUE;
		}
		else {
			TValue old = this->head->info.second;
			this->head->info.second = v;
			return old;
		}
	}

	else
	{
		Node* current = this->head;
		while (current->next != nullptr && this->relation(current->next->info.first, k))
		{
			if (k == current->next->info.first)
			{
				TValue old = current->next->info.second;
				current->next->info.second = v;
				return old;
			}
			current = current->next;
		}
		new_node->next = current->next;
		current->next = new_node;
		return NULL_TVALUE;
	}

}

// O (number of nodes)	       BC: theta(1)     - element is the head or map empty
//							   WC: theta(n)     - element on last position or doesn't exist
//							   AC: theta(n)
//     n = number of nodes in list
TValue SortedMap::search(TKey k) const {

	Node* current = head;

	while (current != nullptr)
	{
		if (current->info.first == k)
			return current->info.second;
		current = current->next;
	}

	return NULL_TVALUE;
}

// O (number of nodes)			BC: theta(1)    - element to be deleted is the head
//								WC: theta(n)    - element to be deleted is the tail
//								AC: theta(n)
//     n = number of nodes in list
TValue SortedMap::remove(TKey k) {

	Node* current = this->head;
	Node* prev = nullptr;

	while (current != nullptr && current->info.first != k)
	{
		prev = current;
		current = current->next;
	}
	if (current != nullptr && prev == nullptr)
	{
		TValue deleted = this->head->info.second;
		this->head = this->head->next;
		return deleted;
	}
	else if (current != nullptr)
	{
		TValue deleted = current->info.second;
		prev->next = current->next;
		current->next = nullptr;
		return deleted;
	}
	else return NULL_TVALUE;
}

// theta (number of nodes)
int SortedMap::size() const {

	int size = 0;
	Node* current = this->head;

	while (current != nullptr)
	{
		size++;
		current = current->next;
	}

	return size;
}

// theta (1)
bool SortedMap::isEmpty() const {

	return this->head == nullptr;
}

// theta (1)
SMIterator SortedMap::iterator(){
	return SMIterator(*this);
}

// theta (number of nodes)
SortedMap::~SortedMap() {

	while (this->head != nullptr)
	{
		Node* aux = this->head;
		this->head = this->head->next;

		delete aux;
	}
}
