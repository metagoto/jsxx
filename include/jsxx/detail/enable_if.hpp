#pragma once

#include <type_traits>


// for use in a template arguments list
// template<typename T, JSXX_ENABLE_IF(std::is_integral<T>::value)>

#define JSXX_ENABLE_IF(e) typename = typename std::enable_if<(e)>::type
