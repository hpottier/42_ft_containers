/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpottier <hpottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 11:19:56 by hpottier          #+#    #+#             */
/*   Updated: 2021/03/12 15:27:49 by hpottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILITY_HPP
#define FT_UTILITY_HPP

#include <cstdlib>
#include <new>
#include <cstddef>
#include <utility>

namespace ft
{
	/* remove_const */

	template <typename T>
	struct remove_const
	{
		typedef T type;
	};

	template <typename T>
	struct remove_const<const T>
	{
		typedef T type;
	};

	/* remove_volatile */

	template <typename T>
	struct remove_volatile
	{
		typedef T type;
	};

	template <typename T>
	struct remove_volatile<volatile T>
	{
		typedef T type;
	};

	/* remove_cv */

	template <typename T>
	struct remove_cv
	{
		typedef typename remove_const<typename remove_volatile<T>::type>::type type;
	};

	/* enable_if */

	template <bool B, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	/* is_pointer */

	template <bool V>
	struct _value { static const bool value = V; };

	template <typename T>
	struct is_pointer : public _value<false> {};

	template <typename T>
	struct is_pointer<T *> : public _value<true> {};

	/* is_input_iterator */

	template <class T>
	struct _has_iterator_category
	{
	private:
		struct _yes {char __c1; char __c2;};

		template <class U>
		static char _test(...);
		template <class U>
		static _yes _test(typename U::iterator_category * = NULL);

	public:
		static const bool value = sizeof(_test<T>(0)) == sizeof(_yes);
	};

	template <bool, class T>
	struct _is_input_iterator
	{
		static const bool value = false;
	};

	template <class T>
	struct _is_input_iterator<true, T>
	{
	private:
		struct _yes {char _c1;char _c2;};

		static _yes _test(typename std::input_iterator_tag *);
		static char _test(...);

	public:
		static const bool value = sizeof(_test(static_cast<typename T::iterator_category *>(NULL))) == sizeof(_yes);
	};

	template <class T>
	struct is_input_iterator : public _value<_is_input_iterator<_has_iterator_category<T>::value, T>::value || is_pointer<T>::value> {};

	/* binary_function */

	template <typename T1, typename T2, typename U>
	struct binary_function
	{
		typedef T1 first_argument_type;

		typedef T2 second_argument_type;

		typedef U result_type;
	};

	/* less */

	template <class T>
	struct less
	{
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;

		bool operator()(const T &x, const T &y) const { return x < y; }
	};

	/* pair */

	template <class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair() : first(), second() {}

		template <class U, class V>
		pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {}

		pair(const first_type &a, const second_type &b) : first(a), second(b) {}

		pair &operator=(const pair &pr)
		{
			first = pr.first;
			second = pr.second;
			return *this;
		}

		operator std::pair<T1, T2>()
		{
			return std::pair<T1, T2>(first, second);
		}
	};

	template <class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return rhs < lhs;
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(lhs < rhs);
	}

	/* make_pair */

	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}

} // namespace ft

#endif
