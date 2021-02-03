#include "parser.hpp"

#include "class.hpp"
#include "function.hpp"

#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <iostream>

Element::pointer Parser::parse(std::string& pathToFile)
{
  auto model = new Element();
  std::ifstream in(pathToFile);
  if (!in)
  {
    throw std::runtime_error("Couldn't read from file " + pathToFile);
  }
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
    in >> std::ws;
    if (Class::isClassDeclaration(declaration))
    {
      auto newClass = new Class(declaration);
      if (declaration.find(';') == std::string::npos)
      {
        std::stringstream contentOfClass(Class::getContent(in));
        initialize(contentOfClass, newClass);
      }
      
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


