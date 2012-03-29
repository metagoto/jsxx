#pragma once

#include <memory>


namespace jsxx
{

    namespace detail
    {


        template<typename T>
        struct iter_impl_base
        {
            virtual ~iter_impl_base() {}
            virtual bool operator!=(iter_impl_base const&) const = 0;
            virtual iter_impl_base& operator++() = 0;
            virtual iter_impl_base& operator+(std::size_t) = 0;
            virtual T const& operator*() const = 0;
            virtual T& operator*() = 0;
        };


        template<typename T, typename C>
        struct iter_impl : public iter_impl_base<T>
        {

            typedef T val_type;
            typedef C container_type;
            typedef iter_impl<T, C> self_type;
            typedef iter_impl_base<T> base_type;
            typedef typename T::array array;
            typedef typename T::object object;

            typedef typename std::conditional<
                std::is_const<C>::value
               ,typename C::const_iterator
               ,typename C::iterator
            >::type it_type;


            virtual ~iter_impl() {}


            iter_impl(container_type& c, bool end = false)
                : it(end ? c.end() : c.begin())
            { }


            bool operator!=(base_type const& rhs) const
            {
                it_type const& itr = static_cast<self_type const&>(rhs).it;
                return it != itr;
            }


            base_type& operator++()
            {
                ++it;
                return *this;
            }

            base_type& operator+(std::size_t i)
            {
                it += i;
                return *this;
            }


            val_type const& operator*() const
            {
                return deref(std::is_same<typename std::remove_const<C>::type, object>());
            }


            val_type& operator*()
            {
                return const_cast<val_type&>(
                    deref(std::is_same<typename std::remove_const<C>::type, object>()));
            }


            val_type const& deref(std::true_type) const
            {
                return it->second;
            }


            val_type const& deref(std::false_type) const
            {
                return *it;
            }


            it_type it;
        };



        template<typename T>
        struct iter
        {

            typedef T  value;
            typedef T& reference;
            typedef iter<T> self_type;
            typedef iter_impl_base<T> erase_type;

            typedef typename T::array array;
            typedef typename T::object object;


            template<typename U>
            struct c_qual
            {
                typedef typename std::conditional<
                    std::is_const<T>::value, U const, U
                >::type type;
            };


            iter(value& v, bool end = false)
                : v(v)
                , end(end)
                , it_impl(v.type() == val_type::object
                    ? static_cast<erase_type*>(new iter_impl<T,typename c_qual<object>::type>(v.o_, end))
                    : static_cast<erase_type*>(new iter_impl<T,typename c_qual<array>::type>(v.a_, end)))
            {
                if (v.type() != val_type::object || v.type() != val_type::array)
                    throw std::invalid_argument("not an object nor an array");
            }


            bool operator==(self_type const& rhs) const
            {
                return !it_impl->operator!=(*(rhs.it_impl));
            }


            bool operator!=(self_type const& rhs) const
            {
                return it_impl->operator!=(*(rhs.it_impl));
            }


            self_type& operator++()
            {
                it_impl->operator++();
                return *this;
            }


            self_type& operator+(std::size_t i)
            {
                it_impl->operator+(i);
                return *this;
            }


            reference operator*() const
            {
                return it_impl->operator*();
            }


            operator iter<typename std::add_const<T>::type> ()
            {
                return iter<value const>(v, end);
            }


            value& v;
            bool end;
            std::shared_ptr<erase_type> it_impl;
        };


    }


    template<typename T>
    typename basic_val<T>::iterator begin(basic_val<T>& v)
    {
        return typename basic_val<T>::iterator(v);
    }


    template<typename T>
    typename basic_val<T>::iterator end(basic_val<T>& v)
    {
        return typename basic_val<T>::iterator(v, true);
    }


    template<typename T>
    typename basic_val<T>::const_iterator begin(basic_val<T> const& v)
    {
        return typename basic_val<T>::const_iterator(v);
    }


    template<typename T>
    typename basic_val<T>::const_iterator end(basic_val<T> const& v)
    {
        return typename basic_val<T>::const_iterator(v, true);
    }


}
