#include "tree-model.h"

#include <iostream>
#include <QVariant>

TreeModel::TreeModel(const Element::pointer model, QObject* parent):
  QAbstractItemModel (parent),
  rootItem(model)
  //rootItem(new Element(*model))
{
  std::cerr << __PRETTY_FUNCTION__ << "\n";
}

TreeModel::~TreeModel()
{
  std::cerr << __PRETTY_FUNCTION__ << "\n";
  //qDeleteAll(rootItem);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  std::cerr << __PRETTY_FUNCTION__ << "  " << role << "\n";

  //return QVariant(rootItem->getVectorOfElements().at(role)->getName().c_str());
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
  {
    if (section == 0)
    {
      return QVariant("Name");
    }
    return QVariant("Description");
    //std::cerr << rootItem->getName() << "\n";
    //return QVariant("smt");
    //return QVariant(rootItem->getName().c_str());
    //return rootItem->data(section);
  }
  //std::cerr << "None\n";
  return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
  std::cerr << __PRETTY_FUNCTION__ << " row = " << row << ", column = " << column << "\n";
  if (!hasIndex(row, column, parent))
  {
    return QModelIndex();
  }
  //std::cerr << "nice\n";

  auto parentItem = rootItem;
  if (parent.isValid())
  {
    parentItem = static_cast<Element*>(parent.internalPointer());
    //parentItem.reset(static_cast<Element*>(parent.internalPointer()));
  }
  /*std::shared_ptr<Element> parentItem = parent.isValid() ?
      std::make_shared<Element>(static_cast<Element*>(parent.internalPointer())) :
        rootItem;*/

  Element::pointer childItem = parentItem->getVectorOfElements().at(row);
  if (childItem)
  {
    //return QModelIndex();
    //Element* clone = new Element(*childItem);
    //return createIndex(row, column, clone);
    return createIndex(row, column, childItem);
  }
  return QModelIndex();

}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
  std::cerr << __PRETTY_FUNCTION__ << "\n";
  if (!index.isValid())
  {
    //std::cerr << "Qmodelindex\n";
    return QModelIndex();
  }

  //std::shared_ptr<Element> childItem(static_cast<Element*>(index.internalPointer()));
  //std::shared_ptr<Element> parentItem = childItem->getParent();

  Element::pointer childItem = static_cast<Element::pointer>(index.internalPointer());
  //std::cerr << "here\n";
  //Element* parentItem = new Element(*childItem->getParent());
  Element::pointer parentItem = childItem->getParent();
  if (!parentItem)
  {
    throw std::runtime_error("Parent item = nullptr");
  }
  if (parentItem == rootItem)
  {
      //std::cerr << "ParentItem  = rootItem\n";
      return QModelIndex();
  }
  int row = childItem->getRow();
  if (row == -1 ) throw std::runtime_error("aaaa\n");
  //std::cout << "row = " << row << "\n";
  return createIndex(row, 0, parentItem);
  //return createIndex(0, 0, parentItem); // row? column?

  /*TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
  TreeItem *parentItem = childItem->parentItem();

  if (parentItem == rootItem)
  {
    return QModelIndex();
  }
  return createIndex(parentItem->row(), 0, parentItem);*/
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
  std::cerr << __PRETTY_FUNCTION__ << "\n";
  /*if (parent.column() > 0)
  {
    std::cerr << 0 <<  "\n";
    return 0;
  }*/
  auto parentItem = rootItem;
  if (parent.isValid())
  {
    parentItem = static_cast<Element::pointer>(parent.internalPointer());
    //parentItem.reset(static_cast<Element*>(parent.internalPointer()));
  }
  if(!parentItem)
  {
    throw std::runtime_error("parentItem is nullptr\n");
  }
  //std::cerr << "|" << parentItem->getName() << ", " << parentItem->getListOfElements().size() << "\n";
  return parentItem->getListOfElements().size();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
  std::cerr << __PRETTY_FUNCTION__ << "\n";
  if (parent.isValid())
  {
    std::cerr << ", Valid\n";
    return 2;
  }
  std::cerr << ", Invalid\n";
  return 2;
  //return 1;
  /*if (parent.isValid())
    return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
  return rootItem->columnCount();*/
}

Qt::ItemFlags TreeModel::flags(const QModelIndex& index) const
{
  std::cerr << __PRETTY_FUNCTION__ << "\n";
  if (!index.isValid())
  {
    //std::cerr << "not editable\n";
    return Qt::ItemIsEnabled;
    //return Qt::ItemIsSelectable;
    //return Qt::ItemIsEditable;
  }
  //std::cerr << "editable\n";
  //return Qt::ItemIsEditable;
  return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool TreeModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
  std::cerr << __PRETTY_FUNCTION__ << "\n";
  if (index.isValid() && role == Qt::EditRole)
  {
    Element::pointer item = static_cast<Element::pointer>(index.internalPointer());
    if (index.column() == 0)
    {
      item->setName(value.toString().toStdString());
    }
    else {
      item->setDescription(value.toString().toStdString());
    }
    emit dataChanged(index, index);
    return true;
  }
  return false;
}

/*void TreeModel::setupModelData(const QStringList& lines, TreeItem* parent)
{

}*/

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
  //std::cerr << __PRETTY_FUNCTION__ << "\n";
  if (!index.isValid())
    return QVariant();
  if (role != Qt::DisplayRole)
  {
    return QVariant();
  }
  Element::pointer item = static_cast<Element::pointer>(index.internalPointer());
  if (index.column() == 0)
  {
    return QVariant(item->getName().c_str());
  }
  return QVariant(item->getDescription().c_str());

  /*TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
  return item->data(index.column());*/
}
