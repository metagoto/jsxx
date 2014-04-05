#pragma once


#include <jsxx/core/functions.hpp>


namespace jsxx
{
  //TODO: wtf
  template<typename T, typename Tag>
  inline typename std::enable_if<!std::is_same<T, typename basic_val<Tag>::char_t const*>::value
    && !std::is_same<T, typename basic_val<Tag>::null_t>::value, bool>::type
  operator==(basic_val<Tag> const& v, T const& a) noexcept {
    if (auto p = get<T>(&v)) return *p == a;
    return false;
  }
  template<typename T, typename Tag>
  inline typename std::enable_if<!std::is_same<T, typename basic_val<Tag>::char_t const*>::value
    && !std::is_same<T, typename basic_val<Tag>::null_t>::value, bool>::type
  operator==(T const& a, basic_val<Tag> const& v) noexcept {
    return v == a;
  }

  template<typename T, typename Tag>
  inline typename std::enable_if<!std::is_same<T, typename basic_val<Tag>::char_t const*>::value
    && !std::is_same<T, typename basic_val<Tag>::null_t>::value, bool>::type
  operator!=(basic_val<Tag> const& v, T const& a) noexcept {
    if (auto p = get<T>(&v)) return *p != a;
    return true;
  }
  template<typename T, typename Tag>
  inline typename std::enable_if<!std::is_same<T, typename basic_val<Tag>::char_t const*>::value
    && !std::is_same<T, typename basic_val<Tag>::null_t>::value, bool>::type
  operator!=(T const& a, basic_val<Tag> const& v) noexcept {
    return v != a;
  }

  // overloads for null_t
  template<typename T>
  inline bool operator==(typename basic_val<T>::null_t, basic_val<T> const& v) noexcept {
    return is_null(v);
  }
  template<typename T>
  inline bool operator==(basic_val<T> const& v, typename basic_val<T>::null_t) noexcept {
    return is_null(v);
  }

  template<typename T>
  inline bool operator!=(typename basic_val<T>::null_t, basic_val<T> const& v) noexcept {
    return !is_null(v);
  }
  template<typename T>
  inline bool operator!=(basic_val<T> const& v, typename basic_val<T>::null_t) noexcept {
    return !is_null(v);
  }

  // overload for char_t const*
  template<typename T>
  inline bool operator==(basic_val<T> const& v, typename basic_val<T>::char_t const* a) noexcept {
    if (auto p = get<typename basic_val<T>::string_t>(&v))
      return p->compare(a) == 0;
    return false;
  }
  template<typename T>
  inline bool operator==(typename basic_val<T>::char_t const* a, basic_val<T> const& v) noexcept {
    return v == a;
  }

  template<typename T>
  inline bool operator!=(basic_val<T> const& v, typename basic_val<T>::char_t const* a) noexcept {
    if (auto p = get<typename basic_val<T>::string_t>(&v))
      return p->compare(a) != 0;
    return true;
  }
  template<typename T>
  inline bool operator!=(typename basic_val<T>::char_t const* a, basic_val<T> const& v) noexcept {
    return v != a;
  }

  //template<typename Tag, std::size_t N>
  //inline bool operator==(basic_val<Tag> const& v, typename basic_val<Tag>::char_t const (&a)[N]) {
  //  std::cout << "C";
  //  auto const& s = get<typename basic_val<Tag>::string>(v);
  //  return s.compare(a) == 0;
  //}

  //template<typename Tag, std::size_t N>
  //inline bool operator==(typename basic_val<Tag>::char_t const (&a)[N], basic_val<Tag> const& v) {
  //  std::cout << "c";
  //  auto const& s = get<typename basic_val<Tag>::string>(v);
  //  return s.compare(a) == 0;
  //}

}

