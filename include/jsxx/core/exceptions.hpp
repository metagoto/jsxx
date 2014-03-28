#pragma once

#include <stdexcept>

namespace jsxx
{
  struct json_error : public std::runtime_error {
    json_error(std::string const& s) : std::runtime_error(s) {}
  };

  struct parse_error : public json_error {
    parse_error(std::string const& s) : json_error(s) {}
  };

  struct type_error : public json_error {
    type_error(std::string const& s) : json_error(s) {}
  };

  struct range_error : public json_error {
    range_error(std::string const& s) : json_error(s) {}
  };
}
