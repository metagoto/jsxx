
#include <gtest/gtest.h>

#include <limits>
#include <jsxx/val.hpp>
#include <jsxx/val/literal_key.hpp>


using namespace jsxx;

typedef val::k k;


TEST(construct1, integer)
{
    {
        val v = 0;

        

        EXPECT_EQ(v, 0);
        EXPECT_EQ(0, v); 
        
    }
    {
        val v = 0;

        

        EXPECT_EQ(v, 0);
        EXPECT_EQ(0, v); 
        
    }
    {
        val v = 1;

        

        EXPECT_EQ(v, 1);
        EXPECT_EQ(1, v); 
        
    }
    {
        val v = 3;

        

        EXPECT_EQ(v, 3);
        EXPECT_EQ(3, v); 
        
    }
    {
        val v = -1;

        

        EXPECT_EQ(v, -1);
        EXPECT_EQ(-1, v); 
        
    }
    {
        val v = -2;

        

        EXPECT_EQ(v, -2);
        EXPECT_EQ(-2, v); 
        
    }
    {
        val v = 100;

        

        EXPECT_EQ(v, 100);
        EXPECT_EQ(100, v); 
        
    }
    {
        val v = 123456789;

        

        EXPECT_EQ(v, 123456789);
        EXPECT_EQ(123456789, v); 
        
    }
    
}

TEST(construct1, real)
{
    {
        val v = 0.0;

        

        EXPECT_EQ(v, 0.0);
        EXPECT_EQ(0.0, v); 
        
    }
    {
        val v = -0.0;

        

        EXPECT_EQ(v, -0.0);
        EXPECT_EQ(-0.0, v); 
        
    }
    {
        val v = 0.1;

        

        EXPECT_EQ(v, 0.1);
        EXPECT_EQ(0.1, v); 
        
    }
    {
        val v = 3.1415;

        

        EXPECT_EQ(v, 3.1415);
        EXPECT_EQ(3.1415, v); 
        
    }
    {
        val v = -2.618;

        

        EXPECT_EQ(v, -2.618);
        EXPECT_EQ(-2.618, v); 
        
    }
    {
        val v = 123456789.1;

        

        EXPECT_EQ(v, 123456789.1);
        EXPECT_EQ(123456789.1, v); 
        
    }
    
}

TEST(construct1, false)
{
    {
        val v = false;

        

        EXPECT_EQ(v, false);
        
        
    }
    
}


TEST(construct2, inequality)
{
    {
        val v = 0;

        EXPECT_NE(v, 1);
        EXPECT_NE(1, v); 
        

        
    }
    {
        val v = 3;

        EXPECT_NE(v, 6);
        EXPECT_NE(6, v); 
        

        
    }
    {
        val v = 3.14;

        EXPECT_NE(v, 2.618);
        EXPECT_NE(2.618, v); 
        

        
    }
    {
        val v = true;

        EXPECT_NE(v, false);
        EXPECT_NE(false, v); 
        

        
    }
    {
        val v = null;

        EXPECT_NE(v, false);
        EXPECT_NE(false, v); 
        

        
    }
    
}

TEST(construct2, inequality2)
{
    {
        val v = false;

        EXPECT_NE(v, true);
        
        

        
    }
    
}


TEST(construct3, simple_str)
{
    {
        val v = "0";

        

        EXPECT_STREQ(v, "0");
        EXPECT_STREQ("0", v); 
        
    }
    {
        val v = "3";

        

        EXPECT_STREQ(v, "3");
        EXPECT_STREQ("3", v); 
        
    }
    {
        val v = "3.14";

        

        EXPECT_STREQ(v, "3.14");
        EXPECT_STREQ("3.14", v); 
        
    }
    {
        val v = "tru\"e";

        

        EXPECT_STREQ(v, "tru\"e");
        EXPECT_STREQ("tru\"e", v); 
        
    }
    {
        val v = "fal'se";

        

        EXPECT_STREQ(v, "fal'se");
        EXPECT_STREQ("fal'se", v); 
        
    }
    {
        val v = "null";

        

        EXPECT_STREQ(v, "null");
        EXPECT_STREQ("null", v); 
        
    }
    {
        val v = "z\"z";

        

        EXPECT_STREQ(v, "z\"z");
        EXPECT_STREQ("z\"z", v); 
        
    }
    
}

TEST(construct3, simple_val2)
{
    {
        val v = "42";

        EXPECT_STRNE(v, "test");
        EXPECT_STRNE("test", v); 
        

        
    }
    {
        val v = "str";

        EXPECT_STRNE(v, "strr");
        EXPECT_STRNE("strr", v); 
        

        
    }
    
}


TEST(construct4, limits)
{
    {
        val v = std::numeric_limits<int>::max();

        

        EXPECT_EQ(v, std::numeric_limits<int>::max());
        EXPECT_EQ(std::numeric_limits<int>::max(), v); 
        
    }
    {
        val v = std::numeric_limits<int>::min();

        

        EXPECT_EQ(v, std::numeric_limits<int>::min());
        EXPECT_EQ(std::numeric_limits<int>::min(), v); 
        
    }
    {
        val v = std::numeric_limits<double>::max();

        

        EXPECT_EQ(v, std::numeric_limits<double>::max());
        EXPECT_EQ(std::numeric_limits<double>::max(), v); 
        
    }
    {
        val v = std::numeric_limits<double>::min();

        

        EXPECT_EQ(v, std::numeric_limits<double>::min());
        EXPECT_EQ(std::numeric_limits<double>::min(), v); 
        
    }
    
}



