# ft_container

My c++ STL container (c++98)

## Allocator

할당을 위한 `template class`

### C++ named requirements: Allocaotr

[Allocator requiremnts](https://en.cppreference.com/w/cpp/named_req/Allocator#cite_ref-1)

Allocator를 만족하기 위한 조건이 존재하여, 이를 구현해야 Allocator로 사용할 수 있다.

### C++ std::allocator

[cppreference std::allocator](https://en.cppreference.com/w/cpp/memory/allocator)

[cplusplus std::allocator](https://www.cplusplus.com/reference/memory/allocator/)

default allocator으로, STL containers에서 사용하는 allocator를 제공하며 특정한 allocator가 제공되지 않으면 `std::allocator` 가 사용된다.

Prototype:

```c++
/**
 * @brief default allocator
 * @tparam T: type of the elements allocated by the object
 **/
template<class T> class allocator;
```

Member types:

```c++
typedef T value_type;
typedef T* pointer;
typedef T& reference;
typedef const T* const_pointer;
typedef const T& const_reference;
typedef std::size_t size_type;
typedef std::ptrdiff_t difference_type;

// 주어진 타입이 아닌 다른 타입으로 할당하기 위함.
typedef template<class U> struct rebind{ typedef allocator<U> other; } rebind;
```

## Vector

### Prototype

```c++
/**
 * @brief generic template of vector
 * @tparam T: type of the elements. Must meet the requirements of
 * CopyAssignable and CopyConstructible
 * @tparam Allocator: type of the allocator that is used to acquire/release
 * memory and to construct/destroy the elements in that memory
 * Must meet the requirements of Allocator
 *
 **/
template <class T, class Allocator = std::allocator<T> > class vector;
```

### Member types

```c++
typedef T value_type;

// default to allocator<value_type>
typedef Allocator allocator_type;
typedef typename allocator_type::pointer pointer;
typedef typename allocator_type::const_pointer const_pointer;
typedef typename allocator_type::reference reference;
typedef typename allocator_type::const_reference const_reference;

// same to std::size_t when Allocator is std::allocator
typedef typename allocator_type::size_type size_type;

// same to std::ptrdiff_t when Allocator is std::allocator
typedef typename allocator_type::difference_type difference_type;

// a random access iterator to value_type
typedef pointer iterator;

// a random access iterator to const value_type
typedef const_pointer const_iterator;

// TODO: convert to ft::reverse_iterator later
typedef std::reverse_iterator<iterator> reverse_iterator;
typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
```

### Member functions

constructor:

```c++
// default constructor which constructs an empty container
explicit vector(const allocator_type& alloc = allocator_type());

// fill constructor which constructs a container with n elements with value val
explicit vector(size_type n, const value_type& val = value_type(),
		const allocator_type& alloc = allocator_type());

// range constructor which constructs a container with range first to last
template <class InputIterator>
vector (InputIterator first, InputIterator last,
		const allocator_type& alloc = allocator_type());

// copy constructor which constructs a container with the copy of the container
vector (const vector& other);
```

destructor:

This destroys all elements in the container and deallocates all the storage capacity.

operator=:

Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.

**The container preserve its current allocator.** -> 재할당 하는 경우에 사용됨!

```c++
vector& operator=(const vector& rhs);
```

#### Iterators:

`begin(), end(), rbegin(), rend(), cbegin(), cend(), crbegin(), crend()`

#### Capacity:

`size(), max_size(), resize(), capacity(), empty(), reserve()`

#### Element access:

`operator[], at(), front(), back()`

#### Modifiers:

`assign(), push_back(), pop_back(), insert(), erase(), swap(), clear()`

#### Allocator:

`get_allocator()`

#### Non-member functions:

relational operators:

```c++
template <class T, class Alloc>
bool operator == (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator != (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator <  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator <= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator > (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator >= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
```

swap()

```c++
template <class T, class Alloc>
void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
```

#### Template specializations:

`vector<bool>`

## TODO

- [ ] vector
- [ ] map
- [ ] stack
- [ ] set

---

- [ ] iterator_traits
- [ ] reverse_iterator
- [ ] enable_if
- [ ] is_integral
- [ ] equal and lexicographical_compare
- [ ] std::pair
- [ ] std::make_pair
