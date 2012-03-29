#pragma once

namespace jsxx
{
    namespace
    {
        typedef basic_val<tag::simple> val_t;
    }

    inline constexpr val_t::k operator"" _k(val_t::char_type const* s, std::size_t)
    {
        return val_t::k(s);
    }
}
