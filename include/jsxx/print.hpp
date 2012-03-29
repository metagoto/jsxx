#pragma once

#include <iostream>
//#include <codecvt>


namespace jsxx
{

    // temp
    template<typename T>
    inline void print(std::ostream& o, basic_val<T> const& v)
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
                o << "{\n";
                for (pair const& p : get<object>(v)) {
                    o << '"' << p.first << "\": ";
                    print(o, p.second);
                    o << ",\n";
                }
                o << "}\n";
                break;
            case val_type::array:
                o << "[ ";
                for (basic_val<T> const& w : get<array>(v)) {
                    print(o, w);
                    o << ", ";
                }
                o << "]";
                break;
            case val_type::string:
                o << '"' << get<string>(v) << '"';
                break;
            case val_type::integer:
                o << get<int_type>(v);
                break;
            case val_type::real:
                o << get<float_type>(v);
                break;
            case val_type::boolean:
                o << std::boolalpha << get<bool>(v);
                break;
            case val_type::null:
                o << "null";
                break;
            case val_type::undefined:
                o << "undefined";
                break;
            default:
                o << "*UNKNOWN*";

        }
    }


}


template<typename T>
std::ostream& operator<<(std::ostream& o, jsxx::basic_val<T> const& v)
{
    jsxx::print(o, v);
    return o;
}
