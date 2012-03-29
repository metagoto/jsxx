#pragma once

#include <type_traits>
#include <initializer_list>

#include <algorithm>
#include <stdexcept>

#include <jsxx/detail/enable_if.hpp>

#include <jsxx/fw.hpp>
#include <jsxx/type.hpp>
#include <jsxx/detail/operator.hpp>
#include <jsxx/detail/iterator.hpp>


namespace jsxx
{

    template<typename Tag>
    struct basic_val
    {

        typedef Tag            tag;
        typedef basic_val<tag> self_type;

        typedef typename traits<self_type,tag>::string_type string;
        typedef typename traits<self_type,tag>::pair_type   pair;
        typedef typename traits<self_type,tag>::array_type  array;
        typedef typename traits<self_type,tag>::object_type object;
        typedef typename traits<self_type,tag>::char_type   char_type;
        typedef typename traits<self_type,tag>::int_type    int_type;
        typedef typename traits<self_type,tag>::float_type  float_type;

        typedef detail::iter<self_type>       iterator;
        typedef detail::iter<self_type const> const_iterator;


        struct k
        {
            constexpr explicit k(char_type const*);

            constexpr pair operator=(array const&);

            template<typename T>
            constexpr typename std::enable_if<
                !std::is_same<T,std::initializer_list<pair>>::value
                ,pair
            >::type operator=(T&&);

            constexpr pair operator=(std::initializer_list<pair>);

            char_type const* const key;
        };


        constexpr basic_val();
        constexpr basic_val(int_type);
        constexpr basic_val(float_type);
        constexpr basic_val(bool);
        constexpr basic_val(char_type const*);
        constexpr basic_val(string const&);
        constexpr basic_val(null_type);
        constexpr basic_val(empty_array_type);
        constexpr basic_val(empty_object_type);
        constexpr basic_val(array const&);
        constexpr basic_val(object const&);

        constexpr basic_val(string&&);
        constexpr basic_val(array&&);
        constexpr basic_val(object&&);

        //// type coercion for arithmetic types (tmp)
        //// TODO better integration with traits. exclude irrelevant ops
        template<typename T, JSXX_ENABLE_IF(std::is_integral<T>::value)>
        constexpr basic_val(T);
        template<typename T, JSXX_ENABLE_IF(std::is_floating_point<T>::value), typename = void>
        constexpr basic_val(T);

        basic_val(std::initializer_list<pair>);
        basic_val(std::initializer_list<self_type>);

        basic_val(self_type const&);
        self_type& operator=(self_type const&);

        basic_val(self_type&&);
        self_type& operator=(self_type&&);

        ~basic_val();

        self_type& operator[](std::size_t);
        self_type const& operator[](std::size_t) const;

        self_type& operator[](string const&);
        self_type const& operator[](string const&) const;

        template<std::size_t N>
        self_type& operator[](char_type const(&)[N]);
        template<std::size_t N>
        self_type const& operator[](char_type const(&)[N]) const;

        template<typename T>
        operator T() const;
        operator char_type const*() const;

        bool operator==(self_type const&) const;
        bool operator!=(self_type const&) const;

        val_type type() const;

        std::size_t size() const;

        ////
        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;
        const_iterator cbegin() const;
        const_iterator cend() const;


    private:

        val_type type_;

        union {
            object     o_;
            array      a_;
            string     s_;
            int_type   i_;
            float_type d_;
            bool       b_;
        };


        void copy(self_type const&);
        void move(self_type&&);
        void free();

        template<typename>
        friend struct detail::iter;

        template<typename,typename>
        friend struct detail::type_to_mem;


    };


}


#include <jsxx/detail/basic_val_imp.hpp>
