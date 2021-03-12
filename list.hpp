/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpottier <hpottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:52:02 by hpottier          #+#    #+#             */
/*   Updated: 2021/03/12 17:18:55 by hpottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include <iterator>
#include <cstddef>
#include "reverse_iterator.hpp"
#include "ft_utility.hpp"
#include <iostream>
#include "ft_allocator.hpp"

namespace ft
{
	template < class T, class Alloc = ft::allocator<T> >
	class list
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

	private:
		template <bool IsConst>
		class _list_iterator;
		// class _list_const_iterator;

	public:
		typedef _list_iterator<false> iterator;
		typedef _list_iterator<true> const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

	private:
		typedef struct _snode_base
		{
			struct _snode_base *prev;
			struct _snode_base *next;
		} _node_base;

		typedef struct _snode : public _snode_base
		{
			pointer data;
		} _node;

		typedef struct _snode_end : public _snode_base
		{
			size_type size;
		} _node_end;

		_node_base *_end;
		allocator_type _alloc;

		static inline void _unlink_nodes(_node_base *_f, _node_base *_l)
		{
			_f->prev->next = _l->next;
			_l->next->prev = _f->prev;
		}

		static inline void _link_nodes(_node_base *_p, _node_base *_f, _node_base *_l)
		{
			_p->prev->next = _f;
			_f->prev = _p->prev;
			_p->prev = _l;
			_l->next = _p;
		}

		template <bool IsConst>
		class _list_iterator
		{
			friend class ft::list<T>;

		private:
			_node_base *_pos;

		public:
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef typename std::ptrdiff_t difference_type;
			typedef typename list::value_type value_type;
			typedef typename list::pointer pointer;
			typedef typename list::reference reference;

			_list_iterator() : _pos() {}

		private:
			explicit _list_iterator(_node_base *__x) : _pos(__x) {}

		public:
			// template <bool WasConst, class = typename ft::enable_if<IsConst || !WasConst>::type>
			// _list_iterator(const _list_iterator<WasConst> &__x) : _pos(__x._pos) {}

			_list_iterator(const _list_iterator<false> &__x) : _pos(__x._pos) {}

			bool operator==(const _list_iterator &__x) const
			{
				return _pos == __x._pos;
			}

			bool operator!=(const _list_iterator &__x) const
			{
				return _pos != __x._pos;
			}

			reference operator*()
			{
				return *(static_cast<_node *>(_pos)->data);
			}

			pointer operator->()
			{
				return static_cast<_node *>(_pos)->data;
			}

			_list_iterator<IsConst> &operator++()
			{
				_pos = _pos->next;
				return *this;
			}

			_list_iterator<IsConst> operator++(int)
			{
				_list_iterator<IsConst> tmp = *this;
				_pos = _pos->next;
				return tmp;
			}

			_list_iterator<IsConst> &operator--()
			{
				_pos = _pos->prev;
				return *this;
			}

			_list_iterator<IsConst> operator--(int)
			{
				_list_iterator<IsConst> tmp = *this;
				_pos = _pos->prev;
				return tmp;
			}
		};
/*
		class _list_const_iterator
		{
			friend class ft::list<T>;

		private:
			const _node_base *_pos;

		public:
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef typename std::ptrdiff_t difference_type;
			typedef typename list::value_type value_type;
			typedef typename list::const_pointer pointer;
			typedef typename list::const_reference reference;

			_list_const_iterator() : _pos() {}

		private:
			explicit _list_const_iterator(const _node_base *__x) : _pos(__x) {}

		public:
			_list_const_iterator(const iterator &__x) : _pos(__x._pos) {}

			bool operator==(const _list_const_iterator &__x) const
			{
				return _pos == __x._pos;
			}

			bool operator!=(const _list_const_iterator &__x) const
			{
				return _pos != __x._pos;
			}

			const_reference operator*()
			{
				return *(static_cast<const _node *>(_pos)->data);
			}

			const_pointer operator->()
			{
				return static_cast<const _node *>(_pos)->data;
			}

			_list_const_iterator &operator++()
			{
				_pos = _pos->next;
				return *this;
			}

			_list_const_iterator operator++(int)
			{
				_list_const_iterator tmp = *this;
				_pos = _pos->next;
				return tmp;
			}

			_list_const_iterator &operator--()
			{
				_pos = _pos->prev;
				return *this;
			}

			_list_const_iterator operator--(int)
			{
				_list_const_iterator tmp = *this;
				_pos = _pos->prev;
				return tmp;
			}
		};
*/
	private:
		template <typename Tit>
		static inline Tit _next(Tit ite, size_type n = 1)
		{
			for (size_type x = 0; x < n; ++x)
				++ite;
			return ite;
		};

	public:
		explicit list(const allocator_type &alloc = allocator_type()) : _alloc(alloc)
		{
			_node_end *end = new _node_end;
			end->size = 0;
			_end = static_cast<_node_base *>(end);
			_end->prev = _end;
			_end->next = _end;
		}

		explicit list(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : _alloc(alloc)
		{
			_node_end *end = new _node_end;
			end->size = 0;
			_end = static_cast<_node_base *>(end);
			_end->next = _end;
			_end->prev = _end;
			for (size_type i = 0; i < n; ++i)
				push_back(val);
		}

		template <class InputIterator>
		list(InputIterator first, typename ft::enable_if<ft::is_input_iterator<InputIterator>::value, InputIterator>::type last, const allocator_type &alloc = allocator_type()) : _alloc(alloc)
		{
			_node_end *end = new _node_end;
			end->size = 0;
			_end = static_cast<_node_base *>(end);
			_end->next = _end;
			_end->prev = _end;
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		list(const list &x) : _alloc(x._alloc)
		{
			_node_end *end = new _node_end;
			end->size = 0;
			_end = static_cast<_node_base *>(end);
			_end->next = _end;
			_end->prev = _end;
			iterator it(x._end);
			while ((++it)._pos != x._end)
				push_back(*it);
		}

		list &operator=(const list &x)
		{
			clear();
			iterator it(x._end);
			while ((++it)._pos != x._end)
				push_back(*it);
			return *this;
		}

		~list()
		{
			if (static_cast<_node_end *>(_end)->size != 0)
			{
				_node_base *curr = _end->next->next;
				_alloc.destroy(static_cast<_node *>(curr->prev)->data);
				_alloc.deallocate(static_cast<_node *>(curr->prev)->data, sizeof(value_type));
				::operator delete(static_cast<_node *>(curr->prev));
				while (curr != _end)
				{
					curr = curr->next;
					_alloc.destroy(static_cast<_node *>(curr->prev)->data);
					_alloc.deallocate(static_cast<_node *>(curr->prev)->data, sizeof(value_type));
					::operator delete(static_cast<_node *>(curr->prev));
				}
			}
			::operator delete(_end);
		}

		iterator begin()
		{
			return iterator(_end->next);
		}

		const_iterator begin() const
		{
			return const_iterator(_end->next);
		}

		iterator end()
		{
			return iterator(_end);
		}

		const_iterator end() const
		{
			return const_iterator(_end);
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

		bool empty() const
		{
			return static_cast<_node_end *>(_end)->size == 0 ? true : false;
		}

		size_type size() const
		{
			return static_cast<_node_end *>(_end)->size;
		}

		size_type max_size() const
		{
			return _alloc.max_size();
		}

		reference front()
		{
			return *(static_cast<_node *>(_end->next)->data);
		}

		const_reference front() const
		{
			return *(static_cast<_node *>(_end->next)->data);
		}

		reference back()
		{
			return *(static_cast<_node *>(_end->prev)->data);
		}

		const_reference back() const
		{
			return *(static_cast<_node *>(_end->prev)->data);
		}

		template <class InputIterator>
		typename ft::enable_if<ft::is_input_iterator<InputIterator>::value, void>::type assign(InputIterator first, InputIterator last)
		{
			this->clear();
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		void assign(size_type n, const value_type &val)
		{
			this->clear();
			for (size_type i = 0; i < n; ++i)
				push_back(val);
		}

		void push_front(const value_type &val)
		{
			if (static_cast<_node_end *>(_end)->size != 0)
			{
				_node_base *tmp = _end->next;
				_end->next = static_cast<_node_base *>(::operator new(sizeof(_node)));
				static_cast<_node *>(_end->next)->data = _alloc.allocate(1);
				_alloc.construct(static_cast<_node *>(_end->next)->data, val);
				_end->next->prev = _end;
				_end->next->next = tmp;
				tmp->prev = _end->next;
			}
			else
			{
				_end->next = static_cast<_node_base *>(::operator new(sizeof(_node)));
				static_cast<_node *>(_end->next)->data = _alloc.allocate(1);
				_alloc.construct(static_cast<_node *>(_end->next)->data, val);
				_end->next->prev = _end;
				_end->next->next = _end;
				_end->prev = _end->next;
			}
			++static_cast<_node_end *>(_end)->size;
		}

		void pop_front()
		{
			_node_base *tmp = _end->next->next;
			_alloc.destroy(static_cast<_node *>(_end->next)->data);
			_alloc.deallocate(static_cast<_node *>(_end->next)->data, sizeof(value_type));
			::operator delete(static_cast<_node *>(_end->next));
			if (tmp != _end)
			{
				_end->next = tmp;
				tmp->prev = _end;
			}
			else
			{
				_end->prev = _end;
				_end->next = _end;
			}
			--static_cast<_node_end *>(_end)->size;
		}

		void push_back(const value_type &val)
		{
			if (static_cast<_node_end *>(_end)->size != 0)
			{
				_node_base *tmp = _end->prev;
				_end->prev = static_cast<_node_base *>(::operator new(sizeof(_node)));
				static_cast<_node *>(_end->prev)->data = _alloc.allocate(1);
				_alloc.construct(static_cast<_node *>(_end->prev)->data, val);
				_end->prev->next = _end;
				_end->prev->prev = tmp;
				tmp->next = _end->prev;
			}
			else
			{
				_end->prev = static_cast<_node_base *>(::operator new(sizeof(_node)));
				static_cast<_node *>(_end->prev)->data = _alloc.allocate(1);
				_alloc.construct(static_cast<_node *>(_end->prev)->data, val);
				_end->prev->next = _end;
				_end->prev->prev = _end;
				_end->next = _end->prev;
			}
			++static_cast<_node_end *>(_end)->size;
		}

		void pop_back()
		{
			_node_base *tmp = _end->prev->prev;
			_alloc.destroy(static_cast<_node *>(_end->prev)->data);
			_alloc.deallocate(static_cast<_node *>(_end->prev)->data, sizeof(value_type));
			::operator delete(static_cast<_node *>(_end->prev));
			if (tmp != _end)
			{
				_end->prev = tmp;
				tmp->next = _end;
			}
			else
			{
				_end->prev = _end;
				_end->next = _end;
			}
			--static_cast<_node_end *>(_end)->size;
		}

		iterator insert(iterator position, const value_type &val)
		{
			_node_base *tmp = position._pos->prev;
			position._pos->prev = static_cast<_node_base *>(::operator new(sizeof(_node)));
			static_cast<_node *>(position._pos->prev)->data = _alloc.allocate(1);
			_alloc.construct(static_cast<_node *>(position._pos->prev)->data, val);
			position._pos->prev->next = position._pos;
			position._pos->prev->prev = tmp;
			tmp->next = position._pos->prev;
			++static_cast<_node_end *>(_end)->size;
			return iterator(position._pos->prev);
		}

		void insert(iterator position, size_type n, const value_type &val)
		{
			if (n > 0)
			{
				static_cast<_node_end *>(_end)->size += n;
				_node_base *start = static_cast<_node_base *>(::operator new(sizeof(_node)));
				static_cast<_node *>(start)->data = _alloc.allocate(1);
				_alloc.construct(static_cast<_node *>(start)->data, val);
				_node_base *curr = start;
				for (size_type i = 1; i < n; ++i)
				{
					_node_base *tmp = static_cast<_node_base *>(::operator new(sizeof(_node)));
					static_cast<_node *>(tmp)->data = _alloc.allocate(1);
					_alloc.construct(static_cast<_node *>(tmp)->data, val);
					curr->next = tmp;
					tmp->prev = curr;
					curr = tmp;
				}
				position._pos->prev->next = start;
				start->prev = position._pos->prev;
				curr->next = position._pos;
				position._pos->prev = curr;
			}
		}

		template <class InputIterator>
		typename ft::enable_if<ft::is_input_iterator<InputIterator>::value, void>::type insert(iterator position, InputIterator first, InputIterator last)
		{
			if (first != last)
			{
				_node_base *start = static_cast<_node_base *>(::operator new(sizeof(_node)));
				static_cast<_node *>(start)->data = _alloc.allocate(1);
				_alloc.construct(static_cast<_node *>(start)->data, *first);
				++first;
				_node_base *curr = start;
				while (first != last)
				{
					_node_base *tmp = static_cast<_node_base *>(::operator new(sizeof(_node)));
					static_cast<_node *>(tmp)->data = _alloc.allocate(1);
					_alloc.construct(static_cast<_node *>(tmp)->data, *first);
					curr->next = tmp;
					tmp->prev = curr;
					curr = tmp;
					++first;
					++static_cast<_node_end *>(_end)->size;
				}
				position._pos->prev->next = start;
				start->prev = position._pos->prev;
				curr->next = position._pos;
				position._pos->prev = curr;
			}
		}

		iterator erase(iterator position)
		{
			iterator ret(position._pos->next);
			position._pos->prev->next = position._pos->next;
			position._pos->next->prev = position._pos->prev;
			_alloc.destroy(static_cast<_node *>(position._pos)->data);
			_alloc.deallocate(static_cast<_node *>(position._pos)->data, sizeof(value_type));
			::operator delete(static_cast<_node *>(position._pos));
			--(static_cast<_node_end *>(_end)->size);
			return ret;
		}

		iterator erase(iterator first, iterator last)
		{
			while (first != last)
				erase(first++);
			return last;
		}

		void swap(list &x)
		{
			_node_base *tmp = _end;
			_end = x._end;
			x._end = tmp;
		}

		void resize(size_type n, value_type val = value_type())
		{
			size_type size = static_cast<_node_end *>(_end)->size;
			if (n > size)
				while (size < n)
				{
					push_back(val);
					++size;
				}
			else if (n < size)
				while (size > n)
				{
					pop_back();
					--size;
				}
		}

		void clear()
		{
			erase(begin(), end());
		}

		void splice(iterator position, list &x)
		{
			if (static_cast<_node_end *>(x._end)->size > 0)
			{
				x._end->next->prev = position._pos->prev;
				position._pos->prev->next = x._end->next;
				x._end->next = x._end;
				position._pos->prev = x._end->prev;
				x._end->prev->next = position._pos;
				x._end->prev = x._end;
				static_cast<_node_end *>(_end)->size += static_cast<_node_end *>(x._end)->size;
				static_cast<_node_end *>(x._end)->size = 0;
			}
		}

		void splice(iterator position, list &x, iterator i)
		{
			i._pos->next->prev = i._pos->prev;
			i._pos->prev->next = i._pos->next;
			i._pos->next = position._pos;
			i._pos->prev = position._pos->prev;
			position._pos->prev->next = i._pos;
			position._pos->prev = i._pos;
			++static_cast<_node_end *>(_end)->size;
			--static_cast<_node_end *>(x._end)->size;
		}

		void splice(iterator position, list &x, iterator first, iterator last)
		{
			iterator tmp(first._pos->prev);
			tmp._pos->next = last._pos;
			first._pos->prev = position._pos->prev;
			first._pos->prev->next = first._pos;
			position._pos->prev = last._pos->prev;
			position._pos->prev->next = position._pos;
			last._pos->prev = tmp._pos;
			while (first != position)
			{
				++static_cast<_node_end *>(_end)->size;
				--static_cast<_node_end *>(x._end)->size;
				++first;
			}
		}

		void remove(const value_type &val)
		{
			iterator it(_end);

			while (++it != end())
			{
				if (*it == val)
					erase(it--);
			}
		}

		template <class Predicate>
		void remove_if(Predicate pred)
		{
			iterator it(_end);

			while (++it != end())
			{
				if (pred(*it) == true)
					erase(it--);
			}
		}

		void unique()
		{
			if (size() > 1)
			{
				iterator it(_end->next);
				while (++it != end())
					if (*it == *(static_cast<_node *>(it._pos->prev)->data))
						erase(it--);
			}
		}

		template <class BinaryPredicate>
		void unique(BinaryPredicate binary_pred)
		{
			if (size() > 1)
			{
				iterator it(_end->next);
				while (++it != end())
					if (binary_pred(*it, *(static_cast<_node *>(it._pos->prev)->data)) == true)
						erase(it--);
			}
		}

		void merge(list &x)
		{
			if (&x != this)
			{
				iterator itx(x._end->next);
				iterator it(_end->next);

				while (itx != x.end())
				{
					while (it != end() && (*itx < *it == false))
						++it;
					splice(it, x, itx++);
				}
			}
		}

		template <class Compare>
		void merge(list &x, Compare comp)
		{
			if (&x != this)
			{
				iterator itx(x._end->next);
				iterator it(_end->next);

				while (itx != x.end())
				{
					while (it != end() && (comp(*itx, *it) == false))
						++it;
					splice(it, x, itx++);
				}
			}
		}

		void sort()
		{
			struct MergeSort
			{
				static iterator _sort(iterator f1, iterator e2, size_type n)
				{
					switch (n)
					{
					case 0:
					case 1:
						return f1;
					case 2:
						if (*(--e2) < *f1)
						{
							_node_base *f = e2._pos;
							_unlink_nodes(f, f);
							_link_nodes(f1._pos, f, f);
							return e2;
						}
						return f1;
					}
					size_type n2 = n / 2;
					iterator e1 = _next<iterator>(f1, n2);
					iterator ret = f1 = _sort(f1, e1, n2);
					iterator f2 = e1 = _sort(e1, e2, n - n2);
					if (*f2 < *f1)
					{
						iterator x = _next<iterator>(f2);
						for (; x != e2 && *x < *f1; ++x)
							;
						_node_base *f = f2._pos;
						_node_base *l = x._pos->prev;
						ret = f2;
						e1 = f2 = x;
						_unlink_nodes(f, l);
						x = _next<iterator>(f1);
						_link_nodes(f1._pos, f, l);
						f1 = x;
					}
					else
						++f1;
					while (f1 != e1 && f2 != e2)
					{
						if (*f2 < *f1)
						{
							iterator x = _next<iterator>(f2);
							for (; x != e2 && *x < *f1; ++x)
								;
							_node_base *f = f2._pos;
							_node_base *l = x._pos->prev;
							if (e1 == f2)
								e1 = x;
							f2 = x;
							_unlink_nodes(f, l);
							x = _next<iterator>(f1);
							_link_nodes(f1._pos, f, l);
							f1 = x;
						}
						else
							++f1;
					}
					return ret;
				}
			};
			MergeSort::_sort(begin(), end(), size());
		}

		template <class Compare>
		void sort(Compare comp)
		{
			struct MergeSort
			{
				static iterator _sort(iterator f1, iterator e2, size_type n, Compare comp)
				{
					switch (n)
					{
					case 0:
					case 1:
						return f1;
					case 2:
						if (comp(*(--e2), *f1))
						{
							_node_base *f = e2._pos;
							_unlink_nodes(f, f);
							_link_nodes(f1._pos, f, f);
							return e2;
						}
						return f1;
					}
					size_type n2 = n / 2;
					iterator e1 = _next<iterator>(f1, n2);
					iterator ret = f1 = _sort(f1, e1, n2, comp);
					iterator f2 = e1 = _sort(e1, e2, n - n2, comp);
					if (comp(*f2, *f1))
					{
						iterator x = _next<iterator>(f2);
						for (; x != e2 && comp(*x, *f1); ++x)
							;
						_node_base *f = f2._pos;
						_node_base *l = x._pos->prev;
						ret = f2;
						e1 = f2 = x;
						_unlink_nodes(f, l);
						x = _next<iterator>(f1);
						_link_nodes(f1._pos, f, l);
						f1 = x;
					}
					else
						++f1;
					while (f1 != e1 && f2 != e2)
					{
						if (*f2 < *f1)
						{
							iterator x = _next<iterator>(f2);
							for (; x != e2 && comp(*x, *f1); ++x)
								;
							_node_base *f = f2._pos;
							_node_base *l = x._pos->prev;
							if (e1 == f2)
								e1 = x;
							f2 = x;
							_unlink_nodes(f, l);
							x = _next<iterator>(f1);
							_link_nodes(f1._pos, f, l);
							f1 = x;
						}
						else
							++f1;
					}
					return ret;
				}
			};
			MergeSort::_sort(begin(), end(), size(), comp);
		}

		void reverse()
		{
			iterator it(this->begin());
			_node_base *tmp;
			iterator itmp;
			while (it != end())
			{
				itmp = it++;
				tmp = itmp._pos->next;
				itmp._pos->next = itmp._pos->prev;
				itmp._pos->prev = tmp;
			}
			tmp = _end->next;
			_end->next = _end->prev;
			_end->prev = tmp;
		}
	};

	template <class T>
	bool operator==(const list<T> &lhs, const list<T> &rhs)
	{
		if (lhs.size() == rhs.size())
		{
			typename list<T>::const_iterator lit;
			lit = lhs.begin();
			typename list<T>::const_iterator rit;
			rit = rhs.begin();

			while (lit != lhs.end())
			{
				if (!(*lit == *rit))
					return false;
				++lit;
				++rit;
			}
			return true;
		}
		return false;
	}

	template <class T>
	bool operator!=(const list<T> &lhs, const list<T> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T>
	bool operator<(const list<T> &lhs, const list<T> &rhs)
	{
		typename list<T>::const_iterator lit;
		lit = lhs.begin();
		typename list<T>::const_iterator rit;
		rit = rhs.begin();

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
	bool operator<=(const list<T> &lhs, const list<T> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class T>
	bool operator>(const list<T> &lhs, const list<T> &rhs)
	{
		return rhs < lhs;
	}

	template <class T>
	bool operator>=(const list<T> &lhs, const list<T> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class T>
	void swap(list<T> &x, list<T> &y)
	{
		x.swap(y);
	}
} // namespace ft

#endif
