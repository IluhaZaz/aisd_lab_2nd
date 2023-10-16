#pragma once

#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

class string {
private:

	char* _data;
public:

	string() :_data(nullptr) {};
	string(char* data) :_data(data) {};

	friend string operator+(const string& first, const string& other) {
		return string(strcat(first._data, other._data));
	}
};

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
private:

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
		_tail->get_next(l.head);

		_head = l._head;
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

	friend bool operator==(CyclicList<T> a, CyclicList<T> b) {
		if (a.get_len() != b.get_len())
			return false;
		for (int i = 0; i < a.get_len(); i++) {
			if (*a[i] != *b[i])
				return false;
		}
		return true;
	}

};