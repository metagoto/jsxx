jsxx
====

A C++ header only JSON library, the C++11 way (well, kinda).

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

The library is header only. No need to build anything. Make your compiler aware of the jsxx include path (`-I/path/to/jsxx/include`) and enable the C++11 support with `-std=c++11` for clang or gcc.


Test
----

Building tests requires CMAKE. Proceed as follow:

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

WIP.................

