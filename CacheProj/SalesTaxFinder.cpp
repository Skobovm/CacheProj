#include "SalesTaxFinder.h"

// Someone needs to declare this function
template <typename S>
extern float sales_tax_lookup(S address);

template <class T>
DoublyLinkedQueue<T>::DoublyLinkedQueue(int maxCount)
{
	_maxCount = maxCount;
}

template <class T>
DLLNode<T>* DoublyLinkedQueue<T>::Enqueue(T value)
{
	// TODO: Must create Node and return pointer

	// TODO: Must handle dequeueing its own elements when it hits max count
	return nullptr;
}

template <class T>
T DoublyLinkedQueue<T>::Dequeue()
{

}

template <class T>
void DoublyLinkedQueue<T>::MoveToFront(DLLNode<T>* node)
{

}

template <class T>
int DoublyLinkedQueue<T>::GetCount()
{

}

template <class T>
SalesTaxFinder<T>::SalesTaxFinder(int maxEntries)
{
	_maxEntries = maxEntries;
	_cacheOrderList = new DoublyLinkedQueue<float>(maxEntries);
	// TODO: does hash map need to be alloced?
}

template <class T>
float SalesTaxFinder<T>::fast_rate_lookup(T address)
{
	// TODO: Check hash map for address

	// TODO: If exists, move to front of queue, return 

	// TODO: Address/tax rate is not in cache. Call sales_tax_lookup

	// TODO: Enqueue the new val and get DLLNode back. 
}
