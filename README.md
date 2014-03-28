jsxx
====

C++ headers-only JSON library, the C++11 way (well, kinda)

The #1 goal is to mimic the JSON syntax as close as possible straight in your C++ code.

``` c++
#include <jsxx/val.hpp>

val json = {
  "key"_k    = "value",
  "bool"_k   = true,
  "int"_k    = 42,
  "real"_k   = 3.14,
  "null"_k   = nullptr,
  "object"_k = {
    "array"_k = { 0, 1, "str", {"key"_k = 2}, false },
    "other"_k = "value"
  }
};
```

This is what jsxx does. It relies on a bunch of C++11 features, hence a recent C++ compiler is required.

Building tests requires CMAKE. Proceed as follow:

```
mkdir build
cd build
cmake ..
make
make test
```

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
It is then possible to refine the fundamental data types.

WIP.................

