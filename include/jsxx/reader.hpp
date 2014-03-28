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
  Val read(It beg, It end) {
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
  Val read(Str const& s, bool& success) {
    typedef typename Str::const_iterator it_t;
    parser<Val, it_t, Grammar> p;
    success = true;
    try { return p.parse(s.cbegin(), s.cend()); }
    catch (...) { }
    success = false;
    return nullptr;
  }

  template<typename Val, typename It
          ,template<class> class Grammar = grammar::json_strict>
  Val read(It beg, It end, bool& success) {
    parser<Val, It, Grammar> p;
    success = true;
    try { return p.parse(beg, end); }
    catch (...) { }
    success = false;
    return nullptr;
  }

  template<typename Val, typename Char, std::size_t N
          ,template<class> class Grammar = grammar::json_strict>
  Val read(Char const (&s)[N], bool& success) {
    parser<Val, Char const*, Grammar> p;
    success = true;
    try { return p.parse(s, s+N-1); }
    catch (...) { }
    success = false;
    return nullptr;
  }

  template<typename Val, typename Char
          ,template<class> class Grammar = grammar::json_strict>
  Val read(Char const* s, std::size_t len, bool& success) {
    parser<Val, Char const*, Grammar> p;
    success = true;
    try { return p.parse(s, s+len); }
    catch (...) { }
    success = false;
    return nullptr;
  }


}
