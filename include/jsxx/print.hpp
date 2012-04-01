#pragma once

#include <algorithm>
#include <iterator>
#include <iostream>
//#include <codecvt>


namespace jsxx
{

    namespace detail
    {

        template<typename It, typename T>
        inline void serialize_str(It it, T const& v)
        {
            *it++ = '"';
            //TODO escape, encode etc
            std::copy(std::begin(v), std::end(v), it);
            *it++ = '"';
        }


        template<typename T, typename It, typename U>
        inline void serialize(It it, U v)
        {
            //TODO dispatch according to basic_val string type
            typename basic_val<T>::string s = std::to_string(v);
            std::copy(std::begin(s), std::end(s), it);
        }


        template<typename T>
        inline typename basic_val<T>::string as_str(basic_val<T> const& v)
        {
            switch (v.type())
            {
                case val_type::boolean:
                    return get<bool>(v) ? "true" : "false";
                case val_type::null:
                    return "null";
                case val_type::undefined:
                default:
                    return "undefined";
            }
        }

    }


    template<typename It, typename T>
    inline void serialize(It it, basic_val<T> const& v)
    {
        typedef typename basic_val<T>::string string;
        typedef typename basic_val<T>::pair   pair;
        typedef typename basic_val<T>::object object;
        typedef typename basic_val<T>::array  array;
        typedef typename basic_val<T>::int_type int_type;
        typedef typename basic_val<T>::float_type float_type;

        switch (v.type())
        {
            case val_type::object:
            {
                *it++ = '{';
                object const& o = get<object>(v);
                for (auto i = o.cbegin(); i != o.cend(); ++i)
                {
                    if (i != o.cbegin())
                        *it++ = ',';
                    detail::serialize_str(it, i->first);
                    *it++ = ':';
                    serialize(it, i->second);
                }
                *it++ = '}';
                break;
            }
            case val_type::array:
            {
                *it++ = '[';
                array const& a = get<array>(v);
                for (auto i = a.cbegin(); i != a.cend(); ++i)
                {
                    if (i != a.cbegin())
                        *it++ = ',';
                    serialize(it, *i);
                }
                *it++ = ']';
                break;
            }
            case val_type::string:
                detail::serialize_str(it, get<string>(v));
                break;
            case val_type::integer:
                detail::serialize<T>(it, get<int_type>(v));
                break;
            case val_type::real:
                detail::serialize<T>(it, get<float_type>(v));
                break;
            case val_type::boolean:
            case val_type::null:
            case val_type::undefined:
            default:
                string const& s = detail::as_str(v);
                std::copy(std::begin(s), std::end(s), it);
        }
    }

}


template<typename T>
std::ostream& operator<<(std::ostream& o, jsxx::basic_val<T> const& v)
{
    typedef typename jsxx::basic_val<T>::char_type char_type;
    jsxx::serialize(std::ostream_iterator<char_type>(o), v);
    return o;
}
