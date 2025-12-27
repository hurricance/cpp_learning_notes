# cpp_learning_notes

> Reference:
> [CS106L Text Book](https://cs106l.github.io/textbook/)

## Chapter 1: Types & Structs

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

>> uniform initialization cares about types, doesn't allow for narrowing conversions
```cpp
int num{12.0}
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
      - basic_istringstrema
      - basic_ifstream
    - ostream
      - basic_ostringstrema
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

>> sequence containers store a linear sequence of elements

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

>> associative containers organize elements by unique keys

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