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


}


