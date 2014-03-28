#pragma once


#include <jsxx/core/functions.hpp>


namespace jsxx
{

  template<typename T, typename Tag>
  inline typename std::enable_if<!std::is_same<T,char const*>::value, bool>::type
  operator==(basic_val<Tag> const& v, T const& a) {
    if (auto p = get<T>(&v)) return *p == a;
    return false;
  }
  template<typename T, typename Tag>
  inline typename std::enable_if<!std::is_same<T,char const*>::value, bool>::type
  operator==(T const& a, basic_val<Tag> const& v) {
    return v == a;
  }

  template<typename T, typename Tag>
  inline typename std::enable_if<!std::is_same<T,char const*>::value, bool>::type
  operator!=(basic_val<Tag> const& v, T const& a) {
    if (auto p = get<T>(&v)) return *p != a;
    return true;
  }
  template<typename T, typename Tag>
  inline typename std::enable_if<!std::is_same<T,char const*>::value, bool>::type
  operator!=(T const& a, basic_val<Tag> const& v) {
    return v != a;
  }

  // overloads for nullptr
  template<typename T>
  inline bool operator==(std::nullptr_t, basic_val<T> const& v) {
    return is_null(v);
  }
  template<typename T>
  inline bool operator==(basic_val<T> const& v, std::nullptr_t) {
    return is_null(v);
  }

  template<typename T>
  inline bool operator!=(std::nullptr_t, basic_val<T> const& v) {
    return !is_null(v);
  }
  template<typename T>
  inline bool operator!=(basic_val<T> const& v, std::nullptr_t) {
    return !is_null(v);
  }

  // overload for char_t const*
  template<typename T>
  inline bool operator==(basic_val<T> const& v, typename basic_val<T>::char_t const* a) {
    if (auto p = get<typename basic_val<T>::string>(&v))
      return p->compare(a) == 0;
    return false;
  }
  template<typename T>
  inline bool operator==(typename basic_val<T>::char_t const* a, basic_val<T> const& v) {
    return v == a;
  }

  template<typename T>
  inline bool operator!=(basic_val<T> const& v, typename basic_val<T>::char_t const* a) {
    if (auto p = get<typename basic_val<T>::string>(&v))
      return p->compare(a) != 0;
    return true;
  }
  template<typename T>
  inline bool operator!=(typename basic_val<T>::char_t const* a, basic_val<T> const& v) {
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

