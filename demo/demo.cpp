
#include <jsxx/val.hpp>
#include <jsxx/val/literal_key.hpp>
#include <jsxx/print.hpp>

using namespace jsxx;
using std::cout;
using std::endl;
using std::string;


void echo(val const& v)
{
    cout << v << endl;
}


int main()
{
    val json =
    {
        "key"_k   = "value",
        "bool"_k  = true,
        "int"_k   = 42,
        "real"_k  = 3.14,
        "null"_k  = null,
        "object"_k=
        {
            "array"_k = { 0, 1, "str", {"key"_k = 2}, false },
            "other"_k = "value"
        }
    };

    json["new"] = string("oki doki");

    json["object"]["empty_obj"] = { };

    json["object"]["array"][2] = true;
    json["object"]["array"][5] = "new val";


    echo(json);

    echo({ "inline"_k = true, "blah"_k = {"one","two",3} });

}
