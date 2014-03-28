#pragma once

#include <jsxx/core/prologue.hpp>
#include <jsxx/core/veg.hpp>


namespace jsxx { namespace grammar
{

using namespace jsxx::veg;

template<typename Char>
struct json_strict
{

  using space = set<Char,' ','\n','\r','\t'>;
  using ws = star<space>;

  struct true_ : seq<ch<Char,'t','r','u','e'>, storex<token::true_>> {};
  struct false_: seq<ch<Char,'f','a','l','s','e'>, storex<token::false_>> {};
  struct null  : seq<ch<Char,'n','u','l','l'>, storex<token::null>> {};

  // str (validity of escape sequences is checked in the string handler)
  //using esc_ch = seq<ch<Char,'\\'>, set<Char,'"', '/', '\\', 'b', 'f', 'n', 'r', 't', 'u'>>;
  using esc_ch = seq<ch<Char,'\\'>, set<Char,'"','\\'>>;
  struct string :
    seq<
      ch<Char,'"'>
     ,store<
        star<
          alter<
            esc_ch
           ,not_ch<Char, '"'>
          >
        >
       ,token::string
      >
     ,ch<Char,'"'>
    > {};

  using number = jnum<token::integer, token::real>;

  // obj
  struct value;

  struct kv_pair :
    seq<
      tok<string>
     ,ch_tok<Char, ':'>
     ,value
    > {};

  struct object :
    seq<
      ch_tok<Char, '{'>
     ,store<
        opt<
          seq<
            kv_pair
           ,star<
              seq<
                ch_tok<Char, ','>
               ,kv_pair
              >
            >
          >
        >
       ,token::object
      >
     ,ch<Char,'}'>
    > {};

  // arr
  struct array :
    seq<
      ch_tok<Char, '['>
     ,store<
        opt<
          seq<
            value
           ,star<
              seq<
                ch_tok<Char, ','>
               ,value
              >
            >
          >
        >
       ,token::array
      >
     ,ch<Char,']'>
    > {};

  // value
  struct value :
    tok<
      alter<
        string
       ,number
       ,object
       ,array
       ,true_
       ,false_
       ,null
      >
    > {};

  // json
  struct start :
    seq<
      ws
     ,value
     ,eoi
    > {};

};

} }
