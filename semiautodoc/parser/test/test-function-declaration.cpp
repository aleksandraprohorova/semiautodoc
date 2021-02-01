#include "gtest/gtest.h"
#include "function.hpp"

TEST(testFunctionDeclaration, main)
{
    std::string line = "void main(int argc, char[] argv)";
    EXPECT_TRUE(Function::isFunctionDeclaration(line));
}
TEST(testFunctionDeclaration, funcWithoutArgs)
{
    std::string line = "void func()";
    EXPECT_TRUE(Function::isFunctionDeclaration(line));
}
TEST(testFunctionDeclaration, constMethod)
{
    std::string line = "void method() const";
    EXPECT_TRUE(Function::isFunctionDeclaration(line));
}
TEST(testFunctionDeclaration, funcWithManyArgs)
{
    std::string line = "void func(int a, long b, Class c, Struct d, bool e) const";
    EXPECT_TRUE(Function::isFunctionDeclaration(line));
}
TEST(testFunctionDeclaration, spaceBetweenNameAndArgs)
{
    std::string line = "void func (int a, long b)";
    EXPECT_TRUE(Function::isFunctionDeclaration(line));
}
TEST(testFunctionDeclaration, virtualMethod)
{
    std::string line = "virtual bool qux();";
    EXPECT_TRUE(Function::isFunctionDeclaration(line));
}
TEST(testFunctionDeclaration, constReturnType)
{
    std::string line = "const Class::subclass& method(const std::string arg);";
    EXPECT_TRUE(Function::isFunctionDeclaration(line));
}
TEST(testFunctionDeclaration, staticFunction)
{
    std::string line = "static Element::pointer parse(std::string& pathToFile);";
    EXPECT_TRUE(Function::isFunctionDeclaration(line));
}
TEST(testFunctionDeclaration, constructor)
{
    std::string line = "Function(std::string name);";
    EXPECT_TRUE(Function::isFunctionDeclaration(line));
}
TEST(testFunctionDeclaration, copyConstructor)
{
    std::string line = "ClassName(const ClassNameReference& object);";
    EXPECT_TRUE(Function::isFunctionDeclaration(line));
}
TEST(testFunctionDeclaration, moveConstructor)
{
    std::string line = "ClassName(const ClassNameReference&& object);";
    EXPECT_TRUE(Function::isFunctionDeclaration(line));
}
TEST(testFunctionDeclaration, destructor)
{
    std::string line = "~ClassName();";
    EXPECT_TRUE(Function::isFunctionDeclaration(line));
}
TEST(testFunctionDeclaration, operatorAssignment)
{
    std::string line = "ClassNameReference& operator=(ClassNameReference& object);";
    EXPECT_TRUE(Function::isFunctionDeclaration(line));
}

TEST(testFunctionDeclaration, field)
{
    std::string line = "std::string name_;";
    EXPECT_FALSE(Function::isFunctionDeclaration(line));
}
TEST(testFunctionDeclaration, alias)
{
    std::string line = "using vectorOfElements = std::vector<pointer>;";
    EXPECT_FALSE(Function::isFunctionDeclaration(line));
}
TEST(testFunctionDeclaration, assignment)
{
    std::string line = "auto model = new Element();";
    EXPECT_FALSE(Function::isFunctionDeclaration(line));
}