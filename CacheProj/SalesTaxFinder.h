#pragma once

#include <list>
#include <string>
#include <unordered_map>
#include <iostream>

template <class T>
class DLLNode
{
public:
	DLLNode(T value);
	DLLNode<T>* prev = nullptr;
	DLLNode<T>* next = nullptr;
	T value;
};

// Implement our own queue for O(1) MoveToFront
template <class T>
class DoublyLinkedQueue
{
public:
	DLLNode<T>* Enqueue(T value);
	DLLNode<T>* Dequeue(T* outVal);
	void MoveToFront(DLLNode<T>* node);
	int GetCount();

private:
	DLLNode<T>* _head = nullptr;
	DLLNode<T>* _tail = nullptr;
	int _count = 0;
	int _maxCount;
};

// This class will be used to actually find 
class SalesTaxFinder
{
public:
	SalesTaxFinder(int maxEntries);
	float fast_rate_lookup(std::string address);

private:
	int _maxEntries;
	DoublyLinkedQueue<float> _cacheOrderList;
	std::unordered_map<std::string, DLLNode<float>*> _addressHashMap;
};

// Helper functions
void LogEvent(const char * format, ...);
void Assert(bool condition, std::string err);
