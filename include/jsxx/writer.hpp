#pragma once

// TMP
#include <jsxx/core/basic_val.hpp>
//

//TODO: WIP......

namespace jsxx
{

  template<typename Tag>
  inline std::ostream& print(std::ostream& o, basic_val<Tag> const& v)
  {
    switch (v.type()) {
      case json::null:
        o << "null"; break;
      case json::boolean:
        o << (/*get<typename basic_val<Tag>::bool_t>(v)*/(bool)v ? "true" : "false"); break;
      case json::integer:
        o << get<typename basic_val<Tag>::int_t>(v); break;
      case json::real:
        o << get<typename basic_val<Tag>::real_t>(v); break;
      case json::string:
        o << "\"" << get<typename basic_val<Tag>::string_t>(v) << "\""; break;
      case json::array: {
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
      case json::object: {
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
