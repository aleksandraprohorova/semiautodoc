#include "parser.hpp"

#include <fstream>
#include <string>
#include <iostream>

Element::pointer Parser::parse(std::string pathToFile)
{
  auto model = new Element();
  std::ifstream in(pathToFile);
  initializeModel(in, model);
  in.close();
  return model;
}


