#pragma once


namespace jsxx
{

    template<typename, typename>
    struct traits;

    template<typename>
    struct basic_val;

    struct null_type;
    struct empty_array_type;
    struct empty_object_type;

    enum class type_info : unsigned int;


    template<typename R, typename T>
    R& get(basic_val<T>&);

    template<typename R, typename T>
    R const& get(basic_val<T> const&);

    template<typename R, typename T>
    R* get(basic_val<T>*);

    template<typename R, typename T>
    R const* get(basic_val<T> const*);


    template<typename T, typename U>
    bool operator==(basic_val<T> const&, U const&);

    template<typename T, typename U>
    bool operator==(U const&, basic_val<T> const&);

    template<typename T>
    bool operator==(basic_val<T> const&, null_type);

    template<typename T>
    bool operator==(null_type, basic_val<T> const&);

    template<typename T, typename U>
    bool operator!=(basic_val<T> const&, U const&);

    template<typename T, typename U>
    bool operator!=(U const&, basic_val<T> const&);


    namespace detail
    {
        template<typename,typename>
        struct type_to_mem;

        template<typename>
        struct iter;
    }

}
