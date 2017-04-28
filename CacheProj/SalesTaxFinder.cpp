#include "SalesTaxFinder.h"

using namespace std;

// Someone needs to declare this function
template <typename S>
extern float sales_tax_lookup(S address);

void LogEvent(string eventStr)
{
	cout << eventStr << '\n';
}

void Assert(bool condition, string err)
{
	if (!condition)
	{
		LogEvent("ERROR: " + err);
	}
}

template <class T>
DLLNode<T>::DLLNode(T val)
{
	value = val;
}

template <class T>
DoublyLinkedQueue<T>::DoublyLinkedQueue()
{
	// TODO: consider removing ctor
}

// Inserts a value into the queue. New values go to tail
template <class T>
DLLNode<T>* DoublyLinkedQueue<T>::Enqueue(T value)
{
	// Create node and init
	DLLNode<T> newNode = new DLLNode<T>(value);
	LogEvent("Inserting new node. Value: " + value);

	if (tail == nullptr)
	{
		// Queue is empty
		LogEvent("Queue is empty");

		tail = &newNode;
		head = &newNode;
	}
	else
	{
		tail->next = &newNode;
		newNode.prev = tail;
		tail = &newNode;
	}

	return &newNode;
}

template <class T>
void DoublyLinkedQueue<T>::Dequeue(T* outVal)
{
	if (head != nullptr)
	{

	}
	else
	{
		LogEvent("Nothing to dequeue");
	}
}

template <class T>
void DoublyLinkedQueue<T>::MoveToFront(DLLNode<T>* node)
{
	// Tail = front. Do nothing
	if (node != tail)
	{
		DLLNode<T>* prev = node->prev;
		DLLNode<T>* next = node->next;

		// Remove the node from where it currently is
		if (prev != nullptr)
		{
			prev->next = next;
		}
		else
		{
			// Ensure head is pointing here, then move up
			Assert(node == head, "Last node is not head");
			head = node->next;
		}
		if (next != nullptr)
		{
			next->prev = prev;
		}
		else
		{
			// Front node not tail. Force assert
			Assert(false, "Front node not tail");
		}

		// Move to front
		node->prev = tail;
		node->next = nullptr;
		tail->next = node;
		tail = node;
	}
}

template <class T>
int DoublyLinkedQueue<T>::GetCount()
{
	return _count;
}

template <class T>
SalesTaxFinder<T>::SalesTaxFinder(int maxEntries)
{
	_maxEntries = maxEntries;
	_cacheOrderList = new DoublyLinkedQueue<float>();
	// TODO: does hash map need to be alloced?
}

template <class T>
float SalesTaxFinder<T>::fast_rate_lookup(T address)
{
	// TODO: Check hash map for address

	// TODO: If exists, move to front of queue, return rate

	// TODO: Address/tax rate is not in cache. Call sales_tax_lookup

	// TODO: Check queue size, dequeue element if too large

	// TODO: Enqueue element and get DLLNode* back

	// TODO: Hash the pointer with address as key
}
