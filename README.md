jsxx [![Build Status](https://drone.io/github.com/metagoto/jsxx/status.png)](https://drone.io/github.com/metagoto/jsxx/latest) [![Build Status](https://travis-ci.org/metagoto/jsxx.svg?branch=master)](https://travis-ci.org/metagoto/jsxx)
====

A C++11 header-only JSON library.


The #1 goal is to mimic the JSON syntax as close as possible straight into your C++ code.

``` c++
val json = {
  "key"_k    = "value",
  "bool"_k   = true,
  "int"_k    = 42,
  "real"_k   = 3.14,
  "null"_k   = nullptr,
  "object"_k = {
    "array"_k = { 0, 1, "str", { "key"_k = 2 }, false },
    "other"_k = "value"
  }
};
```

This is what jsxx does. It relies on a bunch of C++11 features, hence a recent C++ compiler is required.


Usage
-----

The library is header-only. No need to build anything. To use it in you project, make your compiler aware of the jsxx include path (`-I/path/to/jsxx/include`) and enable the C++11 support with `-std=c++11` for clang or gcc.

Quick example:

``` c++
#include <iostream>
#include <jsxx/val.hpp>
#include <jsxx/reader.hpp>
#include <jsxx/writer.hpp>

using namespace jsxx;

// import val's literal _k into current namespace
using namespace jsxx::val_literals;

int main() {

  // [true, false, null]
  val arr = { true, false, nullptr };

  // { "hello": "world" }
  val obj = { "hello"_k = "world" };

  // add a new entry
  obj["arr"] = arr;

  // textual json
  std::string json = R"(
    { "hello": "world", "arr": [true, false, null] }
  )";

  // read it into a val
  auto obj2 = read<val>(json);

  // this should be true
  if (obj == obj2) {
    std::cout << obj << std::endl;
  }
}
```


Test
----

Building tests requires CMAKE. From the directory where `CMakeLists.txt` resides, proceed as follow:

```
mkdir build
cd build
cmake ..
make
make test
```


Customization
-------------

Under the hood `val` resides in the `jsxx` namespace and is defined as:

``` c++
using val = basic_val<simple_val_tag>;
```

Such a `basic_val` is statically configured with the following traits specialization:

``` c++
template<typename Val>
struct trait<Val, struct simple_val_tag> {
  using bool_t = bool;
  using real_t = double;
  using int_t = int;
  using string_t = std::string;
  using pair_t = std::pair<string_t, Val>;
  using array_t = std::vector<Val>;
  using object_t = std::vector<pair_t>;
};
```

It is then possible to customize the fundamental data types.

When converting textual JSON data to C++ types, the decode routines can be statically selected for the specific `basic_val` in use. Yet again it is a matter of template specialization:

``` c++
template<>
struct decode_handler<val>
{
  template<typename It, typename T>
  static int integer(It beg, It end, T& result) {
    return string_to_integer(beg, end, result);
  }
  template<typename It, typename T>
  static int real(It beg, It end, T& result) {
    return string_to_real(beg, end, result);
  }
  template<typename It, typename T>
  static int string(It beg, It end, T& result) {
    return decode_string(beg, end, result);
  }
  template<typename It, typename T>
  static int key_string(It beg, It end, T& result) {
    return decode_string(beg, end, result);
  }
};
```

The default provided decode routines (`string_to_integer` etc) are quite efficient and able to work with the most common C++ types without change.


WIP.................

