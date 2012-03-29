#pragma once


namespace jsxx
{


    namespace detail
    {

        inline namespace
        {
            template<typename T, typename U>
            struct pc_qual
            {
                typedef typename std::conditional<
                    std::is_const<T>::value, U const, U
                >::type* type;
            };
        }


        template<typename T>
        struct type_to_mem<T, typename T::int_type>
        {
            typedef typename T::int_type int_type;

            template<typename U>
            static typename pc_qual<U, int_type>::type
            get(U& v)
            {
                if (v.type() == val_type::integer)
                    return &v.i_;
                return nullptr;
            }
        };


        template<typename T>
        struct type_to_mem<T, typename T::float_type>
        {
            typedef typename T::float_type float_type;

            template<typename U>
            static typename pc_qual<U, float_type>::type
            get(U& v)
            {
                if (v.type() == val_type::real)
                    return &v.d_;
                return nullptr;
            }
        };


        template<typename T>
        struct type_to_mem<T, bool>
        {
            template<typename U>
            static typename pc_qual<U, bool>::type
            get(U& v)
            {
                if (v.type() == val_type::boolean)
                    return &v.b_;
                return nullptr;
            }
        };


        template<typename T>
        struct type_to_mem<T, typename T::string>
        {
            typedef typename T::string string;

            template<typename U>
            static typename pc_qual<U, string>::type
            get(U& v)
            {
                if (v.type() == val_type::string)
                    return &v.s_;
                return nullptr;
            }
        };


        template<typename T>
        struct type_to_mem<T, typename T::object>
        {
            typedef typename T::object object;

            template<typename U>
            static typename pc_qual<U, object>::type
            get(U& v)
            {
                if (v.type() == val_type::object)
                    return &v.o_;
                return nullptr;
            }
        };


        template<typename T>
        struct type_to_mem<T, typename T::array>
        {
            typedef typename T::array array;

            template<typename U>
            static typename pc_qual<U, array>::type
            get(U& v)
            {
                if (v.type() == val_type::array)
                    return &v.a_;
                return nullptr;
            }
        };


        // TODO wtf specialization
        template<typename T>
        struct type_to_mem<T, typename T::char_type const>
        {
            template<typename U>
            static typename T::char_type const*
            get(U& v)
            {
                if (v.type() == val_type::string)
                    return const_cast<T const&>(v).s_.c_str();
                return nullptr;
            }
        };


        // for type coercion
        // TODO see basic_val decl
        template<typename T, typename V>
        struct type_to_mem
        {
            template<typename U>
            static typename std::enable_if<
                std::is_integral<V>::value
               ,typename pc_qual<U, V>::type
            >::type
            get(U& v)
            {
                if (v.type() == val_type::integer)
                    return reinterpret_cast<typename pc_qual<U,V>::type>(&v.i_);
                return nullptr;
            }

            template<typename U>
            static typename std::enable_if<
                std::is_floating_point<V>::value
               ,typename pc_qual<U,V>::type
            >::type
            get(U& v)
            {
                if (v.type() == val_type::real)
                    return reinterpret_cast<typename pc_qual<U,V>::type>(&v.d_);
                return nullptr;
            }
        };

    }



    template<typename R, typename T>
    inline R& get(basic_val<T>& v)
    {
        R* r = detail::type_to_mem<basic_val<T>,R>::get(v);
        if (r)
            return *r;
        throw std::invalid_argument("bad type request");
    }


    template<typename R, typename T>
    inline R const& get(basic_val<T> const& v)
    {
        R const* r = detail::type_to_mem<basic_val<T>,R>::get(v);
        if (r)
            return *r;
        throw std::invalid_argument("bad type request");
    }


    template<typename R, typename T>
    inline R* get(basic_val<T>* v)
    {
        return v ? detail::type_to_mem<basic_val<T>,R>::get(*v) : nullptr;
    }


    template<typename R, typename T>
    inline R const* get(basic_val<T> const* v)
    {
        return v ? detail::type_to_mem<basic_val<T>,R>::get(*v) : nullptr;
    }


    template<typename T, typename U>
    inline bool operator==(basic_val<T> const& v, U const& u)
    {
        U const* t = detail::type_to_mem<basic_val<T>,U>::get(v);
        if (t)
            return *t == u;
        return false;
    }


    template<typename T, typename U>
    inline bool operator==(U const& u, basic_val<T> const& v)
    {
        return v == u;
    }


    template<typename T>
    inline bool operator==(basic_val<T> const& v, null_type)
    {
        return v.type() == val_type::null;
    }


    template<typename T>
    inline bool operator==(null_type, basic_val<T> const& v)
    {
        return v.type() == val_type::null;
    }


    template<typename T, typename U>
    inline bool operator!=(basic_val<T> const& v, U const& u)
    {
        return !(v == u);
    }


    template<typename T, typename U>
    inline bool operator!=(U const& u, basic_val<T> const& v)
    {
        return !(v == u);
    }



}
