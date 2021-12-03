/*
	LinkedList.h - V1.1 - Generic LinkedList implementation
	Works better with FIFO, because LIFO will need to
	search the entire List to find the last one;

	For instructions, go to https://github.com/ivanseidel/LinkedList

	Created by Ivan Seidel Gomes, March, 2013.
	Released into the public domain.
*/

#ifndef LinkedList_h
#define LinkedList_h

#include <stddef.h>

template <class Data>
struct ListNode
{
	Data data;
	ListNode<Data> *next;
};

template <typename Data>
class LinkedList
{

protected:
	int _size;
	ListNode<Data> *root;
	ListNode<Data> *last;

	// Helps "get" method, by saving last position
	ListNode<Data> *lastNodeGot;
	int lastIndexGot;
	// isCached should be set to FALSE
	// everytime the list suffer changes
	bool isCached;

	ListNode<Data> *getNode(int index);

	ListNode<Data> *findEndOfSortedString(ListNode<Data> *p, int (*cmp)(Data &, Data &));

public:
	LinkedList();
	LinkedList(int sizeIndex, Data _t); // initiate list size and default value
	virtual ~LinkedList();

	/*
		Returns current size of LinkedList
	*/
	virtual int size();
	/*
		Adds a T object in the specified index;
		Unlink and link the LinkedList correcly;
		Increment _size
	*/
	virtual bool add(int index, Data);
	/*
		Adds a T object in the end of the LinkedList;
		Increment _size;
	*/
	virtual bool add(Data);
	/*
		Adds a T object in the start of the LinkedList;
		Increment _size;
	*/
	virtual bool unshift(Data);
	/*
		Set the object at index, with T;
	*/
	virtual bool set(int index, Data);
	/*
		Remove object at index;
		If index is not reachable, returns false;
		else, decrement _size
	*/
	virtual Data remove(int index);
	/*
		Remove last object;
	*/
	virtual Data pop();
	/*
		Remove first object;
	*/
	virtual Data shift();
	/*
		Get the index'th element on the list;
		Return Element if accessible,
		else, return false;
	*/
	virtual Data get(int index);

	/*
		Clear the entire array
	*/
	virtual void clear();

	/*
		Sort the list, given a comparison function
	*/
	virtual void sort(int (*cmp)(Data &, Data &));

	// add support to array brakets [] operator
	inline Data &operator[](int index);
	inline Data &operator[](size_t &i) { return this->get(i); }
	inline const Data &operator[](const size_t &i) const { return this->get(i); }
};

// Initialize LinkedList with false values
template <typename Data>
LinkedList<Data>::LinkedList()
{
	root = NULL;
	last = NULL;
	_size = 0;

	lastNodeGot = root;
	lastIndexGot = 0;
	isCached = false;
}

// Clear Nodes and free Memory
template <typename Data>
LinkedList<Data>::~LinkedList()
{
	ListNode<Data> *tmp;
	while (root != NULL)
	{
		tmp = root;
		root = root->next;
		delete tmp;
	}
	last = NULL;
	_size = 0;
	isCached = false;
}

/*
	Actualy "logic" coding
*/

template <typename Data>
ListNode<Data> *LinkedList<Data>::getNode(int index)
{

	int _pos = 0;
	ListNode<Data> *current = root;

	// Check if the node trying to get is
	// immediatly AFTER the previous got one
	if (isCached && lastIndexGot <= index)
	{
		_pos = lastIndexGot;
		current = lastNodeGot;
	}

	while (_pos < index && current)
	{
		current = current->next;

		_pos++;
	}

	// Check if the object index got is the same as the required
	if (_pos == index)
	{
		isCached = true;
		lastIndexGot = index;
		lastNodeGot = current;

		return current;
	}

	return NULL;
}

template <typename Data>
int LinkedList<Data>::size()
{
	return _size;
}

template <typename Data>
LinkedList<Data>::LinkedList(int sizeIndex, Data _t)
{
	for (int i = 0; i < sizeIndex; i++)
	{
		add(_t);
	}
}

template <typename Data>
bool LinkedList<Data>::add(int index, Data _t)
{

	if (index >= _size)
		return add(_t);

	if (index == 0)
		return unshift(_t);

	ListNode<Data> *tmp = new ListNode<Data>(),
				   *_prev = getNode(index - 1);
	tmp->data = _t;
	tmp->next = _prev->next;
	_prev->next = tmp;

	_size++;
	isCached = false;

	return true;
}

template <typename Data>
bool LinkedList<Data>::add(Data _t)
{

	ListNode<Data> *tmp = new ListNode<Data>();
	tmp->data = _t;
	tmp->next = NULL;

	if (root)
	{
		// Already have elements inserted
		last->next = tmp;
		last = tmp;
	}
	else
	{
		// First element being inserted
		root = tmp;
		last = tmp;
	}

	_size++;
	isCached = false;

	return true;
}

template <typename Data>
bool LinkedList<Data>::unshift(Data _t)
{

	if (_size == 0)
		return add(_t);

	ListNode<Data> *tmp = new ListNode<Data>();
	tmp->next = root;
	tmp->data = _t;
	root = tmp;

	_size++;
	isCached = false;

	return true;
}

template <typename Data>
Data &LinkedList<Data>::operator[](int index)
{
	return getNode(index)->data;
}

template <typename Data>
bool LinkedList<Data>::set(int index, Data _t)
{
	// Check if index position is in bounds
	if (index < 0 || index >= _size)
		return false;

	getNode(index)->data = _t;
	return true;
}

template <typename Data>
Data LinkedList<Data>::pop()
{
	if (_size <= 0)
		return Data();

	isCached = false;

	if (_size >= 2)
	{
		ListNode<Data> *tmp = getNode(_size - 2);
		Data ret = tmp->next->data;
		delete (tmp->next);
		tmp->next = NULL;
		last = tmp;
		_size--;
		return ret;
	}
	else
	{
		// Only one element left on the list
		Data ret = root->data;
		delete (root);
		root = NULL;
		last = NULL;
		_size = 0;
		return ret;
	}
}

template <typename Data>
Data LinkedList<Data>::shift()
{
	if (_size <= 0)
		return Data();

	if (_size > 1)
	{
		ListNode<Data> *_next = root->next;
		Data ret = root->data;
		delete (root);
		root = _next;
		_size--;
		isCached = false;

		return ret;
	}
	else
	{
		// Only one left, then pop()
		return pop();
	}
}

template <typename Data>
Data LinkedList<Data>::remove(int index)
{
	if (index < 0 || index >= _size)
	{
		return Data();
	}

	if (index == 0)
		return shift();

	if (index == _size - 1)
	{
		return pop();
	}

	ListNode<Data> *tmp = getNode(index - 1);
	ListNode<Data> *toDelete = tmp->next;
	Data ret = toDelete->data;
	tmp->next = tmp->next->next;
	delete (toDelete);
	_size--;
	isCached = false;
	return ret;
}

template <typename Data>
Data LinkedList<Data>::get(int index)
{
	ListNode<Data> *tmp = getNode(index);

	return (tmp ? tmp->data : Data());
}

template <typename Data>
void LinkedList<Data>::clear()
{
	while (size() > 0)
		shift();
}

template <typename Data>
void LinkedList<Data>::sort(int (*cmp)(Data &, Data &))
{
	if (_size < 2)
		return; // trivial case;

	for (;;)
	{

		ListNode<Data> **joinPoint = &root;

		while (*joinPoint)
		{
			ListNode<Data> *a = *joinPoint;
			ListNode<Data> *a_end = findEndOfSortedString(a, cmp);

			if (!a_end->next)
			{
				if (joinPoint == &root)
				{
					last = a_end;
					isCached = false;
					return;
				}
				else
				{
					break;
				}
			}

			ListNode<Data> *b = a_end->next;
			ListNode<Data> *b_end = findEndOfSortedString(b, cmp);

			ListNode<Data> *tail = b_end->next;

			a_end->next = NULL;
			b_end->next = NULL;

			while (a && b)
			{
				if (cmp(a->data, b->data) <= 0)
				{
					*joinPoint = a;
					joinPoint = &a->next;
					a = a->next;
				}
				else
				{
					*joinPoint = b;
					joinPoint = &b->next;
					b = b->next;
				}
			}

			if (a)
			{
				*joinPoint = a;
				while (a->next)
					a = a->next;
				a->next = tail;
				joinPoint = &a->next;
			}
			else
			{
				*joinPoint = b;
				while (b->next)
					b = b->next;
				b->next = tail;
				joinPoint = &b->next;
			}
		}
	}
}

template <typename Data>
ListNode<Data> *LinkedList<Data>::findEndOfSortedString(ListNode<Data> *p, int (*cmp)(Data &, Data &))
{
	while (p->next && cmp(p->data, p->next->data) <= 0)
	{
		p = p->next;
	}

	return p;
}

#endif
