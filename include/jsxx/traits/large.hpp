#pragma once

#include <jsxx/traits/simple64.hpp>


namespace jsxx
{

    namespace tag
    {
        struct large {};
    }


    template<typename Self>
    struct traits<Self, tag::large> : traits<Self, tag::simple64>
    {
        typedef long double float_type;
    };


}
