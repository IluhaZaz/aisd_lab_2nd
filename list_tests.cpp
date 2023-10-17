#include "list.cpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <iostream>
using namespace std;
#define EPSILON 0.0001



TEST(CyclicListTests, First) {
	CyclicList<int> l;
	l.push_head(new Node<int>(new int(3)));

	EXPECT_EQ(l.get_len(), 1);

	l.push_head(new Node<int>(new int(2)));
	l.push_head(new Node<int>(new int(1)));
	cout << l;

	EXPECT_EQ(l.get_len(), 3);
	EXPECT_EQ(2, *l[1]->get_data());

	l[0]->set_data(new int(88));

	EXPECT_EQ(*l[0]->get_data(), 88);

	CyclicList<int> l2(l);

	EXPECT_TRUE(l == l2);
	for (int i = 0; i < l.get_len(); i++) {
		EXPECT_FALSE(l[i] == l2[i]);
	}

	CyclicList<int> l3;
	l3.push_head(new Node<int>(new int(3)));
	l3.push_head(new Node<int>(new int(2)));
	l3.push_head(new Node<int>(new int(0)));

	EXPECT_FALSE(l3 == l2);

	l2.push_head(l3);
	cout << l2;
	l.push_tail(l3);
	cout << l;
	l.pop_head();
	cout << l;
	l.pop_tail();
	cout << l;
	l.push_head(new Node<int>(new int(2)));
	cout << l;
	l.delete_node(2);
	cout << l;
	l = l2;
	cout << l;
}