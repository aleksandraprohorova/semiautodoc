#include "class.hpp"

#include <iostream>
#include <sstream>


Class::Class(std::string name):
  Element(name)
{
}

bool Class::isClassDeclaration(std::string line)
{
    return ((line.find("class") != std::string::npos) || (line.find("struct") != std::string::npos));
}

std::string Class::getContent(std::istream& in)
{
  std::string line;
  std::string contentOfClassStr;
  getline(in, line, '{');
  while(getline(in, line, '}'), line.find('{') != std::string::npos)
  {
    contentOfClassStr += line;
  }
  contentOfClassStr += line;
  return contentOfClassStr;
}
