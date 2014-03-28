#pragma once

#include <iterator>
#include <fstream>
#include <stdexcept>

namespace jsxx {

std::string read_file(char const* filename)
{
  std::ifstream in(filename, std::ios_base::in);
  if (!in)
    throw std::invalid_argument(std::string("could not open ")+filename);

  std::string data;
  in.unsetf(std::ios::skipws);
  std::copy(
        std::istream_iterator<char>(in),
        std::istream_iterator<char>(),
        std::back_inserter(data));

  return data;
}

}
