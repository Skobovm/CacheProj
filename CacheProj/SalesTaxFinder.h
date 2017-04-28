#pragma once

#include <list>
#include <string>
#include <unordered_map>

template <class T>
class DLLNode
{
public:
	DLLNode<T>* prev;
	DLLNode<T>* next;
	T value;
};

// Implement our own queue for O(1) MoveToFront
template <class T>
class DoublyLinkedQueue
{
public:
	DoublyLinkedQueue(int maxCount);
	DLLNode<T>* Enqueue(T value);
	T Dequeue();
	void MoveToFront(DLLNode<T>* node);
	int GetCount();

private:
	DLLNode<T>* _head = nullptr;
	DLLNode<T>* _tail = nullptr;
	int _count = 0;
	int _maxCount;
};

// This class will be used to actually find 
template <class T>
class SalesTaxFinder
{
public:
	SalesTaxFinder(int maxEntries);
	float fast_rate_lookup(T address);

private:
	int _maxEntries;
	DoublyLinkedQueue<float> _cacheOrderList;
	std::unordered_map<T, DLLNode<float>*> _addressHashMap;
};