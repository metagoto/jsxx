#pragma once


#include <jsxx/core/basic_val.hpp>
#include <jsxx/core/parser.hpp>


namespace jsxx
{

  template<typename Val, typename Str
          ,template<class> class Grammar = grammar::json_strict>
  Val read(Str const& s) {
    typedef typename Str::const_iterator it_t;
    parser<Val, it_t, Grammar> p;
    return p.parse(s.cbegin(), s.cend());
  }

  template<typename Val, typename It
          ,template<class> class Grammar = grammar::json_strict>
  Val read(It beg, It const end) {
    parser<Val, It, Grammar> p;
    return p.parse(beg, end);
  }

  template<typename Val, typename Char, std::size_t N
          ,template<class> class Grammar = grammar::json_strict>
  Val read(Char const (&s)[N]) {
    parser<Val, Char const*, Grammar> p;
    return p.parse(s, s+N-1);
  }

  template<typename Val, typename Char
          ,template<class> class Grammar = grammar::json_strict>
  Val read(Char const* s, std::size_t len) {
    parser<Val, Char const*, Grammar> p;
    return p.parse(s, s+len);
  }


  // non throwing. return json null if parsing fails
  template<typename Val, typename Str
          ,template<class> class Grammar = grammar::json_strict>
  bool read(Str const& s, Val& v) noexcept {
    try { v = read<Val, Str, Grammar>(s); return true; }
    catch (...) { }
    return false;
  }

  template<typename Val, typename It
          ,template<class> class Grammar = grammar::json_strict>
  bool read(It beg, It const end, Val& v) noexcept {
    try { v = read<Val, It, Grammar>(beg, end); return true; }
    catch (...) { }
    return false;
  }

  template<typename Val, typename Char, std::size_t N
          ,template<class> class Grammar = grammar::json_strict>
  bool read(Char const (&s)[N], Val& v) noexcept {
    try { v = read<Val, Char, N, Grammar>(s); return true; }
    catch (...) { }
    return false;
  }

  template<typename Val, typename Char
          ,template<class> class Grammar = grammar::json_strict>
  bool read(Char const* s, std::size_t len, Val& v) noexcept {
    try { v = read<Val, Char, Grammar>(s, len); return true; }
    catch (...) { }
    return false;
  }


}
