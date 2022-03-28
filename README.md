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

## Exception safety

<details> 
<summary> 원문 </summary>

> The C++ standard library provides a generally useful conceptual framework for design for exception-safe program components. The library provides one of the following guarantees for every library operation:
>
> - The basic guarantee for all operations: The basic invariants of all objects are maintained, and no resources, such as memory, are leaked. In particular, the basic invariants of every built-in and standard-library type guarantee that you can destroy an object or assign to it after every standard-library operation (§iso.17.6.3.1).
> - The strong guarantee for key operations: in addition to providing the basic guarantee, either the operation succeeds, or it has no effect. This guarantee is provided for key operations, such as `push_back(), single-element insert() on a list, and uninitialized_copy()`.
> - The nothrow guarantee for some operations: in addition to providing the basic guarantee, some operations are guaranteed not to throw an exception. This guarantee is provided for a few simple operations, such as `swap() of two containers and pop_back()`.
>   > _Reference : The c++ Programming language, 4rd edition_

</details>

- The basic guarantee:
  - 모든 객체가 유지되며 리소스가 부족한 상태에선 누수가 발생하지 않음. 특히, 빌트인 혹은 표준 라이브러리에서 the basic garantee를 보장할 땐 객체를 소멸시키거나 값을 할당할 수 있음.
- The strong Guarantee for key operations:
  - the basic guarantee에 추가로 operation이 실패시 아무런 영향을 미치지 않음.
- The nothrow guarantee for some operations:
  - the basic guarantee에 추가로 일부 operation은 예외를 발생시키지 않음.

[한국문서](https://scvgoe.github.io/2019-07-06-Exception-Safety/)

### RAII (Resource Acquisition Is Initialization)

exception safety를 보장하기 위한 방법중 하나.
초기화에 성공하면 리소스가 존재하는것을 보장해줘야 하며, 초기화에 실패시 (construct 실패) 자원을 해제해줘야함.

이게 보장이 된다면, 컨테이너를 생성할때 \_\_container_type_base 를 상속받아서 생성하면 된다?

[Ref](https://www.stroustrup.com/3rd_safe.pdf)

> The ‘‘resource acquisition is initialization’’ technique (§14.4) can be used to reduce the amount of
> code needing to be written and to make the code more stylized. In this case, the key resource
> required by the vectoris memory to hold its elements. By providing an auxiliary class to represent
> the notion of memory used by a vector, we can simplify the code and decrease the chance of accidentally forgetting to release it:

```c++
template<class T, class A= allocator<T> >
struct vector_base{
	A alloc; // allocator
	T* v;  // start of allocation
	T* space; // end of element sequence, start of space allocated for possible expansion
	T* last; // end of allocated space
	vector_base(const A& a, typename A: :size_type n)
	: alloc(a) , v(a.allocate(n)) , space(v + n) , last(v + n) { }
	~vector_base() { alloc.deallocate(v,last - v) ; }
};
```

[한국어 문서](https://occamsrazr.net/tt/297)

[\_\_base_vector](https://stackoverflow.com/questions/50050659/what-is-going-on-with-vector-base-common)

## Vector

<details>
<summary> vector 내부 구현 </summary>

# LLVM

`__vector_base_common`, `__vector_base` 를 사용하여 vector 내부 구현을 제공.

vector implementation에 필요한 메소드들을 정의해서 이를 이용하여 vector를 구현함.

</details>

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

# Reference

[gnu source code (github)](https://github.com/gcc-mirror/gcc/tree/master/libstdc%2B%2B-v3/include/bits)
[gnu docs](https://gcc.gnu.org/onlinedocs/gcc-11.2.0/libstdc++/api/files.html)
[cplusplus](https://www.cplusplus.com/)
[cppreference](https://en.cppreference.com/)
