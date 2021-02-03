#include "gtest/gtest.h"
#include "parser.hpp"

TEST(testParser, fileWithOneClass)
{
    std::string fileName = "../../parser/include/element.hpp";

    Element::pointer expected = new Element("../../parser/include/element.hpp");
    Element::pointer Class = new Element("class Element");

    Class->addElement(new Element("Element();"));
    Class->addElement(new Element("Element(std::string name);"));
    Class->addElement(new Element("~Element();"));
    Class->addElement(new Element("bool operator==(const Element& element) const;"));
    Class->addElement(new Element("bool operator!=(const Element& element) const;"));
    Class->addElement(new Element("std::string getName() const;"));
    Class->addElement(new Element("std::string getDescription() const;"));
    Class->addElement(new Element("void addElement(pointer newElement);"));
    Class->addElement(new Element("void show(std::ostream& out);"));
    Class->addElement(new Element("bool isComposite() const;"));
    Class->addElement(new Element("listOfElements& getListOfElements();"));
    Class->addElement(new Element("vectorOfElements getVectorOfElements();"));
    Class->addElement(new Element("pointer getParent();"));
    Class->addElement(new Element("int getRow();"));
    Class->addElement(new Element("void setName(std::string name);"));
    Class->addElement(new Element("void setDescription(std::string description);"));
    Class->addElement(new Element("void removeElement(int row);"));
    Class->addElement(new Element("void addElement(int row, Element::pointer newElement);"));
    expected->addElement(Class);

    auto result = Parser::parse(fileName);

    EXPECT_EQ(*expected, *result);

    delete result;
    delete expected;
}
TEST(testParser, classWithFunctionDefinitions)
{
    std::string sourceCode = 
    "#include <iostream>\n"
    "#pragma once\n"
    "\n"
    "class MyClass\n"
    "{\n"
    "public:              // Access specifier\n"
    "   MyClass(int arg)\n"
    "   {\n"
    "       field = arg;\n"
    "       ++count;\n"
    "   }\n"
    "   ~MyClass()\n"
    "   {\n"
    "       --count;\n"
    "   }\n"
    "   void myMethod()\n" 
    "   {\n"
    "       cout << \"Hello World!\";\n"
    "   }\n"
    "private:\n"
    "   static int count;\n"
    "   int field;"
    "}\n";

    Element::pointer expected = new Element();
    Element::pointer result = new Element();
    Element::pointer Class = new Element("class MyClass");

    Class->addElement(new Element("MyClass(int arg)"));
    Class->addElement(new Element("~MyClass()"));
    Class->addElement(new Element("void myMethod()"));
    
    expected->addElement(Class);

    std::stringstream in;
    in << sourceCode;
    Parser::initialize(in, result);

    EXPECT_TRUE(*expected == *result);

    delete result;
    delete expected;
}
TEST(testParser, severalClassesAndFreeFunctions)
{
    std::string sourceCode = 
    "#include <iostream>\n"
    "#pragma once\n"
    "\n"
    "class MyClass\n"
    "{\n"
    "public:              // Access specifier\n"
    "   MyClass(int arg);\n"
    "   ~MyClass();\n"
    "   void myMethod() const;\n" 
    "private:\n"
    "   static int count;\n"
    "   int field;\n"
    "};\n"
    "class ClassWithoutDefinition;\n"
    "struct Struct\n"
    "{\n"
    "   int a;\n"
    "   int b;\n"
    "   int c;\n"
    "};\n"
    "struct derivedStruct: Struct\n"
    "{\n"
    "   long d;\n"
    "}\n"
    "int sum(int a, int b);\n";

    Element::pointer expected = new Element();
    Element::pointer result = new Element();
    Element::pointer myClass = new Element("class MyClass");

    myClass->addElement(new Element("MyClass(int arg);"));
    myClass->addElement(new Element("~MyClass();"));
    myClass->addElement(new Element("void myMethod() const;"));
    
    expected->addElement(myClass);
    expected->addElement(new Element("class ClassWithoutDefinition;"));
    expected->addElement(new Element("struct Struct"));
    expected->addElement(new Element("struct derivedStruct: Struct"));
    expected->addElement(new Element("int sum(int a, int b);"));

    std::stringstream in;
    in << sourceCode;
    Parser::initialize(in, result);

    EXPECT_TRUE(*expected == *result);

    delete result;
    delete expected;
}