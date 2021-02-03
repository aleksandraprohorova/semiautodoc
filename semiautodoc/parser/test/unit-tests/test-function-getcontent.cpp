#include "gtest/gtest.h"
#include "function.hpp"

TEST(testFunctionGetContent, functionWithDefinition)
{
    std::string sourceCode = "{\n"
    "int tmp = arg1 + arg2;\n"
    "int tmp2 = tmp * tmp;\n;"
    "return tmp2 - tmp;\n"
    "}\n"
    "    \n"
    "#endif\n";

    std::stringstream in;
    in << sourceCode;

    std::string expectedContent =
    "\nint tmp = arg1 + arg2;\n"
    "int tmp2 = tmp * tmp;\n;"
    "return tmp2 - tmp;\n";

    std::string content = Function::getContent(in);

    EXPECT_EQ(expectedContent, content);
}
TEST(testFunctionGetContent, functionWithoutDefinition)
{
    std::string sourceCode =
    "private:\n"
    "int field;\n"
    "}\n"
    "static long func(long a, long b)\n"
    "{\n"
    "   return a + b;\n"
    "}";

    std::stringstream in;
    in << sourceCode;

    std::string expectedContent = "";

    std::string content = Function::getContent(in);

    EXPECT_EQ(expectedContent, content);
}