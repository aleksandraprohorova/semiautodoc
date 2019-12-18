### class Element

|Name|Description|
|-|-|
|Element();||
|Element(std::string name);||
|~Element();|Ввиду некоторых причин невозможно воспользоваться средствами автоматического управления ресурсами, так что освобождать память приходится вручную|
|std::string getName();||
|std::string getDescription();||
|void addElement(pointer newElement);||
|void show(std::ostream& out);||
|bool isComposite();|Информация, необходимая для решения того, выводить ли таблицу для вложенных элементов|
|listOfElements& getListOfElements();||
|vectorOfElements getVectorOfElements();||
|pointer getParent();|Необходимо для создания QTreeView, информация о родителе сохраняется при добавлении элемента|
|int getRow();||
|void setName(std::string name);||
|void setDescription(std::string description);||
|void removeElement(int row);||
|void addElement(int row, Element::pointer newElement);||
### class Function: public Element

|Name|Description|
|-|-|
|  Function(std::string name);||
### class Class: public Element

|Name|Description|
|-|-|
|  Class(std::string name);||
### void initializeModel(std::istream& in, Element::pointer model);
### Class::pointer createClass(std::istream& in, std::string line);
### Function::pointer createFunction(std::istream& in, std::string line);
