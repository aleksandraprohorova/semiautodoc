#ifndef MODEL
#define MODEL

#include <string>
#include <list>
#include <vector>
#include <memory>


class Element
{
public:
  //using pointer = std::shared_ptr<Element>;
  using pointer = Element*;
  using listOfElements = std::list<pointer>;
  using vectorOfElements = std::vector<pointer>;

  Element();
  Element(std::string name);

  std::string getName();
  std::string getDescription();
  void addElement(pointer newElement);
  void show(std::ostream& out);
  bool isComposite();

  listOfElements& getListOfElements();
  vectorOfElements getVectorOfElements();

  pointer getParent();
  int getRow();
  void setName(std::string name);
  void setDescription(std::string description);
  
  void removeElement(int row);

protected:
  listOfElements elements_;
  std::string name_;
  std::string desctiption_;

  pointer parent;
};
class Function: public Element
{
public:
  using pointer = Function*;
  Function(std::string name);
};
class Class: public Element
{
public:
  using pointer = Class*;
  Class(std::string name);
};

void initializeModel(std::istream& in, Element::pointer model);
Class::pointer createClass(std::istream& in, std::string line);
Function::pointer createFunction(std::istream& in, std::string line);

#endif // MODEL
