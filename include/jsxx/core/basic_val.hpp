#pragma once

#include <jsxx/core/prologue.hpp>


namespace jsxx
{

  template<typename Tag>
  struct basic_val
  {
    using tag_t = Tag;
    using self_t = basic_val<Tag>;

    using int_t = typename trait<self_t, Tag>::int_t;
    using real_t = typename trait<self_t, Tag>::real_t;
    using bool_t = typename trait<self_t, Tag>::bool_t;
    using string_t = typename trait<self_t, Tag>::string_t;
    using array_t = typename trait<self_t, Tag>::array_t;
    using object_t = typename trait<self_t, Tag>::object_t;
    using pair_t = typename trait<self_t, Tag>::pair_t;
    using char_t = typename string_t::value_type;
    using null_t = std::nullptr_t;

    using iterator = typename array_t::iterator;
    using const_iterator = typename array_t::const_iterator;

    constexpr basic_val() noexcept;

    basic_val(self_t const&);
    basic_val(self_t&&) noexcept;

    constexpr basic_val(null_t) noexcept;
    constexpr basic_val(bool_t) noexcept;
    constexpr basic_val(int_t) noexcept;
    constexpr basic_val(real_t) noexcept;
    constexpr basic_val(string_t const&);
    constexpr basic_val(char_t const*);
    constexpr basic_val(array_t const&);
    constexpr basic_val(object_t const&);

    constexpr basic_val(empty::array_t);
    constexpr basic_val(empty::object_t);
    constexpr basic_val(empty::array_t, std::size_t const&);

    template<typename T = self_t>
    constexpr basic_val(empty::object_t, std::size_t const&
                       ,typename std::enable_if<internal::has_assoc_object<T>::value>::type* = 0);
    template<typename T = self_t>
    constexpr basic_val(empty::object_t, std::size_t const&
                       ,typename std::enable_if<!internal::has_assoc_object<T>::value>::type* = 0);

    constexpr basic_val(string_t&&) noexcept;
    constexpr basic_val(array_t&&) noexcept;
    constexpr basic_val(object_t&&) noexcept;

    constexpr basic_val(std::initializer_list<pair_t>);
    constexpr basic_val(std::initializer_list<self_t>);

    template<typename T>
    constexpr basic_val(T, typename std::enable_if<std::is_integral<T>::value>::type* = 0) noexcept;
    template<typename T>
    constexpr basic_val(T, typename std::enable_if<std::is_floating_point<T>::value>::type* = 0) noexcept;

    ~basic_val() noexcept;

    self_t& operator=(self_t const&) &;
    self_t& operator=(self_t&&) & noexcept;
    self_t& operator=(std::initializer_list<self_t>) &;
    self_t& operator=(empty::array_t) &;
    self_t& operator=(empty::object_t) &;

    json type() const noexcept;

    self_t& operator[](std::size_t);
    self_t const& operator[](std::size_t) const;

    self_t& operator[](string_t const&);
    self_t const& operator[](string_t const&) const;

    template<std::size_t N>
    self_t& operator[](char_t const(&)[N]);
    template<std::size_t N>
    self_t const& operator[](char_t const(&)[N]) const;

    template<typename T>
    operator T() const;
    operator char_t const*() const;
    operator bool() const noexcept;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    // TOTO: cbegin...., rbegin etc..

    bool operator==(self_t const&) const noexcept;
    bool operator!=(self_t const&) const noexcept;
    //TODO: < <= ...

    struct k
    {
      constexpr explicit k(char_t const*) noexcept;

      constexpr pair_t operator=(std::initializer_list<self_t>) const;

      template<typename T>
      constexpr typename std::enable_if<
        !std::is_same<T,std::initializer_list<pair_t>>::value, pair_t>::type
      operator=(T&&) const;

      constexpr pair_t operator=(std::initializer_list<pair_t>) const;

      char_t const* const key;
    };

  private:
    json type_;

    union {
      bool_t b_;
      int_t i_;
      real_t r_;
      string_t s_;
      array_t a_;
      object_t o_;
    };

    void free() noexcept;
    void copy(self_t const&);
    void move(self_t&&) noexcept;

    template<class, class, class> friend struct internal::access;
  };


} // ns

#include "basic_val-inl.hpp"
