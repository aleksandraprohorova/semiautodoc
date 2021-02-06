### class Element

|Name|Description|
|-|-|
|Element();||
|Element(std::string name);||
|~Element();|Ввиду некоторых причин невозможно воспользоваться средствами автоматического управления ресурсами, так что освобождать память приходится вручную|
|bool operator==(const Element& element) const;|Необходимо для сравнения ожидаемого и полученного дерева в тестах|
|bool operator!=(const Element& element) const;||
|std::string getName() const;||
|std::string getDescription() const;||
|void addElement(pointer newElement);||
|void show(std::ostream& out);||
|bool isComposite() const;|Информация, необходимая для решения того, выводить ли таблицу для вложенных элементов|
|listOfElements& getListOfElements();||
|vectorOfElements getVectorOfElements();||
|pointer getParent();|Необходимо для создания QTreeView, информация о родителе сохраняется при добавлении элемента|
|int getRow();||
|void setName(std::string name);||
|void setDescription(std::string description);||
|void removeElement(int row);||
|void addElement(int row, Element::pointer newElement);||
