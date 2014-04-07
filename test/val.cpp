
#include <iostream>
#include <jsxx/val.hpp>
#include <jsxx/reader.hpp>
///#include <jsxx/writer.hpp>
#include <cstring>
#include "lest.hpp"


using namespace jsxx;
using namespace jsxx::val_literals;

static_assert(std::is_nothrow_move_constructible<val>::value,"");
static_assert(std::is_nothrow_move_assignable<val>::value,"");


#include "val.specs.hpp"


int main() {
  return lest::run(specs);
}

