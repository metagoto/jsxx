#pragma once

#include <jsxx/core/prologue.hpp>
#include <jsxx/core/functions.hpp>
//
#include <jsxx/core/basic_val.hpp>
//


namespace jsxx
{

  template<typename T>
  constexpr inline basic_val<T>::basic_val() noexcept
    : type_(json::null) {}

  template<typename T>
  inline basic_val<T>::basic_val(self_t const& v)
    : type_(json::null)
  { copy(v); }

  template<typename T>
  inline basic_val<T>::basic_val(self_t&& v) noexcept
    : type_(json::null)
  { move(std::move(v)); }

  template<typename T>
  constexpr inline basic_val<T>::basic_val(std::nullptr_t) noexcept
    : type_(json::null) {}

  template<typename T>
  constexpr inline basic_val<T>::basic_val(bool_t v) noexcept
    : type_(json::boolean), b_(v) {}

  template<typename T>
  constexpr inline basic_val<T>::basic_val(int_t v) noexcept
    : type_(json::integer), i_(v) {}

  template<typename T>
  constexpr inline basic_val<T>::basic_val(real_t v) noexcept
    : type_(json::real), r_(v) {}

  template<typename T>
  constexpr inline basic_val<T>::basic_val(string_t const& v)
    : type_(json::string), s_(v) {}

  template<typename T>
  constexpr inline basic_val<T>::basic_val(char_t const* v)
    : type_(json::string), s_(v) {}

  template<typename T>
  constexpr inline basic_val<T>::basic_val(array_t const& v)
    : type_(json::array), a_(v) {}

  template<typename T>
  constexpr inline basic_val<T>::basic_val(object_t const& v)
    : type_(json::object), o_(v) {}

  template<typename T>
  constexpr inline basic_val<T>::basic_val(empty::array_t)
    : type_(json::array), a_() {}

  template<typename T>
  constexpr inline basic_val<T>::basic_val(empty::object_t)
    : type_(json::object), o_() {}

  template<typename T>
  constexpr inline basic_val<T>::basic_val(empty::array_t, std::size_t const& v)
    : type_(json::array), a_(v) {}

  template<typename T>
  constexpr inline basic_val<T>::basic_val(empty::object_t, std::size_t const& v)
    : type_(json::object), o_(v) {}

  template<typename T>
  constexpr inline basic_val<T>::basic_val(string_t&& v) noexcept
    : type_(json::string), s_(std::move(v)) {}

  template<typename T>
  constexpr inline basic_val<T>::basic_val(array_t&& v) noexcept
    : type_(json::array), a_(std::move(v)) {}

  template<typename T>
  constexpr inline basic_val<T>::basic_val(object_t&& v) noexcept
    : type_(json::object), o_(std::move(v)) {}

  template<typename T>
  constexpr inline basic_val<T>::basic_val(std::initializer_list<pair_t> l)
    : type_(json::object), o_(std::begin(l), std::end(l)) {}

  template<typename T>
  constexpr inline basic_val<T>::basic_val(std::initializer_list<self_t> l)
    : type_(json::array), a_(std::begin(l), std::end(l)) {}

  template<typename T>
  template<typename U>
  constexpr inline basic_val<T>::basic_val(U v, typename std::enable_if<std::is_integral<U>::value>::type*) noexcept
    : type_(json::integer), i_(v) {}

  template<typename T>
  template<typename U>
  constexpr inline basic_val<T>::basic_val(U v, typename std::enable_if<std::is_floating_point<U>::value>::type*) noexcept
    : type_(json::real), r_(v) {}

  template<typename T>
  inline basic_val<T>& basic_val<T>::operator=(self_t const& v) &
  {
    if (this != &v)
      copy(v);
    return *this;
  }

  template<typename T>
  inline basic_val<T>& basic_val<T>::operator=(self_t&& v) & noexcept
  {
    move(std::move(v));
    return *this;
  }

  template<typename T>
  inline basic_val<T>& basic_val<T>::operator=(std::initializer_list<self_t> l) &
  {
    free();
    if (l.size()) {
      type_ = json::array;
      new (&a_) array_t(std::begin(l), std::end(l));
    }
    return *this;
  }

  template<typename T>
  inline basic_val<T>& basic_val<T>::operator=(empty::array_t) &
  {
    free();
    type_ = json::array;
    new (&a_) array_t{};
    return *this;
  }

  template<typename T>
  inline basic_val<T>& basic_val<T>::operator=(empty::object_t) &
  {
    free();
    type_ = json::object;
    new (&o_) object_t{};
    return *this;
  }

  template<typename T>
  inline basic_val<T>::~basic_val() noexcept
  { free(); }

  template<typename T>
  inline json basic_val<T>::type() const noexcept
  { return type_; }

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
  inline basic_val<T>& basic_val<T>::operator[](string_t const& s)
  {
    if (!is_object(*this))
      throw type_error("basic_val is not an object");
    auto it = std::find_if(o_.begin(), o_.end(), [&s](pair_t const& p){
      return p.first == s;
    });
    if (it != o_.end())
      return it->second;
    o_.push_back(pair_t(s, self_t(nullptr))); // null_type() ??
    return o_.back().second;
  }

  template<typename T>
  inline basic_val<T> const& basic_val<T>::operator[](string_t const& s) const
  {
    if (!is_object(*this))
      throw type_error("basic_val is not an object");
    auto it = std::find_if(o_.begin(), o_.end(), [&s](pair_t const& p){
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
    return this->operator[](string_t(s));
  }

  template<typename T>
  template<std::size_t N>
  inline basic_val<T> const& basic_val<T>::operator[](char_t const(&s)[N]) const
  {
    return this->operator[](string_t(s));
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
  inline basic_val<T>::operator bool() const noexcept
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
  inline bool basic_val<T>::operator==(self_t const& v) const noexcept
  {
    if (type_ != v.type_) {
      if ((type_ == json::integer || type_ == json::real) &&
          (v.type_ == json::integer || v.type_ == json::real)) {
        auto const& i = type_ == json::integer ? *this : v;
        auto const& r = type_ == json::integer ? v : *this;
        return i.i_ == r.r_;
      }
      return false;
    }
    switch (type_) {
      default: break;
      case json::null: return true;
      case json::boolean: return b_ == v.b_;
      case json::integer: return i_ == v.i_;
      case json::real: return r_ == v.r_;
      case json::string: return s_ == v.s_;
      case json::array: return a_ == v.a_;
      case json::object: return o_ == v.o_;
    }
    return false;
  }

  template<typename T>
  inline bool basic_val<T>::operator!=(self_t const& v) const noexcept
  {
    return !(*this == v);
  }

  // key/value pair
  template<typename T>
  constexpr inline basic_val<T>::k::k(char_t const* s) noexcept
    : key(s) {}

  template<typename T>
  constexpr inline typename basic_val<T>::pair_t
  basic_val<T>::k::operator=(std::initializer_list<self_t> list) const
  {
    return pair_t(key, list);
  }

  template<typename T>
  template<typename U>
  constexpr inline typename std::enable_if<
    !std::is_same<U,std::initializer_list<typename basic_val<T>::pair_t>>::value
    ,typename basic_val<T>::pair_t
  >::type basic_val<T>::k::operator=(U&& t) const
  {
    return pair_t(key, std::forward<U>(t));
  }

  template<typename T>
  constexpr inline typename basic_val<T>::pair_t
  basic_val<T>::k::operator=(std::initializer_list<pair_t> list) const
  {
    return pair_t(key, list);
  }

  // private:
  template<typename T>
  inline void basic_val<T>::free() noexcept
  {
    switch (type_) {
      default: break;
      case json::string: s_.~string_t(); break;
      case json::array: a_.~array_t(); break;
      case json::object: o_.~object_t(); break;
    }
    type_ = json::null;
  }

  template<typename T>
  inline void basic_val<T>::copy(self_t const& v)
  {
    if (type_ == v.type_) {
      switch (type_) {
        default: break;
        case json::boolean: b_ = v.b_; break;
        case json::integer: i_ = v.i_; break;
        case json::real: r_ = v.r_; break;
        case json::string: s_ = v.s_; break;
        case json::array: a_ = v.a_; break;
        case json::object: o_ = v.o_; break;
      }
      return;
    }
    free();
    switch (type_ = v.type_) {
      default: break;
      case json::boolean: b_ = v.b_; break;
      case json::integer: i_ = v.i_; break;
      case json::real: r_ = v.r_; break;
      case json::string: new (&s_) string_t(v.s_); break;
      case json::array: new (&a_) array_t(v.a_); break;
      case json::object: new (&o_) object_t(v.o_); break;
    }
  }

  template<typename T>
  inline void basic_val<T>::move(self_t&& v) noexcept
  {
    if (type_ == v.type_) {
      switch (type_) {
        default: break;
        case json::boolean: b_ = std::move(v.b_); break;
        case json::integer: i_ = std::move(v.i_); break;
        case json::real: r_ = std::move(v.r_); break;
        case json::string: s_ = std::move(v.s_); break;
        case json::array: a_ = std::move(v.a_); break;
        case json::object: o_ = std::move(v.o_); break;
      }
      return;
    }
    free();
    switch (type_ = v.type_) {
      default: break;
      case json::boolean: b_ = std::move(v.b_); break;
      case json::integer: i_ = std::move(v.i_); break;
      case json::real: r_ = std::move(v.r_); break;
      case json::string: new (&s_) string_t(std::move(v.s_)); break;
      case json::array: new (&a_) array_t(std::move(v.a_)); break;
      case json::object: new (&o_) object_t(std::move(v.o_)); break;
    }
  }

} // ns jsxx
