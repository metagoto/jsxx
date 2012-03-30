jsxx
====

C++ headers-only JSON library, the C++11 way (well, kinda)

``` c++
val json =
{
    "key"_k   = "value",
    "bool"_k  = true,
    "int"_k   = 42,
    "real"_k  = 3.14,
    "null"_k  = null,
    "object"_k=
    {
        "array"_k = { 0, 1, "str", {"key"_k = 2}, false },
        "other"_k = "value"
    }
};
```
..WIP..
