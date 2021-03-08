/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpottier <hpottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:55:26 by hpottier          #+#    #+#             */
/*   Updated: 2021/03/08 22:03:27 by hpottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "list.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include "map.hpp"
#include <list>
#include <vector>
#include <map>
#include <stack>
#include <queue>

#include <string>
#include <sstream>

#include <ctime>
#include <cstdlib>

#ifndef TFT
#define NS std
#else
#define NS ft
#endif

std::string randstr(const size_t n)
{
	std::string ret;
	static const char tab[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	ret.reserve(n);
	for (size_t i = 0; i < n; ++i)
		ret += tab[rand() % 61];
	return ret;
}

template <class T>
void print(NS::list<NS::list<T> > &lst)
{
	for (typename NS::list<NS::list<T> >::iterator it = lst.begin(); it != lst.end(); it++)
	{
		for (typename NS::list<T>::iterator it2 = it->begin(); it2 != it->end(); it2++)
			std::cout << *it2 << ' ';
		std::cout << '\n';
	}
}

template <class T>
void print(NS::list<T> &lst)
{
	for (typename NS::list<T>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << *it << " ";
	std::cout << '\n';
}

template <class Key, class T>
void print(NS::map<Key, T> &lst)
{
	for (typename NS::map<Key, T>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << it->first << " => " << it->second << '\n';
}

bool mycomparison(double first, double second)
{
	return (int(first) < int(second));
}

namespace ft
{
	std::string to_string(size_t n)
	{
		std::stringstream tmp;

		tmp << n;

		return tmp.str();
	}
} // namespace ft

void testassignmentmap()
{
	NS::map<char, int> first;
	NS::map<char, int> second;

	first['x'] = 8;
	first['y'] = 16;
	first['z'] = 32;

	second = first;			  // second now contains 3 ints
	first = NS::map<char, int>(); // and first is now empty

	std::cout << "Size of first: " << first.size() << '\n';
	std::cout << "Size of second: " << second.size() << '\n';
}

void testinceptionlst()
{
	NS::list<int> test(3, 3);

	NS::list<NS::list<int> > JOHN;
	NS::list<NS::list<int> > BOB(5, test);
	std::cout << "BOB(5, test(test, 5)) : \n";
	NS::list<NS::list<int> > MIKE(BOB);
	print(JOHN);
	print(BOB);
	print(MIKE);
	print(test);

	// CTORs
	std::cout << "\nCTORS\n";
	std::cout << "Empty is empty ? " << std::boolalpha << JOHN.empty() << '\n';
	std::cout << "BOB is empty? " << BOB.empty() << '\n';

	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;

	print(JOHN);
	print(BOB);
	print(MIKE);
	print(test);

	// RESIZE
	size_t bob_resize = 2;
	std::cout << "\nRESIZE\n";
	BOB.resize(bob_resize);
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	print(JOHN);
	print(BOB);
	print(MIKE);
	print(test);

	size_t mike_resize = 9;
	bob_resize = 0;

	BOB.resize(bob_resize);
	std::cout << "BOB is empty now ? " << BOB.empty() << '\n';
	MIKE.resize(mike_resize, test);
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	print(JOHN);
	print(BOB);
	print(MIKE);
	print(test);

	// FRONT / BACK
	std::cout << "\nFRONT / BACK\n";
	std::cout << "front() of MIKE : " << MIKE.front().front() << '\n';
	std::cout << "back() of MIKE : " << MIKE.back().back() << '\n';

	//ASSIGN
	std::cout << "\nASSIGN\n";
	test.assign(3, 17);
	BOB.assign(3, test);
	print(JOHN);
	print(BOB);
	print(MIKE);
	print(test);

	//ASSIGN RANGE
	std::cout << "\nASSIGN RANGE\n";
	NS::list<NS::list<int> > assign_range;
	assign_range.assign(8, test);
	print(assign_range);
	std::cout << "assign_range printed" << std::endl;
	assign_range.assign(BOB.begin(), BOB.end());
	print(assign_range);

	//EMPTY
	std::cout << "\nEMPTY\n";
	std::cout << "BOB is empty ? " << BOB.empty() << '\n';

	//PUSH/POP_BACK
	std::cout << "\nPUSH/POP_BACK\n";
	test.assign(2, 42);
	BOB.push_back(test);
	std::cout << "last elem of BOB : " << BOB.back().back() << '\n';
	BOB.pop_back();
	std::cout << "last elem of BOB : " << BOB.back().back() << '\n';
	print(JOHN);
	print(BOB);
	print(MIKE);
	print(test);

	//INSERT
	std::cout << "\nINSERT\n";
	NS::list<NS::list<int> > insert_in_me;
	for (int i = 0; i < 15; i++)
	{
		NS::list<int> j(2, i);
		insert_in_me.push_back(j);
	}
	print(insert_in_me);

	NS::list<NS::list<int> >::iterator tmp;
	test.assign(23, 19);
	tmp = insert_in_me.begin();
	insert_in_me.insert(tmp, 8, test);
	print(test);
	print(insert_in_me);

	NS::list<NS::list<int> >::const_iterator const_it(insert_in_me.begin());
	std::cout << "Const it.front() : " << std::endl;
	std::cout << (*const_it).front() << '\n';

	//INSERT
	std::cout << "\nINSERT\n";
	NS::list<NS::list<int> > std_insert_in_me;
	for (int i = 0; i < 15; i++)
		std_insert_in_me.push_back(test);
	print(insert_in_me);

	NS::list<NS::list<int> >::iterator std_tmp;
	std_tmp = std_insert_in_me.begin();
	std_insert_in_me.insert(std_tmp, 8, test);
	print(std_insert_in_me);

	//INSERT RANGE
	std::cout << "\nINSERT RANGE\n";
	NS::list<NS::list<int> > insert_bis;
	for (int i = 0; i < 7; i++)
	{
		NS::list<int> j(2, i * 3);
		insert_bis.push_back(j);
	}
	print(insert_bis);

	insert_bis.insert(insert_bis.begin(), insert_in_me.begin(), insert_in_me.end());
	print(insert_bis);

	//ERASE
	std::cout << "\nERASE\n";
	NS::list<NS::list<int> > erase_in_me;
	for (int i = 0; i < 15; i++)
	{
		NS::list<int> j(1, i);
		erase_in_me.push_back(j);
	}
	print(erase_in_me);

	erase_in_me.erase(erase_in_me.begin());
	print(erase_in_me);
	erase_in_me.erase(erase_in_me.begin(), ++(erase_in_me.begin()));
	print(erase_in_me);

	//SWAP
	std::cout << "\nSWAP\n";
	BOB.swap(MIKE);
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	print(JOHN);
	print(BOB);
	print(MIKE);
	print(test);

	MIKE.swap(JOHN);
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	print(JOHN);
	print(BOB);
	print(MIKE);
	print(test);

	//CLEAR
	std::cout << "\nCLEAR\n";
	JOHN.clear();
	MIKE.clear();
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	print(JOHN);
	print(BOB);
	print(MIKE);
	print(test);

	//NON MEMBER Functions
	std::cout << "\nNON MEMBER functions\n";
	swap(BOB, MIKE);
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	print(JOHN);
	print(BOB);
	print(MIKE);
	print(test);

	//RELATIONAL OPERATORS
	std::cout << "\nRELATIONAL OPERATORS\n";
	NS::list<NS::list<int> > MIKE_2(MIKE);
	std::cout << "MIKE and BOB are equal ? " << (MIKE == BOB) << '\n';
	std::cout << "MIKE and MIKE_2 are equal ? " << (MIKE == MIKE_2) << '\n';
	print(JOHN);
	print(BOB);
	print(MIKE);
	print(test);

	NS::list<NS::list<int> > real;
	real.assign(5, test);
	print(real);

	std::cout << std::endl;
}

void teststringlst()
{

	NS::list<std::string> JOHN;
	NS::list<std::string> BOB(5, "Hello");
	std::cout << "BOB(5, 8) : ";
	print(BOB);
	NS::list<std::string> MIKE(BOB);

	// CTORs
	std::cout << "\nCTORS\n";
	std::cout << "Empty is empty ? " << std::boolalpha << JOHN.empty() << '\n';
	std::cout << "BOB is empty? " << BOB.empty() << '\n';

	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;

	print(MIKE);
	print(JOHN);
	print(BOB);

	// RESIZE
	size_t bob_resize = 2;
	std::cout << "\nRESIZE\n";
	BOB.resize(bob_resize);
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;

	size_t mike_resize = 9;
	bob_resize = 0;

	BOB.resize(bob_resize);
	std::cout << "BOB is empty now ? " << BOB.empty() << '\n';
	print(MIKE);
	print(JOHN);
	print(BOB);
	MIKE.resize(mike_resize, "juste some random std::string");
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	print(MIKE);
	print(JOHN);
	print(BOB);

	// FRONT / BACK
	std::cout << "\nFRONT / BACK\n";
	std::cout << "front() of MIKE : " << MIKE.front() << '\n';
	std::cout << "back() of MIKE : " << MIKE.back() << '\n';

	//ASSIGN
	std::cout << "\nASSIGN\n";
	BOB.assign(42, "James BOND");
	print(MIKE);
	print(JOHN);
	print(BOB);

	//ASSIGN RANGE
	std::cout << "\nASSIGN RANGE\n";
	NS::list<std::string> assign_range;
	assign_range.assign(8, "Covfefe");
	assign_range.assign(BOB.begin(), BOB.end());
	print(MIKE);
	print(JOHN);
	print(BOB);

	//EMPTY
	std::cout << "\nEMPTY\n";
	std::cout << "BOB is empty ? " << BOB.empty() << '\n';
	print(MIKE);
	print(JOHN);
	print(BOB);

	//PUSH/POP_BACK
	std::cout << "\nPUSH/POP_BACK\n";
	BOB.push_back("My name is Bond");
	std::cout << "last elem of BOB : " << BOB.back() << '\n';
	BOB.pop_back();
	std::cout << "last elem of BOB : " << BOB.back() << '\n';
	print(MIKE);
	print(JOHN);
	print(BOB);

	//INSERT
	std::cout << "\nINSERT\n";
	NS::list<std::string> insert_in_me;
	for (size_t i = 0; i < 15; i++)
		insert_in_me.push_back(ft::to_string(i) + " I love hbaudet\n");
	std::cout << "after push_back, before at\n";

	NS::list<std::string>::iterator tmp;
	tmp = insert_in_me.begin();
	insert_in_me.insert(tmp, 8, "Norminet");
	print(insert_in_me);
	NS::list<std::string>::const_iterator const_it(insert_in_me.begin());
	std::cout << "Const it : " << std::endl;
	std::cout << *const_it << '\n';
	//	*const_it = 89; // Does not compile because it's a const_iterator

	//INSERT
	std::cout << "\nINSERT\n";
	NS::list<std::string> std_insert_in_me;
	for (size_t i = 0; i < 15; i++)
		std_insert_in_me.push_back(ft::to_string(i) + " 42 ");

	print(std_insert_in_me);
	NS::list<std::string>::iterator std_tmp;
	std_tmp = std_insert_in_me.begin();
	std_insert_in_me.insert(std_tmp, 8, "Why are you reading this!?");
	print(std_insert_in_me);

	//INSERT RANGE
	std::cout << "\nINSERT RANGE\n";
	NS::list<std::string> insert_bis;
	for (size_t i = 0; i < 7; i++)
		insert_bis.push_back(ft::to_string(3 * i));
	print(insert_bis);

	insert_bis.insert(insert_bis.begin(), insert_in_me.begin(), insert_in_me.end());

	//ERASE
	std::cout << "\nERASE\n";
	NS::list<std::string> erase_in_me;
	for (size_t i = 0; i < 15; i++)
		erase_in_me.push_back(ft::to_string(2 * i));
	std::cout << '\n';

	erase_in_me.erase(erase_in_me.begin());

	erase_in_me.erase(erase_in_me.begin(), erase_in_me.begin());
	std::cout << '\n';

	//SWAP
	std::cout << "\nSWAP\n";
	BOB.swap(MIKE);
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	print(MIKE);
	print(JOHN);
	print(BOB);

	MIKE.swap(JOHN);
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	print(MIKE);
	print(JOHN);
	print(BOB);

	//CLEAR
	std::cout << "\nCLEAR\n";
	JOHN.clear();
	MIKE.clear();
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	print(MIKE);
	print(JOHN);
	print(BOB);

	//NON MEMBER Functions
	std::cout << "\nNON MEMBER functions\n";
	swap(BOB, MIKE);
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	print(MIKE);
	print(JOHN);
	print(BOB);

	//RELATIONAL OPERATORS
	std::cout << "\nRELATIONAL OPERATORS\n";
	NS::list<std::string> MIKE_2(MIKE);
	std::cout << "MIKE and BOB are equal ? " << (MIKE == BOB) << '\n';
	std::cout << "MIKE and MIKE_2 are equal ? " << (MIKE == MIKE_2) << '\n';
	print(MIKE);
	print(JOHN);
	print(BOB);

	NS::list<std::string> real;
	real.assign(5, "foo");
	for (NS::list<std::string>::iterator it = real.begin(); it != real.end(); it++)
		std::cout << *it << " ";
	std::cout << '\n';

	std::cout << std::endl;
}

int testmergelst()
{
	NS::list<double> first, second;

	first.push_back(3.1);
	first.push_back(2.2);
	first.push_back(2.9);

	second.push_back(3.7);
	second.push_back(7.1);
	second.push_back(1.4);

	first.sort();
	second.sort();

	std::cout << "first contains:";
	for (NS::list<double>::iterator it = first.begin(); it != first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "second contains:";
	for (NS::list<double>::iterator it = second.begin(); it != second.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	first.merge(second);

	std::cout << "first contains:";
	for (NS::list<double>::iterator it = first.begin(); it != first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	// (second is now empty)

	second.push_back(2.1);

	first.merge(second, mycomparison);

	std::cout << "first contains:";
	for (NS::list<double>::iterator it = first.begin(); it != first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	return 0;
}

int testlstsplice()
{
	{
		NS::list<int> one(5, 42);
		NS::list<int> two(one);
		NS::list<int> three(two.begin(), two.end());

		print(one);
		print(two);
		print(three);
		std::cout << one.size() << '\n';
		std::cout << two.size() << '\n';
		std::cout << three.size() << '\n';

		one.push_back(48);
		one.push_back(5);
		one.push_back(1);
		one.push_back(896475);
		print(one);
		print(two);
		print(three);
		std::cout << one.size() << '\n';
		std::cout << two.size() << '\n';
		std::cout << three.size() << '\n';

		two.push_back(1654);
		two.push_back(0);
		two.push_back(-9);
		two.push_back(8666);
		print(one);
		print(two);
		print(three);
		std::cout << one.size() << '\n';
		std::cout << two.size() << '\n';
		std::cout << three.size() << '\n';

		NS::list<int>::iterator it;
		NS::list<int>::iterator rev;

		it = one.begin();

		it++;
		it++;

		three.splice(++(three.begin()), one, it);
		print(one);
		print(two);
		print(three);
		std::cout << one.size() << '\n';
		std::cout << two.size() << '\n';
		std::cout << three.size() << '\n';

		rev = one.end();
		rev--;
		rev--;
		rev--;
		rev--;

		three.splice(three.end(), one, ++(one.begin()), rev);
		print(one);
		print(two);
		print(three);

		three.splice(three.begin(), two, two.begin(), two.end());
		print(one);
		print(two);
		print(three);
		std::cout << one.size() << '\n';
		std::cout << two.size() << '\n';
		std::cout << three.size() << '\n';
	}
	{
		NS::list<int> mylist1, mylist2;
		NS::list<int>::iterator it;

		// set some initial values:
		for (int i = 1; i <= 4; ++i)
			mylist1.push_back(i); // mylist1: 1 2 3 4

		for (int i = 1; i <= 3; ++i)
			mylist2.push_back(i * 10); // mylist2: 10 20 30

		it = mylist1.begin();
		++it; // points to 2

		mylist1.splice(it, mylist2); // mylist1: 1 10 20 30 2 3 4
									 // mylist2 (empty)
									 // "it" still points to 2 (the 5th element)
		std::cout << "AAAAAA 1"
				  << "\n";
		print(mylist1);
		std::cout << mylist2.size() << "\n";

		mylist2.splice(mylist2.begin(), mylist1, it);
		// mylist1: 1 10 20 30 3 4
		// mylist2: 2
		// "it" is now invalid.
		std::cout << "AAAAAA 2"
				  << "\n";
		print(mylist2);

		it = mylist1.begin();
		for (int i = 0; i < 3; i++)
			it++; // "it" points now to 30

		mylist1.splice(mylist1.begin(), mylist1, it, mylist1.end());
		// mylist1: 30 3 4 1 10 20

		std::cout << "mylist1 contains:";
		for (it = mylist1.begin(); it != mylist1.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';

		std::cout << "mylist2 contains:";
		for (it = mylist2.begin(); it != mylist2.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	return (0);
}

void testreverseiteratorlst()
{

	NS::list<float> lst;

	for (int i = 0; i < 7; i++)
		lst.push_back(i * 3.75f);

	NS::list<float>::reverse_iterator rit(lst.begin());
	NS::list<float>::reverse_iterator rit2(lst.end());

	rit--;
	rit2--;
	while (rit != rit2)
	{
		std::cout << *rit << ' ' << '\n';
		--rit;
	}
}

void lst_testeur()
{
	NS::list<int> lst;

	lst.push_back(12);
	lst.push_back(7);
	lst.push_back(35);
	lst.push_back(12);
	lst.push_back(52);
	lst.push_back(17);
	lst.push_back(12);
	lst.push_back(1);
	lst.push_back(40);
	lst.push_back(26);
	lst.push_back(86);
	lst.push_back(13);
	lst.push_back(2);
	lst.push_back(50);
	lst.push_back(85);
	lst.push_back(1);
	lst.push_back(56);
	lst.push_back(88);
	lst.push_back(11);
	lst.push_back(10);
	lst.pop_back();
	lst.pop_front();
	lst.push_front(12);
	lst.push_back(10);

	NS::list<int>::iterator it;
	it = lst.begin();
	std::cout << "print lst: "
			  << "<->";
	while (it != lst.end())
	{
		std::cout << '|' << *it << "|<->";
		++it;
	}
	std::cout << std::endl;

	lst.sort();
	it = lst.begin();
	std::cout << "print lst after sort: "
			  << "<->";
	while (it != lst.end())
	{
		std::cout << '|' << *it << "|<->";
		++it;
	}
	std::cout << std::endl;
	lst.clear();
	for (int i = 0; i < 5000; ++i)
	{
		lst.push_back(rand() % 42845);
		lst.push_front(rand() % 41134);
	}
	lst.sort();
	NS::list<int>::reverse_iterator rit(lst.rbegin());
	while (rit != lst.rend())
	{
		std::cout << *rit << std::endl;
		++rit;
	}
	// for (NS::list<int>::const_reverse_iterator crit = lst.rbegin(); crit != lst.rend(); ++crit)
	// 	std::cout << *crit << std::endl;
	std::cout << std::endl;

	lst.assign(8, 42);

	std::vector<int> test;
	test.push_back(98);
	test.push_back(-45664);
	test.push_back(643);
	test.push_back(-8841);
	test.push_back(0);
	test.push_back(10);
	test.push_back(643);
	test.push_back(10);

	lst.assign(test.begin(), test.end());

	lst.unique();

	NS::list<int> tlst(32, 42);
	for (NS::list<int>::iterator xit = tlst.begin(); xit != tlst.end(); ++xit)
		std::cout << *xit << std::endl;
	NS::list<int> ttlst(test.begin(), test.end());
	for (NS::list<int>::iterator xit = ttlst.begin(); xit != ttlst.end(); ++xit)
		std::cout << *xit << std::endl;

	for (int i = 0; i < 500; ++i)
	{
		lst.push_back(rand() % 42845);
		lst.push_front(rand() % 41134);
	}

	NS::list<int> ylst;

	for (int i = 0; i < 500; ++i)
	{
		ylst.push_back(rand() % 42845);
		ylst.push_front(rand() % 41134);
	}

	NS::list<int>::iterator itins(lst.begin());
	for (int i = 0; i < 52; ++i)
		++itins;
	lst.insert(itins, test.begin(), test.end());
	std::cout << *(lst.insert(itins, 48)) << std::endl;

	ylst.swap(lst);
	lst.resize(lst.size() - 8);

	it = ylst.begin();
	while (it != ylst.end())
	{
		std::cout << *it << std::endl;
		++it;
	}

	it = lst.begin();
	++it;
	++it;
	++it;
	lst.splice(it, ylst);
	lst.push_front(42);
	lst.remove(42);

	rit = lst.rbegin();
	while (rit != lst.rend())
	{
		std::cout << *rit << std::endl;
		++rit;
	}
	std::cout << std::endl;

	NS::list<std::string> lstr;
	for (int i = 0; i < 5000; ++i)
	{
		lstr.push_back(randstr(rand() % 17 + 1));
		lstr.push_front(randstr(rand() % 17 + 1));
	}
	lstr.reverse();

	NS::list<std::string>::iterator itinstr(lstr.begin());
	for (int i = 0; i < 52; ++i)
		++itinstr;
	lstr.insert(itinstr, 42, "Bonjour je suis un str.");

	NS::list<std::string>::const_iterator cit(lstr.begin());

	while (cit != lstr.end())
	{
		std::cout << *cit << std::endl;
		++cit;
	}
	std::cout << std::endl;
}

void map_testeur()
{
	NS::map<std::string, int> m;

	m.insert(NS::make_pair<std::string, int>("D", 42));
	m.insert(NS::make_pair<std::string, int>("V", -15));
	m.insert(NS::make_pair<std::string, int>("E", 684));
	m.insert(NS::make_pair<std::string, int>("A", -43518));
	m.insert(NS::make_pair<std::string, int>("B", -4215));
	m.insert(NS::make_pair<std::string, int>("Z", 6871));
	m.insert(NS::make_pair<std::string, int>("G", 0));
	m.insert(NS::make_pair<std::string, int>("R", -15));
	m.insert(NS::make_pair<std::string, int>("T", 68768415));
	m.insert(NS::make_pair<std::string, int>("U", -144));
	m.insert(NS::make_pair<std::string, int>("H", -7852));

	NS::map<std::string, int> mbis(m);

	NS::map<std::string, int>::iterator it(m.insert(NS::make_pair<std::string, int>("E", 123)).first);
	std::cout << (*it).second << std::endl
			  << std::endl;

	it = m.begin();
	while (it != m.end())
	{
		std::cout << (*it).first << '	' << (*it).second << std::endl;
		++it;
	}
	std::cout << std::endl;

	NS::map<std::string, int>::reverse_iterator rit(m.rbegin());
	while (rit != m.rend())
	{
		std::cout << (*rit).first << '	' << (*rit).second << std::endl;
		++rit;
	}
	std::cout << std::endl;

	std::cout << "m size == " << m.size() << std::endl;

	mbis.erase(mbis.find("D"), mbis.end());
	// m.erase(m.find("D"), m.find("Z"));
	// m.erase(m.find("B"), m.find("V"));
	// m.erase(m.find("A"), m.find("V"));
	// m.erase(m.find("Z"));
	// m.erase(m.find("A"));
	m.erase(m.find("G"));
	m.erase(m.find("D"), m.find("R"));

	std::cout << (*m.upper_bound("T")).first << std::endl;
	std::cout << (*m.lower_bound("T")).first << std::endl;
	std::cout << std::endl;

	m["N"] = 58;
	m["N"] = 332;

	it = m.end();
	while (--it != m.begin())
		std::cout << (*it).first << '	' << (*it).second << std::endl;
	std::cout << (*it).first << '	' << (*it).second << std::endl;

	it = mbis.end();
	while (--it != mbis.begin())
		std::cout << (*it).first << '	' << (*it).second << std::endl;
	std::cout << (*it).first << '	' << (*it).second << std::endl;

	std::cout << "m size == " << m.size() << std::endl;

	// m.clear();
	m.erase(m.begin(), m.end());
	std::cout << "m size == " << m.size() << std::endl
			  << std::endl;

	for (int i = 0; i < 5000; ++i)
		m.insert(NS::make_pair<std::string, int>(randstr(rand() % 17 + 1), rand() % 1024));

	NS::map<std::string, int>::const_iterator cit(m.begin());
	while (cit != m.end())
	{
		std::cout << (*cit).first << '	' << (*cit).second << std::endl;
		++cit;
	}
	std::cout << std::endl;
}

void vector_testeur()
{
	NS::vector<int> vec;

	vec.push_back(2);
	vec.push_back(-48);
	vec.push_back(841);
	vec.push_back(11654164);
	vec.push_back(51);
	vec.push_back(0);
	vec.push_back(-8768451);
	vec.pop_back();
	vec.pop_back();
	vec.push_back(16543);
	vec.push_back(54612);
	vec.push_back(6164);
	vec.pop_back();
	vec.push_back(123);
	vec.push_back(-42);
	vec.push_back(124834);
	vec.push_back(31);
	vec.push_back(32);
	vec.push_back(4535);

	vec.reserve(72);
	vec.resize(72, 42);

	std::cout << vec.at(10) << std::endl;
	std::cout << vec[10] << std::endl;
	std::cout << vec.front() << std::endl;
	std::cout << vec.back() << std::endl;

	NS::vector<int>::iterator it(vec.begin());
	while (it != vec.end())
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::cout << std::endl;

	vec.clear();

	for (int i = 0; i < 5000; ++i)
		vec.push_back(rand() % 354351);
	std::cout << "SIZE = " << vec.size() << std::endl;
	vec.assign(8, 42);
	std::cout << "SIZE = " << vec.size() << std::endl;

	std::list<int> test;
	test.push_back(98);
	test.push_back(-45664);
	test.push_back(643);
	test.push_back(-8841);
	test.push_back(0);
	test.push_back(10);

	vec.assign(test.begin(), test.end());
	std::cout << "SIZE = " << vec.size() << std::endl;

	NS::vector<int> tvec(32, 42);
	for (NS::vector<int>::iterator xit = tvec.begin(); xit != tvec.end(); ++xit)
		std::cout << *xit << std::endl;
	NS::vector<int> ttvec(test.begin(), test.end());
	for (NS::vector<int>::iterator xit = ttvec.begin(); xit != ttvec.end(); ++xit)
		std::cout << *xit << std::endl;

	for (int i = 0; i < 500; ++i)
		vec.push_back(rand() % 354351);

	NS::vector<int>::iterator itins(vec.begin());
	for (int i = 0; i < 52; ++i)
		++itins;
	vec.insert(itins, test.begin(), test.end());
	std::cout << "SIZE = " << vec.size() << std::endl;
	std::cout << *(vec.insert(itins, 48)) << std::endl;
	std::cout << "SIZE = " << vec.size() << std::endl;

	NS::vector<int>::reverse_iterator rit(vec.rbegin());
	while (rit != vec.rend())
	{
		std::cout << *rit << std::endl;
		++rit;
	}
	std::cout << std::endl;

	NS::vector<std::string> svec;

	for (int i = 0; i < 5000; ++i)
		svec.push_back(randstr(rand() % 17 + 1));

	NS::vector<std::string>::iterator itinstr(svec.begin());
	for (int i = 0; i < 52; ++i)
		++itinstr;
	svec.insert(itinstr, 42, "Bonjour je suis un str.");

	NS::vector<std::string>::const_iterator sit(svec.begin());
	while (sit != svec.end())
	{
		std::cout << *sit << std::endl;
		++sit;
	}
	std::cout << std::endl;
}

void stack_testeur()
{
	NS::stack<int> st;

	st.push(42);
	st.push(-4);
	st.push(0);
	st.push(42210);
	st.pop();
	st.push(-8654);
	st.push(12);
	st.push(1);
	st.pop();
	st.push(-468445);
	st.push(5410);
	st.push(123);
	st.pop();
	st.push(545);

	std::cout << st.top() << '	' << st.size() << std::endl;

	st.pop();

	std::cout << st.top() << '	' << st.size() << std::endl;

	NS::stack<int> st2 = st;

	std::cout << (st2 == st) << std::endl;
	st2.pop();
	std::cout << (st2 == st) << std::endl;
	std::cout << (st2 < st) << std::endl;

	while (st.empty() != true)
		st.pop();
	std::cout << st.size() << std::endl
			  << std::endl;
}

void queue_testeur()
{
	NS::queue<int> qu;

	qu.push(42);
	qu.push(-4);
	qu.push(0);
	qu.push(42210);
	qu.pop();
	qu.push(-8654);
	qu.push(12);
	qu.push(1);
	qu.pop();
	qu.push(-468445);
	qu.push(5410);
	qu.push(123);
	qu.pop();
	qu.push(545);

	std::cout << qu.front() << '	' << qu.back() << '	' << qu.size() << std::endl;

	qu.pop();

	std::cout << qu.front() << '	' << qu.back() << '	' << qu.size() << std::endl;

	NS::queue<int> qu2 = qu;

	std::cout << (qu2 == qu) << std::endl;
	qu2.pop();
	std::cout << (qu2 == qu) << std::endl;
	std::cout << (qu2 > qu) << std::endl;

	while (qu.empty() != true)
		qu.pop();
	std::cout << qu.size() << std::endl
			  << std::endl;
}

int main()
{
	// srand(clock());
	// lst_testeur();
	// map_testeur();
	// vector_testeur();
	// stack_testeur();
	// queue_testeur();
	// testlstsplice();
	// testmergelst();
	// testreverseiteratorlst();
	// teststringlst();
	// testinceptionlst();
	// testassignmentmap();
	std::cout << std::endl;
}
