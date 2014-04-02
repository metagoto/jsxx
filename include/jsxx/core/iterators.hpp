#pragma once

#include <jsxx/core/prologue.hpp>


namespace jsxx
{
  namespace internal
  {

    struct iterator_tag {};

    template<typename T, typename IT>
    struct iterator_proxy;

    struct const_items {};

    template<typename T>
    struct iterator_proxy<T, const_items>
    {
      using object = typename T::object_t;
      using const_iterator = typename object::const_iterator;

      iterator_proxy(object const& o) : o_(o) {}

      const_iterator begin() { return o_.begin(); }
      const_iterator end() { return o_.end(); }

    private:
      object const& o_;
    };


    struct const_values {};

    template<typename T>
    struct const_values_iterator : std::iterator<std::forward_iterator_tag, T>
    {
      using const_iterator = typename T::object_t::const_iterator;
      using value_type = typename std::iterator<std::forward_iterator_tag, T>::value_type;
      using self_type = const_values_iterator<T>;

      const_values_iterator(const_iterator it) : it_(it) { }

      bool operator==(self_type const& rhs) const { return rhs.it_ == it_; }
      bool operator!=(self_type const& rhs) const { return rhs.it_ != it_; }

      self_type& operator++() { ++it_; return *this; }
      self_type operator++(int) { auto c = *this; ++it_; return c; }

      value_type const& operator*() const { return it_->second; }
      value_type const* operator->() const { return &it_->second; }

    private:
      const_iterator it_;
    };

    template<typename T>
    struct iterator_proxy<T, const_values>
    {
      using object = typename T::object_t;

      iterator_proxy(object const& o) : o_(o) {}

      const_values_iterator<T> begin() { return const_values_iterator<T>(o_.begin()); }
      const_values_iterator<T> end() { return const_values_iterator<T>(o_.end()); }

    private:
      object const& o_;
    };

    //
    struct const_keys {};

    template<typename T>
    struct const_keys_iterator
      : std::iterator<std::forward_iterator_tag, typename T::string>
    {

      using const_iterator = typename T::object_t::const_iterator;
      using value_type = typename std::iterator<std::forward_iterator_tag, T>::value_type;
      using self_type = const_keys_iterator<T>;

      const_keys_iterator(const_iterator it) : it_(it) {}

      bool operator==(self_type const& rhs) const { return rhs.it_ == it_; }
      bool operator!=(self_type const& rhs) const { return rhs.it_ != it_; }

      self_type& operator++() { ++it_; return *this; }
      self_type operator++(int) { auto c = *this; ++it_; return c; }

      value_type const& operator*() const { return it_->first; }
      value_type const* operator->() const { return &it_->first; }

    private:
      const_iterator it_;
    };

    template<typename T>
    struct iterator_proxy<T, const_keys>
    {
      using object = typename T::object_t;

      iterator_proxy(object const& o) : o_(o) {}

      const_keys_iterator<T> begin() { return const_keys_iterator<T>(o_.begin()); }
      const_keys_iterator<T> end() { return const_keys_iterator<T>(o_.end()); }

    private:
      object const& o_;
    };

    //
    template<typename T>
    struct access<T, iterator_tag>
    {
      static iterator_proxy<T, const_items> items(T const& v) {
        ensure(v, value::object);
        return iterator_proxy<T, const_items>(v.o_);
      }

      static iterator_proxy<T, const_values> values(T const& v) {
        ensure(v, value::object);
        return iterator_proxy<T, const_values>(v.o_);
      }

      static iterator_proxy<T, const_keys> keys(T const& v) {
        ensure(v, value::object);
        return iterator_proxy<T, const_keys>(v.o_);
      }
    };

  }


  template<typename T>
  inline auto items(basic_val<T> const& v)
    -> internal::iterator_proxy<basic_val<T>, internal::const_items>
  {
    return internal::access<basic_val<T>, internal::iterator_tag>::items(v);
  }

  template<typename T>
  inline auto values(basic_val<T> const& v)
    -> internal::iterator_proxy<basic_val<T>, internal::const_values>
  {
    return internal::access<basic_val<T>, internal::iterator_tag>::values(v);
  }

  template<typename T>
  inline auto keys(basic_val<T> const& v)
    -> internal::iterator_proxy<basic_val<T>, internal::const_keys>
  {
    return internal::access<basic_val<T>, internal::iterator_tag>::keys(v);
  }


}
