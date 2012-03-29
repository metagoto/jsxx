
#include <gtest/gtest.h>

#include <jsxx/basic_val.hpp>
#include <jsxx/traits/simple.hpp>
#include <jsxx/print.hpp>
#include <jsxx/literal_key.hpp>


using namespace jsxx;

typedef basic_val<tag::simple> val;
typedef val::k k;


val json = {
    "bool"_k  = true,
    "key"_k   = "val",
    "other"_k = "da value",
    "int"_k   = 42,
    "obj"_k   = {
        "key2"_k = null,
        "arr"_k  = {1, 2, "STR", {3, 1.4142}, {"dd"_k = 66}, false}
    },
    "pi"_k    = 3.14
};


TEST(literal, demo)
{
    val v = {
        "bool"_k  = true,
        "key"_k   = "val",
        "other"_k = "da value",
        "int"_k   = 42,
        "obj"_k   = {
            "key2"_k = null,
            "arr"_k  = {1, 2, "STR", {3, 1.4142}, {"dd"_k = 66}, false}
        },
        "pi"_k    = 3.14
    };
}

TEST(test1, a_test)
{

    val v = 6;
    EXPECT_EQ(v, 6);
    EXPECT_EQ(6, v);

    v = 3.1;
    EXPECT_DOUBLE_EQ(3.1, v);


    v = 5.4f;
    //EXPECT_DOUBLE_EQ(5.4, v);
    //std::cout << v << " " << (v == 5.4f) << std::endl;

    v = "str";
    EXPECT_STREQ(v, "str");

    v = true;
    EXPECT_EQ(v, true);

    v = null;
    EXPECT_EQ(v, null);

    v = {1,2,3};
    EXPECT_EQ(v, (val{1,2,3}));


    v = {};
    EXPECT_EQ(v.type(), val_type::object);

}


TEST(test1, literal)
{
    val v = {
        k("key") = 42
    };

}

TEST(test2, stuff)
{
    {
        typedef val::string string;

        val j = 3;
        EXPECT_EQ(j, 3);
        EXPECT_EQ(3, j);

        j = 3.14;
        EXPECT_NE(j, 3);
        EXPECT_EQ(j, 3.14);
        EXPECT_EQ(3.14, j);

        j = true;
        EXPECT_NE(j, 3.14);
        EXPECT_EQ(j, true);
        EXPECT_EQ(true, j);

        j = null;
        EXPECT_NE(j, true);
        EXPECT_EQ(j, null);
        EXPECT_EQ(null, j);

        j = "str";
        EXPECT_NE(j, null);
        EXPECT_STREQ(j, "str");
        EXPECT_STREQ("str", j);
        EXPECT_STRNE(j, "strz");
        EXPECT_STRNE("zstr", j);
        EXPECT_EQ(j, string("str"));
        EXPECT_EQ(string("str"), j);
        EXPECT_NE(j, string("strx"));
        EXPECT_NE(string("strx"), j);

        j = string{"str"};
        EXPECT_STREQ( j, "str");
        EXPECT_STREQ( "str", j);
        EXPECT_STRNE(j, "strz");
        EXPECT_STRNE("zstr", j);
        EXPECT_EQ(j, string("str"));
        EXPECT_EQ(string("str"), j);
        EXPECT_NE(j, string("strx"));
        EXPECT_NE(string("strx"), j);

        j = {1, 2};
        val j2 = {1, 2};
        EXPECT_EQ(j, j2);
        EXPECT_EQ(j2, j);
        EXPECT_TRUE( j == val({1,2}) );
        EXPECT_TRUE( j != val({1,2,3}) );


        j = {k("a") = 1, k("b") = 2};
        j2= {k("a") = 1, k("b") = 2};
        EXPECT_EQ(j, j2);
        EXPECT_EQ(j2, j);
        EXPECT_TRUE( j == val({k("a") = 1, k("b") = 2}) );
        EXPECT_TRUE( j != val({k("a") = 1, k("b") = 2, k("c") = 3}) );
    }

    {
        val j = {}; //empty_object;

        j["key"] = 1;
        EXPECT_EQ(j["key"], 1);
        EXPECT_NE(j["key"], 2);

        j["key"] = "blah";
        EXPECT_NE(  j["key"], 1);
        EXPECT_STREQ(j["key"], "blah");

        j["key2"] = {true, "test",null};
        EXPECT_EQ(   j["key2"][0], true);
        EXPECT_STREQ(j["key2"][1], "test");
        EXPECT_EQ(   j["key2"][2], null);

        val j2 = {0,1,2};
        EXPECT_EQ(j2[0], 0);
        EXPECT_EQ(j2[1], 1);
        EXPECT_EQ(j2[2], 2);
        //EXPECT_ANY_THROW(j2[3]);

        j2[0] = {}; //empty_object;
        EXPECT_NO_THROW(j2[0]["key"]);
        EXPECT_EQ(j2[0]["key"], null);

    }


    {
        typedef val::iterator iterator;
        typedef val::const_iterator const_iterator;

        val jo = {k("x")=1, k("y")=true, k("z")=null};
        val ja = {1, true, null};
        val const cjo = jo;
        val const cja = ja;

//        for (auto v : ja) {
//            //PRINT(v);
//            //v == v;
//            //int a = 3; (void)a;
//        }

//        for (val& v : ja) {
//            //PRINT(v);
//            v == v;
//        }

//        for (val const& v : ja) {
//            //PRINT(v);
//            v == v;
//        }

//        const_iterator cit = begin(cja);
//        const_iterator cit2 = begin(ja);
//        iterator it = begin(ja);
//        const_iterator cit3 = it;
//        //iterator it2 = begin(cja); // error const -> non const

//        {
//            const_iterator cit = begin(cjo);
//            const_iterator cit2 = begin(jo);
//            iterator it = begin(jo);
//            const_iterator cit3 = it;
//        }

//        EXPECT_NE(begin(ja), end(ja));
//        EXPECT_TRUE(begin(ja) != end(ja));
//        EXPECT_EQ(end(ja), end(ja));
//        EXPECT_TRUE(end(ja) == end(ja));

//        EXPECT_NE(begin(jo), end(jo));
//        EXPECT_TRUE(begin(jo) != end(jo));
//        EXPECT_EQ(end(jo), end(jo));
//        EXPECT_TRUE(end(jo) == end(jo));

//        std::for_each(begin(cjo), end(cjo), [](val const& v){
//            //(v); //PRINT(v)
//            v == v;
//            return;
//        });
//        //std::for_each(begin(cj), end(cj), [](val& v){});
//        std::for_each(begin(cjo), end(cjo), [](val v){
//            //(v); //PRINT(v)
//            v == v;
//            return;
//        });

//        // int i = 0;
//        std::for_each(begin(cjo), end(cjo), [&](val const& v){
//            //EXPECT_EQ(v, ja[i++]);
//            v == v;
//            return;
//        });

//        for (val& v : ja) {
//            v = "str";
//        }
//        std::for_each(begin(ja), end(ja), [](val const& v){
//            //EXPECT_STREQ(v, "str");
//            v == v;
//            return;
//        });
    }

    {
        typedef val::string string;
        typedef val::object object;
        typedef val::array array;
        typedef val::pair pair;

        val j = json;
        val& jj = j;
        val const& cjj = jj;

        string const& cs = get<string>(jj["key"]);
        EXPECT_EQ(cs, "val");

        string& s = get<string>(jj["other"]);
        EXPECT_EQ(s, "da value");
        s = "new";
        EXPECT_STREQ(jj["other"], "new");
        EXPECT_EQ(get<string>(jj["other"]), "new");

    //        bool const& b = get<bool>(val{k("woot")=true}["woot"]);
    //        EXPECT_EQ(b, true);

        EXPECT_ANY_THROW(get<string>(jj["int"]));

        //string& bl = get<string>(cjj["key"]); // error const -> non const

        string* ps = get<string>(&jj["key"]);
        EXPECT_EQ(*ps, "val");

        string const* cps = get<string>(&cjj["key"]);
        EXPECT_EQ(*cps, "val");

        string* es = get<string>(&jj["int"]);
        EXPECT_EQ(es, nullptr);

        jj["key"] = 3.14;
        EXPECT_ANY_THROW(get<string>(cjj["key"]));
        EXPECT_NO_THROW(get<double>(cjj["key"]));

        EXPECT_NO_THROW(get<bool>(jj["bool"]));
        EXPECT_NO_THROW(get<double>(jj["pi"]));
        EXPECT_ANY_THROW(get<array>(jj["obj"]));

        object const& o = get<object>(jj["obj"]);
        for (pair const& p : o) {
            //PRINT(p.second);
            p.second == p.second;
        }

    }

}
