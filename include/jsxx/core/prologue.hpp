#pragma once

#include <jsxx/core/meta.hpp>
#include <jsxx/core/exceptions.hpp>
#include <initializer_list>
#include <type_traits>
#include <algorithm>
#include <iterator>
#include <limits>
#include <cmath>
#include <cstddef>


namespace jsxx {


  template<typename Self, typename Tag> struct trait;

  enum struct json : char {
    null,
    boolean,
    integer,
    real,
    string,
    array,
    object
  };

  namespace empty {
    struct array_t {};
    struct object_t {};

    // predefined constants
    constexpr array_t const array = {};
    constexpr object_t const object = {};
  }

  template<typename Tag>
  struct basic_val;


  template<typename T>
  struct decode_handler;


  namespace internal {
    template<typename, typename, typename = void> struct access;

    struct assoc {};
    struct not_assoc {};
  }

  namespace grammar {
    //////////// TO BE MOVED!!!
    //enum class kind : int {
    namespace token { enum {
      string = 1,
      integer,
      real,
      object,
      array,
      true_,
      false_,
      null
    };
    }
    ///////////////
  }

}
