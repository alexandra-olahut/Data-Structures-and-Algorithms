#include "SortedBag.h"
#include "SortedBagIterator.h"

#define LEFT 0
#define RIGHT 1

#include <iostream>
using namespace std;

// Complexity: theta (capacity)
//				AC = BC = WC
SortedBag::SortedBag(Relation r) {

	this->r = r;
	this->nrElems = 0;
	this->capacity = 10;

	this->nodes = new Node[this->capacity];

	this->firstEmpty = 0;
	this->root = -1;

	// we initialize a linked list of empty position
	for (int i = 0; i < capacity; i++)
		this->nodes[i].left = i + 1;
	this->nodes[capacity - 1].left = -1;
}


// Complexity: O(n)
//		BC: theta (1)   - when we add the element that is in the root and just increase its frequencies / or we add it as child of the root
//		AC: theta (log2 n) - the average height of the tree with n elements
//		WC: theta (n) - when the tree is degenerate and we parse all elements
void SortedBag::add(TComp e) {

	this->nrElems++;

	int current = this->root;
	int parent = -1;
	while (current != -1)
	{
		parent = current;
		if (nodes[current].info.first == e)
		{
			// if we found the element in the bag, we just increase its frequency
			nodes[current].info.second++;
			return;
		}

		// we keep searching right/left according to the relation
		if (r(e, this->nodes[current].info.first))
			current = this->nodes[current].left;
		else
			current = this->nodes[current].right;
		// we stop when we reach an empty node
	}

	// if the element was not found in the bag, we need to allocate space for it in the array
	int new_index = allocate();
	// its children are initialized empty (=-1)
	if (new_index == -1)
	{
		resize();
		new_index = allocate();
	}

	// now set its value to the element, with frequency 1
	this->nodes[new_index].info.first = e;
	this->nodes[new_index].info.second = 1;

	// if the bag is empty, we set the root to be the new element
	if (this->root == -1)
	{
		this->root = new_index;
		return;
	}

	// otherwise we check if the element should be added as left or right child
	if (r(e, this->nodes[parent].info.first))
		this->nodes[parent].left = new_index;
	else
		this->nodes[parent].right = new_index;
}


// Complexity: O (n)
//		BC: theta (1)   - when we add the element that is in the root and just decrease its frequencies / or we remove the child of the root
//		AC: theta (log2 n) - the average height of the tree with n elements
//		WC: theta (n) - when the tree is degenerate and we parse all elements
bool SortedBag::remove(TComp e) {

	int left_or_right = -1;
	// remember on which side of the parent is the node we want to remove
	//		0 -> left
	//		1 -> right

	int current = this->root;
	int parent = -1;
	
	// we start looking for the element we need to remove, using the relation
	while (current != -1)
	{
		if (this->nodes[current].info.first == e)
		{
			// when we find the element
			if (this->nodes[current].info.second > 1)
			{
				// if there are more than one, we decrease de frequencies and return true - element was removed
				this->nrElems--;
				this->nodes[current].info.second--;
				return true;
			}
			// else we keep the element we want to remove in 'current' and its parent in 'parent'
			else
				break;
		}
		parent = current;

		if (r(e, this->nodes[current].info.first))
		{
			current = this->nodes[current].left;
			left_or_right = LEFT;
		}
		else
		{
			current = this->nodes[current].right;
			left_or_right = RIGHT;
		}
	}

	// if current reached an empty position, it means the element was not found
	if (current == -1)
		return false;
	
	this->nrElems--;
	int index_to_remove = current;

	// has no children, we set it to null and free it
	if (nodes[index_to_remove].left == -1 && nodes[index_to_remove].right == -1)
	{
		if (index_to_remove == this->root)
		{
			// we need to remove the root so we set the root to empty (as it had no children)
			this->root = -1;
			free(index_to_remove);
			return true;
		}
	
		// for its parent we set the child as empty (left/right - which is needed)
		if (left_or_right == LEFT)
			this->nodes[parent].left = -1;
		else
			this->nodes[parent].right = -1;
		
		free(index_to_remove);
		return true;
	}

	// has only left child, so the parent receives the left child of the element we remove
	if (nodes[index_to_remove].left != -1 && nodes[index_to_remove].right == -1)
	{
		if (index_to_remove == this->root)
		{
			this->root = nodes[index_to_remove].left;
			free(index_to_remove);
			return true;
		}
		
		if (left_or_right == LEFT)
			this->nodes[parent].left = nodes[index_to_remove].left;
		else
			this->nodes[parent].right = nodes[index_to_remove].left;

		free(index_to_remove);
		return true;
	}

	// has only right child, so parent receives the right child of the element we remove
	if (nodes[index_to_remove].left == -1 && nodes[index_to_remove].right != -1)
	{
		if (index_to_remove == this->root)
		{
			this->root = nodes[index_to_remove].right;
			free(index_to_remove);
			return true;
		}
		
		if (left_or_right == LEFT)
			this->nodes[parent].left = nodes[index_to_remove].right;
		else
			this->nodes[parent].right = nodes[index_to_remove].right;

		free(index_to_remove);
		return true;
	}

	// otherwise the node to remove has 2 children
	// we replace e with the maximum element on the left subtree and delete that element
	int maximum = nodes[index_to_remove].left;
	int parent_of_maximum = index_to_remove;

	while (nodes[maximum].right != -1)
	{
		parent_of_maximum = maximum;
		maximum = nodes[maximum].right;
	}
	// we remember the maximum (the element on the most right of the left subtree of the element to be removed)
	// and its parent

	// the value of the element we want to remove is replaced by its predecessor
	this->nodes[index_to_remove].info = this->nodes[maximum].info;

	// the node containing that predecessor needs to be removed and the position freed
	if(parent_of_maximum == index_to_remove)
		// this means the predecessor is right on the left of 'index_to_remove', so we replace it with its left subtree
		this->nodes[parent_of_maximum].left = this->nodes[maximum].left;
	else
		// the predecessor is replaced by its left subtree in the right child of its parent
		this->nodes[parent_of_maximum].right = this->nodes[maximum].left;
	
	free(maximum);
	return true;
}

// Complexity: O (n)
//		BC: theta (1)   - when we search for the root
//		AC: theta (log2 n) - the average height of the tree with n elements
//		WC: theta (n) - when the tree is degenerate and we parse all elements
bool SortedBag::search(TComp elem) const {

	int current = this->root;

	while (current != -1)
	{
		// we return true when we find the element
		if (this->nodes[current].info.first == elem)
			return true;

		// otherwise we search left/right according to the relation of the bag
		if (r(elem, this->nodes[current].info.first))
			current = this->nodes[current].left;
		else
			current = this->nodes[current].right;
	}

	// the end of the while meand the element was not found
	return false;
}


// Complexity: O (n)
//		BC: theta (1)   - when we add the element that is in the root and just decrease its frequencies / or we remove the child of the root
//		AC: theta (log2 n) - the average height of the tree with n elements
//		WC: theta (n) - when the tree is degenerate and we parse all elements
int SortedBag::nrOccurrences(TComp elem) const {

	int current = this->root;

	while (current != -1)
	{
		// the same as search but we return the frequency of the found 
		if (this->nodes[current].info.first == elem)
			return this->nodes[current].info.second;

		if (r(elem, this->nodes[current].info.first))
			current = this->nodes[current].left;
		else
			current = this->nodes[current].right;
	}

	// if element was not found the frequency is 0
	return 0;
}


// Complexity: theta(1)
//				AC = BC = WC
int SortedBag::size() const {

	return this->nrElems;
}


// Complexity: theta(1)
//				AC = BC = WC
bool SortedBag::isEmpty() const {

	return this->nrElems == 0;
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


// Complexity: theta(1)
//				AC = BC = WC
SortedBag::~SortedBag() {

	delete[] nodes;
}


// Complexity: theta (capacity)
//				AC = BC = WC
void SortedBag::resize()
{
	Node* aux = new Node[this->capacity*2];

	for (int i = 0; i < capacity; i++)
		aux[i] = this->nodes[i];
	
	for (int i = capacity; i < 2 * capacity; i++)
		aux[i].left = i + 1;
	aux[2 * capacity - 1].left = -1;

	this->firstEmpty = this->capacity;
	this->capacity *= 2;

	delete[] this->nodes;
	this->nodes = aux;
}


// Complexity: theta (1)
//				AC = BC = WC
int SortedBag::allocate()
{
	int new_position = this->firstEmpty;
	if (new_position != -1)
	{
		this->firstEmpty = nodes[firstEmpty].left;
		
		this->nodes[new_position].left = -1;
		this->nodes[new_position].right = -1;
	}
	return new_position;
}


// Complexity: theta (1)
//				AC = BC = WC
void SortedBag::free(int position)
{
	this->nodes[position].left = this->firstEmpty;
	this->firstEmpty = position;
}
