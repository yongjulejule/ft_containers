# ft_containers

My c++ STL containers (c++98)

- vector
- map
- set
- stack
- iterator


# Index  

- [ft_containers](#ft_containers)
- [Index](#index)
- [Convention](#convention)
- [Functional Specification](#functional-specification)
- [Keywords](#keywords)
	- [stack unwinding](#stack-unwinding)
	- [dynamic exception specification _(deprecated c++11, removed c++17)_](#dynamic-exception-specification-deprecated-c11-removed-c17)
	- [Exception safety](#exception-safety)
	- [RAII (Resource Acquisition Is Initialization)](#raii-resource-acquisition-is-initialization)
	- [\*\_traits](#_traits)
	- [type_traits](#type_traits)
	- [iterator_traits](#iterator_traits)
		- [InputIterator](#inputiterator)
	- [SFINAE (Substitution Failure Is Not An Error)](#sfinae-substitution-failure-is-not-an-error)
		- [⚠️ Default Argument Do Not Participate in Overload Resolution](#️-default-argument-do-not-participate-in-overload-resolution)
	- [enable_if](#enable_if)
- [Allocator](#allocator)
	- [C++ named requirements: Allocaotr](#c-named-requirements-allocaotr)
	- [C++ std::allocator](#c-stdallocator)
- [Vector](#vector)
	- [Prototype](#prototype)
	- [Member types](#member-types)
	- [Member functions](#member-functions)
		- [Iterators:](#iterators)
		- [Capacity:](#capacity)
		- [Element access:](#element-access)
		- [Modifiers:](#modifiers)
		- [Allocator:](#allocator-1)
		- [Non-member functions:](#non-member-functions)
		- [Template specializations:](#template-specializations)
	- [private things to implement vector](#private-things-to-implement-vector)
		- [__vector_base](#__vector_base)
		- [__vector_base methods](#__vector_base-methods)
		- [private method in vector](#private-method-in-vector)
		- [exceptions](#exceptions)
	- [TODO](#todo)
- [Reference](#reference)

<small><i><a href='http://ecotrust-canada.github.io/markdown-toc/'>Table of contents generated with markdown-toc</a></i></small>

# Convention

- STL의 메소드들에 맞게, snake_case 사용
- 최대한 공식문서([1](https://en.cppreference.com/w/), [2](https://www.cplusplus.com/))와 일치하도록 작성
- 라이브러리에서만 사용되는 메소드, 클래스는 __class_name 과 같은 형태로 작성
- 외부로 공개되지 않는 변수는 __variable_name_ 과 같은 형태로 작성
- format는 [google style guide](https://google.github.io/styleguide/cppguide.html)에 따름


# Functional Specification

- c++98 기준 모든 기능 구현
- 같은 exception-safety를 보장
- c++98로 가능한 Template Meta Programming 최대한 활용


# Keywords

## stack unwinding

- 스택에서 함수 진행 중, exception이 발생했을 시 catch를 찾아가면서 콜스택을 되돌아가게 되고, 이때 콜스택 하나 하나를 빠져나올 때 마다 해당 스택을 정리해주는것. 만약, 스택 내부에서 힙에 할당된 메모리가 있으면 릭이 발생함! (RAII가 대표적인 해결책.)

```c++
void f3() {
	int *c = new int[100]; // will be leak
	std::string s = "this is stack... would be destroied";
	throw "exception!";
}

void f2() { f3() }

void f1() { try { f2() } catch (...) { std::cout << "back to here!\n"; } }
```

- `f1->f2->f3` 순으로 스택이 쌓이며, `f3->f2->f1` 순으로 스택이 해제됨.
- RAII를 보장하여 `f3` 의 스코프를 나가면서 메모리 해제가 보장된다면, leak이 발생하지 않음.

## dynamic exception specification _(deprecated c++11, removed c++17)_

- `throw(expression)`을 통하여 특정 함수가 어떤 exception을 던지는지 설정 가능
- 만약 expression에 없는 exception이 throw 된다면, std::unexcepted가 작동함.
- `throw()` 형태로 쓴다면, 해당 함수는 exception을 던지지 않는다는 의미가 됨.
- 프로그래머의 의도를 함수에 녹여낼 수 있으며, 컴파일러 상에서 최적화도 가능해짐.
- 하지만 [여러가지 이유](https://stackoverflow.com/questions/13841559/deprecated-throw-list-in-c11)로 삭제됨

  - 런타임시 체크되어서 프로그래머가 모든 runtime-failure를 다룰 수 없음.
  - 오히려 런타임 오버헤드가 생김.
  - generic code에서 사용성이 떨어짐. 해당 함수가 던질 수 있는 exception이 늘어나면 고쳐야할게 더 많아짐.
  - 실제로, 함수가 아무 exception이나 던지거나(`throw(...)`이 없을때) 또는 exception을 절대 던지지 않는 상황(`throw()`)에서만 최적화가 가능
  - 이에 맞게 [noexcept](https://en.cppreference.com/w/cpp/language/noexcept_spec)로 대체됨.
  - 따라서, `#define FT_NOEXCEPT throw()` 로 `noexcept` 대체!

- std::unexpected

  - `std::unexcepted_handler`가 실행되는데, 기본 핸들러가 `std::terminate`이므로 `std::abort()`를 통해 프로그램이 종료됨

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

## RAII (Resource Acquisition Is Initialization)

exception safety를 보장하기 위한 방법중 하나.
초기화에 성공하면 리소스가 존재하는것을 보장해줘야 하며, 초기화에 실패시 (construct 실패) 자원을 해제해줘야함. 또한, 소멸자 호출 시 사용한 리소스들을 모두 잘 해제해줘야함. 따라서 객체가 사용하는 자원은 객체의 수명 내에서 관리됨.

따라서, 스코프에서 객체를 생성하고 스코프에서 나올 때, 모든 자원이 정상적으로 반환되면 됨!

<details> 
<summary> 참고 </summary>

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

[Stroustrup's document](https://www.stroustrup.com/3rd_safe.pdf)

[한국어 문서](https://occamsrazr.net/tt/297)

[\_\_base_vector](https://stackoverflow.com/questions/50050659/what-is-going-on-with-vector-base-common)

</details>

## \*\_traits

> A traits class provides a way of associating information with a compile-time entity (a type, integral constant, or address).

c++에는 `allocator_traits`, `type_traits`, `iterator_traits`, `char_traits` 등 수많은 `*_traits`가 존재하며 STL에서 이런 `*_trait`가 정말 많이 쓰임. 이는 컴파일 타임에 타입을 특성화 해주기 위함이며, 타입이 중요한 메타 프로그래밍에서 많이 쓰임...

`iterator_traits`를 활용하여 5가지 이터레이터에 대한 generic한 코드를 짤 수 있고, `char_traits`를 통하여 `char` 과 `wchar`를 묶어줄 수 있으며 `type_traits`를 이용하여 컴파일 타임에 `true, false`를 사용할 수 있는 등 다양한 기능을 제공해줌

이러한 `traits`은 주로 템플릿 특수화를 통하여 구현됨!

[자세한 설명](http://egloos.zum.com/sweeper/v/3007176)

## type_traits

- `integral_constant`
  - `true_type`
  - `false_type`
- `is_intrgral`
- `is_same`
- `remove_cv`
- `enable_if`



## iterator_traits

![iterator traits](asset/iterator_traits.png)
<p align='center' color='gray'> Reference: https://www.cplusplus.com/reference/iterator/ </p>

### InputIterator

값이 increment되면 이전의 값들의 복사본은 invalidate 될 수 있음.... 왜? 문자를 하나씩 받다가 버퍼가 가득 차면 그냥 버리는 경우를 생각하자.
-> [why does an input iterator invalidate itself after incrementing](https://stackoverflow.com/questions/56319796/why-does-an-input-iterator-invalidate-itself-after-incrementing)

## SFINAE (Substitution Failure Is Not An Error)

c++에서 컴파일시 타입에 맞는 [함수](https://en.cppreference.com/w/cpp/language/functions)를 찾아가는 과정은 매우 복잡하며, 이 과정에서 수많은 후보가 생김.

1. name lookup 을 통하여 함수 이름을 찾음.
2. ADL을 통하여 매칭되는 함수를 찾음. (이 과정에서 암시적 형변환이 일어날 수 있음)
3. 템플릿 함수는 타입이 정해지지 않았으므로 인스턴스화가 될 필요가 있음.
4. 명시적 혹은 암시적으로 템플릿 함수가 인스턴스화가 되지만, 항상 템플릿의 모든 인자가 정해지지는 않음.
5. 이때 가능하다면, 컴파일러가 템플릿의 인자를 추론함(Template argument deduction)
6. 이렇게 candidated function set이 생성되는데 둘 이상의 함수가 후보가 될 수 있음
7. 목록에서 함수의 인자들을 치환하는데, 이때 타입이나 표현상의 문제가 있으면 치환에 실패함
8. **치환에 실패할 시 컴파일 에러를 내지 않고, 해당 후보 함수를 후보군에서 제외하는 방식으로 작동!(SFINAE)**
9. overload resolution을 통하여 실제로 호출한 함수를 찾음!
10. 이때, 함수의 후보들을 `candidate functions`, 실제 호출되는 함수는 `viable function`이라고 부름!

- [name lookup](https://en.cppreference.com/w/cpp/language/lookup)
  - [unqualified name lookup](https://en.cppreference.com/w/cpp/language/unqualified_lookup)
  - [qualified name loopup](https://en.cppreference.com/w/cpp/language/qualified_lookup)
- [ADL (Argument Dependent Lookup)](https://en.cppreference.com/w/cpp/language/adl)
- [template argument deduction](https://en.cppreference.com/w/cpp/language/template_argument_deduction)
- [template argument substitution](https://en.cppreference.com/w/cpp/language/function_template#Template_argument_substitution)
- [overload resolution](https://en.cppreference.com/w/cpp/language/overload_resolution) -> 방대한 설명이 있음...

### ⚠️ Default Argument Do Not Participate in Overload Resolution

- Default Argument 는 overload resolution에 포함되지 않음!!!!!

[function overloading with default parameter](https://stackoverflow.com/questions/53376620/function-overloading-with-default-parameter-in-c)

[why SFINAE doesn't work in right side in default function argument](https://stackoverflow.com/questions/24909652/why-sfinae-doesnt-work-in-right-side-in-default-function-arguments)

## enable_if

SFINAE를 활용하여 특정 조건에서만 해당 템플릿 함수를 호출하게 만들어주는 도구

```c++
template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };
```

# Allocator

할당을 위한 `template class`

## C++ named requirements: Allocaotr

[Allocator requiremnts](https://en.cppreference.com/w/cpp/named_req/Allocator#cite_ref-1)

Allocator를 만족하기 위한 조건이 존재하여, 이를 구현해야 Allocator로 사용할 수 있다.

## C++ std::allocator

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

Member functions:

```c++

// (constructor): Construct allocator object (public member function )
allocator() throw();
allocator(const allocator& alloc) throw();
template <class U>
allocator(const allocator<U>& alloc) throw();

// (destructor): Allocator destructor (public member function )
~allocator() ;

// address:  Return address (public member function )
pointer address(reference x) const;
const_pointer address(const_reference x) const;

// allocate:  Allocate block of storage (public member function )
// @param hint: 0이 아니면, 이전에 할당한 공간의 가장 가까운 곳에 할당해주기 위한 힌트가 됨!
pointer allocate (size_type n, allocator<void>::const_pointer hint=0);

// deallocate:  Release block of storage (public member function )
// @param n: 이전에 allocate를 이용하여 할당한 공간과 크기가 다르면 UB임!
void deallocate (pointer p, size_type n);

// max_size: Maximum size possible to allocate (public member function )
size_type max_size() const throw();

// construct: Construct an object (public member function ). 할당되었던 p 메모리에 val을 씀
void construct(pointer p, const_reference val);

// destroy: Destroy an object (public member function )
void destroy( pointer p ); // Calls ((T*)p)->~T()

```

# Vector

## Prototype

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

## Member types

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
typedef __vector_iterator<pointer> iterator;

// a random access iterator to const value_type
typedef __vector_iterator<const_pointer> const_iterator;

typedef ft::reverse_iterator<iterator> reverse_iterator;
typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
```

## Member functions

constructor:

- exception safety: Strong.
  - [first, last) 가 정상적이지 않으면 UB
  - `allocator::constructor`가 정상적이지 않으면 UB

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

template specialization for consturctor: 
```c++
// InputIterator는 uninitialized_* 을 사용할 수 없어서 하나씩 push_back를 해야함!
template <typename _T, typename _Allocator>
template <typename _InputIterator>
vector<_T, _Allocator>::vector(
    _InputIterator first,
    typename enable_if<__is_input_iterator<_InputIterator>::value &&
                           !__is_forward_iterator<_InputIterator>::value,
                       _InputIterator>::type last,
    const allocator_type& _Alloc);

// ForwardIterator 부터는 uninitialized_* 를 사용할 수 있어 한번에 초기화 가능!
template <typename _T, typename _Allocator>
template <typename _ForwardIterator>
vector<_T, _Allocator>::vector(
    _ForwardIterator first,
    typename enable_if<__is_forward_iterator<_ForwardIterator>::value,
                       _ForwardIterator>::type last,
    const allocator_type& _Alloc);
```

destructor:

- This destroys all elements in the container and deallocates all the storage capacity.
- exception-safety: No-throw

operator=:

- Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.
- exception-safety: Basic
  - `allocator::constructor`가 정상적이지 않거나, `value_type`이 copy-assignable 하지 않으면 UB


**The container preserve its current allocator.** -> 재할당 하는 경우에 사용됨!

```c++
vector& operator=(const vector& rhs);
```

### Iterators:

- exception-safety: No-throw
- return corresponding iterator

```c++
iterator begin() FT_NOEXCEPT;
iterator end() FT_NOEXCEPT;
reverse_iterator rbegin() FT_NOEXCEPT;
reverse_iterator rend() FT_NOEXCEPT;
const iterator cbegin() const FT_NOEXCEPT;
const iterator cend() const FT_NOEXCEPT;
const reverse_iterator crbegin() const FT_NOEXCEPT;
const reverse_iterator crend() const FT_NOEXCEPT;
```

### Capacity:

```c++
// 컨테이너에 저장된 elements의 수를 반환
size_type size() const FT_NOEXCEPT; // No-throw

// 컨테이너에 할당할 수 있는 최대 메모리를 반환
size_type max_size() const FT_NOEXCEPT; // No-throw

// 컨테이너가 가지고 있는 메모리 크기 반환
size_type capacity() const FT_NOEXCEPT; // No-throw

// 컨테이너가 비었는지 여부를 boolean으로 반환
bool empty() const FT_NOEXCEPT; // No-throw

// 컨테이너가 최소한 new_n 만큼의 데이터를 저장하기 위한 메모리를 확보
// n > capacity() 면 재할당, 그렇지 않으면 재할당 x
// n > max_size() 면 length_error throw
// 재할당이 일어나지 않거나, copy constructor가 있으면 strong guarantee
// 그 외에는 basic guarantee
void reserve(size_type __new_n_)

// 컨테이너가 n개의 데이터를 저장하도록 resize.
// n < size()면, n개의 데이터만 저장. 나머지는 제거 -> strong guarantee
// n >= size()면, 남는 공간에 val을 채움  -> No-throw
// n > capacity()면, 현재 메모리만큼 재할당 -> strong guarantee
// val이 copyable하지 않으면 basic guarantee
void resize(size_type __n_, value_type __val_ = value_type());

```

### Element access:

```c++
// 컨테이너에서 저장된 n번째 데이터를 반환
// size() > n 이면 no-throw. 그 외에는 UB
reference operator[] (size_type __n_)
const reference operator[] (size_type __n_) const;

// 컨테이너에 저장된 n번째 데이터를 반환
// n이 범위를 벗어나면 out_of_range exception 발생
// strong-guarantee
reference at(size_type __n_);
const_reference at(size_type __n_) const;

// 컨테이너에 저장된 첫번째 요소의 레퍼런스 반환
// empty이면 UB. empty가 아니면 no-throw -> LLVM 기준 segmentation fault!
reference front();
const_reference front() const;

// 컨테이너에 저장된 마지막 요소의 레퍼런스 반환
// empty이면 UB. empty가 아니면 no-throw -> LLVM 기준 segmentation fault!
reference back();
const_reference back() const;
```

### Modifiers:

- 모든 method는 작동 후 적절하게 size()를 수정하고, 재할당시 내부의 allocator를 사용하여 메모리 할당.
- 할당시 allocator::construct에 문제가 있으면 UB
- `iterator validity`가 있어서, 데이터가 수정되는 경우 이전에 생성된 iterator들의 validity에 유의해야함.
- range는 당연히 [first, last) 임! 

- exception-safety(공통 적용)
  - 재할당이 일어나지 않거나, 재할당이 일어나도 각 요소가 copyable이면 strong guarantee (1)
	- 재할당이 일어났는데, 각 요소가 copyable하지 않으면 basic guarantee (2)
  - allocator::construct에 문제가 있거나, 인자의 iterator가 invalid하면 UB

```c++
// 벡터에 새로운 데이터를 넣고 size를 알맞게 수정
// 이전 데이터는 모두 destroy되고, 새로운 데이터로 replace됨
// 재할당은 새로운 size > capacity인 상황에만 일어나며 내부의 allocator를 이용
// basic-guarantee를 보장
template <typename _InputIterator>
void assign(_InputIterator first, _InputIterator last); // range
void assign(size_type n, const value_type& val); // fill

// val을 컨테이너 end에 추가. 필요하다면 메모리 재할당.
void push_back(const value_type& val);

// 컨테이너의 마지막 요소를 삭제.
// 컨테이너가 비어있지 않으면 no-throw. 그 외에는 UB
void pop_back();

// position 에 해당하는 값들을 삽입. 
// 현재 벡터 size보다 커지게 되면 자동으로 재할당
// iterator를 반환하는 경우, insert된 위치의 iterator 반환
iterator insert(iterator position, const value_type& val); // single element
void insert(iterator position, size_type n, const value_type& val); // fill
// inputiterator면 하나씩 삽입해야 해서 logN의 시간복잡도가 나옴
template <typename _InputIterator>
void insert(iterator position, _InputIterator first, _InputIterator last); // range

// 해당 인자의 element를 destroy하고, size를 줄임
// position이나 range에 end()가 포함되지 않으면, relocate하는 과정이 필요함!
// 마지막으로 지워진 부분의 다음 element가 있는 위치를 리턴
// 이때 iterator는 random_access_iterator
iterator erase(iterator position);
iterator erase(iterator first, iterator last);

// swap data
void swap(vector& x) FT_NOEXCEPT; // no-throw

// 컨테이너에 저장된 모든 데이터를 삭제하고, size를 0으로 설정
void clear() FT_NOEXCEPT; // no-throw
```

### Allocator:

```c++
// return copy of vector's allocator
allocator_type get_allocator() const FT_NOEXCEPT ; // no-throw

```

### Non-member functions:

relational operators:

```c++
bool operator == (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
bool operator != (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
bool operator <  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
bool operator <= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
bool operator > (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
bool operator >= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
```

swap()

```c++
template <class T, class Alloc>
void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
```

### Template specializations:

boolean값을 비트단위로 저장함... 와우... 

`vector<bool>`

## private things to implement vector

### __vector_base

`__vector_base` 에서 필요한 기능
- 생성자에서 메모리 획득이 되어야 하며, 소멸자에서 메모리를 모두 해제해야 함 (RAII)
- 현재 메모리 정보 저장 (`begin, end, capacity, allocator`)
- 메모리 획득
- 메모리 해제
- 문제 발생시 적절한 에러 throw 

base vector 가 필요한 이유
- `vector`의 `consturctor`는 `strong-guarantee`여야 함! 
- 모종의 이유로 `vector`의 `constructor`가 `exception`을 던지면, `vector`의 `destructor`가 호출되지 않음.
- 따라서 벡터 내부에서 자원을 얻고 헤제하는 과정이 `RAII`에 따라 잘 작성되었다고 하더라도, `destructor`가 호출되지 않아 리소스가 적절하게 반환되지 않을 수 있음(`strong-guarantee`를 만족하지 못함)
- `vector_base`를 만들어서 자원을 사용하는 데이터를 이곳에 저장하고, `vector`가 이를 상속받는 구조로 `vector`를 구성한 뒤 자원의 획득과 반환을 `vector_base`에서 `RAII`구조로 처리한다면, `vector`의 `constructor`에서 `exception`이 나더라도 `vector_base`의 `destructor`는 정상적으로 호출이 되어 자원이 반납됨.

<details>
<summary> 간단한 테스트 </summary>

```c++
class thrw {
 protected:
  int *x;
  size_t size;
  std::allocator<int> a;

 public:
  thrw() : x(NULL), size(424242), a(std::allocator<int>()) {
    std::cout << "thrw constructor\n";
    // @@@@ allocate_memory(); <- leaks here! @@@@@@
  }
  void allocate_memory() {
    std::cout << "allocate_memory\n";
    for (;;) {
      x = a.allocate(size);
      if (size > (a.max_size() >> 32)) throw std::bad_alloc();
      a.deallocate(x, size);
      size *= 2;
    }
  }
  ~thrw() {
    std::cout << "thrw destructor\n";
    a.deallocate(x, size);
  }
};

class thrw_child : public thrw {
 public:
  thrw_child() : thrw() {
    std::cout << "thrw_child constructor\n";
    allocate_memory();
  }
  ~thrw_child() { std::cout << "thrw_child destructor\n"; }
};

void raii_test() {
  thrw a;
  std::cout << "a constructed...\n";
  a.allocate_memory();
}

void raii_child_test() { thrw_child a; }

int main() {
  try {
    raii_test();
  } catch (std::exception &e) {
    std::cout << e.what() << " in Main raii_test CATCH\n";
  }
  try {
    raii_child_test();
  } catch (std::exception &e) {
    std::cout << e.what() << " in Main raii_child_test CATCH\n";
  }
  system("leaks mine.out | grep leaked");
}
```

`thrw` 가 부모 클래스가 되며 `thrw_child` 가 자식 클래스가 됨. 
이때, 부모 클래스의 생성자에서 `allocate_memory` 함수를 호출하여 exception이 발생하면 메모리 누수가 발생!
![parent throw](asset/parent_alloc.png)
주석을 해제하고 실행하면 소멸자가 호출되지 않은 모습을 확인할 수 있음.

주석을 넣고 실행하면 자식 클래스의 소멸자는 호출되지 않았지만, 부모 클래스의 소멸자는 정상적으로 호출됨
![child throw](asset/child_alloc.png)
따라서 누수가 발생하지 않음!!

</details>


### __vector_base methods

```c++
// construct n size of memory
pointer __construct_storage(size_type __n_);

// copy data of __vector_base
void __copy_data(__vector_base const& __src_);

// swap data of src and this
void __swap_data(__vector_base& __src_);

// destruct storage (only memory)
void __destruct_storage();

// get current capacity
size_type __capacity() const;

// check whether current capacity is enough to store n elements
size_type __check_size(size_type __n_);
```

### private method in vector

```c++
// push data to end of vector. (not allocate memory)
__construct_one(value_type &__v_); // push_back 하는데, 메모리 용량이 충분할때

// push range of data at specific position
__construct_point(point __pos_, size_type __n_, const_iterator __first_, const_iterator __last_);

// 메모리 재할당 후 내용을 copy
__reconstruct(size_type __new_n_);
```


### exceptions

`out_of_range`
`length_error`

constructor에서 할당 실패는 그냥 exception throw...! 따라서	`max_size()` 체크 안해도 됨

## TODO

- [ ] vector
- [ ] map
- [ ] stack
- [ ] set
  - [ ] Red-Black tree

---

- [x] iterator_traits
- [x] reverse_iterator
- [x] enable_if
- [x] is_integral
- [ ] equal and lexicographical_compare
- [ ] std::pair
- [ ] std::make_pair

# Reference

[cplusplus](https://www.cplusplus.com/)

[cppreference](https://en.cppreference.com/)

[LLVM libcxx source code (github)](https://github.com/llvm/llvm-project/tree/main/libcxx)

[gnu source code (github)](https://github.com/gcc-mirror/gcc/tree/master/libstdc%2B%2B-v3/include/bits)

[gnu docs](https://gcc.gnu.org/onlinedocs/gcc-11.2.0/libstdc++/api/files.html)
