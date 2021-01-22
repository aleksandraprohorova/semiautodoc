#ifndef PARSER_HPP
#define PARSER_HPP

#include "model.hpp"

class Parser
{
public:
  static Element::pointer parse(std::string pathToFile);
};

#endif // PARSER_HPP
