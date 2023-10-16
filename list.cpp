#pragma once
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

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
};

template <typename T>
class CyclicList {
private:

	Node<T>* _head;
	Node<T>* _tail;
public:

	CyclicList() :_head(nullptr), _tail(nullptr) {};

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

	T& operator[](int index) {
		Node<T>* head = _head;
		for (int i = 0; i < index; i++) {
			if (head == _tail && index == 0) {
				return *_head->get_data();
			}
			if (head == _tail && i < index) {
				throw runtime_error("In operator[]: index is out of range");
			}
			head = head->get_next();
		}
		return *head->get_data();
	}
};