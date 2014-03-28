#pragma once

#include <jsxx/core/prologue.hpp>


namespace jsxx
{

  template<typename Tag>
  struct basic_val
  {
    using tag_t = Tag;
    using self_t = basic_val<Tag>;

    using integer = typename trait<self_t, Tag>::int_t;
    using real = typename trait<self_t, Tag>::real_t;
    using boolean = typename trait<self_t, Tag>::bool_t;
    using string = typename trait<self_t, Tag>::string_t;
    using array = typename trait<self_t, Tag>::array_t;
    using object = typename trait<self_t, Tag>::object_t;
    using pair = typename trait<self_t, Tag>::pair_t;
    using char_t = typename string::value_type;
    using null_t = std::nullptr_t;

    using iterator = typename array::iterator;
    using const_iterator = typename array::const_iterator;

    constexpr basic_val();

    basic_val(self_t const&);
    basic_val(self_t&&);

    constexpr basic_val(std::nullptr_t);
    constexpr basic_val(boolean);
    constexpr basic_val(integer);
    constexpr basic_val(real);
    constexpr basic_val(string const&);
    constexpr basic_val(char_t const*);
    constexpr basic_val(array const&);
    constexpr basic_val(object const&);

    constexpr basic_val(empty::array_t);
    constexpr basic_val(empty::object_t);

    constexpr basic_val(string&&);
    constexpr basic_val(array&&);
    constexpr basic_val(object&&);

    constexpr basic_val(std::initializer_list<pair>);
    constexpr basic_val(std::initializer_list<self_t>);

    template<typename T
            ,class = typename std::enable_if<std::is_integral<T>::value>::type>
    constexpr basic_val(T);
    template<typename T
            ,class = typename std::enable_if<std::is_floating_point<T>::value>::type
            ,typename = void>
    constexpr basic_val(T);

    ~basic_val();

    basic_val& operator=(self_t const&);
    basic_val& operator=(self_t&&);
    basic_val& operator=(std::initializer_list<self_t>);
    basic_val& operator=(empty::array_t);
    basic_val& operator=(empty::object_t);
    //TODO: add int/float type coercion for op=

    value type() const;

    self_t& operator[](std::size_t);
    self_t const& operator[](std::size_t) const;

    self_t& operator[](string const&);
    self_t const& operator[](string const&) const;

    template<std::size_t N>
    self_t& operator[](char_t const(&)[N]);
    template<std::size_t N>
    self_t const& operator[](char_t const(&)[N]) const;

    template<typename T>
    operator T() const;
    operator char_t const*() const;
    operator bool() const;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    // TOTO: cbegin...., rbegin etc..

    bool operator==(self_t const&) const;
    bool operator!=(self_t const&) const;
    //TODO: < <= ...

    struct k
    {
      constexpr explicit k(char_t const*);

      constexpr pair operator=(std::initializer_list<self_t>) const;

      template<typename T>
      constexpr typename std::enable_if<
        !std::is_same<T,std::initializer_list<pair>>::value, pair
      >::type operator=(T&&) const;

      constexpr pair operator=(std::initializer_list<pair>) const;

      char_t const* const key;
    };

  private:
    value type_;

    union {
      boolean b_;
      integer i_;
      real r_;
      string s_;
      array a_;
      object o_;
    };

    void free();
    void copy(self_t const& v);
    void move(self_t&& v);

    template<class, class, class> friend struct internal::access;
  };


} // ns

#include "basic_val-inl.hpp"
