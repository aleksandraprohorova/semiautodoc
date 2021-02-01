#ifndef PARSER_FUNCTION
#define PARSER_FUNCTION

#include "element.hpp"

class Function: public Element
{
public:
  using pointer = Function*;
  Function(std::string name);

  static bool isFunctionDeclaration(std::string line);
  static std::string getContent(std::istream& in);
};



#endif
