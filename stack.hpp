/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpottier <hpottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 12:27:50 by hpottier          #+#    #+#             */
/*   Updated: 2021/02/14 13:34:39 by hpottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>
#include "vector.hpp"

namespace ft
{
	template < class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef std::size_t size_type;

		template <class U, class Cont>
		friend bool operator==(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);

		template <class U, class Cont>
		friend bool operator<(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);

	private:
		container_type _cont;

	public:
		explicit stack(const container_type &ctnr = container_type()) : _cont(ctnr) {}

		bool empty() const
		{
			return _cont.empty();
		}

		size_type size() const
		{
			return _cont.size();
		}

		value_type &top()
		{
			return _cont.back();
		}

		const value_type &top() const
		{
			return _cont.back();
		}

		void push(const value_type &val)
		{
			_cont.push_back(val);
		}

		void pop()
		{
			_cont.pop_back();
		}
	};

	template <class T, class Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs._cont == rhs._cont;
	}

	template <class T, class Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs._cont < rhs._cont;
	}

	template <class T, class Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return rhs < lhs;
	}

	template <class T, class Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return !(lhs < rhs);
	}
} // namespace ft

#endif
