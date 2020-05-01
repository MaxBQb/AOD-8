#include "Deque.h"

using std::endl;
using std::out_of_range;
using std::cout;
using std::cin;

template <typename T>
Deque<T>::Deque() : _head(nullptr), _nodesCount(0)
{
}

template <typename T>
Deque<T>::Deque(const Deque& obj)
{
	for (Node* current = obj._head;
	     current != nullptr;
	     current = current->next)
	{
		push_back(current->data);
	}
}

// Добавление элемента (после pos)
template <typename T>
void Deque<T>::insert(T element, unsigned pos)
{
	if (_nodesCount == 0)
		_head = new Node(element);
	else
	{
		Node* current = _getElement(pos - 1);
		current->next = new Node(element, current->next);
	}
	_nodesCount++;
}

// Добавление элемента (до pos)
template <typename T>
void Deque<T>::insert_before(T element, unsigned pos)
{
	if (_nodesCount == 0)
		_head = new Node(element);
	else if (pos == 0)
		_head = new Node(element, _head);
	else
	{
		Node* current = _getElement(pos - 1);
		_getElement(pos - 1)->next = new Node(element, current->next);
	}
	_nodesCount++;
}

// Добавление элемента в конец
template <typename T>
void Deque<T>::push_back(T element)
{
	insert(element, _nodesCount);
}

// Добавление элемента в начало
template <typename T>
void Deque<T>::push_front(T element)
{
	insert_before(element, 0);
}

// Здесь переопределяется оператор []
// В случае успеха вернёт элемент, иначе будет exception
template <typename T>
T& Deque<T>::operator[](unsigned index)
{
	Node* element = _getElement(index);
	if (element == nullptr)
		throw out_of_range("Ошибка! Некорректно задан индекс!");
	return element->data;
}

// Обмен местами элементов first и second
template <typename T>
void Deque<T>::swap(unsigned firstPos, unsigned secondPos)
{
	T tempData = (*this)[firstPos];
	(*this)[firstPos] = (*this)[secondPos];
	(*this)[secondPos] = tempData;
}

// Удаление одного элемента по значению value
// Вернёт true в случае успеха (нашёл)
template <typename T>
bool Deque<T>::remove(T value)
{
	Node* found = _search(value);
	if (found == nullptr)
		return false;
	_remove_node(found, _getPrevious(found));
	_nodesCount--;
	return true;
}

// Удаление элемента на позиции pos
// В случае, если это невозможно вернёт false
template <typename T>
bool Deque<T>::remove_at(unsigned pos)
{
	if (pos >= _nodesCount)
		return false;
	if (pos == 0)
		_remove_node(_head);
	else
	{
		Node* previous = _getElement(pos - 1);
		if (previous == nullptr)
			return false;
		_remove_node(previous->next, previous);
	}
	_nodesCount--;
	return true;
}

// Удаление всех элементов со значением value
// Вернёт количество удалённых элементов
template <typename T>
unsigned Deque<T>::remove_all(T value)
{
	unsigned count = 0;
	while (remove(value))
		count++;
	return count;
}

// Удаление последнего элемента
// В случае, если это невозможно вернёт false
template <typename T>
bool Deque<T>::pop_back()
{
	return remove_at(_nodesCount - 1);
}

// Поиск одного элемента по значению
// В случае успеха вернёт позицию первого элемента
template <typename T>
unsigned Deque<T>::find(T value, unsigned startPos)
{
	for (Node* current = _getElement(startPos);
	     current != nullptr;
	     current = current->next, startPos++)
		if (current->data == value)
			return startPos;
	return NOT_FOUND; // unsigned_max
}

// Поиск всех элементов со значением value
// Вернёт список позиций найденных элементов
template <typename T>
vector<unsigned> Deque<T>::find_all(T value)
{
	vector<unsigned> founds = {};
	unsigned i = 0;
	do
	{
		i = find(value, i);
		if (i != NOT_FOUND)
			founds.push_back(i);
		else
			break;
		i++;
	}
	while (i < _nodesCount);
	return founds;
}

// Изменяет значение найденного вхождения old_value на new_value
// Вернёт true при успехе
template <typename T>
bool Deque<T>::update(T oldValue, T newValue)
{
	Node* current = _search(oldValue);
	if (current == nullptr)
		return false;
	current->data = newValue;
	return true;
}

// Изменяет значение всех найденных вхождения old_value на new_value
// Вернёт количество замен
template <typename T>
unsigned Deque<T>::update_all(T oldValue, T newValue)
{
	unsigned i = 0;
	Node* current = nullptr;
	do
	{
		current = _search(oldValue, current);
		if (current == nullptr)
			return i;
		current->data = newValue;
		current = current->next;
		i++;
	}
	while (i < _nodesCount);
	return i;
}

// Вычисляет длинну списка (или возвращает кэшированную)
template <typename T>
unsigned Deque<T>::size()
{
	return _nodesCount;
}

// Выводит список на экран
template <typename T>
void Deque<T>::print_all()
{
	if (_nodesCount == 0)
	{
		cout << "Список пуст!" << endl;
		return;
	}
	cout << "Содержание списка:" << endl;
	unsigned i = 0;
	for (Node* current = _head;
	     current != nullptr;
	     current = current->next, i++)
	{
		cout << "[" << i << "]\t" << current->data << endl;
	}
}

// Удаляет все элементы из [start; stop)
template <typename T>
bool Deque<T>::erase(unsigned start, unsigned stop)
{
	if (start == stop) return false;
	for (; start < stop; stop--)
	{
		if (!remove_at(start))
			return false;
	}
	return true;
}

// Удаляет все элементы начиная со start
template <typename T>
bool Deque<T>::erase(unsigned start)
{
	return erase(start, _nodesCount);
}

// Удаляет все элементы
template <typename T>
bool Deque<T>::clear()
{
	return erase(0);
}

// Очистка памяти, удаление списка
template <typename T>
Deque<T>::~Deque()
{
	clear();
}

// Удаляет элемент, сохраняя целосность списка
// previous = nullptr для удаления головного объекта
template <typename T>
void Deque<T>::_remove_node(Node* node, Node* previous)
{
	if (node == nullptr) return;
	if (previous != nullptr)
		previous->next = node->next;
	else
		_head = node->next;
	if (node != nullptr)
		delete node;
}

// Получает Node по индексу
template <typename T>
typename Deque<T>::Node* Deque<T>::_getElement(unsigned index)
{
	if (index >= _nodesCount)
		return nullptr;
	Node* element = _head;
	for (unsigned i = 0; i < index; i++)
		element = element->next;
	return element;
}

// Ищет Node по value
template <typename T>
typename Deque<T>::Node* Deque<T>::_search(T value, Node* element)
{
	Node* current = element;
	if (element == nullptr)
		current = _head;
	for (; current != nullptr; current = current->next)
		if (current->data == value)
			return current;
	return nullptr;
}

// Получает предыдущий Node
template <typename T>
typename Deque<T>::Node* Deque<T>::_getPrevious(Node* node)
{
	Node* current = node;
	Node* previous = nullptr;
	for (Node* element = _head;
	     element != nullptr;
	     element = element->next)
	{
		if (element == current)
			return previous;
		previous = element;
	}
	return nullptr;
}
