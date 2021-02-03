#include "gtest/gtest.h"
#include "class.hpp"

TEST(testClassDeclaration, ordinaryClass)
{
    std::string line = "class OrdinaryClass";
    EXPECT_TRUE(Class::isClassDeclaration(line));
}
TEST(testClassDeclaration, ordinaryStruct)
{
    std::string line = "struct ordinary_struct";
    EXPECT_TRUE(Class::isClassDeclaration(line));
}
TEST(testClassDeclaration, derivedClass)
{
    std::string line = "class DerivedClass: public BaseClass";
    EXPECT_TRUE(Class::isClassDeclaration(line));
}
TEST(testClassDeclaration, derivedStruct)
{
    std::string line = "struct DerivedClass: BaseClass";
    EXPECT_TRUE(Class::isClassDeclaration(line));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
    return 0;
}