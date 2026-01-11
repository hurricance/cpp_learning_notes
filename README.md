# cpp_learning_notes

> Reference:
> [CS106L Text Book](https://cs106l.github.io/textbook/)

### Chapter 1: Types & Structs

```cpp
using: type alias
std::pair: a general purpose struct with two fields
auto: infer the type of a variable
```

### Chapter 2: Initialization & References

#### Direct initialization

```cpp
int num = 12.0
int num(12.0)
```

#### Uniform initialization(list initialization) (C++ 11)

> uniform initialization cares about types, doesn't allow for narrowing conversions
```cpp
int num{12.0} // hint error
```

#### Structed Binding (C++17)

```cpp
std::tuple<std::string, std::string, std::string> getClassInfo() {
  std::string className = "CS106L";
  std::string buildingName = "Thornton 110";
  std::string language = "C++";
  return {className, buildingName, language}; // uniform initialization
}

auto [className, buildingName, language] = getClassInfo()
```

#### Left Reference

```cpp
void shift(std::vector<std::pair<int, int>> &nums) {
  for (auto& [num1, num2] : nums) {
    num1++;
    num2++;
  }
}
```

#### Const

```cpp
const std::vector<int> const_vec{ 1, 2, 3 };
std::vector<int>& bad_ref{ const_vec }; // you can't declare a non-const reference to a const variable
```

### Chapter 3: Streams

- ios_base
  - basic_ios
    - istream
      - basic_istringstream
      - basic_ifstream
    - ostream
      - basic_ostringstream
      - basic_ofstream
    - iostream
      - basic_stringstream
      - basic_fstream

```cpp
getline(istream& is, string& str, char delim)
the delim char is by default '\n'
consumes the delim character, but not write to str
```

character in output streams are stored in an intermediary buffer before being flushed to the destination, ways to flush:
- std::flush
- std::endl
- reach the end of program
- when the buffer is full
- When tied streams interact (ie. cout has to flush before you take input via cin)

### Chapter 4: Containers

#### Sequence Containers

> sequence containers store a linear sequence of elements

##### Vector

Use const auto& when possible
```cpp
std::vector<MassiveType> vec { ... };
for (const auto& elem : vec) ...
```

operator[] does not perform bounds checking
```cpp
std::vector<int> vec{5, 6}; // {5, 6}
vec[1] = 3; // {5, 3}
vec[2] = 4; // undefined behavior
vec.at(2) = 4; // Runtime error
```

##### Deque

Array of arrays

#### Associative Containers

> associative containers organize elements by unique keys

##### std::map

std::map<k, v> stores a collection of std::pair<const k, v>, implemented by binary search tree(red-black tree)  
std::map<k, v> requires k to have an operator `<`

##### std::set

std::set is an std::map without values

##### std::unordered_map

std::unordered_map<K, V> requires K to have a hash function and equality  
you can set load_factor by using max_load_factor()

### Chapter 5: Iterators & Pointers

if one container is empty, then `begin()` and `end()` are equal

if the elements is a struct, we can access its members with `->`

all iterator operation should be in constant time

#### Iterators Categories

##### Output

an iterator is an output iterator if it supports overwriting the pointed to element via `operator=`, e.g.:
```cpp
*it = elem;
```

##### Input

an iterator is an input iterator if it supports reading the pointed to element, e.g.:
```cpp
auto elem = *it
```

##### Forward

guarantee that multiple passes are valid, if iterators `a` and `b`  point to the same element, means `a == b`, it must hold that `++a == ++b`

every STL container's iterators are forward

##### Bidirection

a kind of forward iterators that can be moved backwards as well as forwards, e.g.:
```cpp
--it;
```

##### Random Access

a bidirectional iterator that supports jumping forwards or backwards multiple elements at a time

##### Contiguous

a subset of random-access iterators that further stipulate that their elements are stored contiguously in memory

#### Iterator Flavors

iterator "falvors" alow us to handle `const` containers more appropriately

##### `const` Iterators

`std.begin()` for `const` containers and `std::cbegin()` for non `const` containers

##### Reverse Iterators

`std::rbegin()`

Reverse iterators can only exist for bidirectional iterators

### Chapter 6: Classes

structures which are classes without access restrictions  
list initialization constructor
the default access modifier of class is `private`

types of inheritance
> default is private
1. public
  - public -> public
  - protected -> protected
  - private -> not accessible in derived class
2. protected
  - public -> protected
  - protected -> protected
  - private -> not accessible in derived class
3. private
  - public -> private
  - protected -> private
  - private -> not accessible in derived class

virtual method: to implement polymorphism
- for mulitple inheritence, the first vtable will be combined with the derived class, and the rest are keeping their vtables
virtual inheritence: to avoid access ambiguity
- will not combine vtables

to know more about memory alignment of inheritence, virtual inheritence, following these:
- https://www.cnblogs.com/ThousandPine/p/18111381
- https://chillstepp.github.io/2024/06/12/%E7%8E%B0%E4%BB%A3C++%E5%92%8C%E5%86%85%E5%AD%98%E6%A8%A1%E5%9E%8B%E8%A7%86%E8%A7%92%E4%B8%8B%E7%90%86%E8%A7%A3%E8%99%9A%E5%87%BD%E6%95%B0/

### Chapter 7: Inheritence

use `override` to indicate that you're overriding a virtual method

A class with one or more pure virtual functions is an abstract class, it can’t
be instantiated

### Chapter 8: Class Templates & Const Correctness

**macro usage**
- object-like macro
- function-like macro
  - `#`: converts a macro parameter to a string literal
  - `##`: concatenates tokens
  - `\`: for line continuation, the `\` must be the last character on the line
  - Variadic Macros
    - all variable can be replaced with `__VA_ARGS__`
    - to omit comma if `__VA_ARGS__` is empty, use `##__VA_ARGS__`

Non-type Template Parameters:
```cpp
template<typename T, std::size_t N>
struct std::array { /* ... */ };
```

A few template quirks:
- Must copy `template <…>` syntax in .cpp
```cpp
template <typename T>
T& Vector<T>::at(size_t i) {
// Implementation...
}
```
- .h must include .cpp at bottom of file
- `typename` is the same as `class`

`const` method: promise to not modify class member, `const` object can only invoke `const` member function

`const_cast`: used to cast away the const
`mutable` keyword: circumvent const protections

### Chapter 9: Template Functions

`concept`: used to add constrainst for template

cursive template:
Variadic types don’t have to be the same
```cpp
template <Comparable T>
T min(const T& v) { return v; }
template <Comparable T, Comparable... Args>
T min(const T& v, const Args&... args) {
  auto m = min(args...);
  return v < m ? v : m;
}
```

Template Metaprogramming
```cpp
template <>
struct Factorial<0> {
  enum { value = 1 };
};
template <size_t N>
struct Factorial {
  enum { value = N * Factorial<N - 1>::value };
};
std::cout << Factorial<7>::value << std::endl;
```
substitution: `constexpr` or `consteval`

