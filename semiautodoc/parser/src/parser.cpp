#include "parser.hpp"

#include "class.hpp"
#include "function.hpp"

#include <fstream>
#include <string>
#include <sstream>
#include <regex>

Element::pointer Parser::parse(std::string& pathToFile)
{
  auto model = new Element();
  std::ifstream in(pathToFile);
  initialize(in, model);
  in.close();
  model->setName(pathToFile);
  return model;
}

void Parser::initialize(std::istream& in, Element::pointer model)
{
  std::string declaration;
  while(!in.eof())
  {
    getline(in, declaration);
    if (Class::isClassDeclaration(declaration))
    {
      auto newClass = new Class(declaration);
      std::stringstream contentOfClass(Class::getContent(in));
      initialize(contentOfClass, newClass);
      model->addElement(newClass);
      continue;
    }

    if (Function::isFunctionDeclaration(declaration))
    {
      auto newFunction = new Function(declaration);
      Function::getContent(in);
      model->addElement(newFunction);
      continue;
    }
  }
}


