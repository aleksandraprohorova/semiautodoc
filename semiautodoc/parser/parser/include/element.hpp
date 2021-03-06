#ifndef PARSER_ELEMENT
#define PARSER_ELEMENT

#include <list>
#include <vector>
#include <string>

class Element
{
public:
  using pointer = Element*;
  using listOfElements = std::list<pointer>;
  using vectorOfElements = std::vector<pointer>;
  
  Element();
  Element(std::string name);
  ~Element();

  bool operator==(const Element& element) const;
  bool operator!=(const Element& element) const;

  std::string getName() const;
  std::string getDescription() const;
  void addElement(pointer newElement);
  void show(std::ostream& out);
  bool isComposite() const;

  listOfElements& getListOfElements();
  vectorOfElements getVectorOfElements();

  pointer getParent();
  int getRow();
  void setName(std::string name);
  void setDescription(std::string description);

  void removeElement(int row);
  void addElement(int row, Element::pointer newElement);

protected:
  listOfElements elements_;
  std::string name_;
  std::string desctiption_;

  pointer parent;
};

#endif
