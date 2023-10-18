#include "list.cpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <iostream>
using namespace std;
#define EPSILON 0.0001

TEST(CyclicListTests, ConstructorAndOperatorCheck) {
	CyclicList<int> l;
	l.push_tail(new Node<int>(new int(1)));
	l.push_tail(new Node<int>(new int(2)));
	l.push_tail(new Node<int>(new int(3)));

	CyclicList<int> l2(3, new int[3] {1, 2, 3});
	EXPECT_EQ(l, l2);

	CyclicList<int> l3(l);
	EXPECT_EQ(l, l3);
	for (int i = 0; i < l.get_len(); i++) {
		EXPECT_FALSE(l2[i] == l3[i]);
	}

	CyclicList<int> l4 = l;
	EXPECT_EQ(l, l4);
	for (int i = 0; i < l.get_len(); i++) {
		EXPECT_FALSE(l[i] == l4[i]);
	}
}

TEST(CyclicListTests, MethodsCheck) {
	CyclicList<int> l(4, new int[4] {1, 2, 3, 4});
	CyclicList<int> l2(3, new int[3] {1, 2, 3});
	l.pop_tail();
	EXPECT_EQ(l, l2);

	CyclicList<int> l3(2, new int[2] {2, 3});
	l2.pop_head();
	EXPECT_EQ(l3, l2);

	CyclicList<int> l4(5, new int[5] {2, 2, 3, 4, 2});
	CyclicList<int> l5(2, new int[2] {3, 4});
	l4.delete_node(2);
	EXPECT_EQ(l4, l5);
}

TEST(PolynomynalTests, Check) {
	Polynomial p(5);
	cout << p;
	Polynomial p2;
	p2.push_tail((new Node<int>(new int(1))));
	p2.push_tail((new Node<int>(new int(2))));
	p2.push_tail((new Node<int>(new int(3))));
	Polynomial p3(p2);
	for (int i = 0; i < p2.get_len(); i++) {
		EXPECT_FALSE(p2[i] == p3[i]);
		EXPECT_EQ(*p2[i]->get_data(), *p3[i]->get_data());
	}

	EXPECT_EQ(123, p3.get_value());

//	Polynomial p4(3, new int[3] {1, 2, 3});
}