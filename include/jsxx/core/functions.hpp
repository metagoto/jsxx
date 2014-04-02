#pragma once

#include <jsxx/core/prologue.hpp>


namespace jsxx
{

  template<typename T>
  inline bool is_null(basic_val<T> const& v)
  { return v.type() == value::null; }

  template<typename T>
  inline bool is_boolean(basic_val<T> const& v)
  { return v.type() == value::boolean; }

  template<typename T>
  inline bool is_bool(basic_val<T> const& v)
  { return is_boolean(v); }

  template<typename T>
  inline bool is_integer(basic_val<T> const& v)
  { return v.type() == value::integer; }

  template<typename T>
  inline bool is_int(basic_val<T> const& v)
  { return is_integer(v); }

  template<typename T>
  inline bool is_real(basic_val<T> const& v)
  { return v.type() == value::real; }

  template<typename T>
  inline bool is_double(basic_val<T> const& v)
  { return is_real(v); }

  template<typename T>
  inline bool is_string(basic_val<T> const& v)
  { return v.type() == value::string; }

  template<typename T>
  inline bool is_array(basic_val<T> const& v)
  { return v.type() == value::array; }

  template<typename T>
  inline bool is_object(basic_val<T> const& v)
  { return v.type() == value::object; }

  template<typename T>
  inline bool is_number(basic_val<T> const& v)
  { return is_integer(v) || is_real(v); }


  namespace internal
  {
    namespace {
      template<typename T, typename U>
      using cqual = typename std::conditional<std::is_const<T>::value, U const, U>::type;
    }

    struct get_tag {};

    template<typename T>
    struct access<T, get_tag, typename T::boolean> {
      static cqual<T, typename T::boolean>* get(T& v) {
        if (v.type() == value::boolean)
          return &v.b_;
        return nullptr;
      }
    };
    template<typename T>
    struct access<T, get_tag, typename T::integer> {
      static cqual<T, typename T::integer>* get(T& v) {
        if (v.type() == value::integer)
          return &v.i_;
        return nullptr;
      }
    };
    template<typename T>
    struct access<T, get_tag, typename T::real> {
      static cqual<T, typename T::real>* get(T& v) {
        if (v.type() == value::real)
          return &v.r_;
        return nullptr;
      }
    };
    template<typename T>
    struct access<T, get_tag, typename T::string> {
      static cqual<T, typename T::string>* get(T& v) {
        if (v.type() == value::string)
          return &v.s_;
        return nullptr;
      }
    };
    template<typename T>
    struct access<T, get_tag, typename T::array> {
      static cqual<T, typename T::array>* get(T& v) {
        if (v.type() == value::array)
          return &v.a_;
        return nullptr;
      }
    };
    template<typename T>
    struct access<T, get_tag, typename T::object> {
      static cqual<T, typename T::object>* get(T& v) {
        if (v.type() == value::object)
          return &v.o_;
        return nullptr;
      }
    };
  }


  template<typename R, typename T>
  inline R& get(basic_val<T>& v) {
    R* r = internal::access<basic_val<T>, internal::get_tag, R>::get(v);
    if (r)
      return *r;
    throw type_error("wrong type");
  }

  template<typename R, typename T>
  inline R const& get(basic_val<T> const& v) {
    R const* r = internal::access<basic_val<T> const, internal::get_tag, R>::get(v);
    if (r)
      return *r;
    throw type_error("wrong type");
  }

  template<typename R, typename T>
  inline R* get(basic_val<T>* v) {
    return v ? internal::access<basic_val<T>, internal::get_tag, R>::get(*v) : nullptr;
  }

  template<typename R, typename T>
  inline R const* get(basic_val<T> const* v) {
    return v ? internal::access<basic_val<T> const, internal::get_tag, R>::get(*v) : nullptr;
  }


  //
  template<typename T>
  inline auto get_boolean(basic_val<T> const& v) -> typename basic_val<T>::boolean const& {
    return get<typename basic_val<T>::boolean>(v);
  }
  template<typename T>
  inline auto get_boolean(basic_val<T>& v) -> typename basic_val<T>::boolean& {
    return get<typename basic_val<T>::boolean>(v);
  }
  template<typename T>
  inline auto get_bool(basic_val<T> const& v) -> typename basic_val<T>::boolean const& {
    return get_boolean(v);
  }
  template<typename T>
  inline auto get_bool(basic_val<T>& v) -> typename basic_val<T>::boolean& {
    return get_boolean(v);
  }

  template<typename T>
  inline auto get_boolean(basic_val<T> const* v) -> typename basic_val<T>::boolean const* {
    return get<typename basic_val<T>::boolean>(v);
  }
  template<typename T>
  inline auto get_boolean(basic_val<T>* v) -> typename basic_val<T>::boolean* {
    return get<typename basic_val<T>::boolean>(v);
  }
  template<typename T>
  inline auto get_bool(basic_val<T> const* v) -> typename basic_val<T>::boolean const* {
    return get_boolean(v);
  }
  template<typename T>
  inline auto get_bool(basic_val<T>* v) -> typename basic_val<T>::boolean* {
    return get_boolean(v);
  }
  //
  template<typename T>
  inline auto get_integer(basic_val<T> const& v) -> typename basic_val<T>::integer const& {
    return get<typename basic_val<T>::integer>(v);
  }
  template<typename T>
  inline auto get_integer(basic_val<T>& v) -> typename basic_val<T>::integer& {
    return get<typename basic_val<T>::integer>(v);
  }
  template<typename T>
  inline auto get_int(basic_val<T> const& v) -> typename basic_val<T>::integer const& {
    return get_integer(v);
  }
  template<typename T>
  inline auto get_int(basic_val<T>& v) -> typename basic_val<T>::integer& {
    return get_integer(v);
  }

  template<typename T>
  inline auto get_integer(basic_val<T> const* v) -> typename basic_val<T>::integer const* {
    return get<typename basic_val<T>::integer>(v);
  }
  template<typename T>
  inline auto get_integer(basic_val<T>* v) -> typename basic_val<T>::integer* {
    return get<typename basic_val<T>::integer>(v);
  }
  template<typename T>
  inline auto get_int(basic_val<T> const* v) -> typename basic_val<T>::integer const* {
    return get_integer(v);
  }
  template<typename T>
  inline auto get_int(basic_val<T>* v) -> typename basic_val<T>::integer* {
    return get_integer(v);
  }
  //
  template<typename T>
  inline auto get_real(basic_val<T> const& v) -> typename basic_val<T>::real const& {
    return get<typename basic_val<T>::real>(v);
  }
  template<typename T>
  inline auto get_real(basic_val<T>& v) -> typename basic_val<T>::real& {
    return get<typename basic_val<T>::real>(v);
  }
  template<typename T>
  inline auto get_double(basic_val<T> const& v) -> typename basic_val<T>::real const& {
    return get_real(v);
  }
  template<typename T>
  inline auto get_double(basic_val<T>& v) -> typename basic_val<T>::real& {
    return get_real(v);
  }

  template<typename T>
  inline auto get_real(basic_val<T> const* v) -> typename basic_val<T>::real const* {
    return get<typename basic_val<T>::real>(v);
  }
  template<typename T>
  inline auto get_real(basic_val<T>* v) -> typename basic_val<T>::real* {
    return get<typename basic_val<T>::real>(v);
  }
  template<typename T>
  inline auto get_double(basic_val<T> const* v) -> typename basic_val<T>::real const* {
    return get_real(v);
  }
  template<typename T>
  inline auto get_double(basic_val<T>* v) -> typename basic_val<T>::real* {
    return get_real(v);
  }
  //
  template<typename T>
  inline auto get_string(basic_val<T> const& v) -> typename basic_val<T>::string const& {
    return get<typename basic_val<T>::string>(v);
  }
  template<typename T>
  inline auto get_string(basic_val<T>& v) -> typename basic_val<T>::string& {
    return get<typename basic_val<T>::string>(v);
  }

  template<typename T>
  inline auto get_string(basic_val<T> const* v) -> typename basic_val<T>::string const* {
    return get<typename basic_val<T>::string>(v);
  }
  template<typename T>
  inline auto get_string(basic_val<T>* v) -> typename basic_val<T>::string* {
    return get<typename basic_val<T>::string>(v);
  }
  //
  template<typename T>
  inline auto get_array(basic_val<T> const& v) -> typename basic_val<T>::array const& {
    return get<typename basic_val<T>::array>(v);
  }
  template<typename T>
  inline auto get_array(basic_val<T>& v) -> typename basic_val<T>::array& {
    return get<typename basic_val<T>::array>(v);
  }

  template<typename T>
  inline auto get_array(basic_val<T> const* v) -> typename basic_val<T>::array const* {
    return get<typename basic_val<T>::array>(v);
  }
  template<typename T>
  inline auto get_array(basic_val<T>* v) -> typename basic_val<T>::array* {
    return get<typename basic_val<T>::array>(v);
  }
  //
  template<typename T>
  inline auto get_object(basic_val<T> const& v) -> typename basic_val<T>::object const& {
    return get<typename basic_val<T>::object>(v);
  }
  template<typename T>
  inline auto get_object(basic_val<T>& v) -> typename basic_val<T>::object& {
    return get<typename basic_val<T>::object>(v);
  }

  template<typename T>
  inline auto get_object(basic_val<T> const* v) -> typename basic_val<T>::object const* {
    return get<typename basic_val<T>::object>(v);
  }
  template<typename T>
  inline auto get_object(basic_val<T>* v) -> typename basic_val<T>::object* {
    return get<typename basic_val<T>::object>(v);
  }

  //
  template<typename T>
  inline auto as_boolean(basic_val<T> const& v) -> typename basic_val<T>::boolean {
    using V = basic_val<T>;
    if (is_boolean(v)) return get<typename V::boolean>(v);
    if (is_integer(v)) return get<typename V::integer>(v);
    if (is_real(v)) return get<typename V::real>(v);
    if (is_string(v)) return !get<typename V::string>(v).empty();
    if (is_array(v)) return !get<typename V::array>(v).empty();
    if (is_object(v)) return !get<typename V::object>(v).empty();
    return false;
  }
  template<typename T>
  inline auto as_bool(basic_val<T> const& v) -> typename basic_val<T>::boolean {
    return as_boolean(v);
  }

  template<typename T>
  inline auto as_integer(basic_val<T> const& v) -> typename basic_val<T>::integer {
    using V = basic_val<T>;
    if (is_boolean(v)) return get<typename V::boolean>(v);
    if (is_integer(v)) return get<typename V::integer>(v);
    if (is_real(v)) return get<typename V::real>(v);
    if (is_string(v)) return get<typename V::string>(v).size();
    if (is_array(v)) return get<typename V::array>(v).size();
    if (is_object(v)) return get<typename V::object>(v).size();
    return 0;
  }
  template<typename T>
  inline auto as_int(basic_val<T> const& v) -> typename basic_val<T>::integer {
    return as_integer(v);
  }

  template<typename T>
  inline auto as_real(basic_val<T> const& v) -> typename basic_val<T>::real {
    using V = basic_val<T>;
    if (is_boolean(v)) return get<typename V::boolean>(v);
    if (is_integer(v)) return get<typename V::integer>(v);
    if (is_real(v)) return get<typename V::real>(v);
    if (is_string(v)) return get<typename V::string>(v).size();
    if (is_array(v)) return get<typename V::array>(v).size();
    if (is_object(v)) return get<typename V::object>(v).size();
    return 0.;
  }
  template<typename T>
  inline auto as_double(basic_val<T> const& v) -> typename basic_val<T>::real {
    return as_real(v);
  }

  namespace internal
  {
    struct cast_tag {};
    template<typename T, typename U>
    struct access<T, cast_tag, U>
    {
      struct arith {};
      struct not_arith {};
      static U cast_impl(T const& v, arith) {
        if (is_boolean(v)) return get<typename T::boolean>(v);
        if (is_integer(v)) return get<typename T::integer>(v);
        if (is_real(v)) return get<typename T::real>(v);
        throw type_error("invalid cast to arithmetic type");
      }
      static U cast_impl(T const& v, not_arith) {
        return get<U>(v);
      }
      static U cast(T const& v) {
        return cast_impl(v
          ,typename std::conditional<std::is_arithmetic<U>::value, arith, not_arith>::type());
      }
    };


    template<typename T>
    inline void ensure(basic_val<T> const& v, value type) {
      if (v.type() != type)
        throw type_error("wrong value type");
    }

    template<typename T>
    inline void ensure_any(basic_val<T> const& v, value type1, value type2) {
      if (v.type() != type1 && v.type() != type2)
        throw type_error("wrong value type");
    }

  }


  namespace internal {

    struct container_tag {};

    template<typename T>
    struct access<T, container_tag>
    {
      static bool in(T const& v, std::size_t index) {
        ensure(v, value::array);
        return index < v.a_.size();
      }

      static bool in(T const& v, typename T::char_t const* key) {
        return find(v, key) != v.o_.end();
      }

      static bool del(T& v, std::size_t index) {
        ensure(v, value::array);
        if (index < v.a_.size()) {
          v.a_.erase(std::begin(v.a_)+index);
          return true;
        }
        return false;
      }

      static bool del(T& v, typename T::char_t const* key) {
        auto it = find(v, key);
        if (it != v.o_.end()) {
          v.o_.erase(it);
          return true;
        }
        return false;
      }

      template<typename U>
      static auto find(U&& v, typename T::char_t const* key) -> decltype(v.o_.end()) {
        ensure(v, value::object);
        return std::find_if(v.o_.begin(), v.o_.end(), [&key](typename T::pair const& p){
          return p.first == key;
        });
      }
    };
  }


  // object
  template<typename T>
  inline bool in(basic_val<T> const& v, typename basic_val<T>::char_t const* key) {
    return internal::access<basic_val<T>, internal::container_tag>::in(v, key);
  }

  template<typename T>
  inline bool in(basic_val<T> const& v, typename basic_val<T>::string const& key) {
    return in(v, key.c_str());
  }

  // array
  template<typename T>
  inline bool in(basic_val<T> const& v, std::size_t index) {
    return internal::access<basic_val<T>, internal::container_tag>::in(v, index);
  }

  // array or object
  template<typename T>
  inline bool in(basic_val<T> const& v, basic_val<T> const& key_or_index) {
    internal::ensure_any(v, value::object, value::array);
    if (is_object(v)) {
      if (is_string(key_or_index))
        return in(v, get<typename basic_val<T>::string>(key_or_index).c_str());
      throw type_error("key is not convertible to a string");
    }
    // else: array
    if (is_integer(key_or_index))
      return in(v, get<typename basic_val<T>::integer>(key_or_index));
    throw type_error("index is not convertible to an integer");
  }


  // delete key from object
  template<typename T>
  inline bool del(basic_val<T>& v, typename basic_val<T>::char_t const* key) {
    return internal::access<basic_val<T>, internal::container_tag>::del(v, key);
  }

  template<typename T>
  inline bool del(basic_val<T>& v, typename basic_val<T>::string const& key) {
    return del(v, key.c_str());
  }

  // delete index from array
  template<typename T>
  inline bool del(basic_val<T>& v, std::size_t index) {
    return internal::access<basic_val<T>, internal::container_tag>::del(v, index);
  }

  // array or object
  template<typename T>
  inline bool del(basic_val<T>& v, basic_val<T> const& key_or_index) {
    internal::ensure_any(v, value::object, value::array);
    if (is_object(v)) {
      if (is_string(key_or_index))
        return del(v, get<typename basic_val<T>::string>(key_or_index).c_str());
      throw type_error("key is not convertible to a string");
    }
    // else: array
    if (is_integer(key_or_index))
      return del(v, get<typename basic_val<T>::integer>(key_or_index));
    throw type_error("index is not convertible to an integer");
  }


}




//namespace jsxx
//{
//  namespace internal_TMPPPPP
//  {

//    template<typename T, typename V>
//    struct access<T, V>
//    {
//      template<typename U>
//      static auto get(U& v)
//        -> typename std::enable_if<std::is_integral<V>::value, cqual<U, V>>::type
//      {
//        if (v.type() == value::integer)
//          return reinterpret_cast<cqual<U,V>>(&v.i_);
//        return nullptr;
//      }

//      template<typename U>
//      static auto get(U& v)
//        -> typename std::enable_if<std::is_floating_point<V>::value, cqual<U,V>>::type
//      {
//        if (v.type() == value::real)
//          return reinterpret_cast<cqual<U,V>>(&v.r_);
//        return nullptr;
//      }
//    };

//    /// SPECIALIZATION FOR NULLPTR
//    template<typename T>
//    struct access<T, typename T::null_t>
//    {
//      static cqual<T, typename T::null_t> get(T& v) {
//        static constexpr std::nullptr_t const n = nullptr;
//        if (v.type() == value::null)
//          return &n;
//        return nullptr;
//      }
//    };
//  }
//} // ns
