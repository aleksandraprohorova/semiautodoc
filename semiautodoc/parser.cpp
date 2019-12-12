#include "parser.hpp"

#include <fstream>
#include <string>
#include <iostream>

/*std::shared_ptr<Element> Parser::parse(std::string pathToFile)
{
  auto model = std::make_shared<Element>();
  std::ifstream in(pathToFile);
  initializeModel(in, model);
  in.close();
  return model;
}*/

Element::pointer Parser::parse(std::string pathToFile)
{
  //auto model = std::make_shared<Element>();
  auto model = new Element();
  std::ifstream in(pathToFile);
  initializeModel(in, model);
  in.close();
  return model;
}


