#include "gtest/gtest.h"
#include "class.hpp"

TEST(testClassGetContent, ordinaryClass)
{
    std::string sourceCode = "{\n"
    "public:\n"
    "using pointer = Class*\n;"
    "Class(std::string name);\n"
    "static bool isClassDeclaration(std::string line);\n"
    "static std::string getContent(std::istream& in);\n"
    "};\n"
    "    \n"
    "#endif\n";

    std::stringstream in;
    in << sourceCode;

    std::string expectedContent =
    "\npublic:\n"
    "using pointer = Class*\n;"
    "Class(std::string name);\n"
    "static bool isClassDeclaration(std::string line);\n"
    "static std::string getContent(std::istream& in);\n";

    std::string content = Class::getContent(in);

    EXPECT_EQ(expectedContent, content);
}
TEST(testClassGetContent, classWithFunctionDefinitions)
{
    std::string sourceCode = "{\n"
    "public:              // Access specifier\n"
    "MyClass(int arg)\n"
    "{\n"
    "   field = arg;\n"
    "}\n"
    "void myMethod() {  // Method/function defined inside the class\n"
    "   cout << \"Hello World!\";\n"
    "}\n"
    "private:\n"
    "int field;\n"
    "}\n"
    "static long func(long a, long b)\n"
    "{\n"
    "   return a + b;\n"
    "}";

    std::stringstream in;
    in << sourceCode;

    std::string expectedContent =
    "\npublic:              // Access specifier\n"
    "MyClass(int arg)\n"
    "{\n"
    "   field = arg;\n"
    "}\n"
    "void myMethod() {  // Method/function defined inside the class\n"
    "   cout << \"Hello World!\";\n"
    "}\n"
    "private:\n"
    "int field;\n";

    std::string content = Class::getContent(in);

    EXPECT_EQ(expectedContent, content);
}

TEST(testClassGetContent, oneClassAfterAnother)
{
    std::string sourceCode = "{\n"
    "public:              // Access specifier\n"
    "MyClass(int arg)\n"
    "{\n"
    "   field = arg;\n"
    "}\n"
    "void myMethod() {  // Method/function defined inside the class\n"
    "   cout << \"Hello World!\";\n"
    "}\n"
    "private:\n"
    "int field;\n"
    "}\n"
    "struct A\n"
    "{\n"
    "   int field;\n"
    "}";

    std::stringstream in;
    in << sourceCode;

    std::string expectedContent =
    "\npublic:              // Access specifier\n"
    "MyClass(int arg)\n"
    "{\n"
    "   field = arg;\n"
    "}\n"
    "void myMethod() {  // Method/function defined inside the class\n"
    "   cout << \"Hello World!\";\n"
    "}\n"
    "private:\n"
    "int field;\n";

    std::string content = Class::getContent(in);

    EXPECT_EQ(expectedContent, content);
}