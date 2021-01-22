#include "model.hpp"

#include <sstream>
#include <iostream>
#include <exception>
#include <regex>


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
bool Element::isComposite()
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

Class::Class(std::string name):
  Element(name)
{
}
Function::Function(std::string name):
  Element(name)
{
}
std::string Element::getName()
{
  return name_;
}

std::string Element::getDescription()
{
  return desctiption_;
}

Class::pointer createClass(std::istream& in, std::string line)
{
  std::string tmp;
  if (line.find("class") == std::string::npos)
  {
    std::cout << line << " - not a class\n";
    return nullptr;
  }
  std::string contentOfClassStr;
  getline(in, tmp, '{');
  while(getline(in, tmp, '}'), tmp.find('{') != std::string::npos)
  {
    contentOfClassStr += tmp;
  }
  contentOfClassStr += tmp;
  auto newClass = new Class(line);
  std::stringstream contentOfClass(contentOfClassStr);
  initializeModel(contentOfClass, newClass);
  return newClass;
}
Function::pointer createFunction(std::istream& in, std::string line)
{
  std::string tmp;
  std::cmatch result;
  std::regex regular("[[:blank:]]*(static )?(const )?[[:blank:]]*([[:alnum:]|[:punct:]]+[[:blank:]]+)?[^[:space:]\\(\\)]{1,}\\([^\\(\\)]*\\)( const)?[;]?",std::regex_constants::extended);

  if (!std::regex_match(line.c_str(), result, regular))
  {
    std::cout << line << " - not a function\n";
    return nullptr;
  }
  auto newFunction = new Function(line);
  std::string contentOfFunctionStr;
  in >> std::ws;
  if (in.peek() == '{')
  {
    getline(in, tmp, '{');
    while(getline(in, tmp, '}'), tmp.find('{') != std::string::npos)
    {
      contentOfFunctionStr += tmp;
    }
    contentOfFunctionStr += tmp;
  }
  return newFunction;
}
void initializeModel(std::istream& in, Element::pointer model)
{
  std::string tmp;
  while(!in.eof())
  {
    getline(in, tmp);
    auto newClass = createClass(in, tmp);
    if (newClass)
    {
      model->addElement(newClass);
      continue;
    }
    auto newFunction = createFunction(in, tmp);
    if (newFunction)
    {
      model->addElement(newFunction);
      continue;
    }
  }
}
