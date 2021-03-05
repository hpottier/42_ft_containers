/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allocator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpottier <hpottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 17:24:54 by hpottier          #+#    #+#             */
/*   Updated: 2021/03/03 22:18:55 by hpottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ALLOCATOR_HPP
#define FT_ALLOCATOR_HPP

namespace ft
{
	template <class T>
	class allocator;

	template <>
	class allocator<void>
	{
	public:
		typedef void *pointer;
		typedef const void *const_pointer;
		typedef void value_type;

		template <class U>
		struct rebind
		{
			typedef allocator<U> other;
		};
	};

	template <class T>
	class allocator
	{
	public:
		typedef typename std::size_t size_type;
		typedef typename std::ptrdiff_t difference_type;
		typedef T *pointer;
		typedef const T *const_pointer;
		typedef T &reference;
		typedef const T &const_reference;
		typedef T value_type;

		template <class Type>
		struct rebind
		{
			typedef allocator<Type> other;
		};

		allocator() {}

		allocator(const allocator &alloc) { (void)alloc; }

		template <class U>
		allocator(const allocator<U> &alloc) { (void)alloc; }

		~allocator() {}

		pointer address(reference x) const { return &x; }

		const_pointer address(const_reference x) const { return &x; }

		pointer allocate(size_type n, allocator<void>::const_pointer hint = 0)
		{
			(void)hint;
			return static_cast<pointer>(::operator new(sizeof(value_type) * n));
		}

		void deallocate(pointer p, size_type n)
		{
			(void)n;
			::operator delete(p);
		}

		size_type max_size() const { return static_cast<std::size_t>(-1) / sizeof(value_type); }

		void construct(pointer p, const_reference val)
		{
			::new ((void *)p) value_type(val);
		}

		void destroy(pointer p)
		{
			p->~value_type();
		}
	};
} // namespace ft

#endif
