/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpottier <hpottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 12:37:56 by hpottier          #+#    #+#             */
/*   Updated: 2021/02/27 14:03:23 by hpottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>
#include "list.hpp"

namespace ft
{
	template < class T, class Container = ft::list<T> >
	class queue
	{
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef std::size_t size_type;

		template <class U, class Cont>
		friend bool operator==(const queue<U, Cont> &lhs, const queue<U, Cont> &rhs);

		template <class U, class Cont>
		friend bool operator<(const queue<U, Cont> &lhs, const queue<U, Cont> &rhs);

	private:
		container_type _cont;

	public:
		explicit queue(const container_type &ctnr = container_type()) : _cont(ctnr) {}

		bool empty() const
		{
			return _cont.empty();
		}

		size_type size() const
		{
			return _cont.size();
		}

		value_type &front()
		{
			return _cont.front();
		}

		const value_type &front() const
		{
			return _cont.front();
		}

		value_type &back()
		{
			return _cont.back();
		}

		const value_type &back() const
		{
			return _cont.back();
		}

		void push(const value_type &val)
		{
			_cont.push_back(val);
		}

		void pop()
		{
			_cont.pop_front();
		}
	};

	template <class T, class Container>
	bool operator==(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
	{
		return lhs._cont == rhs._cont;
	}

	template <class T, class Container>
	bool operator!=(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool operator<(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
	{
		return lhs._cont < rhs._cont;
	}

	template <class T, class Container>
	bool operator<=(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Container>
	bool operator>(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
	{
		return rhs < lhs;
	}

	template <class T, class Container>
	bool operator>=(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
	{
		return !(lhs < rhs);
	}
} // namespace ft

#endif
