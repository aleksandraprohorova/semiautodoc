#include "function.hpp"

#include <regex>

Function::Function(std::string name):
  Element(name)
{
}

bool Function::isFunctionDeclaration(std::string line)
{
  std::cmatch result;
  std::regex regular("[[:blank:]]*(static )?(const )?[[:blank:]]*([[:alnum:]|[:punct:]]+[[:blank:]]+)?[^[:space:]\\(\\)]{1,}\\([^\\(\\)]*\\)( const)?[;]?",std::regex_constants::extended);

  return (std::regex_match(line.c_str(), result, regular));
}
std::string Function::getContent(std::istream& in)
{
  std::string contentOfFunctionStr;
  std::string tmp;
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
  return contentOfFunctionStr;
}

