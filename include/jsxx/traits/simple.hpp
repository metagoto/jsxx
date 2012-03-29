#pragma once

#include <string>
#include <vector>

#include <jsxx/detail/traits_fw.hpp>

namespace jsxx
{

    namespace tag
    {
        struct simple {};
    }


    template<typename Self>
    struct traits<Self, tag::simple>
    {
        typedef int                              int_type;
        typedef double                           float_type;
        typedef std::string                      string_type;
        typedef typename string_type::value_type char_type;
        typedef std::pair<string_type, Self>     pair_type;
        typedef std::vector<Self>                array_type;
        typedef std::vector<pair_type>           object_type;

    };


}
