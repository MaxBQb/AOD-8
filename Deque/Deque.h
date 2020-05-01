#pragma once
#ifndef LINKED_LIST_CPP
#define LINKED_LIST_CPP
#include <iostream>
#include <vector>

using std::vector;

template <typename T>
class Deque
{
public:
	static unsigned const NOT_FOUND = ~0;
	Deque();
	void insert(T element, unsigned pos);
	void insert_before(T element, unsigned pos);
	void push_back(T element);
	void push_front(T element);
	T& operator[](unsigned index);
	void swap(unsigned firstPos, unsigned secondPos);
	bool remove(T value);
	bool remove_at(unsigned pos);
	unsigned remove_all(T value);
	bool pop_back();
	unsigned find(T value, unsigned startPos = 0);
	vector<unsigned> find_all(T value);
	bool update(T oldValue, T newValue);
	unsigned update_all(T oldValue, T newValue);
	unsigned size();
	void print_all();
	bool erase(unsigned start, unsigned stop);
	bool erase(unsigned start);
	bool clear();
	Deque(const Deque& obj);
	~Deque();
private:
	struct Node
	{
		T data;
		Node* next;

		Node(T data, Node* next = nullptr) : data(data), next(next)
		{
		}
	};

	Node* _head;
	unsigned _nodesСount;
	void _remove_node(Node* node, Node* previous = nullptr);
	Node* _getElement(unsigned index);
	Node* _search(T value, Node* element = nullptr);
	Node* _getPrevious(Node* node);
};

/* Структура двусвязного списка:
head -> node_1 -> ... -> node_n -> nullptr
head так же node, но самый первый
node указывающий на nullptr называется хвостом (tail)
Linked List[0] = head
Linked List[1] = head->next
Linked List[2] = head->next->next
*/
#endif
