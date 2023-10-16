#include "list.cpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <iostream>
using namespace std;
#define EPSILON 0.0001



TEST(CyclicListTests, First) {
	CyclicList<int> l;
	l.push_head(new Node<int>(new int(3)));
	l.push_head(new Node<int>(new int(2)));
	l.push_head(new Node<int>(new int(1)));
	cout << l;

	EXPECT_EQ(l.get_len(), 3);
	EXPECT_EQ(2, *l[1]->get_data());

	l[0]->set_data(new int(88));

	EXPECT_EQ(*l[0]->get_data(), 88);

	CyclicList<int> l2(l);

	EXPECT_EQ(l, l2);
}