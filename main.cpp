/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpottier <hpottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:55:26 by hpottier          #+#    #+#             */
/*   Updated: 2021/03/11 14:41:13 by hpottier         ###   ########.fr       */
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
	for (NS::list<int>::const_reverse_iterator crit = lst.rbegin(); crit != lst.rend(); ++crit)
		std::cout << *crit << std::endl;
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
	lst_testeur();
	map_testeur();
	vector_testeur();
	stack_testeur();
	queue_testeur();
	std::cout << std::endl;
}
