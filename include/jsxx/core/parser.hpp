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
        { }

        token(int type, iterator_t s, iterator_t e, std::size_t parent)
          : token(type, s, parent)
        { end_ = e; }

        token() = delete;
        token(token const&) = default;
        token(token&&) = default;
        token& operator=(token const&) = default;
        token& operator=(token&&) = default;

        int type() const { return type_; }
        iterator_t begin() const { return begin_; }
        iterator_t end() const { return end_; }
        std::size_t count() const { return count_; }

      private:
        int type_;
        iterator_t begin_;
        iterator_t end_;
        std::size_t parent_;
        int count_ = 0;
        template<typename> friend struct context;
      };


      template<int Type>
      void push(iterator_t s) {
        tokens_.push_back(token(Type, s, cur_));
        ++tokens_[cur_].count_;
        cur_ = tokens_.size() - 1;
      }

      void close(iterator_t e) {
        token& i = tokens_[cur_];
        i.end_ = e;
        cur_ = i.parent_;
      }

      void pop() {
        cur_ = tokens_.back().parent_;
        --tokens_[cur_].count_;
        tokens_.pop_back();
      }

      template<int Type>
      void push_close(iterator_t s) {
        tokens_.push_back(token(Type, s, cur_));
        ++tokens_[cur_].count_;
      }

      template<int Type>
      void push_close(iterator_t s, iterator_t e) {
        tokens_.push_back(token(Type, s, e, cur_));
        ++tokens_[cur_].count_;
      }

      void reset(iterator_t ibeg, iterator_t iend) {
        beg = it = ibeg;
        end = iend;
        tokens_.clear();
      }

      void finalize() {
        if (!tokens_.empty())
          --tokens_[0].count_;
      }

      container_t& tokens() { return tokens_; }

    private:
      iterator_t beg;
      iterator_t end;
      iterator_t it;
      container_t tokens_;
      std::size_t cur_ = 0;
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
        ctx_.finalize();
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
      auto const& tokens = ctx_.tokens();
      auto const& tok = tokens[start++];

      switch (tok.type())
      {
        default: break;
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
        case token::object: {
          std::size_t const num = tok.count()/2;
          auto o = val_t(empty::object, num);
          auto& ro = get<typename val_t::object>(o);
          for (std::size_t i = 0; i < num; ++i) {
            auto const& t = tokens[start++];
            typename val_t::string str;
            if (decode_handler<val_t>::key_string(t.begin(), t.end(), str) == 0)
              ro[i] = std::move(typename val_t::pair(std::move(str), build(start))); // TODO: swap
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
          std::size_t const num = tok.count();
          auto a = val_t(empty::array, num);
          auto& ra = get<typename val_t::array>(a);
          for (std::size_t i = 0; i < num;++i)
            ra[i] = build(start);
          return a;
        }
        case token::true_:
          return true;
        case token::false_:
          return false;
      }
      if (error)
        throw parse_error("could not convert to native type"); // TODO: explicit
      return nullptr;
    }

    context_t ctx_;
  };

}
