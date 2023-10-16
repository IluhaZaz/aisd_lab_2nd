#include "list.cpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <iostream>
using namespace std;
#define EPSILON 0.0001



TEST(First, SwapCheck) {
	CyclicList<int> l;

	Node<int> first (new int(1));

	Node<int> second(new int(2));

	Node<int> third(new int(3));

	Node<int> fourth(new int(4));
	
	l.push_tail(&first);
	l.push_head(&second);
	l.push_head(&third);
	l.push_tail(&fourth);
	cout << l;

	cout << l[0]<< l[1]<< l[2]<< l[3];
}