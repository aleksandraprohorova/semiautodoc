#ifndef PARSER_CLASS
#define PARSER_CLASS

#include "element.hpp"

class Class: public Element
{
public:
  using pointer = Class*;
  Class(std::string name);

  static bool isClassDeclaration(std::string line);
  static std::string getContent(std::istream& in);
};




#endif
