#pragma once

#include <algorithm>
#include <stdexcept>


namespace jsxx
{

    template<typename T>
    constexpr inline basic_val<T>::k::k(char_type const* s)
        : key(s)
    { }


    template<typename T>
    constexpr inline typename basic_val<T>::pair
    basic_val<T>::k::operator=(array const& a)
    {
        return pair(key, a);
    }


    template<typename T>
    template<typename U>
    constexpr inline typename
    std::enable_if<
        !std::is_same<U,std::initializer_list<typename basic_val<T>::pair>>::value
        ,typename basic_val<T>::pair
    >::type basic_val<T>::k::operator=(U&& t)
    {
        return pair(key, std::forward<U>(t));
    }


    template<typename T>
    constexpr inline typename basic_val<T>::pair
    basic_val<T>::k::operator=(std::initializer_list<pair> list)
    {
        return pair(key, list);
    }


    ///


    template<typename T>
    constexpr inline basic_val<T>::basic_val()
        //: type_(val_type::null) // used to be
        : basic_val(empty_object_type())
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(basic_val<T>::char_type const* s)
        : type_(val_type::string)
        , s_(s)
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(string const& s)
        : type_(val_type::string)
        , s_(s)
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(basic_val<T>::int_type i)
        : type_(val_type::integer)
        , i_(i)
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(basic_val<T>::float_type d)
        : type_(val_type::real)
        , d_(d)
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(bool b)
        : type_(val_type::boolean)
        , b_(b)
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(null_type)
        : type_(val_type::null)
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(empty_array_type)
        : type_(val_type::array)
        , a_()
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(empty_object_type)
        : type_(val_type::object)
        , o_()
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(array const& a)
        : type_(val_type::array)
        , a_(a)
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(object const& o)
        : type_(val_type::object)
        , o_(o)
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(string&& s)
        : type_(val_type::string)
        , s_(std::move(s))
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(array&& a)
        : type_(val_type::array)
        , a_(std::move(a))
    { }


    template<typename T>
    constexpr inline basic_val<T>::basic_val(object&& o)
        : type_(val_type::object)
        , o_(std::move(o))
    { }


    template<typename T>
    template<typename U, typename>
    constexpr inline basic_val<T>::basic_val(U t)
        ///: basic_val(static_cast<int_type>(t)) // OK?
        : type_(val_type::integer) // TODO constructor delegation
        , i_(t)
    { }


    template<typename T>
    template<typename U, typename, typename>
    constexpr inline basic_val<T>::basic_val(U t)
        : type_(val_type::real)
        , d_(t)
    { }


    template<typename T>
    inline basic_val<T>::basic_val(std::initializer_list<pair> list)
        : type_(val_type::object)
        , o_(list.size())
    {
        std::copy(list.begin(), list.end(), o_.begin());
    }


    template<typename T>
    inline basic_val<T>::basic_val(std::initializer_list<self_type> list)
        : type_(val_type::array)
        , a_(list.size())
    {
        std::copy(list.begin(), list.end(), a_.begin());
    }


    template<typename T>
    inline basic_val<T>::basic_val(self_type const& o)
        : type_(val_type::undefined)
    {
        copy(o);
    }


    template<typename T>
    inline basic_val<T>& basic_val<T>::operator=(self_type const& o)
    {
        if (this != &o)
            copy(o);
        return *this;
    }


    template<typename T>
    inline basic_val<T>::basic_val(self_type&& o)
        : type_(val_type::undefined)
    {
        move(std::move(o));
    }


    template<typename T>
    inline basic_val<T>& basic_val<T>::operator=(self_type&& o)
    {
        move(std::move(o));
        return *this;
    }


    template<typename T>
    inline basic_val<T>::~basic_val()
    {
        free();
    }


    template<typename T>
    inline basic_val<T>& basic_val<T>::operator[](std::size_t i)
    {
        if (type() != val_type::array)
            throw std::invalid_argument("not an array");

        if (i >= a_.size())
            a_.resize(i+1);

        return a_[i];
    }


    template<typename T>
    inline basic_val<T>& basic_val<T>::operator[](string const& s)
    {
        if (type() != val_type::object)
            throw std::invalid_argument("not an object");

        auto it = std::find_if(o_.begin(), o_.end(), [&s](pair const& p){
            return p.first == s;
        });

        if (it != o_.end())
            return it->second;

        o_.push_back(pair(s, null_type()));
        return o_.back().second;
    }


    template<typename T>
    template<std::size_t N>
    inline basic_val<T>& basic_val<T>::operator[](char_type const(&s)[N])
    {
        return this->operator[](string(s));
    }


    template<typename T>
    inline basic_val<T> const& basic_val<T>::operator[](std::size_t i) const
    {
        if (type() != val_type::array)
            throw std::invalid_argument("not an array");

        if (i >= a_.size())
            throw std::out_of_range();

        return a_[i];
    }


    template<typename T>
    inline basic_val<T> const& basic_val<T>::operator[](string const& s) const
    {
        if (type() != val_type::object)
            throw std::invalid_argument("not an object");

        auto it = std::find_if(o_.begin(), o_.end(), [&s](pair const& p){
            return p.first == s;
        });

        if (it != o_.end())
            return it->second;

        throw std::out_of_range(s);
    }


    template<typename T>
    template<std::size_t N>
    inline basic_val<T> const& basic_val<T>::operator[](char_type const(&s)[N]) const
    {
        return this->operator[](string(s));
    }


    template<typename T>
    template<typename U>
    inline basic_val<T>::operator U() const
    {
        return *get<U>(this);
    }


    template<typename T>
    inline basic_val<T>::operator char_type const*() const
    {
        return get<char_type const>(this);
    }


    template<typename T>
    inline bool basic_val<T>::operator==(self_type const& v) const
    {
        if (type() != v.type())
            return false;

        switch (type())
        {
            case val_type::object:
                return o_ == v.o_;
            case val_type::array:
                return a_ == v.a_;
            case val_type::string:
                return s_ == v.s_;
            case val_type::integer:
                return i_ == v.i_;
            case val_type::real:
                return d_ == v.d_;
            case val_type::boolean:
                return b_ == v.b_;
            default:
                break;
        }
        return true;
    }


    template<typename T>
    inline bool basic_val<T>::operator!=(self_type const& v) const
    {
        return !this->operator==(v);
    }


    // TODO redo/refactor/rethink
    template<typename T>
    inline std::size_t basic_val<T>::size() const
    {
        if (type() == val_type::object)
            return o_.size();
        if (type() == val_type::array)
            return a_.size();
        if (type() == val_type::string)
            return s_.size();
        return 0;
    }


    template<typename T>
    inline val_type basic_val<T>::type() const
    {
        return type_;
    }



    /////

    template<typename T>
    typename basic_val<T>::iterator basic_val<T>::begin()
    {
        return iterator(*this);
    }


    template<typename T>
    typename basic_val<T>::iterator basic_val<T>::end()
    {
        return iterator(*this, true);
    }

    template<typename T>
    typename basic_val<T>::const_iterator basic_val<T>::begin() const
    {
        return const_iterator(*this);
    }


    template<typename T>
    typename basic_val<T>::const_iterator basic_val<T>::end() const
    {
        return const_iterator(*this, true);
    }


    template<typename T>
    typename basic_val<T>::const_iterator basic_val<T>::cbegin() const
    {
        return const_iterator(*this);
    }


    template<typename T>
    typename basic_val<T>::const_iterator basic_val<T>::cend() const
    {
        return const_iterator(*this, true);
    }


    /////


    template<typename T>
    inline void basic_val<T>::copy(self_type const& o)
    {
        if (type() == o.type())
        {
            switch (o.type())
            {
                case val_type::object:
                    o_ = o.o_;
                    break;
                case val_type::array:
                    a_ = o.a_;
                    break;
                case val_type::string:
                    s_ = o.s_;
                    break;
                case val_type::integer:
                    i_ = o.i_;
                    break;
                case val_type::real:
                    d_ = o.d_;
                    break;
                case val_type::boolean:
                    b_ = o.b_;
                    break;
                default:
                    break;
            }
            return;
        }

        free();

        switch (type_ = o.type())
        {
            case val_type::object:
                new (&o_) object(o.o_);
                break;
            case val_type::array:
                new (&a_) array(o.a_);
                break;
            case val_type::string:
                new (&s_) string(o.s_);
                break;
            case val_type::integer:
                i_ = o.i_;
                break;
            case val_type::real:
                d_ = o.d_;
                break;
            case val_type::boolean:
                b_ = o.b_;
                break;
            default:
                break;
        }
    }


    template<typename T>
    inline void basic_val<T>::free()
    {
        switch (type())
        {
            case val_type::object:
                o_.~object();
                break;
            case val_type::array:
                a_.~array();
                break;
            case val_type::string:
                s_.~string();
                break;
            default:
                break;
        }

        type_= val_type::undefined;
    }


    template<typename T>
    inline void basic_val<T>::move(self_type&& o)
    {
        if (type() == o.type())
        {
            switch (o.type())
            {
                case val_type::object:
                    o_ = std::move(o.o_);
                    break;
                case val_type::array:
                    a_ = std::move(o.a_);
                    break;
                case val_type::string:
                    s_ = std::move(o.s_);
                    break;
                case val_type::integer:
                    i_ = o.i_;
                    break;
                case val_type::real:
                    d_ = o.d_;
                    break;
                case val_type::boolean:
                    b_ = o.b_;
                    break;
                default:
                    break;
            }
            return;
        }

        free();

        switch (type_ = o.type())
        {
            case val_type::object:
                new (&o_) object(std::move(o.o_));
                break;
            case val_type::array:
                new (&a_) array(std::move(o.a_));
                break;
            case val_type::string:
                new (&s_) string(std::move(o.s_));
                break;
            case val_type::integer:
                i_ = o.i_;
                break;
            case val_type::real:
                d_ = o.d_;
                break;
            case val_type::boolean:
                b_ = o.b_;
                break;
            default:
                break;
        }
    }


}
