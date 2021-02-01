#ifndef PARSER_HPP
#define PARSER_HPP

#include "element.hpp"

class Parser
{
public:
  static Element::pointer parse(std::string& pathToFile);

  static void initialize(std::istream& in, Element::pointer model);

  //static Class::pointer createClass(std::istream& in, std::string line);
  //static Function::pointer createFunction(std::istream& in, std::string line);
};

#endif // PARSER_HPP
