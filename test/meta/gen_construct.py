import pystache
import os
from testlib import *

d = {
    "groups" : [
        {
            "group" : "construct1",
            "test" : [
                {
                    "name": "integer",
                    "kind": "EXPECT_EQ",
                    "data": x( [0, -0, 1, 3, -1, -2, 100, 123456789] )
                },
                {
                    "name": "real",
                    "kind": "EXPECT_EQ",
                    "data": x( [0.0, -0.0, 0.1, 3.1415, -2.618, 123456789.1] )
                },
                {
                    "name": "simple_val3",
                    "kind": "EXPECT_EQ",
                    "noswitch": True,
                    "data": x( ["false"] )
                },
            ]
        },
        {
            "group" : "construct2",
            "test" : [
                {
                    "name": "simple_val",
                    "kind": "EXPECT_NE",
                    "data": x([ [0, 1], [3, 6], [3.14, 2.618]
                               ,["true", "false"], ["null", "false"] ])
                },
                {
                    "name": "simple_val3",
                    "kind": "EXPECT_NE",
                    "noswitch": True,
                    "data": x( [["false", "true"]] )
                },
            ]
        },
        {
            "group" : "construct3",
            "test" : [
                {
                    "name": "simple_str",
                    "kind": "EXPECT_STREQ",
                    "data": xs( [0, 3, 3.14, 'tru"e', "fal'se", "null", "z\"z"] )
                },
                {
                    "name": "simple_val2",
                    "kind": "EXPECT_STRNE",
                    "data": xs( [["42", "test"], ["str", "strr"]] )
                },
            ]
        },
    ]
}


test_name = os.path.basename(__file__)[4:][:-3]
out_file = "../" + test_name + ".cpp"

loader = pystache.Loader()
tpl = loader.load_template(test_name)

str = pystache.render(tpl, d)

#print(d)

with open(out_file, 'w') as f:
    f.write(str)

print("wrote " + out_file)
