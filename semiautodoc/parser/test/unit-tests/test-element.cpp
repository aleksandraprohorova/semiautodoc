#include "gtest/gtest.h"
#include "element.hpp"

TEST(testElement, equality)
{
    Element::pointer el1 = new Element("element");
    Element::pointer el2 = new Element("element");

    Element::pointer cl1 = new Element("class A");
    Element::pointer cl2 = new Element("class A");

    cl1->addElement(new Element("method1"));
    cl1->addElement(new Element("method2"));

    cl2->addElement(new Element("method1"));
    cl2->addElement(new Element("method2"));

    el1->addElement(cl1);
    el2->addElement(cl2);

    el1->addElement(new Element("function"));
    el2->addElement(new Element("function"));

    EXPECT_TRUE(*el1 == *el2);
}