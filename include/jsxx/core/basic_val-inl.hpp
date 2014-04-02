#pragma once

#include <jsxx/core/prologue.hpp>
#include <jsxx/core/functions.hpp>
//
#include <jsxx/core/basic_val.hpp>
//


namespace jsxx
{

  template<typename T>
  constexpr inline basic_val<T>::basic_val()
    : type_(value::null)
  {}

  template<typename T>
  inline basic_val<T>::basic_val(self_t const& v)
    : type_(value::null)
  {
    copy(v);
  }

  template<typename T>
  inline basic_val<T>::basic_val(self_t&& v)
    : type_(value::null)
  {
    move(std::move(v));
  }


  template<typename T>
  constexpr inline basic_val<T>::basic_val(std::nullptr_t)
    : type_(value::null)
  {}

  template<typename T>
  constexpr inline basic_val<T>::basic_val(boolean v)
    : type_(value::boolean), b_(v)
  {}

  template<typename T>
  constexpr inline basic_val<T>::basic_val(integer v)
    : type_(value::integer), i_(v)
  {}

  template<typename T>
  constexpr inline basic_val<T>::basic_val(real v)
    : type_(value::real), r_(v)
  {}


  template<typename T>
  constexpr inline basic_val<T>::basic_val(string const& v)
    : type_(value::string), s_(v)
  {}

  template<typename T>
  constexpr inline basic_val<T>::basic_val(char_t const* v)
    : type_(value::string), s_(v)
  {}


  template<typename T>
  constexpr inline basic_val<T>::basic_val(array const& v)
    : type_(value::array), a_(v)
  {}


  template<typename T>
  constexpr inline basic_val<T>::basic_val(object const& v)
    : type_(value::object), o_(v)
  {}



  template<typename T>
  constexpr inline basic_val<T>::basic_val(empty::array_t)
    : type_(value::array), a_()
  {}


  template<typename T>
  constexpr inline basic_val<T>::basic_val(empty::object_t)
    : type_(value::object), o_()
  {}


  template<typename T>
  constexpr inline basic_val<T>::basic_val(empty::array_t, std::size_t const& v)
    : type_(value::array), a_(v)
  {}


  template<typename T>
  constexpr inline basic_val<T>::basic_val(empty::object_t, std::size_t const& v)
    : type_(value::object), o_(v)
  {}


  template<typename T>
  constexpr inline basic_val<T>::basic_val(string&& v)
    : type_(value::string), s_(std::move(v))
  {}


  template<typename T>
  constexpr inline basic_val<T>::basic_val(array&& v)
    : type_(value::array), a_(std::move(v))
  {}


  template<typename T>
  constexpr inline basic_val<T>::basic_val(object&& v)
    : type_(value::object), o_(std::move(v))
  {}



  template<typename T>
  constexpr inline basic_val<T>::basic_val(std::initializer_list<pair> l)
    : type_(value::object), o_(std::begin(l), std::end(l))
  {}

  template<typename T>
  constexpr inline basic_val<T>::basic_val(std::initializer_list<self_t> l)
    : type_(value::array), a_(std::begin(l), std::end(l))
  {}



//  template<typename T>
//  template<typename U, typename>
//  constexpr inline basic_val<T>::basic_val(U v)
//    : type_(value::integer), i_(v)
//  {}


//  template<typename T>
//  template<typename U, typename, typename>
//  constexpr inline basic_val<T>::basic_val(U v)
//    : type_(value::real), r_(v)
//  {}
  template<typename T>
  template<typename U>
  constexpr inline basic_val<T>::basic_val(U v, typename std::enable_if<std::is_integral<U>::value>::type*)
    : type_(value::integer), i_(v)
  {}


  template<typename T>
  template<typename U>
  constexpr inline basic_val<T>::basic_val(U v, typename std::enable_if<std::is_floating_point<U>::value>::type*)
    : type_(value::real), r_(v)
  {}


  template<typename T>
  inline basic_val<T>& basic_val<T>::operator=(self_t const& v)
  {
    if (this != &v)
      copy(v);
    return *this;
  }

  template<typename T>
  inline basic_val<T>& basic_val<T>::operator=(self_t&& v)
  {
    move(std::move(v));
    return *this;
  }

  template<typename T>
  inline basic_val<T>& basic_val<T>::operator=(std::initializer_list<self_t> l)
  {
    free();
    if (l.size()) {
      type_ = value::array;
      new (&a_) array(std::begin(l), std::end(l));
    }
    return *this;
  }

  template<typename T>
  inline basic_val<T>& basic_val<T>::operator=(empty::array_t)
  {
    free();
    type_ = value::array;
    new (&a_) array{};
    return *this;
  }

  template<typename T>
  inline basic_val<T>& basic_val<T>::operator=(empty::object_t)
  {
    free();
    type_ = value::object;
    new (&o_) object{};
    return *this;
  }


  template<typename T>
  inline basic_val<T>::~basic_val()
  {
    free();
  }

  template<typename T>
  inline value basic_val<T>::type() const
  {
    return type_;
  }


  // accessor
  template<typename T>
  inline basic_val<T>& basic_val<T>::operator[](std::size_t i)
  {
    if (!is_array(*this))
      throw type_error("basic_val is not an array");
    if (i >= a_.size())
      a_.resize(i+1);
    return a_[i];
  }

  template<typename T>
  inline basic_val<T> const& basic_val<T>::operator[](std::size_t i) const
  {
    if (!is_array(*this))
      throw type_error("basic_val is not an array");
    if (i >= a_.size())
      throw range_error("out of range");
    return a_[i];
  }


  template<typename T>
  inline basic_val<T>& basic_val<T>::operator[](string const& s)
  {
    if (!is_object(*this))
      throw type_error("basic_val is not an object");
    auto it = std::find_if(o_.begin(), o_.end(), [&s](pair const& p){
      return p.first == s;
    });
    if (it != o_.end())
      return it->second;
    o_.push_back(pair(s, self_t(nullptr))); // null_type() ??
    return o_.back().second;
  }

  template<typename T>
  inline basic_val<T> const& basic_val<T>::operator[](string const& s) const
  {
    if (!is_object(*this))
      throw type_error("basic_val is not an object");
    auto it = std::find_if(o_.begin(), o_.end(), [&s](pair const& p){
      return p.first == s;
    });
    if (it != o_.end())
      return it->second;
    throw range_error(s);
  }


  template<typename T>
  template<std::size_t N>
  inline basic_val<T>& basic_val<T>::operator[](char_t const(&s)[N])
  {
    return this->operator[](string(s));
  }

  template<typename T>
  template<std::size_t N>
  inline basic_val<T> const& basic_val<T>::operator[](char_t const(&s)[N]) const
  {
    return this->operator[](string(s));
  }


  // cast operators
  template<typename T>
  template<typename U>
  inline basic_val<T>::operator U() const
  {
    return internal::access<self_t const, internal::cast_tag, U>::cast(*this);
  }

  template<typename T>
  inline basic_val<T>::operator typename basic_val<T>::char_t const*() const
  {
    if (!is_string(*this))
      throw type_error("basic_val is not a string");
    return s_.c_str();
  }

  template<typename T>
  inline basic_val<T>::operator bool() const
  {
    return as_boolean(*this);
  }


  // iterator
  template<typename T>
  inline typename basic_val<T>::iterator basic_val<T>::begin()
  {
    if (!is_array(*this))
      throw type_error("basic_val is not an array");
    return std::begin(a_);
  }

  template<typename T>
  inline typename basic_val<T>::iterator basic_val<T>::end()
  {
    if (!is_array(*this))
      throw type_error("basic_val is not an array");
    return std::end(a_);
  }


  template<typename T>
  inline typename basic_val<T>::const_iterator basic_val<T>::begin() const
  {
    if (!is_array(*this))
      throw type_error("basic_val is not an array");
    return std::begin(a_);
  }

  template<typename T>
  inline typename basic_val<T>::const_iterator basic_val<T>::end() const
  {
    if (!is_array(*this))
      throw type_error("basic_val is not an array");
    return std::end(a_);
  }


  // comparison ops
  template<typename T>
  inline bool basic_val<T>::operator==(self_t const& v) const
  {
    if (type_ != v.type_) {
      if ((type_ == value::integer || type_ == value::real) &&
          (v.type_ == value::integer || v.type_ == value::real)) {
        auto const& i = type_ == value::integer ? *this : v;
        auto const& r = type_ == value::integer ? v : *this;
        return i.i_ == r.r_;
      }
      return false;
    }
    switch (type_) {
      default: break;
      case value::null: return true;
      case value::boolean: return b_ == v.b_;
      case value::integer: return i_ == v.i_;
      case value::real: return r_ == v.r_;
      case value::string: return s_ == v.s_;
      case value::array: return a_ == v.a_;
      case value::object: return o_ == v.o_;
    }
    return false;
  }

  template<typename T>
  inline bool basic_val<T>::operator!=(self_t const& v) const
  {
    return !(*this == v);
  }


  // key/value pair
  template<typename T>
  constexpr inline basic_val<T>::k::k(char_t const* s)
    : key(s)
  {}


  template<typename T>
  constexpr inline typename basic_val<T>::pair
  basic_val<T>::k::operator=(std::initializer_list<self_t> list) const
  {
    return pair(key, list);
  }


  template<typename T>
  template<typename U>
  constexpr inline typename std::enable_if<
    !std::is_same<U,std::initializer_list<typename basic_val<T>::pair>>::value
    ,typename basic_val<T>::pair
  >::type basic_val<T>::k::operator=(U&& t) const
  {
    return pair(key, std::forward<U>(t));
  }


  template<typename T>
  constexpr inline typename basic_val<T>::pair
  basic_val<T>::k::operator=(std::initializer_list<pair> list) const
  {
    return pair(key, list);
  }


  // private:
  template<typename T>
  inline void basic_val<T>::free()
  {
    switch (type_) {
      default: break;
      case value::string: s_.~string(); break;
      case value::array: a_.~array(); break;
      case value::object: o_.~object(); break;
    }
    type_ = value::null;
  }

  template<typename T>
  inline void basic_val<T>::copy(self_t const& v)
  {
    if (type_ == v.type_) {
      switch (type_) {
        default: break;
        case value::boolean: b_ = v.b_; break;
        case value::integer: i_ = v.i_; break;
        case value::real: r_ = v.r_; break;
        case value::string: s_ = v.s_; break;
        case value::array: a_ = v.a_; break;
        case value::object: o_ = v.o_; break;
      }
      return;
    }
    free();
    switch (type_ = v.type_) {
      default: break;
      case value::boolean: b_ = v.b_; break;
      case value::integer: i_ = v.i_; break;
      case value::real: r_ = v.r_; break;
      case value::string: new (&s_) string(v.s_); break;
      case value::array: new (&a_) array(v.a_); break;
      case value::object: new (&o_) object(v.o_); break;
    }
  }

  template<typename T>
  inline void basic_val<T>::move(self_t&& v)
  {
    if (type_ == v.type_) {
      switch (type_) {
        default: break;
        case value::boolean: b_ = std::move(v.b_); break;
        case value::integer: i_ = std::move(v.i_); break;
        case value::real: r_ = std::move(v.r_); break;
        case value::string: s_ = std::move(v.s_); break;
        case value::array: a_ = std::move(v.a_); break;
        case value::object: o_ = std::move(v.o_); break;
      }
      return;
    }
    free();
    switch (type_ = v.type_) {
      default: break;
      case value::boolean: b_ = std::move(v.b_); break;
      case value::integer: i_ = std::move(v.i_); break;
      case value::real: r_ = std::move(v.r_); break;
      case value::string: new (&s_) string(std::move(v.s_)); break;
      case value::array: new (&a_) array(std::move(v.a_)); break;
      case value::object: new (&o_) object(std::move(v.o_)); break;
    }
  }

} // ns jsxx
