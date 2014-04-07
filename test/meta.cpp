
#include <iostream>
#include <jsxx/val.hpp>
#include <cstring>
#include "lest.hpp"


using namespace jsxx;

lest::test const specs[] =
{
  {"json enum", [] {
     {
       constexpr auto n = internal::json_type_for<val, val::null_t>::value;
       static_assert(internal::json_index<n>::value == 0, "");
       constexpr auto b = internal::json_type_for<val, val::bool_t>::value;
       static_assert(internal::json_index<b>::value == 1, "");
       constexpr auto i = internal::json_type_for<val, val::int_t>::value;
       static_assert(internal::json_index<i>::value == 2, "");
       constexpr auto r = internal::json_type_for<val, val::real_t>::value;
       static_assert(internal::json_index<r>::value == 3, "");
       constexpr auto s = internal::json_type_for<val, val::string_t>::value;
       static_assert(internal::json_index<s>::value == 4, "");
       constexpr auto a = internal::json_type_for<val, val::array_t>::value;
       static_assert(internal::json_index<a>::value == 5, "");
       constexpr auto o = internal::json_type_for<val, val::object_t>::value;
       static_assert(internal::json_index<o>::value == 6, "");

       static_assert(internal::json_index_for<val, val::null_t>::value == 0, "");
       static_assert(internal::json_index_for<val, val::bool_t>::value == 1, "");
       static_assert(internal::json_index_for<val, val::int_t>::value == 2, "");
       static_assert(internal::json_index_for<val, val::real_t>::value == 3, "");
       static_assert(internal::json_index_for<val, val::string_t>::value == 4, "");
       static_assert(internal::json_index_for<val, val::array_t>::value == 5, "");
       static_assert(internal::json_index_for<val, val::object_t>::value == 6, "");
     }
     {
       constexpr auto n = internal::json_type_for<val const, val::null_t>::value;
       static_assert(internal::json_index<n>::value == 0, "");
       constexpr auto b = internal::json_type_for<val const, val::bool_t>::value;
       static_assert(internal::json_index<b>::value == 1, "");
       constexpr auto i = internal::json_type_for<val const, val::int_t>::value;
       static_assert(internal::json_index<i>::value == 2, "");
       constexpr auto r = internal::json_type_for<val const, val::real_t>::value;
       static_assert(internal::json_index<r>::value == 3, "");
       constexpr auto s = internal::json_type_for<val const, val::string_t>::value;
       static_assert(internal::json_index<s>::value == 4, "");
       constexpr auto a = internal::json_type_for<val const, val::array_t>::value;
       static_assert(internal::json_index<a>::value == 5, "");
       constexpr auto o = internal::json_type_for<val const, val::object_t>::value;
       static_assert(internal::json_index<o>::value == 6, "");

       static_assert(internal::json_index_for<val const, val::null_t>::value == 0, "");
       static_assert(internal::json_index_for<val const, val::bool_t>::value == 1, "");
       static_assert(internal::json_index_for<val const, val::int_t>::value == 2, "");
       static_assert(internal::json_index_for<val const, val::real_t>::value == 3, "");
       static_assert(internal::json_index_for<val const, val::string_t>::value == 4, "");
       static_assert(internal::json_index_for<val const, val::array_t>::value == 5, "");
       static_assert(internal::json_index_for<val const, val::object_t>::value == 6, "");
     }
     {
       constexpr auto n = internal::json_type_for<val, const val::null_t>::value;
       static_assert(internal::json_index<n>::value == 0, "");
       constexpr auto b = internal::json_type_for<val, const val::bool_t>::value;
       static_assert(internal::json_index<b>::value == 1, "");
       constexpr auto i = internal::json_type_for<val, const val::int_t>::value;
       static_assert(internal::json_index<i>::value == 2, "");
       constexpr auto r = internal::json_type_for<val, const val::real_t>::value;
       static_assert(internal::json_index<r>::value == 3, "");
       constexpr auto s = internal::json_type_for<val, const val::string_t>::value;
       static_assert(internal::json_index<s>::value == 4, "");
       constexpr auto a = internal::json_type_for<val, const val::array_t>::value;
       static_assert(internal::json_index<a>::value == 5, "");
       constexpr auto o = internal::json_type_for<val, const val::object_t>::value;
       static_assert(internal::json_index<o>::value == 6, "");

       static_assert(internal::json_index_for<val, const val::null_t>::value == 0, "");
       static_assert(internal::json_index_for<val, const val::bool_t>::value == 1, "");
       static_assert(internal::json_index_for<val, const val::int_t>::value == 2, "");
       static_assert(internal::json_index_for<val, const val::real_t>::value == 3, "");
       static_assert(internal::json_index_for<val, const val::string_t>::value == 4, "");
       static_assert(internal::json_index_for<val, const val::array_t>::value == 5, "");
       static_assert(internal::json_index_for<val, const val::object_t>::value == 6, "");
     }
     {
       constexpr auto n = internal::json_type_for<val const, const val::null_t>::value;
       static_assert(internal::json_index<n>::value == 0, "");
       constexpr auto b = internal::json_type_for<val const, const val::bool_t>::value;
       static_assert(internal::json_index<b>::value == 1, "");
       constexpr auto i = internal::json_type_for<val const, const val::int_t>::value;
       static_assert(internal::json_index<i>::value == 2, "");
       constexpr auto r = internal::json_type_for<val const, const val::real_t>::value;
       static_assert(internal::json_index<r>::value == 3, "");
       constexpr auto s = internal::json_type_for<val const, const val::string_t>::value;
       static_assert(internal::json_index<s>::value == 4, "");
       constexpr auto a = internal::json_type_for<val const, const val::array_t>::value;
       static_assert(internal::json_index<a>::value == 5, "");
       constexpr auto o = internal::json_type_for<val const, const val::object_t>::value;
       static_assert(internal::json_index<o>::value == 6, "");

       static_assert(internal::json_index_for<val const, const val::null_t>::value == 0, "");
       static_assert(internal::json_index_for<val const, const val::bool_t>::value == 1, "");
       static_assert(internal::json_index_for<val const, const val::int_t>::value == 2, "");
       static_assert(internal::json_index_for<val const, const val::real_t>::value == 3, "");
       static_assert(internal::json_index_for<val const, const val::string_t>::value == 4, "");
       static_assert(internal::json_index_for<val const, const val::array_t>::value == 5, "");
       static_assert(internal::json_index_for<val const, const val::object_t>::value == 6, "");
     }
  }},
  {"tmp", [] {
    //val v = 1;
    //auto i = get<float>(v);

  }}
};

int main() {
  return lest::run(specs);
}


