#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

// Complexity: O(n)
//		BC: theta(1)   - when all children are in the right subtree of the root
//		AC: theta(log2 n)   - the average height of the tree
//		WC: theta(n)  - all nodes have left children
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {

	int index = this->bag.root;
	while (index != -1)
	{
		// we traverse the left side of the tree and keep the nodes in a stack
		this->stack.push(index);
		index = bag.nodes[index].left;
	}
	if (!stack.empty())
	{
		// we set the current node as the top of the stack (the most left node)
		this->current = this->stack.top();
		this->current_frequency = 1;
	}
	else
	{
		// if the stack is empty, the tree is empty so the iterator is invalid
		this->current = -1;
		this->current_frequency = -1;
	}
}


// Complexity: theta (1)
//				AC = BC = WC
TComp SortedBagIterator::getCurrent() {

	if (!valid())
		throw exception();
	else
		return bag.nodes[this->current].info.first;
}


// Complexity: theta (1)
//				AC = BC = WC
bool SortedBagIterator::valid() {

	return this->current != -1 && this->current_frequency != -1;
}


// Complexity: O(n)
//		BC: theta(1)   - when the just the frequency is increased and no new elment is needed / or nothing needs to be added to the stack
//		AC: theta(log2 n)
//		WC: theta(n) 
void SortedBagIterator::next() {

	if (!valid())
		throw exception();

	// we first try to raise the current frequency and get the next same element if it apeears more than once
	this->current_frequency++;

	// if the current frequency is bigger than the total frequency of the current node, we need to get to the next element
	if (this->current_frequency > bag.nodes[current].info.second)
	{
		// we get the element on the top of the stack (which is the parent of the current element)
		int index = this->stack.top();
		this->stack.pop();

		if (bag.nodes[index].right != -1)
		{
			index = bag.nodes[index].right;
			while (index != -1)
			{
				this->stack.push(index);
				index = bag.nodes[index].left;
			}
		}

		if (!this->stack.empty())
		{
			this->current = this->stack.top();
			this->current_frequency = 1;
		}
		else
		{
			this->current = -1;
			this->current_frequency = -1;
		}
	}
}


// Complexity: O(n)
//		BC: theta(1)   - when all children are in the right subtree of the root
//		AC: theta(log2 n)   - the average height of the tree
//		WC: theta(n)  - all nodes have left children
void SortedBagIterator::first() {

	// same as initialization
	// but first we need to empty the stack
	while (!this->stack.empty())
		this->stack.pop();

	int index = this->bag.root;
	while (index != -1)
	{
		this->stack.push(index);
		index = bag.nodes[index].left;
	}
	if (!stack.empty())
	{
		this->current = this->stack.top();
		this->current_frequency = 1;
	}
	else
	{
		this->current = -1;
		this->current_frequency = -1;
	}
}

