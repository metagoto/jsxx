#pragma once

namespace jsxx
{

    enum class val_type : unsigned char
    {
        undefined,
        object,
        array,
        string,
        integer,
        real,
        boolean,
        null
    };

    struct null_type {};
    struct empty_object_type {};
    struct empty_array_type {};

    // predefined constants
    null_type const null = {};
    empty_array_type const empty_array = {};
    empty_object_type const empty_object = {};

}
