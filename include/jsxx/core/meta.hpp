#pragma once

#include <type_traits>


namespace jsxx
{
  namespace internal
  {

    //TODO: investigate why this doesn't work..??? sfinao is kind of ignored...
    //template<typename T>
    //struct has_assoc_object {
    //
    //  static constexpr auto test(std::nullptr_t)
    //    -> decltype(std::declval<typename T::object_t>().key_comp(), std::true_type());
    //
    //  static constexpr auto test(...) -> std::false_type;
    //
    //  static constexpr const bool value = std::is_same<decltype(test(nullptr)), std::true_type>::value;
    //};


    // good old workaround
    namespace {
      template<typename T>
      struct enabler { using type = void; };
    }

    template<typename T, typename = void>
    struct has_assoc_object {
      static constexpr const bool value = false;
    };

    template<typename T>
    struct has_assoc_object<T, typename enabler<typename T::object_t::mapped_type>::type> {
      static constexpr const bool value = true;
    };

  }


  namespace meta
  {
    template<typename...> struct typelist {};

    namespace {

      template<int I, typename... T>
      struct type_at_impl;

      template<typename T, typename... Tail>
      struct type_at_impl<0, T, Tail...> {
        typedef T type;
      };

      template<int I, typename T, typename... Tail>
      struct type_at_impl<I, T, Tail...> {
        typedef typename type_at_impl<I-1, Tail...>::type type;
      };


      //
      template<int I, int S, typename... T>
      struct index_of_impl;

      template<int S, typename... T>
      struct index_of_impl<0, S, T...> {
        static constexpr const int value = -1;
      };

      template<int I, int S, typename V, typename T, typename... Tail>
      struct index_of_impl<I, S, V, T, Tail...> {
        static constexpr const int value
          = std::is_same<V, T>::value ? S-I
          : index_of_impl<I-1, S, V, Tail...>::value;
      };


      //
      template <std::size_t... Is>
      struct indices {};

      template <std::size_t N, std::size_t... Is>
      struct build_indices : build_indices<N-1, N-1, Is...> {};

      template <std::size_t... Is>
      struct build_indices<0, Is...> : indices<Is...> {};

    }


    // type_at
    template<std::size_t I, typename T>
    struct type_at;

    template<std::size_t I, template<typename...> class L, typename... T>
    struct type_at<I, L<T...>> {
      typedef typename type_at_impl<I, T...>::type type;
    };


    // index_of
    template<typename V, typename T>
    struct index_of;

    template<typename V, template<typename...> class L, typename... T>
    struct index_of<V, L<T...>> {
      static constexpr const int value
        = index_of_impl<sizeof...(T), sizeof...(T), V, T...>::value;
    };


    // size_of
    template<typename T>
    struct size_of;

    template<template<typename...> class L, typename... T>
    struct size_of<L<T...>> {
      static constexpr const std::size_t value = sizeof...(T);
    };


    // is_any_of
    template<typename T, typename... Args>
    struct is_any_of;

    template<typename T>
    struct is_any_of<T> : std::false_type { };

    template<typename T, typename U, typename ... Args>
    struct is_any_of<T, U, Args...> {
      static constexpr const bool value
        = std::is_same<T,U>::value || is_any_of<T,Args...>::value;
    };

    template<typename T, template<typename...> class L, typename U, typename... Args>
    struct is_any_of<T, L<U, Args...>> {
      static constexpr const bool value
        = std::is_same<T,U>::value || is_any_of<T,Args...>::value;
    };


    // has_duplicate
    template<typename ... Args>
    struct has_duplicate;

    template<>
    struct has_duplicate<> : std::false_type {};

    template<typename T>
    struct has_duplicate<T> : std::false_type {};

    template<typename T, typename ... Args>
    struct has_duplicate<T, Args...> {
      static constexpr const bool value
        = is_any_of<T, Args...>::value || has_duplicate<Args...>::value;
    };

    template<template<typename...> class L, typename T, typename... Args>
    struct has_duplicate<L<T, Args...>> {
      static constexpr const bool value
        = has_duplicate<T, Args...>::value;
    };



    // is_all_of
    template<typename T, typename U>
    struct is_all_of;

    template<template<typename...> class L
            ,template<typename...> class M, typename... Us>
    struct is_all_of<L<>, M<Us...>> : std::true_type {};

    template<typename T, template<typename...> class L, typename... Ts
            ,template<typename...> class M, typename... Us>
    struct is_all_of<L<T, Ts...>, M<Us...>> {
      static constexpr const bool value
        = is_any_of<T,Us...>::value && is_all_of<L<Ts...>,M<Us...>>::value;
    };


    // require_all
    template<template<typename, typename> class Pred, typename T, typename... Args>
    struct require_all;

    template<template<typename, typename> class Pred, typename T>
    struct require_all<Pred, T> : std::true_type { };

    template<template<typename, typename> class Pred, typename T, typename U, typename ... Args>
    struct require_all<Pred, T, U, Args...> {
      static constexpr const bool value
        = Pred<T,U>::value && require_all<Pred, T, Args...>::value;
    };

    template<template<typename...> class L, template<typename, typename> class Pred, typename T, typename U, typename ... Args>
    struct require_all<Pred, T, L<U, Args...>> {
      static constexpr const bool value
        = require_all<Pred, T, U, Args...>::value;
    };
  }



}


