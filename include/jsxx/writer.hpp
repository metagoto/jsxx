#pragma once

// TMP
#include <jsxx/core/basic_val.hpp>
//

namespace jsxx
{

  template<typename Tag>
  inline std::ostream& print(std::ostream& o, basic_val<Tag> const& v)
  {
    switch (v.type()) {
      case value::null:
        o << "null"; break;
      case value::boolean:
        o << (get<typename basic_val<Tag>::boolean>(v) ? "true" : "false"); break;
      case value::integer:
        o << get<typename basic_val<Tag>::integer>(v); break;
      case value::real:
        o << get<typename basic_val<Tag>::real>(v); break;
      case value::string:
        o << "\"" << get<typename basic_val<Tag>::string>(v) << "\""; break;
      case value::array: {
        o << "[";
        bool first = true;
        for (auto const& a : v) {
          if (!first) { o << ","; }
          print(o, a);
          first = false;
        }
        o << "]";
        break;
      }
      case value::object: {
        o << "{";
        bool first = true;
        for (auto const& a : items(v)) {
          if (!first) { o << ","; }
          o << "\"" << a.first << "\"" << ":"; print(o, a.second);
          first = false;
        }
        o << "}";
        break;
      }
      default: break;
    }
    return o;
  }

  ////template<typename Tag> // TMP
  std::ostream& operator<<(std::ostream& o, basic_val<simple_val_tag> const& v) {
    return print(o, v);
  }


}
