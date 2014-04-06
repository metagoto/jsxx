
lest::test const specs[] =
{
  {"constructor", [] {
    val a;
    EXPECT(is_null(a));
    EXPECT(!is_boolean(a));
    EXPECT(!is_bool(a));
    EXPECT(!is_integer(a));
    EXPECT(!is_int(a));
    EXPECT(!is_real(a));
    EXPECT(!is_double(a));
    EXPECT(!is_string(a));
    EXPECT(!is_array(a));
    EXPECT(!is_object(a));
    EXPECT(!is_number(a));

    val z = {};
    EXPECT(is_null(z));

    val b = nullptr;
    EXPECT(is_null(b));

    val c = true;
    EXPECT(is_boolean(c));
    EXPECT(is_bool(c));

    val d = 1;
    EXPECT(is_integer(d));
    EXPECT(is_int(d));
    EXPECT(is_number(d));

    val e = 1.0;
    EXPECT(is_real(e));
    EXPECT(is_double(e));
    EXPECT(is_number(e));

    val f = "hello";
    EXPECT(is_string(f));

    val g = {nullptr, true, 1, "hello"};
    EXPECT(is_array(g));

    val h = { "k1"_k = nullptr, "k2"_k = true, "k3"_k = { 1, "hello" }};
    EXPECT(is_object(h));

    val i = empty::array;
    EXPECT(is_array(i));

    val j = empty::object;
    EXPECT(is_object(j));

    val k = 1.f;
    EXPECT(is_real(k));

    val l = (std::uint8_t)1;
    EXPECT(is_integer(l));

  }},

  {"assignment", [] {
    val a;
    EXPECT(is_null(a));

    a = nullptr;
    EXPECT(is_null(a));

    a = {};
    EXPECT(is_null(a));

    a = true;
    EXPECT(is_boolean(a));
    EXPECT(!is_null(a));
    EXPECT(!is_real(a));
    EXPECT(!is_string(a));
    EXPECT(!is_array(a));
    EXPECT(!is_object(a));

    a = 2;
    EXPECT(is_integer(a));

    a = 2.0;
    EXPECT(is_real(a));

    a = "world";
    EXPECT(is_string(a));

    a = {nullptr, true, 1, "hello"};
    EXPECT(is_array(a));

    a = { "k1"_k = nullptr, "k2"_k = true, "k3"_k = { 1, "hello" }};
    EXPECT(is_object(a));

    a = empty::array;
    EXPECT(is_array(a));

    a = empty::object;
    EXPECT(is_object(a));

    a = 1.f;
    EXPECT(is_real(a));

    a = (std::uint8_t)1;
    EXPECT(is_integer(a));
  }},

  {"operators", [] {
    val a;
    EXPECT(a == nullptr);
    EXPECT(nullptr == a);

    a = nullptr;
    EXPECT(a == nullptr);
    EXPECT(nullptr == a);

    a = {};
    EXPECT(a == nullptr);
    EXPECT(nullptr == a);
    EXPECT(a != true);
    EXPECT(false != a);

    a = true;
    EXPECT(a == true);
    EXPECT(true == a);
    EXPECT(a != nullptr);
    EXPECT(nullptr != a);

    a = 2;
    EXPECT(a == 2);
    EXPECT(2 == a);
    EXPECT(a != 3);
    EXPECT(3 != a);
    EXPECT(a != true);
    EXPECT(true != a);

    a = 2.0;
    EXPECT(a == 2.0);
    EXPECT(2.0 == a);
    EXPECT(a != 2.1);
    EXPECT(2.1 != a);

    a = "world";
    EXPECT(a == "world");
    EXPECT("world" == a);
    EXPECT(a != "hello");
    EXPECT("hello" != a);
    EXPECT(a != 2);
    EXPECT(2 != a);

    char const* s = "world";
    char const* s2 = "worldX";
    EXPECT(a == s);
    EXPECT(s == a);
    EXPECT(a != s2);
    EXPECT(s2 != a);

    char const t[] = "world";
    char const t2[] = "worldZ";
    EXPECT(a == t);
    EXPECT(t == a);
    EXPECT(a != t2);
    EXPECT(t2 != a);

    val u = nullptr;
    val v = nullptr;
    EXPECT(u == v);
    u = 1;
    EXPECT(u != v);
    v = 1;
    EXPECT(u == v);
    u = 1.0;
    EXPECT(u == v);
    v = 1.0;
    EXPECT(u == v);
    u = 1;
    EXPECT(u == v);

    u = true;
    EXPECT(!(u == v));

    u = "hello";
    EXPECT(!(u == v));
    v = "hello";
    EXPECT(u == v);

    u = {1,2,3};
    v = {1,2,3};
    EXPECT(u == v);
    u = {3,2,1};
    EXPECT(!(u == v));

    u = {"a"_k = true, "b"_k = {1.0,2.0,3.0}};
    EXPECT(!(u == v));
    v = {"a"_k = true, "b"_k = {1.0,2.0,3.0}};
    EXPECT(u == v);

    v = u;
    EXPECT(u == v);
    v = 1;
    EXPECT(u != v);
    u = 1;
    EXPECT(u == v);

  }},

  {"as", [] {
     {
       auto f = [](bool b) { return b; };
       val a = nullptr;
       EXPECT(!as_bool(a));
       EXPECT(!f(a));
       a = 0;
       EXPECT(!as_bool(a));
       EXPECT(!f(a));
       a = 1;
       EXPECT(as_bool(a));
       EXPECT(f(a));
       a = 0.;
       EXPECT(!as_bool(a));
       EXPECT(!f(a));
       a = 0.1;
       EXPECT(as_bool(a));
       EXPECT(f(a));
       a = "";
       EXPECT(!as_bool(a));
       EXPECT(!f(a));
       a = "ok";
       EXPECT(as_bool(a));
       EXPECT(f(a));
       a = empty::array;
       EXPECT(!as_bool(a));
       EXPECT(!f(a));
       a[0] = 0;
       EXPECT(as_bool(a));
       EXPECT(f(a));
       a = empty::object;
       EXPECT(!as_bool(a));
       EXPECT(!f(a));
       a = {"a"_k = 0 };
       EXPECT(as_bool(a));
       EXPECT(f(a));
       EXPECT(as_boolean(a));
     }
     {
       val a = nullptr;
       EXPECT(!as_integer(a));
       a = 0;
       EXPECT(!as_integer(a));
       a = 1;
       EXPECT(as_integer(a));
       a = 0.;
       EXPECT(!as_integer(a));
       a = 0.1;
       EXPECT(!as_integer(a));
       a = 1.;
       EXPECT(as_integer(a));
       a = "";
       EXPECT(!as_integer(a));
       a = "ok";
       EXPECT(as_integer(a));
       a = empty::array;
       EXPECT(!as_integer(a));
       a[0] = 0;
       EXPECT(as_integer(a));
       a = empty::object;
       EXPECT(!as_integer(a));
       a = {"a"_k = 0 };
       EXPECT(as_integer(a));
       EXPECT(as_int(a));
     }
     {
       val a = nullptr;
       EXPECT(!as_real(a));
       a = 0;
       EXPECT(!as_real(a));
       a = 1;
       EXPECT(as_real(a));
       a = 0.;
       EXPECT(!as_real(a));
       a = 0.1;
       EXPECT(as_real(a));
       a = 1.;
       EXPECT(as_real(a));
       a = "";
       EXPECT(!as_real(a));
       a = "ok";
       EXPECT(as_real(a));
       a = empty::array;
       EXPECT(!as_real(a));
       a[0] = 0;
       EXPECT(as_real(a));
       a = empty::object;
       EXPECT(!as_real(a));
       a = {"a"_k = 0 };
       EXPECT(as_real(a));
       EXPECT(as_double(a));
     }

  }},

  {"get", [] {
     {
       val v = true;
       EXPECT(v);
       auto b = get_boolean(v);
       EXPECT(b);
       auto& br = get_boolean(v);
       br = false;
       EXPECT(!v);
       b = get_bool(v);
       EXPECT(!b);
       v = true;
       EXPECT(get_bool(v));
     }
     {
       val const v = true;
       EXPECT(v);
       auto b = get_boolean(v);
       EXPECT(b);
       auto& br = get_boolean(v);
       //br = false; // fatal error expected
       (void)br;
       b = get_bool(v);
       EXPECT(b);
     }
     {
       val v = true;
       EXPECT(v);
       auto b = get_boolean(&v);
       EXPECT(b);
       EXPECT(*b);
       auto br = get_boolean(&v);
       *br = false;
       EXPECT(!v);
       b = get_bool(&v);
       EXPECT(!*b);
       v = true;
       EXPECT(*get_bool(&v));
     }
     {
       val const v = true;
       EXPECT(v);
       auto b = get_boolean(&v);
       EXPECT(b);
       auto br = get_boolean(&v);
       //*br = false; // fatal error expected
       (void)br;
       EXPECT(*get_bool(&v));
     }
     {
       val v = 1;
       EXPECT(v);
       EXPECT_THROWS((get_boolean(v), true));
       auto b = get_boolean(&v);
       EXPECT(!b);
     }
     //
     {
       val v = 1;
       EXPECT(v);
       auto b = get_int(v);
       EXPECT(b == 1);
       auto& br = get_int(v);
       br = 2;
       EXPECT(v);
       b = get_int(v);
       EXPECT(b == 2);
       v = 3;
       EXPECT(get_integer(v) == 3);
     }
     {
       val const v = 1;
       EXPECT(v);
       auto b = get_int(v);
       EXPECT(b == 1);
       auto& br = get_int(v);
       //br = 2; // fatal error expected
       (void)br;
       b = get_integer(v);
       EXPECT(b == 1);
     }
     {
       val v = 1;
       EXPECT(v);
       auto b = get_int(&v);
       EXPECT(b);
       EXPECT(*b == 1);
       auto br = get_int(&v);
       *br = 2;
       EXPECT(v);
       b = get_int(&v);
       EXPECT(*b == 2);
       v = 3;
       EXPECT(*get_integer(&v) == 3);
     }
     {
       val const v = 1;
       EXPECT(v);
       auto b = get_int(&v);
       EXPECT(b);
       EXPECT(*b == 1);
       auto br = get_int(&v);
       //*br = 2; // fatal error expected
       (void)br;
       EXPECT(*get_integer(&v) == 1);
     }
     {
       val v = true;
       EXPECT(v);
       EXPECT_THROWS((get_int(v), true));
       auto b = get_int(&v);
       EXPECT(!b);
     }
     //
     {
       val v = 1.;
       EXPECT(v);
       auto b = get_real(v);
       EXPECT(b == 1.);
       auto& br = get_real(v);
       br = 2.;
       EXPECT(v);
       b = get_real(v);
       EXPECT(b == 2.);
       v = 3.;
       EXPECT(get_double(v) == 3.);
     }
     {
       val const v = 1.;
       EXPECT(v);
       auto b = get_real(v);
       EXPECT(b == 1.);
       auto& br = get_real(v);
       //br = 2; // fatal error expected
       (void)br;
       b = get_double(v);
       EXPECT(b == 1.);
     }
     {
       val v = 1.;
       EXPECT(v);
       auto b = get_real(&v);
       EXPECT(b);
       EXPECT(*b == 1.);
       auto br = get_real(&v);
       *br = 2.;
       EXPECT(v);
       b = get_real(&v);
       EXPECT(*b == 2.);
       v = 3.;
       EXPECT(*get_double(&v) == 3.);
     }
     {
       val const v = 1.;
       EXPECT(v);
       auto b = get_real(&v);
       EXPECT(b);
       EXPECT(*b == 1.);
       auto br = get_real(&v);
       //*br = 2; // fatal error expected
       (void)br;
       EXPECT(*get_double(&v) == 1.);
     }
     {
       val v = true;
       EXPECT(v);
       EXPECT_THROWS((get_real(v), true));
       auto b = get_real(&v);
       EXPECT(!b);
     }


  }},

  {"object", [] {
    val a = empty::object;
    EXPECT(is_object(a));

    a["1"] = true;
    EXPECT(is_boolean(a["1"]));
    EXPECT(a["1"]);

    a["1"] = false;
    EXPECT(is_boolean(a["1"]));
    EXPECT(a["1"] == false);
    EXPECT(!a["1"]);

    a["1"] = 3.14;
    EXPECT(is_real(a["1"]));
    EXPECT(a["1"] == 3.14);

    a["1"] = nullptr;
    EXPECT(is_null(a["1"]));
    EXPECT(a["1"] == nullptr);
    EXPECT(a["1"] == nullptr);
    EXPECT(nullptr == a["1"]);

    a["2"] = empty::object;
    EXPECT(is_object(a["2"]));

    a["2"]["21"] = true;
    EXPECT(is_boolean(a["2"]["21"]));
    EXPECT(a["2"]["21"] == true);

    a["2"]["22"] = {nullptr, true, 1, "hello", empty::object};
    EXPECT(is_array(a["2"]["22"]));
    EXPECT(is_object(a["2"]["22"][4]));

    a["2"]["22"][4]["k"] = 3.14;
    EXPECT(is_real(a["2"]["22"][4]["k"]));
    EXPECT(a["2"]["22"][4]["k"] == 3.14);

  }},

  {"iterators", [] {

    using std::cout;
    using std::endl;

    val a = { "k1"_k = nullptr, "k2"_k = true, "k3"_k = { 1, "hello" }};

    val ks = { "k1", "k2", "k3" };
    val vs = { nullptr, true, {1, "hello"}};

    val tk = empty::array;
    val tv = empty::array;

    auto is = items(a);
    for (auto const& v : is) {
      get<val::array_t>(tk).push_back(v.first);
      get<val::array_t>(tv).push_back(v.second);
    }

    EXPECT(tk == ks);
    EXPECT(tv == vs);


    for (auto& v : values(a)) {
        (void)v;
    }

    for (auto& v : ks) {
       (void)v;
    }

//    std::for_each(values_.begin(), values_.end(), [] (val const& v) {
//        std::cout << v << endl;
//    });

//    //
//    auto values2_ = values(a);
//    for (auto& v : values2_) {
//        std::cout << v << endl;
//        //print(v);
//    }

//    auto i = values_.begin();
//    cout << (i->type() == json::null ? "NULL" : "ERR") << endl;

    //
//    auto xs = items(a);
//    for (auto& v : xs) {
//        //v = 1; // err car const
//        //a[v.first] = 1; // ok
//    }
    //std::cout << a;

  }},

  {"cast operators", [] {
    {
      val u = 0;
      val v = 1;

      int i = u;
      EXPECT(i == 0);
      i = v;
      EXPECT(i == 1);

      double d = u;
      EXPECT(d == 0.0);
      d = v;
      EXPECT(d == 1.0);

      bool b = u;
      EXPECT(b == false);
      b = v;
      EXPECT(b == true);

      float f = u;
      EXPECT(f == 0.f);
      f = v;
      EXPECT(f == 1.0f);
    }
    {
      val u = 0.0;
      val v = 1.0;

      int i = u;
      EXPECT(i == 0);
      i = v;
      EXPECT(i == 1);

      double d = u;
      EXPECT(d == 0.0);
      d = v;
      EXPECT(d == 1.0);

      bool b = u;
      EXPECT(b == false);
      b = v;
      EXPECT(b == true);

      float f = u;
      EXPECT(f == 0.f);
      f = v;
      EXPECT(f == 1.0f);
    }
    {
      val u = false;
      val v = true;

      int i = u;
      EXPECT(i == 0);
      i = v;
      EXPECT(i == 1);

      double d = u;
      EXPECT(d == 0.0);
      d = v;
      EXPECT(d == 1.0);

      bool b = u;
      EXPECT(b == false);
      b = v;
      EXPECT(b == true);

      float f = u;
      EXPECT(f == 0.f);
      f = v;
      EXPECT(f == 1.0f);
    }
    {
      val v = {1};
      bool b = v;
      EXPECT(b == true);

      v = "";
      b = v;
      EXPECT(b == false);
      v = "s";
      b = v;
      EXPECT(b == true);
      val::string_t s = v;
      EXPECT(s.size() == 1);

      v = {};
      EXPECT(is_null(v));
      v = empty::array;
      b = v;
      EXPECT(b == false);
      v[0] = 0;
      b = v;
      EXPECT(b == true);
      val::array_t a = v;
      a = get<val::array_t>(v);
      EXPECT(a.size() == 1);

      v = empty::object;
      b = v;
      EXPECT(b == false);
      val::object_t o = v;
      EXPECT(o.size() == 0);
      v["k"] = 0;
      b = v;
      EXPECT(b == true);
      o = get<val::object_t>(v);
      EXPECT(o.size() == 1);
    }
    {
      val v = "hello";
      [](char const* s){ EXPECT(std::string("hello") == s); }(v);

      v = 1;
      EXPECT_THROWS(([](char const* s){ EXPECT(std::string("hello") == s); }(v), true));

    }
  }},

  {"in del", [] {

     val a = {1,"2",3};
     EXPECT(in(a, 0ul));
     EXPECT(in(a, 1));
     EXPECT(in(a, 2));
     EXPECT(!in(a, 3));
     EXPECT_THROWS((in(a, "1"), true));

     val o = {"1"_k = 1, "2"_k = 2 };
     EXPECT(in(o, "1"));
     EXPECT(in(o, std::string("2")));
     EXPECT(!in(o, "3"));
     EXPECT_THROWS((in(o, 2), true));

     EXPECT(in(o, a[1]));
     EXPECT(in(a, o["2"]));
     EXPECT_THROWS((in(o, a[0]), true));
     EXPECT_THROWS((in(o, val{3.14}), true));

     EXPECT(del(a, 0ul));
     EXPECT(a[0] == "2");
     EXPECT(!del(a, 2));

     EXPECT(del(o, "1"));
     EXPECT(!in(o, "1"));
     EXPECT(!del(o, "1"));
     EXPECT(del(o, std::string("2")));
     EXPECT(!in(o, "2"));
     EXPECT(!del(o, "2"));

  }},

  {"reader", [] {
     {
       std::string s = "[1,2,3]";
       auto v = read<val>(s);
       EXPECT(is_array(v));

       bool b = read(s, v);
       EXPECT(b);

       v = read<val>(s.begin(), s.end());
       EXPECT(is_array(v));

       b = read(s.begin(), s.end(), v);
       EXPECT(b);

       s = R"("should FAIL: \i")";
       EXPECT_THROWS((read<val>(s), true));
       b = read(s, v);
       EXPECT(!b);

       s = R"("\")";
       EXPECT_THROWS((read<val>(s), true));
       b = read(s, v);
       EXPECT(!b);

       s = R"("ok")";
       v = read<val>(s);
       EXPECT(is_string(v));
       b = read(s, v);
       EXPECT(b);
     }
     {
       char const* s = "[1,2,3]";
       auto v = read<val>(s, s+std::strlen(s));
       EXPECT(is_array(v));
       bool b = read(s, s+std::strlen(s), v);
       EXPECT(b);
     }
     {
       char const s[] = "[1,2,3]";
       auto v = read<val>(s);
       EXPECT(is_array(v));
       bool b = read(s, v);
       EXPECT(b);
     }
     {
       char const* s = "[1,2,3]";
       auto v = read<val>(s, std::strlen(s));
       EXPECT(is_array(v));
       EXPECT_THROWS((read<val>(s, std::strlen(s)-1), true));
       bool b = read(s, std::strlen(s), v);
       EXPECT(b);
     }

  }},

};
