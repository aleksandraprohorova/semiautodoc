#include "element.hpp"

#include <istream>

Element::Element()
{
}
Element::Element(std::string name):
  name_(name)
{
}
Element::~Element()
{
  for (auto element: elements_)
  {
    delete element;
  }
}



void Element::addElement(Element::pointer newElement)
{
  newElement->parent = this;
  elements_.push_back(newElement);
}
bool Element::isComposite() const
{
  return !elements_.empty();
}

Element::listOfElements& Element::getListOfElements()
{
  return elements_;
}

Element::vectorOfElements Element::getVectorOfElements()
{
  return vectorOfElements(elements_.begin(), elements_.end());
}

Element::pointer Element::getParent()
{
  return parent;
}

int Element::getRow()
{
  if (!parent)
  {
    throw std::runtime_error("Invalid parent pointer.");
  }
  for (int i = 0; i < parent->getVectorOfElements().size(); ++i)
  {
    if (this == parent->getVectorOfElements().at(i))
    {
      return i;
    }
  }
  return -1;
}

void Element::setName(std::string name)
{
  name_ = name;
}

void Element::setDescription(std::string description)
{
  desctiption_ = description;
}

void Element::removeElement(int row)
{
  auto it = elements_.begin();
  for (int i = 0; i < row; ++i)
  {
    ++it;
  }
  elements_.erase(it);
}

void Element::addElement(int row, Element::pointer newElement)
{
  newElement->parent = this;
  auto it = elements_.begin();
  for (int i = 0; i < row; ++i)
  {
    ++it;
  }
  elements_.insert(it, newElement);
}
void Element::show(std::ostream& out)
{
  for (auto element: elements_)
  {
    out << element->getName() << "\t" << element->getDescription() << "\n";
    if (element->isComposite())
    {
      out << "Content:\n";
      element->show(out);
      out << "End content\n";
    }
  }
}


std::string Element::getName() const
{
  return name_;
}

std::string Element::getDescription() const
{
  return desctiption_;
}

bool Element::operator==(const Element& element) const
{
  if ((name_ != element.getName()) || (elements_.size() != element.elements_.size()))
  {
    return false;
  }
  auto it1 = elements_.begin();
  auto it2 = element.elements_.begin();
  while (it1 != elements_.end())
  {
    if (**it1 != **it2) 
    {
      return false;
    }
    ++it1;
    ++it2;
  }
  return true;
}
bool Element::operator!=(const Element& element) const
{
  return !(*this == element);
}