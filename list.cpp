#pragma once

#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>
#include <cmath>

using namespace std;

template<typename T>
std::uniform_int_distribution<T> getDice(std::true_type)
{
	return std::uniform_int_distribution<T>(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}

template<typename T>
std::uniform_real_distribution<T> getDice(std::false_type)
{
	return std::uniform_real_distribution<T>(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}

template<typename T>
T random()
{
	std::random_device randomDevice;
	std::mt19937_64 generator(randomDevice());
	auto dice = getDice<T>(std::integral_constant<bool, std::numeric_limits<T>::is_integer>());
	return dice(generator);
}

template <typename T>
class Node {
private:

	Node* _next;
	Node* _prev;
	T* _data;
public:

	Node() :_next(nullptr), _prev(nullptr), _data(nullptr) {};
	Node(T* data) :_next(nullptr), _prev(nullptr), _data(data) {};
	Node(Node* next, Node* prev, T* data) :_next(next), _prev(prev), _data(data) {};
	Node(const Node<T>& other) {
		_next = nullptr;
		_prev = nullptr;
		_data = new T(*other._data);
	}

	Node* get_next() {
		return _next;
	}
	Node* get_prev() {
		return _prev;
	}
	T* get_data() {
		return _data;
	}

	void set_next(Node* next) {
		_next = next;
	}
	void set_prev(Node* prev) {
		_prev = prev;
	}
	void set_data(T* data) {
		_data = data;
	}

	~Node() {
		delete _data;
	}

	friend std::ostream& operator<< (std::ostream& out, const Node<T>& n) {
		cout << *n._data;
		return out;
	}

	friend bool operator==(Node<T> a, Node<T> b) {
		if (*a.get_data() != *b.get_data())
			return false;
		return true;
	}

	friend bool operator!=(Node<T> a, Node<T> b) {
		return!(a == b);
	}
};

template <typename T>
class CyclicList {
protected:

	Node<T>* _head;
	Node<T>* _tail;
public:

	CyclicList() :_head(nullptr), _tail(nullptr) {};

	CyclicList(const CyclicList& other) {
		_head = nullptr;
		_tail = nullptr;
		Node<T>* node = other._head;
		this->push_tail(new Node<T>(*node));
		node = node->get_next();
		while (node != other._head) {
			Node<T>* new_node = new Node<T>(*node);
			
			this->push_tail(new_node);
			node = node->get_next();
		}
	}

	CyclicList(int size, T* val) {
		_head = nullptr;
		_tail = nullptr;
		for (int i = 0; i < size; i++) {
			this->push_tail(new Node<T>(new T(val[i])));
		}
	}

	CyclicList(int size) {
		_head = nullptr;
		_tail = nullptr;
		for (int i = 0; i < size; i++) {
			this->push_tail(new Node<T>(new T(random<T>())));
		}
	}


	


	void push_head(Node<T>* head) {
		if (_head == nullptr) {
			_head = head;
			_tail = head;
			head->set_next(head);
			head->set_prev(head);
		}
		else {
			_tail->set_next(head);
			_head->set_prev(head);
			head->set_next(_head);
			head->set_prev(_tail);
			_head = head;
		}
	}

	void push_tail(Node<T>* tail) {
		if (_tail == nullptr) {
			_head = tail;
			_tail = tail;
			tail->set_next(tail);
			tail->set_prev(tail);
		}
		else {
			_head->set_prev(tail);
			_tail->set_next(tail);
			tail->set_next(_head);
			tail->set_prev(_tail);
			_tail = tail;
		}
	}

	void push_head(CyclicList<T> l) {
		l._tail->set_next(_head);
		_head->set_prev(l._tail);
		l._head->set_prev(_tail);
		_tail->set_next(l._head);

		_head = l._head;
	}

	void push_tail(CyclicList<T> l) {
		l._head->set_prev(_tail);
		_tail->set_next(l._head);
		l._tail->set_next(_head);
		_head->set_prev(l._tail);

		_tail = l._tail;
	}

	void pop_head() {
		_tail->set_next(_head->get_next());
		_head->get_next()->set_prev(_tail);
		_head = _head->get_next();
	}

	void pop_tail() {
		_head->set_prev(_tail->get_prev());
		_tail->get_prev()->set_next(_head);
		_tail = _tail->get_prev();
	}

	void delete_node(T val) {
		Node<T>* node = _head;
		int len = this->get_len();
		for (int i = 0; i < len; i++) {
			if (*node->get_data() == val) {
				if (node == _head)
				{
					this->pop_head();
				}
				else if (node == _tail)
				{
					this->pop_tail();
				}
				else
				{
					node->get_prev()->set_next(node->get_next());
					node->get_next()->set_prev(node->get_prev());
				}
			}
			node = node->get_next();
		}
	}
	
	~CyclicList() = default;

	friend std::ostream& operator<< (std::ostream& out, const CyclicList<T>& l) {
		Node<T>* head = l._head;
		while (head != l._tail) {
			cout << *head << " ";
			head = head->get_next();
		}
		cout << *head->get_data() << endl;
		return out;
	}

	Node<T>* operator[](int index) {
		Node<T>* head = _head;
		for (int i = 0; i < index; i++) {
			if (head == _tail && index == 0) {
				return _head;
			}
			if (head == _tail && i < index) {
				throw runtime_error("In operator[]: index is out of range");
			}
			head = head->get_next();
		}
		return head;
	}

	int get_len() {
		if (_head == nullptr)
			return 0;
		int len = 1;
		Node<T>* node = _head->get_next();
		while (node != _head) {
			len += 1;
			node = node->get_next();
		}
		return len;
	}
	
	CyclicList<T>& operator=(CyclicList<T> rhs)
	{
		return rhs;
	}
	
};


class Polynomial : public CyclicList<int> {
public:
	/*
	Polynomial(int size, T* val) {
		_head = nullptr;
		_tail = nullptr;
		for (int i = 0; i < size; i++) {
			this->push_tail(new Node<T>(new T(val[i])));
		}
	}
	*/
	float get_value() {
		float val = 0;
		Node<int>* node = this->_head;
		int len = this->get_len();
		for (int i = 0; i < len; i++) {
			val += pow(10, len - i - 1) * (*node->get_data());
			node = node->get_next();
		}
		return val;
	}
};

template <typename T>
bool operator == (CyclicList<T> a, CyclicList<T> b) {
	if (a.get_len() != b.get_len())
		return false;
	for (int i = 0; i < a.get_len(); i++) {
		if (*a[i] != *b[i])
			return false;
	}
	return true;
}

