#pragma once

namespace jsxx
{
  namespace veg
  {

    template<typename Ctx>
    struct guard
    {
      guard(Ctx& c) noexcept
        : cx(c)
        , it(c.pos())
        , dismissed(false)
      { }

      ~guard() noexcept {
        if (!dismissed)
          cx.pos(it);
      }

      bool dismiss() noexcept {
        return dismissed = true; // yes
      }

      Ctx& cx;
      typename Ctx::iterator_t it;
      bool dismissed;
    };

    ////

    template<typename... Args>
    struct alter;

    template<typename T>
    struct alter<T>
    {
      template<typename Ctx>
      static bool match(Ctx& c) noexcept {
        return T::match(c);
      }
    };

    template<typename T, typename ...Args>
    struct alter<T, Args...>
    {
      typedef alter<Args...> rest;

      template<typename Ctx>
      static bool match(Ctx& c) noexcept {
        return T::match(c) || rest::match(c);
      }
    };

    ////

    template<typename... Args>
    struct seq;

    template<typename T>
    struct seq<T>
    {
      template<typename Ctx>
      static bool match(Ctx& c) noexcept {
        return T::match(c);
      }
    };

    template<typename T, typename ...Args>
    struct seq<T, Args...>
    {
      typedef seq<Args...> rest;

      template<typename Ctx>
      static bool match(Ctx& c) noexcept {
        guard<Ctx> g(c);
        if (T::match(c) && rest::match(c)) {
          return g.dismiss();
        }
        return false;
      }
    };

    ////

    template<typename T>
    struct star
    {
      template<typename Ctx>
      static bool match(Ctx& c) noexcept {
        if (!c.eoi()) {
          while (T::match(c));
        }
        return true;
      }
    };

    ////

    template<typename Char, Char... Args>
    struct ch;

    template<typename Char, Char C>
    struct ch<Char, C>
    {
      template<typename Ctx>
      static bool match(Ctx& c) noexcept {
        if (!c.eoi() && *c == C) {
          ++c;
          return true;
        }
        return false;
      }
    };

    template<typename Char, Char C, Char... Args>
    struct ch<Char, C, Args...>
    {
      template<typename Ctx>
      static bool match(Ctx& c) noexcept {
        return seq<ch<Char,C>, ch<Char,Args...>>::match(c);
      }

    };

    ////

    template<typename Char, Char C>
    struct not_ch
    {
      template<typename Ctx>
      static bool match(Ctx& c) noexcept {
        if (!c.eoi() && *c != C) {
          ++c;
          return true;
        }
        return false;
      }
    };

    ////

    template<typename Char, Char... Args>
    struct set;

    template<typename Char, Char C>
    struct set<Char, C>
    {
      template<typename Ctx>
      static bool match(Ctx& c) noexcept {
        return ch<Char,C>::match(c);
      }
    };


    template<typename Char, Char C, Char... Args>
    struct set<Char, C, Args...>
    {
      template<typename Ctx>
      static bool match(Ctx& c) noexcept {
        return ch<Char,C>::match(c) || set<Char,Args...>::match(c);
      }

    };

    ////

    template<typename T>
    struct opt
    {
      template<typename Ctx>
      static bool match(Ctx& c) noexcept {
        if (!c.eoi()) {
          T::match(c);
        }
        return true;
      }
    };

    ////

    template<typename T, int Type>
    struct store
    {
      template<typename Ctx>
      static bool match(Ctx& c) noexcept {
        c.template push<Type>(c.pos());
        if (T::match(c)) {
          c.close(c.pos());
          return true;
        }
        c.pop();
        return false;
      }
    };

    ////

    template<int Type>
    struct storex // always store
    {
      template<typename Ctx>
      static bool match(Ctx& c) noexcept {
        c.template push_close<Type>(c.pos());
        return true;
      }
    };

    ////

    struct eoi
    {
      template<typename Ctx>
      static bool match(Ctx& c) noexcept {
        return c.eoi();
      }
    };

    ////

    template<int Integer, int Real>
    struct jnum
    {
      template<typename Ctx>
      static bool match(Ctx& c) noexcept {
        if (c.eoi())
          return false;
        auto const a = *c;
        if (a != '-' && (a < '0' || a > '9'))
          return false;

        auto const G = c.pos();
        if (a == '-') {
          ++c;
          if (c.eoi() || *c < '0' || *c > '9') {
            c.pos(G);
            return false;
          }
        }

        bool zero = *c == '0';
        ++c;
        if (c.eoi()) {
          c.template push_close<Integer>(G, c.pos());
          return true;
        }

        if (zero && '0' <= *c && *c <= '9') {
          c.pos(G);
          return false;
        }

        while (!c.eoi() && '0' <= *c && *c <= '9') {
          ++c;
        }

        if (c.eoi()) {
          c.template push_close<Integer>(G, c.pos());
          return true;
        }

        if (*c != '.' && *c != 'e' && *c != 'E') {
          c.template push_close<Integer>(G, c.pos());
          return true;
        }

        if (*c == '.') {
          ++c;
          if (c.eoi() || *c < '0' || *c > '9') {
            c.pos(G);
            return false;
          }
          do { ++c; } while (!c.eoi() && '0' <= *c && *c <= '9');
        }

        if (c.eoi()) {
          c.template push_close<Real>(G, c.pos());
          return true;
        }

        if (*c != 'e' && *c != 'E') {
          c.template push_close<Real>(G, c.pos());
          return true;
        }

        ++c;
        if (c.eoi()) {
          c.pos(G);
          return false;
        }
        if (*c == '+' || *c == '-') {
          ++c;
        }

        if (c.eoi() || *c < '0' || *c > '9') {
          c.pos(G);
          return false;
        }

        do { ++c; } while (!c.eoi() && '0' <= *c && *c <= '9');
        c.template push_close<Real>(G, c.pos());
        return true;
      }
    };

    ////

    template<typename T>
    struct tok
    {
      template<typename Ctx>
      static bool match(Ctx& c) noexcept {
        if (T::match(c)) {
          while (!c.eoi() && (*c == ' ' || *c == '\n' || *c == '\r' || *c == '\t'))
            ++c;
          return true;
        }
        return false;
      }
    };

    template<typename Char, Char C>
    struct ch_tok
    {
      template<typename Ctx>
      static bool match(Ctx& c) noexcept {
        if (!c.eoi() && *c == C) {
          ++c;
          while (!c.eoi() && (*c == ' ' || *c == '\n' || *c == '\r' || *c == '\t'))
            ++c;
          return true;
        }
        return false;
      }
    };

  }
}
