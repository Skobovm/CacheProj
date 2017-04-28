#include "SalesTaxFinder.h"
#include <stdarg.h>

// Comment out the line below if you do not want to see debug output
#define DEBUG_LOG

using namespace std;

// NOTE: This can be modified to take in whatever kind of object, as long as it returns a float
//		 Add a "wait" or countdown loop to make timing more realistic
template <typename S>
float sales_tax_lookup(S address)
{
	// NOTE: This is a terrible way to add delay, and would never go into production code
	double volatile i = 500000000;
	while (i > 0)
	{
		i--;
	}
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

void LogEvent(const char * format, ...)
{
#ifdef DEBUG_LOG
	char buffer[256];
	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);
	
	printf(buffer);
	printf("\n");
	va_end(args);
#endif
}

void Assert(bool condition, string err)
{
	if (!condition)
	{
		LogEvent("ERROR: %s", err);
	}
}

template <class T>
DLLNode<T>::DLLNode(T val)
{
	value = val;
}

// Inserts a value into the queue. New values go to tail
template <class T>
DLLNode<T>* DoublyLinkedQueue<T>::Enqueue(T value)
{
	// Create node and init
	DLLNode<T>* newNode = new DLLNode<T>(value);
	LogEvent("Inserting new node. Value: %f", value);

	if (_tail == nullptr)
	{
		// Queue is empty
		LogEvent("Queue is empty");

		_tail = newNode;
		_head = newNode;
	}
	else
	{
		LogEvent("Appending to tail");
		_tail->next = newNode;
		newNode->prev = _tail;
		_tail = newNode;
	}
	_count++;

	return newNode;
}

// Remove the front-most element in the FIFO
template <class T>
DLLNode<T>* DoublyLinkedQueue<T>::Dequeue(T* outVal)
{
	DLLNode<T>* returnedElement = nullptr;
	if (_head != nullptr)
	{
		returnedElement = _head;
		*outVal = _head->value;

		DLLNode<T>* next = _head->next;
		if (_head == _tail)
		{
			LogEvent("Dequeing last remaining element");
		}

		// Remove last element in queue
		LogEvent("Dequeing head");
		next->prev = nullptr;
		delete(_head);
		_head = next;

		_count--;
	}
	else
	{
		LogEvent("Nothing to dequeue");
	}
	return returnedElement;
}

// Move a node in the queue to the front (end of FIFO)
template <class T>
void DoublyLinkedQueue<T>::MoveToFront(DLLNode<T>* node)
{
	// Tail = front. Do nothing
	if (node != _tail)
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
			Assert(node == _head, "Last node is not head");
			_head = node->next;
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
		node->prev = _tail;
		node->next = nullptr;
		_tail->next = node;
		_tail = node;
	}
}

// Returns number of elements in the FIFO
template <class T>
int DoublyLinkedQueue<T>::GetCount()
{
	return _count;
}

// 50K is the default per spec received in email
SalesTaxFinder::SalesTaxFinder(int maxEntries)
{
	_maxEntries = maxEntries;
}

// Look up tax rate for an address with a cache. Fallback to using sales_tax_lookup
// if the address/tax rate pair is not found
float SalesTaxFinder::fast_rate_lookup(string address)
{
	float taxRate;

	LogEvent("Rate lookup for: %s", address.c_str());

	// Check hash map for address
	auto searchIter = _addressHashMap.find(address);
	if (searchIter != _addressHashMap.end())
	{
		// Address found in cache
		LogEvent("Address found in cache!");

		// Move to front of queue, return rate
		DLLNode<float>* node = searchIter->second;
		_cacheOrderList.MoveToFront(node);

		taxRate = node->value;
	}
	else
	{
		LogEvent("Address not found");

		// Address/tax rate is not in cache. Call sales_tax_lookup
		taxRate = sales_tax_lookup(address);

		// Check queue size, dequeue element if too large
		if (_cacheOrderList.GetCount() >= _maxEntries)
		{
			// Since we control the type (float in this case) we do not need to 
			// free memory, as it's done by dequeue for intrinsic types
			float last;
			DLLNode<float>* removedNode = _cacheOrderList.Dequeue(&last);

			bool nodeRemoved = false;
			for (auto iter = _addressHashMap.begin(); iter != _addressHashMap.end(); ++iter) 
			{
				auto nodePtr = iter->second;
				if (nodePtr == removedNode)
				{
					LogEvent("Found old node. Removing");
					_addressHashMap.erase(iter);
					nodeRemoved = true;
					break;
				}
			}
			Assert(nodeRemoved, "Did not find remove node in hash map");
		}

		// Enqueue element and get DLLNode* back
		DLLNode<float>* newNode = _cacheOrderList.Enqueue(taxRate);

		// Hash the pointer with address as key
		_addressHashMap.emplace(address, newNode);
	}

	return taxRate;
}
