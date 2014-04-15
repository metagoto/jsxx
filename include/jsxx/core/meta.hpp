#pragma once

#include <type_traits>


namespace jsxx
{
  namespace internal
  {

    namespace impl {
      template<typename T>
      struct enabler { using type = void; };
    }

    template<typename T, typename = void>
    struct has_assoc_object {
      static constexpr const bool value = false;
    };

    template<typename T>
    struct has_assoc_object<T, typename impl::enabler<typename T::object_t::mapped_type>::type> {
      static constexpr const bool value = true;
    };

  }


  namespace meta
  {
    template<typename...T>
    struct typelist {};

    namespace impl {
      template<std::size_t N, typename T, typename... U>
      struct index_of;

      template<std::size_t N, typename T, typename... U>
      struct index_of<N, T, T, U...> : std::integral_constant<std::size_t, N> {};

      template<std::size_t N, typename T, typename U, typename... UU>
      struct index_of<N, T, U, UU...> : index_of<N+1, T, UU...> {};
    }

    template<typename T, typename... U>
    struct index_of;

    template<typename T, typename... U>
    struct index_of<T, typelist<U...>> : impl::index_of<0, T, U...> {};

  }



}


