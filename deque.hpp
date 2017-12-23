#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP

#include "exceptions.hpp"

#include <cstddef>

namespace sjtu {

	template<class T>
	class deque {
	private:
		struct node
		{
			T data;
			node *prev;
			node *next;
			node(const T &x, node *p = NULL, node *n = NULL) :data(x), prev(p), next(n) {}
			//node() :prev(NULL), next(NULL) {}
			~node() {}
		};
		node *head, *tail;
		size_t curLen;
		node *move(long long int i) const
		{
			node *p = head->next;
			for (long long int j = 1; j < i; ++j)
				p = p->next;
			return p;
		}

	public:
		class const_iterator;
		class iterator {
			friend class deque;
			friend class const_iterator;
		private:
			/**
			 * TODO add data members
			 *   just add whatever you want.
			 */
			node *ptr;
			const deque *container;
			size_t pos;
		public:
			iterator(node *p = NULL, const deque *c = NULL, long long int x = 1) :ptr(p), container(c), pos(x) {}
			iterator(const const_iterator &other)
			{
				ptr = other.ptr;
				container = other.container;
				pos = other.pos;
			}
			iterator(const iterator &other)
			{
				ptr = other.ptr;
				container = other.container;
				pos = other.pos;
			}
			/**
			 * return a new iterator which pointer n-next elements
			 *   even if there are not enough elements, the behaviour is **undefined**.
			 * as well as operator-
			 */
			iterator &operator=(const iterator &rhs)
			{
				if (this == &rhs)
					return *this;
				ptr = rhs.ptr;
				pos = rhs.pos;
				container = rhs.container;
				return *this;
			}

			iterator operator+(const int &n) const
			{
				//TODO
				if (n > 0)
				{
					if (pos + n > container->curLen + 1)
						throw invalid_iterator();
					else
					{
						iterator itr(*this);
						for (int i = 0; i < n; ++i)
						{
							itr.ptr = itr.ptr->next;
							++itr.pos;
						}
						return itr;
					}
				}
				else
				{
					if (pos + n <= 0)
					{
						throw invalid_iterator();
					}
					else
					{
						iterator itr(*this);
						for (int i = 0; i < -n; ++i)
						{
							itr.ptr = itr.ptr->prev;
							--itr.pos;
						}
						return itr;
					}
				}
			}
			iterator operator-(const int &n) const
			{
				//TODO
				if (n > 0)
				{
					if (pos - n <= 0)
					{
						throw invalid_iterator();
					}
					else
					{
						iterator itr(*this);
						for (int i = 0; i < n; ++i)
						{
							itr.ptr = itr.ptr->prev;
							--itr.pos;
						}
						return itr;
					}
				}
				else
				{
					if (pos - n > container->curLen + 1)
						throw invalid_iterator();
					else
					{
						iterator itr(*this);
						for (int i = 0; i < -n; ++i)
						{
							itr.ptr = itr.ptr->next;
							++itr.pos;
						}
						return itr;
					}
				}
			}
			// return th distance between two iterator,
			// if these two iterators points to different vectors, throw invaild_iterator.
			int operator-(const iterator &rhs) const
			{
				//TODO
				if (container != rhs.container)
					throw invalid_iterator();
				else
				{
					return pos - rhs.pos;
				}
			}
			iterator &operator+=(const int &n)
			{
				//TODO
				if (n > 0)
				{
					if (pos + n > container->curLen + 1)
						throw invalid_iterator();
					else
					{
						for (int i = 0; i < n; ++i)
						{
							++pos;
							ptr = ptr->next;
						}
						return *this;
					}
				}
				else
				{
					if (pos + n <= 0)
					{
						throw invalid_iterator();
					}
					for (int i = 0; i < -n; ++i)
					{
						--pos;
						ptr = ptr->prev;
					}
					return *this;
				}
			}
			iterator &operator-=(const int &n)
			{
				//TODO
				if (n > 0)
				{
					if (pos - n <= 0)
						throw invalid_iterator();
					else
					{
						for (int i = 0; i < n; ++i)
						{
							--pos;
							ptr = ptr->prev;
						}
						return *this;
					}
				}
				else
				{
					if (pos - n > container->curLen + 1)
					{
						throw invalid_iterator();
					}
					else
					{
						for (int i = 0; i < -n; ++i)
						{
							++pos;
							ptr = ptr->next;
						}
						return *this;
					}
				}
			}
			/**
			 * TODO iter++
			 */
			iterator operator++(int)
			{
				if (pos > container->curLen)
					throw invalid_iterator();
				else
				{
					iterator itr(*this);
					++pos;
					ptr = ptr->next;
					return itr;
				}

			}
			/**
			 * TODO ++iter
			 */
			iterator& operator++()
			{
				if (pos > container->curLen)
					throw invalid_iterator();
				else
				{
					++pos;
					ptr = ptr->next;
					return *this;
				}
			}
			/**
			 * TODO iter--
			 */
			iterator operator--(int)
			{
				if (pos - 1 <= 0)
					throw invalid_iterator();
				else
				{
					iterator itr(*this);
					--pos;
					ptr = ptr->prev;
					return itr;
				}
			}
			/**
			 * TODO --iter
			 */
			iterator& operator--()
			{
				if (pos - 1 <= 0)
					throw invalid_iterator();
				else
				{
					--pos;
					ptr = ptr->prev;
					return *this;
				}
			}
			/**
			 * TODO *it
			 */
			T& operator*() const
			{
				if (pos == container->curLen + 1)
					throw index_out_of_bound();
				else
					return ptr->data;
			}
			/**
			 * TODO it->field
			 */
			T* operator->() const noexcept
			{
				//if (pos == container->curLen + 1)
				//	throw invalid_iterator();
				return &(ptr->data);
			}
			/**
			 * a operator to check whether two iterators are same (pointing to the same memory).
			 */
			bool operator==(const iterator &rhs) const
			{
				return (ptr == rhs.ptr);
			}
			bool operator==(const const_iterator &rhs) const
			{
				return (ptr == rhs.ptr);
			}
			/**
			 * some other operator for iterator.
			 */
			bool operator!=(const iterator &rhs) const
			{
				return (ptr != rhs.ptr);
			}
			bool operator!=(const const_iterator &rhs) const
			{
				return (ptr != rhs.ptr);
			}
		};
		class const_iterator {
			// it should has similar member method as iterator.
			//  and it should be able to construct from an iterator.
			friend class deque;
			friend class iterator;
		private:
			// data members.
			node *ptr;
			const deque *container;
			size_t pos;
		public:
			const_iterator(node *p = NULL, const deque *c = NULL, long long int x = 1) :ptr(p), container(c), pos(x)
			{
				// TODO
			}
			const_iterator(const const_iterator &other)
			{
				// TODO
				ptr = other.ptr;
				container = other.container;
				pos = other.pos;
			}
			const_iterator(const iterator &other)
			{
				// TODO
				ptr = other.ptr;
				container = other.container;
				pos = other.pos;
			}
			// And other methods in iterator.
			// And other methods in iterator.
			// And other methods in iterator.
			const_iterator &operator=(const const_iterator &rhs)
			{
				if (this == &rhs)
					return *this;
				ptr = rhs.ptr;
				pos = rhs.pos;
				container = rhs.container;
				return *this;
			}

			const_iterator operator+(const int &n) const
			{
				//TODO
				if (n > 0)
				{
					if (pos + n > container->curLen + 1)
						throw invalid_iterator();
					else
					{
						const_iterator itr(*this);
						for (int i = 0; i < n; ++i)
						{
							itr.ptr = itr.ptr->next;
							++itr.pos;
						}
						return itr;
					}
				}
				else
				{
					if (pos + n <= 0)
						throw invalid_iterator();
					else
					{
						const_iterator itr(*this);
						for (int i = 0; i < -n; ++i)
						{
							itr.ptr = itr.ptr->prev;
							--itr.pos;
						}
						return itr;
					}
				}
			}
			const_iterator operator-(const int &n) const
			{
				//TODO
				if (n > 0)
				{
					if (pos - n <= 0)
					{
						throw invalid_iterator();
					}
					else
					{
						const_iterator itr(*this);
						for (int i = 0; i < n; ++i)
						{
							itr.ptr = itr.ptr->prev;
							--itr.pos;
						}
						return itr;
					}
				}
				else
				{
					if (pos - n > container->curLen + 1)
						throw invalid_iterator();
					else
					{
						const_iterator itr(*this);
						for (int i = 0; i < -n; ++i)
						{
							itr.ptr = itr.ptr->next;
							++itr.pos;
						}
						return itr;
					}
				}
			}
			// return th distance between two iterator,
			// if these two iterators points to different vectors, throw invaild_iterator.
			int operator-(const const_iterator &rhs) const
			{
				//TODO
				if (container != rhs.container)
					throw invalid_iterator();
				else
				{
					return pos - rhs.pos;
				}
			}
			const_iterator &operator+=(const int &n)
			{
				//TODO
				if (n > 0)
				{
					if (pos + n > container->curLen + 1)
						throw invalid_iterator();
					else
					{
						for (int i = 0; i < n; ++i)
						{
							++pos;
							ptr = ptr->next;
						}
						return *this;
					}
				}
				else
				{
					if (pos + n <= 0)
						throw invalid_iterator();
					else
					{
						for (int i = 0; i < -n; ++i)
						{
							--pos;
							ptr = ptr->prev;
						}
						return *this;
					}
				}
			}
			const_iterator &operator-=(const int &n)
			{
				//TODO
				if (n > 0)
				{
					if (pos - n <= 0)
						throw invalid_iterator();
					else
					{
						for (int i = 0; i < n; ++i)
						{
							--pos;
							ptr = ptr->prev;
						}
						return *this;
					}
				}
				else
				{
					if (pos - n > container->curLen + 1)
						throw invalid_iterator();
					else
					{
						for (int i = 0; i < -n; ++i)
						{
							++pos;
							ptr = ptr->next;
						}
						return *this;
					}
				}
			}
			/**
			* TODO iter++
			*/
			const_iterator operator++(int)
			{
				if (pos > container->curLen)
					throw invalid_iterator();
				else
				{
					const_iterator itr(*this);
					++pos;
					ptr = ptr->next;
					return itr;
				}

			}
			/**
			* TODO ++iter
			*/
			const_iterator& operator++()
			{
				if (pos > container->curLen)
					throw invalid_iterator();
				else
				{
					++pos;
					ptr = ptr->next;
					return *this;
				}
			}
			/**
			* TODO iter--
			*/
			const_iterator operator--(int)
			{
				if (pos - 1 <= 0)
					throw invalid_iterator();
				else
				{
					const_iterator itr(*this);
					--pos;
					ptr = ptr->prev;
					return itr;
				}
			}
			/**
			* TODO --iter
			*/
			const_iterator& operator--()
			{
				if (pos - 1 <= 0)
					throw invalid_iterator();
				else
				{
					--pos;
					ptr = ptr->prev;
					return *this;
				}
			}
			/**
			* TODO *it
			*/
			const T &operator*() const
			{
				if (pos == container->curLen + 1)
					throw invalid_iterator();
				else
					return ptr->data;
			}
			/**
			* TODO it->field
			*/
			const T* operator->() const noexcept
			{
				/*if (pos == container->curLen + 1)
					throw invalid_iterator();*/
				return &(ptr->data);
			}
			/**
			* a operator to check whether two iterators are same (pointing to the same memory).
			*/
			bool operator==(const iterator &rhs) const
			{
				return (ptr == rhs.ptr);
			}
			bool operator==(const const_iterator &rhs) const
			{
				return (ptr == rhs.ptr);
			}
			/**
			* some other operator for iterator.
			*/
			bool operator!=(const iterator &rhs) const
			{
				return (ptr != rhs.ptr);
			}
			bool operator!=(const const_iterator &rhs) const
			{
				return (ptr != rhs.ptr);
			}
		};
		/**
		 * TODO Constructors
		 */
		deque()
		{
			void *tmp1 = operator new(sizeof(node));
			head = reinterpret_cast<node*>(tmp1);
			void *tmp2 = operator new(sizeof(node));
			tail = reinterpret_cast<node*>(tmp2);
			head->next = tail;
			tail->prev = head;
			curLen = 0;
		}

		deque(const deque &other)
		{
			void *tmp1 = operator new(sizeof(node));
			head = reinterpret_cast<node*>(tmp1);
			void *tmp2 = operator new(sizeof(node));
			tail = reinterpret_cast<node*>(tmp2);
			head->next = tail;
			tail->prev = head;
			node *tmp = other.head->next;
			while (tmp != other.tail)
			{
				push_back(tmp->data);
				tmp = tmp->next;
			}
			curLen = other.curLen;
		}
		/**
		 * TODO Deconstructor
		 */
		~deque()
		{
			clear();
			operator delete (head);
			operator delete (tail);
		}
		/**
		 * TODO assignment operator
		 */
		deque &operator=(const deque &other)
		{
			if (this == &other)
				return *this;
			clear();
			node *tmp = other.head->next;
			while (tmp != other.tail)
			{
				push_back(tmp->data);
				tmp = tmp->next;
			}
			curLen = other.curLen;
			return *this;
		}
		/**
		 * access specified element with bounds checking
		 * throw index_out_of_bound if out of bound.
		 */
		T & at(const size_t &pos)
		{
			if (pos > curLen - 1 || pos < 0)
				throw index_out_of_bound();
			else
			{
				node *tmp = move(pos + 1);
				return tmp->data;
			}
		}
		const T & at(const size_t &pos) const
		{
			if (pos > curLen - 1 || pos < 0)
				throw index_out_of_bound();
			else
			{
				node *tmp = move(pos + 1);
				return tmp->data;
			}
		}
		T & operator[](const size_t &pos)
		{
			if (pos > curLen - 1 || pos < 0)
				throw index_out_of_bound();
			else
			{
				node *tmp = move(pos + 1);
				return tmp->data;
			}
		}
		const T & operator[](const size_t &pos) const
		{
			if (pos > curLen - 1 || pos < 0)
				throw index_out_of_bound();
			else
			{
				node *tmp = move(pos + 1);
				return tmp->data;
			}
		}
		/**
		 * access the first element
		 * throw container_is_empty when the container is empty.
		 */
		const T & front() const
		{
			if (curLen == 0)
				throw container_is_empty();
			else
				return head->next->data;
		}
		/**
		 * access the last element
		 * throw container_is_empty when the container is empty.
		 */
		const T & back() const
		{
			if (curLen == 0)
				throw container_is_empty();
			else
				return tail->prev->data;
		}
		/**
		 * returns an iterator to the beginning.
		 */
		iterator begin()
		{
			iterator itr(head->next, this, 1);
			return itr;
		}
		const_iterator cbegin() const
		{
			const_iterator itr(head->next, this, 1);
			return itr;
		}
		/**
		 * returns an iterator to the end.
		 */
		iterator end()
		{
			iterator itr(tail, this, curLen + 1);
			return itr;
		}
		const_iterator cend() const
		{
			const_iterator itr(tail, this, curLen + 1);
			return itr;
		}
		/**
		 * checks whether the container is empty.
		 */
		bool empty() const
		{
			return curLen == 0;
		}
		/**
		 * returns the number of elements
		 */
		size_t size() const
		{
			return curLen;
		}
		/**
		 * clears the contents
		 */
		void clear()
		{
			node *p = head->next, *q;
			head->next = tail;
			while (p != tail)
			{
				q = p->next;
				delete p;
				p = q;
			}
			curLen = 0;
			tail->prev = head;
		}
		/**
		 * inserts elements at the specified locat on in the container.
		 * inserts value before pos
		 * returns an iterator pointing to the inserted value
		 *     throw if the iterator is invalid or it point to a wrong place.
		 */
		iterator insert(iterator p, const T &value)
		{
			if (p.ptr == NULL || p.container != this)
				throw invalid_iterator();
			else
			{
				node *tmp = p.ptr->prev;
				tmp->next = new node(value, tmp, p.ptr);
				p.ptr->prev = tmp->next;
				iterator itr(tmp->next, this, p.pos);
				++p.pos;
				++curLen;
				return itr;
			}
		}
		/**
		 * removes specified element at pos.
		 * removes the element at pos.
		 * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
		 * throw if the container is empty, the iterator is invalid or it points to a wrong place.
		 */
		iterator erase(iterator p)
		{
			if (curLen == 0)
				throw container_is_empty();
			else if (p.container != this || p.ptr == NULL || p.pos == curLen + 1)
				throw invalid_iterator();
			else
			{
				node *tmp = p.ptr;
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
				iterator itr(p.ptr->next, p.container, p.pos);
				--curLen;
				delete tmp;
				return itr;
			}
		}
		/**
		 * adds an element to the end
		 */
		void push_back(const T &value)
		{
			node *tmp = tail->prev;
			tmp->next = new node(value, tmp, tail);
			tail->prev = tmp->next;
			++curLen;
		}
		/**
		 * removes the last element
		 *     throw when the container is empty.
		 */
		void pop_back()
		{
			if (curLen == 0)
				throw container_is_empty();
			else
			{
				node *tmp = tail->prev;
				tmp->prev->next = tail;
				tail->prev = tmp->prev;
				delete tmp;
				--curLen;
			}
		}
		/**
		 * inserts an element to the beginning.
		 */
		void push_front(const T &value)
		{
			node *tmp = head->next;
			head->next = new node(value, head, tmp);
			tmp->prev = head->next;
			++curLen;
		}
		/**
		 * removes the first element.
		 *     throw when the container is empty.
		 */
		void pop_front()
		{
			if (curLen == 0)
				throw container_is_empty();
			else
			{
				node *tmp = head->next;
				head->next = tmp->next;
				tmp->next->prev = head;
				delete tmp;
				--curLen;
			}
		}
	};

}

#endif
