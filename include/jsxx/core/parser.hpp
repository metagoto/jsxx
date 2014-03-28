#pragma once

#include <jsxx/core/prologue.hpp>
#include <jsxx/core/veg.hpp>
#include <jsxx/core/grammar.hpp>
#include <vector>


namespace jsxx
{
  namespace internal
  {

    template<typename Iterator>
    struct context
    {
      struct token;
      using iterator_t = Iterator;
      using value_t = typename std::iterator_traits<Iterator>::value_type;
      using container_t = std::vector<token>;

      iterator_t pos() const { return it; }
      void pos(iterator_t i) { it = i; }
      value_t operator*() const { return *it; }
      void operator++() { ++it; }
      value_t operator++(int) { return it++; }
      bool eoi() const { return it == end; }
      void operator+=(int i) { it += i; }
      void operator-=(int i) { it -= i; }

      struct token
      {
        token(int type, iterator_t s, std::size_t parent)
          : type_(type)
          , begin_(s)
          , end_(s)
          , parent_(parent)
          , delta_(0)
        { }

        token(int type, iterator_t s, iterator_t e, std::size_t parent)
          : type_(type)
          , begin_(s)
          , end_(e)
          , parent_(parent)
          , delta_(0)
        { }

        token() = delete;
        token(token const&) = default;
        token(token&&) = default;
        token& operator=(token const&) = default;
        token& operator=(token&&) = default;

        int type() const { return type_; }
        iterator_t begin() const { return begin_; }
        iterator_t end() const { return end_; }
        std::size_t delta() const { return delta_; }

      private:
        int type_;
        iterator_t begin_;
        iterator_t end_;
        std::size_t parent_;
        std::size_t delta_;
        template<typename> friend struct context;
      };


      template<int Type>
      void push(iterator_t s) {
        tokens_.push_back(token(Type, s, cur_));
        cur_ = tokens_.size() - 1;
      }

      void close(iterator_t e) {
        token& i = tokens_[cur_];
        i.end_ = e;
        i.delta_ = tokens_.size() - cur_ - 1;
        cur_ = i.parent_;
      }

      void pop() {
        token const& i = tokens_.back();
        cur_ = i.parent_;
        tokens_.pop_back();
      }

      template<int Type>
      void push_close(iterator_t s) {
        tokens_.push_back(token(Type, s, cur_));
      }

      template<int Type>
      void push_close(iterator_t s, iterator_t e) {
        tokens_.push_back(token(Type, s, e, cur_));
      }

      void reset(iterator_t ibeg, iterator_t iend) {
        beg = it = ibeg;
        end = iend;
        tokens_.clear();
        tokens_.reserve(std::distance(ibeg, iend)/8); /// TMP
      }

      container_t& tokens() { return tokens_; }

    private:
      iterator_t beg;
      iterator_t end;
      iterator_t it;
      container_t tokens_;
      std::size_t cur_;
    };

  }


  template<typename T, typename It, template<class> class Grammar>
  struct parser
  {
    using val_t = T;
    using it_t = It;
    using context_t = internal::context<it_t>;
    using grammar_t = Grammar<typename std::iterator_traits<it_t>::value_type>;

    val_t parse(it_t beg, it_t end) {
      ctx_.reset(beg, end);
      if (grammar_t::start::match(ctx_) && !ctx_.tokens().empty()) {
        std::size_t start = 0;
        return build(start);
      }
      throw parse_error("parse error"); // TODO: explicit position
    }

  private:

    val_t build(std::size_t& start)
    {
      using namespace jsxx::grammar;

      int error = 0;
      auto& tokens = ctx_.tokens();
      auto const& tok = tokens[start++];

      switch (tok.type())
      {
        case token::string: {
          typename val_t::string str;
          if (decode_handler<val_t>::string(tok.begin(), tok.end(), str) == 0)
            return str;
          error = -1;
          break;
        }
        case token::integer: {
          typename val_t::integer integer;
          if (decode_handler<val_t>::integer(tok.begin(), tok.end(), integer) == 0)
            return integer;
          // else fallback to real
        }
        case token::real: {
          typename val_t::real real;
          if (decode_handler<val_t>::real(tok.begin(), tok.end(), real) == 0)
            return real;
          error = -1;
          break;
        }
        case token::true_:
          return true;
        case token::false_:
          return false;
        case token::object: {
          val_t o = empty::object;
          auto& ro = get<typename val_t::object>(o);
          ro.reserve(tok.delta()/2);
          std::size_t const e = start+tok.delta();
          for ( ; start != e;) {
            auto const& t = tokens[start++];
            typename val_t::string str;
            if (decode_handler<val_t>::key_string(t.begin(), t.end(), str) == 0)
              ro.emplace_back(std::move(str), build(start));
            else {
              error = -1;
              break;
            }
          }
          if (error)
            break;
          return o;
        }
        case token::array: {
          val_t a = empty::array;
          auto& ra = get<typename val_t::array>(a);
          ra.reserve(tok.delta());
          std::size_t const e = start+tok.delta();
          for ( ; start != e;)
            ra.push_back(build(start));
          return a;
        }
        default:
          break;
      }
      if (error)
        throw parse_error("could not convert to native type"); // TODO: explicit
      return nullptr;
    }

    context_t ctx_;
  };


//  template<typename Val, typename Str>
//  Val parse(Str const& s)
//  {
//    typedef typename Str::const_iterator it_t;
//    parser<Val, it_t, grammar::json_strict> p;
//    return p.parse(s.cbegin(), s.cend());
//  }

//  template<typename Val, typename Char, std::size_t N>
//  Val parse(Char const (&s)[N])
//  {
//    parser<Val, Char const*, grammar::json_strict> p;
//    return p.parse(s, s+N-1);
//  }

//  template<typename Val, typename It>
//  Val parse(It beg, It end)
//  {
//    parser<Val, It, grammar::json_strict> p;
//    return p.parse(beg, end);
//  }

} // ns
