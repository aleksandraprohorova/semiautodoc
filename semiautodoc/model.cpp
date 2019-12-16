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

/*Element::Element(const Element& other)
  name_(other.name_),
  elements_(other.elements_),
  parent()
  //parent(std::make_shared<Element>(other.parent->name_))
{
  name_ = other.name_;
  if (other.parent)
  {
    parent = std::make_shared<Element>(*other.parent);
  }
  for (auto it = other.elements_.begin(); it != other.elements_.end(); ++it)
  {
    elements_.emplace_back(*it);
  }
}*/

/*bool Element::operator==(const Element& other)
{
  return name_ == other.name_;
}*/
void Element::addElement(Element::pointer newElement)
{
  //newElement->parent = std::shared_ptr<Element>(this);
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
    //std::cout << line << " - not a class\n";
    return nullptr;
  }
  //std::cout << line << " + class\n";
  std::string contentOfClassStr;
  getline(in, tmp, '{');
  while(getline(in, tmp, '}'), tmp.find('{') != std::string::npos)
  {
    //std::cout << "tmp:\n" << tmp << "\n";
    contentOfClassStr += tmp;
  }
  //std::cout << "tmp:\n" << tmp << "\n";
  contentOfClassStr += tmp;
  //auto newClass = std::make_shared<Class>(line);
  auto newClass = new Class(line);
  std::stringstream contentOfClass(contentOfClassStr);
  //std::cout << contentOfClassStr << "\n";
  initializeModel(contentOfClass, newClass);
  return newClass;
}
Function::pointer createFunction(std::istream& in, std::string line)
{
  std::string tmp;
  std::cmatch result;
  std::regex regular("[[:blank:]]*[[:alnum:]|[:punct:]]+[[:blank:]]+[^[:space:]\\(\\)]{1,}\\([^\\(\\)]*\\)[;]?",std::regex_constants::extended);

  if (!std::regex_match(line.c_str(), result, regular))
  {
    //std::cout << line << " - not a function\n";
    return nullptr;
  }
  /*if ((line.find("(") == std::string::npos) || (line.find(")") == std::string::npos))
  {
    //std::cout << line << " - not a function \n";
    return nullptr;
  }*/
  //auto newFunction = std::make_shared<Function>(line);
  auto newFunction = new Function(line);
  std::string contentOfFunctionStr;
  //getline(in, tmp);
  in >> std::ws;
  if (in.peek() == '{')
  {
    getline(in, tmp, '{');
    while(getline(in, tmp, '}'), tmp.find('{') != std::string::npos)
    {
      //std::cout << "tmp:\n" << tmp << "\n";
      contentOfFunctionStr += tmp;
    }
    contentOfFunctionStr += tmp;
    std::stringstream contentOfFunction(contentOfFunctionStr);
    initializeModel(contentOfFunction, newFunction);
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
