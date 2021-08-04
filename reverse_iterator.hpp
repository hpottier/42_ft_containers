/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpottier <hpottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:30:24 by hpottier          #+#    #+#             */
/*   Updated: 2021/03/12 17:04:25 by hpottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "ft_utility.hpp"

namespace ft
{
	template <typename T>
	class _reverse_iterator_base
	{
	public:
		typedef typename enable_if<_has_iterator_category<T>::value, T>::type iterator_type;
		typedef typename iterator_type::iterator_category iterator_category;
		typedef typename iterator_type::value_type value_type;
		typedef typename iterator_type::difference_type difference_type;
		typedef typename iterator_type::pointer pointer;
		typedef typename iterator_type::reference reference;
	};

	template <typename T>
	class _reverse_iterator_base<T *>
	{
	public:
		typedef T *iterator_type;
		typedef typename std::random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef typename std::ptrdiff_t difference_type;
		typedef T *pointer;
		typedef T &reference;
	};

	template <class Iterator>
	class reverse_iterator
	{
	public:
		typedef typename _reverse_iterator_base<Iterator>::iterator_type iterator_type;
		typedef typename _reverse_iterator_base<Iterator>::iterator_category iterator_category;
		typedef typename _reverse_iterator_base<Iterator>::value_type value_type;
		typedef typename _reverse_iterator_base<Iterator>::difference_type difference_type;
		typedef typename _reverse_iterator_base<Iterator>::pointer pointer;
		typedef typename _reverse_iterator_base<Iterator>::reference reference;

	private:
		iterator_type _it;

	public:
		reverse_iterator() {}

		explicit reverse_iterator(iterator_type it) : _it(--it) {}

		template <class IteratorType>
		reverse_iterator(const reverse_iterator<IteratorType> &rev_it) : _it(rev_it.base()) {}

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

		reverse_iterator operator+(difference_type __n) const
		{
			return reverse_iterator(_it - __n);
		}

		reverse_iterator &operator+=(difference_type __n)
		{
			_it -= __n;
			return *this;
		}

		reverse_iterator operator-(difference_type __n) const
		{
			return reverse_iterator(_it + __n);
		}

		reverse_iterator &operator-=(difference_type __n)
		{
			_it += __n;
			return *this;
		}

		reference operator[](difference_type __n) const
		{
			return *(*this + __n);
		}
	};
} // namespace ft

#endif
