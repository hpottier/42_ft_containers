/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpottier <hpottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 08:59:15 by hpottier          #+#    #+#             */
/*   Updated: 2021/03/22 12:53:37 by hpottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iterator>
#include <cstddef>
#include <stdexcept>
#include "reverse_iterator.hpp"
#include "ft_utility.hpp"
#include "ft_allocator.hpp"

namespace ft
{
	template < class T, class Alloc = ft::allocator<T> >
	class vector
	{
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename std::size_t size_type;
		typedef typename std::ptrdiff_t difference_type;

	public:
		typedef pointer iterator;
		typedef const_pointer const_iterator;
		typedef typename std::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

	private:
		pointer _tab;
		size_type _size;
		size_type _capacity;
		allocator_type _alloc;

		void vecDelete(pointer p, size_type n)
		{
			for (size_type x = 0; x < n; ++x)
				_alloc.destroy(&(p[x]));
			_alloc.deallocate(p, n);
		}

		pointer vecNew(size_type n)
		{
			pointer ret = _alloc.allocate(n);
			for (size_type x = 0; x < n; ++x)
				_alloc.construct(&(ret[x]), value_type());
			return ret;
		}

	public:
		explicit vector(const allocator_type &alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc)
		{
			_tab = vecNew(0);
		}

		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type()) : _size(n), _capacity(n), _alloc(alloc)
		{
			_tab = vecNew(n);
			for (size_type x = 0; x < n; ++x)
				_tab[x] = val;
		}

		template <class InputIterator>
		vector(InputIterator first, typename ft::enable_if<ft::is_input_iterator<InputIterator>::value, InputIterator>::type last,
			   const allocator_type &alloc = allocator_type()) : _size(0), _alloc(alloc)
		{
			for (InputIterator tmp(first); tmp != last; ++tmp)
				++_size;
			_tab = vecNew(_size);
			_capacity = _size;
			for (size_type x = 0; x < _size; ++x)
			{
				_tab[x] = *first;
				++first;
			}
		}

		vector(const vector &x) : _size(x._size), _capacity(x._capacity), _alloc(x._alloc)
		{
			_tab = vecNew(_capacity);
			for (size_type i = 0; i < _size; ++i)
				_tab[i] = x._tab[i];
		}

		vector &operator=(const vector &x)
		{
			vecDelete(_tab, _capacity);
			_size = x._size;
			_capacity = x._capacity;
			_alloc = x._alloc;
			_tab = vecNew(_capacity);
			for (size_type i = 0; i < _size; ++i)
				_tab[i] = x._tab[i];
			return *this;
		}

		~vector()
		{
			vecDelete(_tab, _capacity);
		}

	private:
		void modCapacity(size_type n)
		{
			pointer tmp = vecNew(n);
			for (size_type x = 0; x < _size && x < _capacity; ++x)
				tmp[x] = _tab[x];
			vecDelete(_tab, _capacity);
			_tab = tmp;
			_capacity = n;
		}

	public:
		iterator begin()
		{
			return iterator(_tab);
		}

		const_iterator begin() const
		{
			return const_iterator(_tab);
		}

		iterator end()
		{
			return iterator(_tab + _size);
		}

		const_iterator end() const
		{
			return const_iterator(_tab + _size);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(this->end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(this->end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(this->begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(this->begin());
		}

		size_type size() const
		{
			return _size;
		}

		size_type max_size() const
		{
			return _alloc.max_size();
		}

		void resize(size_type n, value_type val = value_type())
		{
			if (n < _size)
				_size = n;
			else
			{
				if (n > _capacity)
					modCapacity(n + _capacity);
				while (_size < n)
				{
					_tab[_size] = val;
					++_size;
				}
			}
		}

		size_type capacity() const
		{
			return _capacity;
		}

		bool empty() const
		{
			if (_size == 0)
				return true;
			return false;
		}

		void reserve(size_type n)
		{
			if (n > this->max_size())
				throw std::length_error("vector::reserve");
			if (n > _capacity)
				modCapacity(n);
		}

		reference operator[](size_type n)
		{
			return _tab[n];
		}

		const_reference operator[](size_type n) const
		{
			return _tab[n];
		}

		reference at(size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("vector::at");
			return _tab[n];
		}

		const_reference at(size_type n) const
		{
			if (n >= _size)
				throw std::out_of_range("vector::at");
			return _tab[n];
		}

		reference front()
		{
			return _tab[0];
		}

		const_reference front() const
		{
			return _tab[0];
		}

		reference back()
		{
			return _tab[_size - 1];
		}

		const_reference back() const
		{
			return _tab[_size - 1];
		}

		template <class InputIterator>
		typename ft::enable_if<ft::is_input_iterator<InputIterator>::value, void>::type assign(InputIterator first, InputIterator last)
		{
			this->clear();
			_size = 0;
			for (InputIterator tmp(first); tmp != last; ++tmp)
				++_size;
			if (_size > _capacity)
			{
				vecDelete(_tab, _capacity);
				_tab = vecNew(_size);
				_capacity = _size;
			}
			for (_size = 0; first != last; ++_size)
			{
				_tab[_size] = *first;
				++first;
			}
		}

		void assign(size_type n, const value_type &val)
		{
			this->clear();
			if (n > _capacity)
			{
				vecDelete(_tab, _capacity);
				_tab = vecNew(n);
				_capacity = n;
			}
			for (_size = 0; _size < n; ++_size)
				_tab[_size] = val;
		}

		void push_back(const value_type &val)
		{
			if (_size + 1 > _capacity)
				modCapacity(_capacity == 0 ? 1 : _capacity * 2);
			_tab[_size] = val;
			++_size;
		}

		void pop_back()
		{
			--_size;
		}

		iterator insert(iterator position, const value_type &val)
		{
			size_type pos = position - _tab;
			if (_size + 1 > _capacity)
				modCapacity(_capacity == 0 ? 2 : _capacity * 2);
			for (iterator tmp = end(); tmp != _tab + pos; --tmp)
				*tmp = *(tmp - 1);
			*(_tab + pos) = val;
			++_size;
			return iterator(_tab + pos);
		}

		void insert(iterator position, size_type n, const value_type &val)
		{
			size_type pos = position - _tab;
			if (_size + n > _capacity)
				modCapacity(n + _capacity * 2);
			for (iterator tmp(&_tab[_size + n - 1]); tmp != _tab + pos + n - 1; --tmp)
				*tmp = *(tmp - n);
			_size += n;
			while (n)
			{
				*(_tab + pos) = val;
				++pos;
				--n;
			}
		}

		template <class InputIterator>
		typename ft::enable_if<ft::is_input_iterator<InputIterator>::value, void>::type insert(iterator position, InputIterator first, InputIterator last)
		{
			size_type pos = position - _tab;
			size_type n = 0;
			for (InputIterator tmp(first); tmp != last; ++tmp)
				++n;
			if (_size + n > _capacity)
				modCapacity(n + _capacity * 2);
			for (iterator tmp(&_tab[_size + n]); tmp != _tab + pos + n - 1; --tmp)
				*tmp = *(tmp - n);
			_size += n;
			while (first != last)
			{
				*(_tab + pos) = *first;
				++pos;
				++first;
			}
		}

		iterator erase(iterator position)
		{
			iterator ret(position);
			while (position != end())
			{
				*position = *(position + 1);
				++position;
			}
			--_size;
			return ret;
		}

		iterator erase(iterator first, iterator last)
		{
			iterator ret(first);
			pointer tmp = last._elem;
			size_type i = _size;

			while (last._elem != _tab + i)
			{
				*(first._elem) = *(last._elem);
				++first;
				++last;
				if (first._elem <= tmp)
					--_size;
			}
			if (first._elem <= tmp)
				--_size;
			return ret;
		}

		void swap(vector &x)
		{
			pointer tmp = _tab;
			_tab = x._tab;
			x._tab = tmp;
			size_type tmp2 = _size;
			_size = x._size;
			x._size = tmp2;
			tmp2 = _capacity;
			_capacity = x._capacity;
			x._capacity = tmp2;
		}

		void clear()
		{
			_size = 0;
		}
	};

	template <class T>
	bool operator==(const vector<T> &lhs, const vector<T> &rhs)
	{
		if (lhs.size() == rhs.size())
		{
			typename vector<T>::const_iterator lit(lhs.begin());
			typename vector<T>::const_iterator rit(rhs.begin());
			while (lit != lhs.end())
			{
				if (*lit != *rit)
					return false;
				++lit;
				++rit;
			}
			return true;
		}
		return false;
	}

	template <class T>
	bool operator!=(const vector<T> &lhs, const vector<T> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T>
	bool operator<(const vector<T> &lhs, const vector<T> &rhs)
	{
		typename vector<T>::const_iterator lit = lhs.begin();
		typename vector<T>::const_iterator rit = rhs.begin();

		while (lit != lhs.end())
		{
			if (rit == rhs.end() || *rit < *lit)
				return false;
			else if (*lit < *rit)
				return true;
			++lit;
			++rit;
		}
		return rit != rhs.end();
	}

	template <class T>
	bool operator<=(const vector<T> &lhs, const vector<T> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class T>
	bool operator>(const vector<T> &lhs, const vector<T> &rhs)
	{
		return rhs < lhs;
	}

	template <class T>
	bool operator>=(const vector<T> &lhs, const vector<T> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class T>
	void swap(vector<T> &x, vector<T> &y)
	{
		x.swap(y);
	}
} // namespace ft

#endif
