#pragma once

#include <jsxx/core/basic_val.hpp>
#include <jsxx/core/functions.hpp>
#include <jsxx/core/operators.hpp>
#include <jsxx/core/iterators.hpp>
#include <jsxx/core/handlers.hpp>

#include <string>
#include <vector>

//
//#include <map>
//

namespace jsxx
{

  template<typename Val>
  struct trait<Val, struct simple_val_tag> {
    using bool_t = bool;
    using int_t = int;
    using real_t = double;
    using string_t = std::string;
    using pair_t = std::pair<string_t, Val>;
    using array_t = std::vector<Val>;
    using object_t = std::vector<pair_t>;
    //using object_t = std::map<string_t, Val>;
  };

  using val = basic_val<simple_val_tag>;

  namespace val_literals
  {
    inline constexpr val::k operator"" _k(val::char_t const* s, std::size_t) noexcept
    {
      return val::k(s);
    }
  }

  template<>
  struct decode_handler<val>
  {
    template<typename It, typename T>
    static int integer(It beg, It end, T& result) noexcept {
      return string_to_integer(beg, end, result);
    }

    template<typename It, typename T>
    static int real(It beg, It end, T& result) noexcept {
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

}
