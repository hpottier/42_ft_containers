/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpottier <hpottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 13:14:27 by hpottier          #+#    #+#             */
/*   Updated: 2021/03/05 11:41:34 by hpottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <iterator>
#include <cstddef>
#include "reverse_iterator.hpp"
#include "ft_utility.hpp"

namespace ft
{
	template < class Key, class T, class Compare = ft::less<Key>, class Alloc = ft::allocator< ft::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::value_type value_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename std::size_t size_type;
		typedef typename std::ptrdiff_t difference_type;

		class value_compare
		{
			friend class map;

		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {}

		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;

			bool operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
		};

	private:
		class _map_iterator;
		class _map_const_iterator;

	public:
		typedef _map_iterator iterator;
		typedef _map_const_iterator const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

	private:
		struct _node
		{
			value_type data;
			_node *origin;
			_node *left;
			_node *right;
		};

		allocator_type _alloc;
		_node *_end;
		size_type _size;
		key_compare _comp;

		class _map_iterator
		{
			friend class ft::map<Key, T, Compare, Alloc>;

		private:
			_node *_pos;
			key_compare _compit;
			_node *_mend;

		public:
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef typename std::ptrdiff_t difference_type;
			typedef typename map::value_type value_type;
			typedef typename map::pointer pointer;
			typedef typename map::reference reference;

			_map_iterator() : _pos() {}

		private:
			explicit _map_iterator(_node *__x, key_compare __comp, _node *__end) : _pos(__x), _compit(__comp), _mend(__end) {}

		public:
			bool operator==(const _map_iterator &__x) const
			{
				return _pos == __x._pos;
			}

			bool operator!=(const _map_iterator &__x) const
			{
				return _pos != __x._pos;
			}

			reference operator*()
			{
				return _pos->data;
			}

			pointer operator->()
			{
				return &(_pos->data);
			}

			_map_iterator &operator++()
			{
				if (_pos->right != NULL)
				{
					if (_pos->right->left == NULL || _pos->right == _mend)
						_pos = _pos->right;
					else
						_pos = ft::map<Key, T, Compare, Alloc>::getleftmostnode(_pos->right);
				}
				else if (_pos->origin != NULL)
				{
					_node *og = _pos;
					_pos = _pos->origin;
					while (_compit(og->data.first, _pos->data.first) == false)
						_pos = _pos->origin;
				}
				return *this;
			}

			_map_iterator operator++(int)
			{
				_map_iterator tmp = *this;
				if (_pos->right != NULL)
				{
					if (_pos->right->left == NULL || _pos->right == _mend)
						_pos = _pos->right;
					else
						_pos = ft::map<Key, T, Compare, Alloc>::getleftmostnode(_pos->right);
				}
				else if (_pos->origin != NULL)
				{
					_node *og = _pos;
					_pos = _pos->origin;
					while (_compit(og->data.first, _pos->data.first) == false)
						_pos = _pos->origin;
				}
				return tmp;
			}

			_map_iterator &operator--()
			{
				if (_pos == _mend)
				{
					if (_mend->left != NULL)
						_pos = _mend->left;
					return *this;
				}
				else if (_pos == _mend->right)
				{
					_pos = _mend;
					return *this;
				}
				if (_pos->left != NULL)
				{
					if (_pos->left->right == NULL)
						_pos = _pos->left;
					else
						_pos = ft::map<Key, T, Compare, Alloc>::getrightmostnode(_pos->left, _mend);
				}
				else if (_pos->origin != NULL)
				{
					_node *og = _pos;
					_pos = _pos->origin;
					while (_compit(_pos->data.first, og->data.first) == false)
						_pos = _pos->origin;
				}
				return *this;
			}

			_map_iterator operator--(int)
			{
				_map_iterator tmp = *this;
				if (_pos == _mend)
				{
					if (_mend->left != NULL)
						_pos = _mend->left;
					return tmp;
				}
				else if (_pos == _mend->right)
				{
					_pos = _mend;
					return *tmp;
				}
				if (_pos->left != NULL)
				{
					if (_pos->left->right == NULL)
						_pos = _pos->left;
					else
						_pos = ft::map<Key, T, Compare, Alloc>::getrightmostnode(_pos->left, _mend);
				}
				else if (_pos->origin != NULL)
				{
					_node *og = _pos;
					_pos = _pos->origin;
					while (_compit(_pos->data.first, og->data.first) == false)
						_pos = _pos->origin;
				}
				return tmp;
			}
		};

		class _map_const_iterator
		{
			friend class ft::map<Key, T, Compare, Alloc>;

		private:
			const _node *_pos;
			key_compare _compit;
			_node *_mend;

		public:
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef typename std::ptrdiff_t difference_type;
			typedef typename map::value_type value_type;
			typedef typename map::const_pointer pointer;
			typedef typename map::const_reference reference;

			_map_const_iterator() : _pos() {}

		private:
			explicit _map_const_iterator(const _node *__x, key_compare __comp, _node *__end) : _pos(__x), _compit(__comp), _mend(__end) {}

		public:
			_map_const_iterator(const iterator &__x) : _pos(__x._pos), _compit(__x._compit), _mend(__x._mend) {}

			bool operator==(const _map_const_iterator &__x) const
			{
				return _pos == __x._pos;
			}

			bool operator!=(const _map_const_iterator &__x) const
			{
				return _pos != __x._pos;
			}

			reference operator*()
			{
				return _pos->data;
			}

			pointer operator->()
			{
				return &(_pos->data);
			}

			_map_const_iterator &operator++()
			{
				if (_pos->right != NULL)
				{
					if (_pos->right->left == NULL || _pos->right == _mend)
						_pos = _pos->right;
					else
						_pos = ft::map<Key, T, Compare, Alloc>::getleftmostnode(_pos->right);
				}
				else if (_pos->origin != NULL)
				{
					const _node *og = _pos;
					_pos = _pos->origin;
					while (_compit(og->data.first, _pos->data.first) == false)
						_pos = _pos->origin;
				}
				return *this;
			}

			_map_const_iterator operator++(int)
			{
				_map_iterator tmp = *this;
				if (_pos->right != NULL)
				{
					if (_pos->right->left == NULL || _pos->right == _mend)
						_pos = _pos->right;
					else
						_pos = ft::map<Key, T, Compare, Alloc>::getleftmostnode(_pos->right);
				}
				else if (_pos->origin != NULL)
				{
					const _node *og = _pos;
					_pos = _pos->origin;
					while (_compit(og->data.first, _pos->data.first) == false)
						_pos = _pos->origin;
				}
				return tmp;
			}

			_map_const_iterator &operator--()
			{
				if (_pos == _mend)
				{
					if (_mend->left != NULL)
						_pos = _mend->left;
					return *this;
				}
				else if (_pos == _mend->right)
				{
					_pos = _mend;
					return *this;
				}
				if (_pos->left != NULL)
				{
					if (_pos->left->right == NULL)
						_pos = _pos->left;
					else
						_pos = ft::map<Key, T, Compare, Alloc>::getrightmostnode(_pos->left, _mend);
				}
				else if (_pos->origin != NULL)
				{
					const _node *og = _pos;
					_pos = _pos->origin;
					while (_compit(_pos->data.first, og->data.first) == false)
						_pos = _pos->origin;
				}
				return *this;
			}

			_map_const_iterator operator--(int)
			{
				_map_iterator tmp = *this;
				if (_pos == _mend)
				{
					if (_mend->left != NULL)
						_pos = _mend->left;
					return tmp;
				}
				else if (_pos == _mend->right)
				{
					_pos = _mend;
					return *tmp;
				}
				if (_pos->left != NULL)
				{
					if (_pos->left->right == NULL)
						_pos = _pos->left;
					else
						_pos = ft::map<Key, T, Compare, Alloc>::getrightmostnode(_pos->left, _mend);
				}
				else if (_pos->origin != NULL)
				{
					const _node *og = _pos;
					_pos = _pos->origin;
					while (_compit(_pos->data.first, og->data.first) == false)
						_pos = _pos->origin;
				}
				return tmp;
			}
		};

		_node *search(const key_type &k, _node *curr)
		{
			if (curr != NULL)
			{
				bool ret = _comp(curr->data.first, k);
				if (ret == false && _comp(k, curr->data.first) == false)
					return curr;
				else if (ret == false)
					return this->search(k, curr->left);
				else if (curr->right != _end)
					return this->search(k, curr->right);
			}
			return NULL;
		}

		void clear(_node *curr)
		{
			if (curr->left != NULL)
				this->clear(curr->left);
			if (curr->right != NULL && curr->right != _end)
				this->clear(curr->right);
			_alloc.destroy(&(curr->data));
			::operator delete(curr);
		}

		static _node *getleftmostnode(_node *curr)
		{
			if (curr->left != NULL)
				return getleftmostnode(curr->left);
			return curr;
		}

		static _node *getrightmostnode(_node *curr, _node *end)
		{
			if (curr->right != NULL && curr->right != end)
				return getrightmostnode(curr->right, end);
			return curr;
		}

		size_type getheight(_node *curr, size_type n)
		{
			size_type r = 0;
			size_type l = 0;

			if (curr != NULL && curr != _end)
			{
				if (curr->right != _end)
					r = getheight(curr->right, n + 1);
				l = getheight(curr->left, n + 1);
				return l < r ? r : l;
			}
			return n - 1;
		}

		_node *rotleft(_node *xnode, _node *znode, int &xbal, int zbal)
		{
			xnode->right = znode->left;
			if (xnode->right != NULL)
				xnode->right->origin = xnode;
			znode->left = xnode;
			znode->origin = xnode->origin;
			xnode->origin = znode;
			if (znode->origin != NULL)
			{
				if (znode->origin->left == xnode)
					znode->origin->left = znode;
				else
					znode->origin->right = znode;
			}
			else
				_end->origin = znode;

			if (zbal == 0)
				xbal = zbal - 1;
			else
				xbal = 0;
			return znode;
		}

		_node *rotright(_node *xnode, _node *znode, int &xbal, int zbal)
		{
			xnode->left = znode->right;
			if (xnode->left != NULL)
				xnode->left->origin = xnode;
			znode->right = xnode;
			znode->origin = xnode->origin;
			xnode->origin = znode;
			if (znode->origin != NULL)
			{
				if (znode->origin->left == xnode)
					znode->origin->left = znode;
				else
					znode->origin->right = znode;
			}
			else
				_end->origin = znode;

			if (zbal == 0)
				xbal = zbal + 1;
			else
				xbal = 0;
			return znode;
		}

		_node *rotrl(_node *xnode, _node *znode, int &xbal, int zbal)
		{
			int ybal = zbal;
			int tmp = getheight(znode->left->right, 1) - getheight(znode->left->left, 1);

			return rotleft(xnode, rotright(znode, znode->left, ybal, tmp), xbal, ybal);
		}

		_node *rotlr(_node *xnode, _node *znode, int &xbal, int zbal)
		{
			int ybal = zbal;
			int tmp = getheight(znode->right->right, 1) - getheight(znode->right->left, 1);

			return rotright(xnode, rotleft(znode, znode->right, ybal, tmp), xbal, ybal);
		}

		void balance(_node *curr, _node *old, size_type old_h, int old_bal)
		{
			int bal;
			size_type h;

			if (curr->left == old)
			{
				h = getheight(curr->right, 1);
				bal = h - old_h;
				if (old_h < h)
					old = curr->right;
			}
			else
			{
				h = getheight(curr->left, 1);
				bal = old_h - h;
				if (old_h < h)
					old = curr->left;
			}
			if (old_h < h)
				old_bal = getheight(old->right, 1) - getheight(old->left, 1);
			if (bal < -1 || bal > 1)
			{
				if (old == curr->right && old_bal >= 0)
					curr = rotleft(curr, old, bal, old_bal);
				else if (old == curr->left && old_bal <= 0)
					curr = rotright(curr, old, bal, old_bal);
				else if (old == curr->right && old_bal < 0)
					curr = rotrl(curr, old, bal, old_bal);
				else if (old == curr->left && old_bal > 0)
					curr = rotlr(curr, old, bal, old_bal);
			}
			if (curr->origin != NULL)
				balance(curr->origin, curr, (h < old_h ? old_h : h) + 1, bal);
		}

	public:
		explicit map(const key_compare &comp = key_compare(),
					 const allocator_type &alloc = allocator_type()) : _alloc(alloc),
																	   _size(0),
																	   _comp(comp)
		{
			_end = new _node;
			_end->origin = NULL;
			_end->left = NULL;
			_end->right = NULL;
		}

		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()) : _alloc(alloc),
															  _size(0),
															  _comp(comp)
		{
			_end = new _node;
			_end->origin = NULL;
			_end->left = NULL;
			_end->right = NULL;
			this->insert(first, last);
		}

		map(const map &x) : _alloc(x._alloc), _size(0), _comp(x._comp)
		{
			_end = new _node;
			_end->origin = NULL;
			_end->left = NULL;
			_end->right = NULL;
			this->insert(x.begin(), x.end());
		}

		map &operator=(const map &x)
		{
			_alloc = x._alloc;
			_size = 0;
			_comp = x._comp;
			_end = new _node;
			_end->origin = NULL;
			_end->left = NULL;
			_end->right = NULL;
			this->insert(x.begin(), x.end());
		}

		~map()
		{
			if (_size != 0)
				this->clear(_end->origin);
			::operator delete(_end);
		}

		iterator begin()
		{
			return iterator(_end->right, _comp, _end);
		}

		const_iterator begin() const
		{
			return const_iterator(_end->right, _comp, _end);
		}

		iterator end()
		{
			return iterator(_end, _comp, _end);
		}

		const_iterator end() const
		{
			return const_iterator(_end, _comp, _end);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(iterator(_end->left, _comp, _end));
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(const_iterator(_end->left, _comp, _end));
		}

		reverse_iterator rend()
		{
			return reverse_iterator(iterator(_end, _comp, _end));
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(const_iterator(_end, _comp, _end));
		}

		bool empty() const
		{
			return _size == 0 ? true : false;
		}

		size_type size() const
		{
			return _size;
		}

		size_type max_size() const
		{
			return _alloc.max_size();
		}

		mapped_type &operator[](const key_type &k)
		{
			return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second;
		}

		ft::pair<iterator, bool> insert(const value_type &val)
		{
			if (_end->origin == NULL)
			{
				_end->origin = new _node;
				_end->origin->origin = NULL;
				_end->origin->left = NULL;
				_end->origin->right = _end;
				_end->right = _end->origin;
				_end->left = _end->origin;
				_alloc.construct(&(_end->origin->data), val);
				++_size;
				return ft::pair<iterator, bool>(iterator(_end->origin, _comp, _end), true);
			}
			_node *curr = this->search(val.first, _end->origin);
			if (curr != NULL)
				return ft::pair<iterator, bool>(iterator(curr, _comp, _end), false);
			curr = _end->origin;
			while (true)
			{
				if (_comp(val.first, curr->data.first))
				{
					if (curr->left == NULL)
					{
						curr->left = new _node;
						curr->left->origin = curr;
						if (_comp(val.first, _end->right->data.first) == true)
							_end->right = curr->left;
						curr = curr->left;
						curr->right = NULL;
						curr->left = NULL;
						break;
					}
					curr = curr->left;
				}
				else
				{
					if (curr->right == NULL)
					{
						curr->right = new _node;
						curr->right->origin = curr;
						curr = curr->right;
						curr->right = NULL;
						curr->left = NULL;
						break;
					}
					else if (curr->right == _end)
					{
						curr->right = new _node;
						curr->right->origin = curr;
						curr = curr->right;
						curr->right = _end;
						curr->left = NULL;
						_end->left = curr;
						break;
					}
					curr = curr->right;
				}
			}
			++_size;
			_alloc.construct(&(curr->data), val);
			this->balance(curr->origin, curr, 1, 0);
			return ft::pair<iterator, bool>(iterator(curr, _comp, _end), true);
		}

		iterator insert(iterator position, const value_type &val)
		{
			(void)position;
			return iterator(this->search(this->insert(val).first), _comp, _end);
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				this->insert(*first);
				++first;
			}
		}

		void erase(iterator position)
		{
			_node *og = position._pos->origin;
			if (position._pos->left == NULL && position._pos->right == NULL)
			{
				if (og != NULL)
				{
					if (og->left == position._pos)
						og->left = NULL;
					else
						og->right = NULL;
				}
				else
				{
					_end->left = NULL;
					_end->origin = NULL;
				}
				if (_end->right == position._pos)
					_end->right = og;
				_alloc.destroy(&(position._pos->data));
				::operator delete(position._pos);
				--_size;
				if (og != NULL)
				{
					if (og->right != NULL)
						this->balance(og, og->right, getheight(og->right, 1), getheight(og->right->right, 1) - getheight(og->right->left, 1));
					else
						this->balance(og, og->right, 0, 0);
				}
				return;
			}
			else if (position._pos->left == NULL && position._pos->right != NULL)
			{
				if (og == NULL)
				{
					_end->origin = position._pos->right;
					_end->left = _end->origin;
					_end->right = _end->origin;
					position._pos->right->origin = NULL;
					_alloc.destroy(&(position._pos->data));
					::operator delete(position._pos);
					--_size;
					return;
				}
				if (og->left == position._pos)
					og->left = position._pos->right;
				else
					og->right = position._pos->right;
				if (position._pos->right != _end)
					position._pos->right->origin = og;
				if (_end->right == position._pos)
					_end->right = getleftmostnode(og);
				else if (_end->left == position._pos)
					_end->left = getrightmostnode(og, _end);
				_alloc.destroy(&(position._pos->data));
				::operator delete(position._pos);
				--_size;
				if (og != NULL)
				{
					if (og->right != NULL)
						this->balance(og, og->right, getheight(og->right, 1), getheight(og->right->right, 1) - getheight(og->right->left, 1));
					else
						this->balance(og, og->right, 0, 0);
				}
				return;
			}
			else if (position._pos->left != NULL && position._pos->right == NULL)
			{
				if (og->left == position._pos)
					og->left = position._pos->left;
				else
					og->right = position._pos->left;
				position._pos->left->origin = og;
				if (_end->right == position._pos)
					_end->right = getleftmostnode(og);
				_alloc.destroy(&(position._pos->data));
				::operator delete(position._pos);
				--_size;
				if (og != NULL)
				{
					if (og->right != NULL)
						this->balance(og, og->right, getheight(og->right, 1), getheight(og->right->right, 1) - getheight(og->right->left, 1));
					else
						this->balance(og, og->right, 0, 0);
				}
				return;
			}
			else
			{
				if (position._pos->right == _end)
				{
					_node *curr = position._pos->left;
					while (curr->right != NULL)
						curr = curr->right;
					curr->right = _end;
					_end->left = curr;
					if (og != NULL)
					{
						if (og->left == position._pos)
							og->left = position._pos->left;
						else
							og->right = position._pos->left;
					}
					else
						_end->origin = position._pos->left;
					position._pos->left->origin = og;
					curr = position._pos->left;
					_alloc.destroy(&(position._pos->data));
					::operator delete(position._pos);
					--_size;
					if (og != NULL)
					{
						if (og->right != NULL)
							this->balance(og, og->right, getheight(og->right, 1), getheight(og->right->right, 1) - getheight(og->right->left, 1));
						else
							this->balance(og, og->right, 0, 0);
					}
					return;
				}
				else
				{
					_node *curr = getleftmostnode(position._pos->right);
					_alloc.destroy(&(position._pos->data));
					if (curr != position._pos->right)
					{
						curr->origin->left = curr->right;
						if (curr->right != NULL)
							curr->right->origin = curr->origin;
						curr->right = position._pos->right;
						curr->right->origin = curr;
					}
					curr->origin = position._pos->origin;
					if (curr->origin != NULL)
					{
						if (curr->origin->left == position._pos)
							curr->origin->left = curr;
						else
							curr->origin->right = curr;
					}
					else
						_end->origin = curr;
					curr->left = position._pos->left;
					if (curr->left != NULL)
						curr->left->origin = curr;
					::operator delete(position._pos);
					--_size;
					if (og != NULL)
					{
						if (og->right != NULL)
							this->balance(og, og->right, getheight(og->right, 1), getheight(og->right->right, 1) - getheight(og->right->left, 1));
						else
							this->balance(og, og->right, 0, 0);
					}
					return;
				}
			}
		}

		size_type erase(const key_type &k)
		{
			_node *tmp = search(k, _end->origin);
			if (tmp == NULL)
				return 0;
			erase(iterator(tmp, _comp, _end));
			return 1;
		}

		void erase(iterator first, iterator last)
		{
			while (first != last)
				erase(first++);
		}

		void swap(map &x)
		{
			_node *tmp;
			tmp = _end;
			_end = x._end;
			x._end = tmp;

			size_type tmp2;
			tmp2 = _size;
			_size = x._size;
			x._size = tmp2;

			key_compare tmp3;
			tmp3 = _comp;
			_comp = x._comp;
			x._comp = tmp3;
		}

		void clear()
		{
			if (_size != 0)
			{
				this->clear(_end->origin);
				_end->origin = NULL;
				_end->left = NULL;
				_end->right = NULL;
			}
			_size = 0;
		}

		key_compare key_comp() const
		{
			return _comp;
		}

		value_compare value_comp() const
		{
			return value_comp(_comp);
		}

		iterator find(const key_type &k)
		{
			_node *ret = this->search(k, _end->origin);
			if (ret == NULL)
				return this->end();
			return iterator(ret, _comp, _end);
		}

		const_iterator find(const key_type &k) const
		{
			_node *ret = this->search(k, _end->origin);
			if (ret == NULL)
				return this->end();
			return const_iterator(ret, _comp, _end);
		}

		size_type count(const key_type &k) const
		{
			if (this->search(k, _end->origin) != NULL)
				return 1;
			return 0;
		}

		iterator lower_bound(const key_type &k)
		{
			if (_size == 0)
				return iterator(_end, _comp, _end);
			iterator it(this->begin());
			while (it != this->end() && _comp((*it).first, k) == true)
				++it;
			return it;
		}

		const_iterator lower_bound(const key_type &k) const
		{
			if (_size == 0)
				return const_iterator(_end, _comp, _end);
			const_iterator it(this->begin());
			while (it != this->end() && _comp((*it).first, k) == true)
				++it;
			return it;
		}

		iterator upper_bound(const key_type &k)
		{
			if (_size == 0)
				return iterator(_end, _comp, _end);
			iterator it(this->begin());
			while (it != this->end() && _comp(k, (*it).first) == false)
				++it;
			return it;
		}

		const_iterator upper_bound(const key_type &k) const
		{
			if (_size == 0)
				return const_iterator(_end, _comp, _end);
			const_iterator it(this->begin());
			while (it != this->end() && _comp(k, (*it).first) == false)
				++it;
			return it;
		}

		ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			return ft::make_pair(this->lower_bound(k), this->upper_bound(k));
		}

		ft::pair<iterator, iterator> equal_range(const key_type &k)
		{
			return ft::make_pair(this->lower_bound(k), this->upper_bound(k));
		}
	};

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y)
	{
		x.swap(y);
	}
} // namespace ft

#endif
