#pragma once

#include <jsxx/core/prologue.hpp>


namespace jsxx
{

  template<typename T>
  inline bool is_null(basic_val<T> const& v) noexcept
  { return v.type() == json::null; }

  template<typename T>
  inline bool is_boolean(basic_val<T> const& v) noexcept
  { return v.type() == json::boolean; }

  template<typename T>
  inline bool is_bool(basic_val<T> const& v) noexcept
  { return is_boolean(v); }

  template<typename T>
  inline bool is_integer(basic_val<T> const& v) noexcept
  { return v.type() == json::integer; }

  template<typename T>
  inline bool is_int(basic_val<T> const& v) noexcept
  { return is_integer(v); }

  template<typename T>
  inline bool is_real(basic_val<T> const& v) noexcept
  { return v.type() == json::real; }

  template<typename T>
  inline bool is_double(basic_val<T> const& v) noexcept
  { return is_real(v); }

  template<typename T>
  inline bool is_string(basic_val<T> const& v) noexcept
  { return v.type() == json::string; }

  template<typename T>
  inline bool is_array(basic_val<T> const& v) noexcept
  { return v.type() == json::array; }

  template<typename T>
  inline bool is_object(basic_val<T> const& v) noexcept
  { return v.type() == json::object; }

  template<typename T>
  inline bool is_number(basic_val<T> const& v) noexcept
  { return is_integer(v) || is_real(v); }


  namespace internal
  {
    template<typename T>
    inline void ensure(basic_val<T> const& v, json type) {
      if (v.type() != type)
        throw type_error("wrong json type");
    }

    namespace {
      template<typename T>
      inline bool ensure_any_impl(basic_val<T> const&) {
        return false;
      }

      template<typename T, typename... Type>
      inline bool ensure_any_impl(basic_val<T> const& v, json type, Type... types) {
        return v.type() == type || ensure_any_impl(v, types...);
      }
    }

    template<typename T, typename... Type>
    inline void ensure_any(basic_val<T> const& v, Type... types) {
      ensure_any_impl(v, types...) || (throw type_error("wrong json type"), false);
    }
  }


  namespace internal
  {
    template<typename T, typename R>
    struct json_type_for {
      using r = typename std::decay<R>::type;
      using ts = typename T::types_t;
      using u = std::underlying_type<json>::type;
      static constexpr const int i = meta::index_of<r, ts>::value;
      static_assert(i >= 0, "");
      static constexpr const auto d = static_cast<u>(json::null) + static_cast<u>(i);
      static constexpr const json value = static_cast<json>(d);
    };

    template<json J>
    struct json_index {
      using u = std::underlying_type<json>::type;
      static constexpr const auto value = static_cast<u>(J);
    };

    template<typename T, typename R>
    struct json_index_for {
      static constexpr const auto value = json_index<json_type_for<T, R>::value>::value;
    };
  }


  namespace internal
  {
    namespace {
      template<typename T, typename U>
      using cqual = typename std::conditional<std::is_const<T>::value, U const, U>::type;
    }

    struct get_tag {};

    template<typename T, typename R>
    struct access<T, get_tag, R> {
      using r = typename std::decay<R>::type;
      static constexpr const auto i = json_index_for<T, r>::value;
      static_assert(i > 0 && i < 7, "you don't want to do that. do you?");
      using cr = cqual<T, r>;
      static cr* get(T& v) noexcept {
        switch (i) {
          case 1: return reinterpret_cast<cr*>(&v.b_);
          case 2: return reinterpret_cast<cr*>(&v.i_);
          case 3: return reinterpret_cast<cr*>(&v.r_);
          case 4: return reinterpret_cast<cr*>(&v.s_);
          case 5: return reinterpret_cast<cr*>(&v.a_);
          case 6: return reinterpret_cast<cr*>(&v.o_);
          default: return nullptr;
        }
      }
    };

    template<typename R, typename T>
    inline /*constexpr*/ cqual<T, typename std::decay<R>::type>* get(T& v) noexcept {
      constexpr const auto t = json_type_for<T, R>::value;
      if (v.type() == t)
        return access<T, get_tag, R>::get(v);
      return nullptr;
    }
  }

  template<typename R, typename T>
  inline R& get(basic_val<T>& v) {
    R* r = internal::get<R>(v);
    if (r)
      return *r;
    throw type_error("wrong type");
  }

  template<typename R, typename T>
  inline R const& get(basic_val<T> const& v) {
    R const* r = internal::get<R>(v);
    if (r)
      return *r;
    throw type_error("wrong type");
  }

  template<typename R, typename T>
  inline R* get(basic_val<T>* v) noexcept {
    return v ? internal::get<R>(*v) : nullptr;
  }

  template<typename R, typename T>
  inline R const* get(basic_val<T> const* v) noexcept {
    return v ? internal::get<R>(*v) : nullptr;
  }


  //
  template<typename T>
  inline auto get_boolean(basic_val<T> const& v) -> typename basic_val<T>::bool_t const& {
    return get<typename basic_val<T>::bool_t>(v);
  }
  template<typename T>
  inline auto get_boolean(basic_val<T>& v) -> typename basic_val<T>::bool_t& {
    return get<typename basic_val<T>::bool_t>(v);
  }
  template<typename T>
  inline auto get_bool(basic_val<T> const& v) -> typename basic_val<T>::bool_t const& {
    return get_boolean(v);
  }
  template<typename T>
  inline auto get_bool(basic_val<T>& v) -> typename basic_val<T>::bool_t& {
    return get_boolean(v);
  }

  template<typename T>
  inline auto get_boolean(basic_val<T> const* v) noexcept -> typename basic_val<T>::bool_t const* {
    return get<typename basic_val<T>::bool_t>(v);
  }
  template<typename T>
  inline auto get_boolean(basic_val<T>* v) noexcept -> typename basic_val<T>::bool_t* {
    return get<typename basic_val<T>::bool_t>(v);
  }
  template<typename T>
  inline auto get_bool(basic_val<T> const* v) noexcept -> typename basic_val<T>::bool_t const* {
    return get_boolean(v);
  }
  template<typename T>
  inline auto get_bool(basic_val<T>* v) noexcept -> typename basic_val<T>::bool_t* {
    return get_boolean(v);
  }
  //
  template<typename T>
  inline auto get_integer(basic_val<T> const& v) -> typename basic_val<T>::int_t const& {
    return get<typename basic_val<T>::int_t>(v);
  }
  template<typename T>
  inline auto get_integer(basic_val<T>& v) -> typename basic_val<T>::int_t& {
    return get<typename basic_val<T>::int_t>(v);
  }
  template<typename T>
  inline auto get_int(basic_val<T> const& v) -> typename basic_val<T>::int_t const& {
    return get_integer(v);
  }
  template<typename T>
  inline auto get_int(basic_val<T>& v) -> typename basic_val<T>::int_t& {
    return get_integer(v);
  }

  template<typename T>
  inline auto get_integer(basic_val<T> const* v) noexcept -> typename basic_val<T>::int_t const* {
    return get<typename basic_val<T>::int_t>(v);
  }
  template<typename T>
  inline auto get_integer(basic_val<T>* v) noexcept -> typename basic_val<T>::int_t* {
    return get<typename basic_val<T>::int_t>(v);
  }
  template<typename T>
  inline auto get_int(basic_val<T> const* v) noexcept -> typename basic_val<T>::int_t const* {
    return get_integer(v);
  }
  template<typename T>
  inline auto get_int(basic_val<T>* v) noexcept -> typename basic_val<T>::int_t* {
    return get_integer(v);
  }
  //
  template<typename T>
  inline auto get_real(basic_val<T> const& v) -> typename basic_val<T>::real_t const& {
    return get<typename basic_val<T>::real_t>(v);
  }
  template<typename T>
  inline auto get_real(basic_val<T>& v) -> typename basic_val<T>::real_t& {
    return get<typename basic_val<T>::real_t>(v);
  }
  template<typename T>
  inline auto get_double(basic_val<T> const& v) -> typename basic_val<T>::real_t const& {
    return get_real(v);
  }
  template<typename T>
  inline auto get_double(basic_val<T>& v) -> typename basic_val<T>::real_t& {
    return get_real(v);
  }

  template<typename T>
  inline auto get_real(basic_val<T> const* v) noexcept -> typename basic_val<T>::real_t const* {
    return get<typename basic_val<T>::real_t>(v);
  }
  template<typename T>
  inline auto get_real(basic_val<T>* v) noexcept -> typename basic_val<T>::real_t* {
    return get<typename basic_val<T>::real_t>(v);
  }
  template<typename T>
  inline auto get_double(basic_val<T> const* v) noexcept -> typename basic_val<T>::real_t const* {
    return get_real(v);
  }
  template<typename T>
  inline auto get_double(basic_val<T>* v) noexcept -> typename basic_val<T>::real_t* {
    return get_real(v);
  }
  //
  template<typename T>
  inline auto get_string(basic_val<T> const& v) -> typename basic_val<T>::string_t const& {
    return get<typename basic_val<T>::string_t>(v);
  }
  template<typename T>
  inline auto get_string(basic_val<T>& v) -> typename basic_val<T>::string_t& {
    return get<typename basic_val<T>::string_t>(v);
  }

  template<typename T>
  inline auto get_string(basic_val<T> const* v) noexcept -> typename basic_val<T>::string_t const* {
    return get<typename basic_val<T>::string_t>(v);
  }
  template<typename T>
  inline auto get_string(basic_val<T>* v) noexcept -> typename basic_val<T>::string_t* {
    return get<typename basic_val<T>::string_t>(v);
  }
  //
  template<typename T>
  inline auto get_array(basic_val<T> const& v) -> typename basic_val<T>::array_t const& {
    return get<typename basic_val<T>::array_t>(v);
  }
  template<typename T>
  inline auto get_array(basic_val<T>& v) -> typename basic_val<T>::array_t& {
    return get<typename basic_val<T>::array_t>(v);
  }

  template<typename T>
  inline auto get_array(basic_val<T> const* v) noexcept -> typename basic_val<T>::array_t const* {
    return get<typename basic_val<T>::array_t>(v);
  }
  template<typename T>
  inline auto get_array(basic_val<T>* v) noexcept -> typename basic_val<T>::array_t* {
    return get<typename basic_val<T>::array_t>(v);
  }
  //
  template<typename T>
  inline auto get_object(basic_val<T> const& v) -> typename basic_val<T>::object_t const& {
    return get<typename basic_val<T>::object_t>(v);
  }
  template<typename T>
  inline auto get_object(basic_val<T>& v) -> typename basic_val<T>::object_t& {
    return get<typename basic_val<T>::object_t>(v);
  }

  template<typename T>
  inline auto get_object(basic_val<T> const* v) noexcept -> typename basic_val<T>::object_t const* {
    return get<typename basic_val<T>::object_t>(v);
  }
  template<typename T>
  inline auto get_object(basic_val<T>* v) noexcept -> typename basic_val<T>::object_t* {
    return get<typename basic_val<T>::object_t>(v);
  }

  //
  template<typename T>
  inline auto as_boolean(basic_val<T> const& v) noexcept -> typename basic_val<T>::bool_t {
    using V = basic_val<T>;
    if (is_boolean(v)) return get<typename V::bool_t>(v);
    if (is_integer(v)) return get<typename V::int_t>(v);
    if (is_real(v)) return get<typename V::real_t>(v);
    if (is_string(v)) return !get<typename V::string_t>(v).empty();
    if (is_array(v)) return !get<typename V::array_t>(v).empty();
    if (is_object(v)) return !get<typename V::object_t>(v).empty();
    return false;
  }
  template<typename T>
  inline auto as_bool(basic_val<T> const& v) noexcept -> typename basic_val<T>::bool_t {
    return as_boolean(v);
  }

  template<typename T>
  inline auto as_integer(basic_val<T> const& v) noexcept -> typename basic_val<T>::int_t {
    using V = basic_val<T>;
    if (is_boolean(v)) return get<typename V::bool_t>(v);
    if (is_integer(v)) return get<typename V::int_t>(v);
    if (is_real(v)) return get<typename V::real_t>(v);
    if (is_string(v)) return get<typename V::string_t>(v).size();
    if (is_array(v)) return get<typename V::array_t>(v).size();
    if (is_object(v)) return get<typename V::object_t>(v).size();
    return 0;
  }
  template<typename T>
  inline auto as_int(basic_val<T> const& v) noexcept -> typename basic_val<T>::int_t {
    return as_integer(v);
  }

  template<typename T>
  inline auto as_real(basic_val<T> const& v) noexcept -> typename basic_val<T>::real_t {
    using V = basic_val<T>;
    if (is_boolean(v)) return get<typename V::bool_t>(v);
    if (is_integer(v)) return get<typename V::int_t>(v);
    if (is_real(v)) return get<typename V::real_t>(v);
    if (is_string(v)) return get<typename V::string_t>(v).size();
    if (is_array(v)) return get<typename V::array_t>(v).size();
    if (is_object(v)) return get<typename V::object_t>(v).size();
    return 0.;
  }
  template<typename T>
  inline auto as_double(basic_val<T> const& v) noexcept -> typename basic_val<T>::real_t {
    return as_real(v);
  }

  namespace internal //TODO: merge as_blah() with access<T,cast_tag,U>. + specialization
  {
    struct cast_tag {};
    template<typename T, typename U>
    struct access<T, cast_tag, U>
    {
      struct arith {};
      struct not_arith {};
      static U cast_impl(T const& v, arith) {
        if (is_boolean(v)) return get<typename T::bool_t>(v);
        if (is_integer(v)) return get<typename T::int_t>(v);
        if (is_real(v)) return get<typename T::real_t>(v);
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
  }


  // generic cast/conversion
  template<typename R, typename T>
  inline R as(basic_val<T> const& v) {
    return internal::access<basic_val<T> const, internal::cast_tag, R>::cast(v);
  }



  namespace internal {

    struct container_tag {};

    template<typename T>
    struct access<T, container_tag>
    {
      static bool in(T const& v, std::size_t index) {
        ensure(v, json::array);
        return index < v.a_.size();
      }

      static bool in(T const& v, typename T::char_t const* key) {
        ensure(v, json::object);
        return find(v, key) != v.o_.end();
      }

      static bool del(T& v, std::size_t index) {
        ensure(v, json::array);
        if (index < v.a_.size()) {
          v.a_.erase(std::begin(v.a_)+index);
          return true;
        }
        return false;
      }

      static bool del(T& v, typename T::char_t const* key) {
        ensure(v, json::object);
        auto it = find(v, key);
        if (it != v.o_.end()) {
          v.o_.erase(it);
          return true;
        }
        return false;
      }

      //TODO: specialize for assoc object
      template<typename V>
      static auto find(V&& v, typename T::char_t const* key) -> decltype(v.o_.end()) {
        return std::find_if(v.o_.begin(), v.o_.end(), [&key](typename T::pair_t const& p){
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
  inline bool in(basic_val<T> const& v, typename basic_val<T>::string_t const& key) {
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
    internal::ensure_any(v, json::object, json::array);
    if (is_object(v)) {
      if (is_string(key_or_index))
        return in(v, get<typename basic_val<T>::string_t>(key_or_index).c_str());
      throw type_error("key is not convertible to a string");
    }
    // else: array
    if (is_integer(key_or_index))
      return in(v, get<typename basic_val<T>::int_t>(key_or_index));
    throw type_error("index is not convertible to an integer");
  }


  // delete key from object
  template<typename T>
  inline bool del(basic_val<T>& v, typename basic_val<T>::char_t const* key) {
    return internal::access<basic_val<T>, internal::container_tag>::del(v, key);
  }

  template<typename T>
  inline bool del(basic_val<T>& v, typename basic_val<T>::string_t const& key) {
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
    internal::ensure_any(v, json::object, json::array);
    if (is_object(v)) {
      if (is_string(key_or_index))
        return del(v, get<typename basic_val<T>::string_t>(key_or_index).c_str());
      throw type_error("key is not convertible to a string");
    }
    // else: array
    if (is_integer(key_or_index))
      return del(v, get<typename basic_val<T>::int_t>(key_or_index));
    throw type_error("index is not convertible to an integer");
  }


  namespace internal
  {

    struct subscript_tag {};

    template<typename T>
    struct access<T, subscript_tag>
    {
      using string_t = typename T::string_t;
      using pair_t = typename T::pair_t;

      static T& sub_impl(T& v, string_t const& s, assoc) {
        return v.o_[s];
      }

      static T& sub_impl(T& v, string_t const& s, not_assoc) {
        auto it = std::find_if(v.o_.begin(), v.o_.end(), [&s](pair_t const& p){
          return p.first == s;
        });
        if (it != v.o_.end())
          return it->second;
        v.o_.push_back(pair_t(s, T(nullptr)));
        return v.o_.back().second;
      }

      static T& sub(T& v, string_t const& s) {
        return sub_impl(v, s
          ,typename std::conditional<has_assoc_object<T>::value, assoc, not_assoc>::type());
      }
    };

    template<typename T>
    struct access<T const, subscript_tag>
    {
      using string_t = typename T::string_t;
      using pair_t = typename T::pair_t;

      static T const& sub_impl(T const& v, string_t const& s, assoc) {
        auto it = v.o_.find(s);
        if (it != v.o_.end())
          return it->second;
        throw range_error(s);
      }

      static T const& sub_impl(T const& v, string_t const& s, not_assoc) {
        auto it = std::find_if(v.o_.begin(), v.o_.end(), [&s](pair_t const& p){
          return p.first == s;
        });
        if (it != v.o_.end())
          return it->second;
        throw range_error(s);
      }

      static T const& sub(T const& v, string_t const& s) {
        return sub_impl(v, s
          ,typename std::conditional<has_assoc_object<T>::value, assoc, not_assoc>::type());
      }
    };
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
//        if (v.type() == json::integer)
//          return reinterpret_cast<cqual<U,V>>(&v.i_);
//        return nullptr;
//      }

//      template<typename U>
//      static auto get(U& v)
//        -> typename std::enable_if<std::is_floating_point<V>::value, cqual<U,V>>::type
//      {
//        if (v.type() == json::real)
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
//        if (v.type() == json::null)
//          return &n;
//        return nullptr;
//      }
//    };
//  }
//} // ns
