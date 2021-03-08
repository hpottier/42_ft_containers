/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpottier <hpottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:30:24 by hpottier          #+#    #+#             */
/*   Updated: 2021/03/08 21:46:36 by hpottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "ft_utility.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{
	public:
		typedef Iterator iterator_type;
		typedef typename iterator_type::iterator_category iterator_category;
		typedef typename iterator_type::value_type value_type;
		typedef typename iterator_type::difference_type difference_type;
		typedef typename iterator_type::pointer pointer;
		typedef typename iterator_type::reference reference;

	private:
		iterator_type _it;

	public:
		reverse_iterator() {}

		explicit reverse_iterator(iterator_type it) : _it(--it) {}

		reverse_iterator(const reverse_iterator &rev_it) : _it(rev_it._it) {}

		bool operator==(const reverse_iterator &__x) const
		{
			return _it == __x._it;
		}

		bool operator!=(const reverse_iterator &__x) const
		{
			return _it != __x._it;
		}

		iterator_type base() const
		{
			return _it;
		}

		reference operator*()
		{
			return _it.operator*();
		}

		pointer operator->()
		{
			return &(operator*());
		}

		reverse_iterator &operator++()
		{
			--_it;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			_it--;
			return *this;
		}

		reverse_iterator &operator--()
		{
			++_it;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			_it++;
			return *this;
		}
	};
} // namespace ft

#endif
