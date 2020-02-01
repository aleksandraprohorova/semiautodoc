#include "tree-model.h"

#include <iostream>
#include <QVariant>

TreeModel::TreeModel(const Element::pointer model, QObject* parent):
  QAbstractItemModel (parent),
  rootItem(model)
{
}

TreeModel::~TreeModel()
{
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
  {
    if (section == 0)
    {
      return QVariant("Name");
    }
    return QVariant("Description");
  }
  return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
  if (!hasIndex(row, column, parent))
  {
    return QModelIndex();
  }

  auto parentItem = rootItem;
  if (parent.isValid())
  {
    parentItem = static_cast<Element*>(parent.internalPointer());
  }

  Element::pointer childItem = parentItem->getVectorOfElements().at(row);
  if (childItem)
  {
    return createIndex(row, column, childItem);
  }
  return QModelIndex();

}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
  if (!index.isValid())
  {
    return QModelIndex();
  }
  Element::pointer childItem = static_cast<Element::pointer>(index.internalPointer());

  Element::pointer parentItem = childItem->getParent();
  if (!parentItem)
  {
    throw std::runtime_error("Parent item = nullptr");
  }
  if (parentItem == rootItem)
  {
      return QModelIndex();
  }
  int row = childItem->getRow();
  if (row == -1 ) throw std::runtime_error("aaaa\n");

  return createIndex(row, 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
  auto parentItem = rootItem;
  if (parent.isValid())
  {
    parentItem = static_cast<Element::pointer>(parent.internalPointer());
  }
  if(!parentItem)
  {
    throw std::runtime_error("parentItem is nullptr\n");
  }
  return parentItem->getListOfElements().size();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
  if (parent.isValid())
  {
    std::cerr << ", Valid\n";
    return 2;
  }
  std::cerr << ", Invalid\n";
  return 2;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex& index) const
{
  if (!index.isValid())
  {
    return Qt::ItemIsEnabled;
  }
  return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool TreeModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
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

bool TreeModel::removeRows(int position, int rows, const QModelIndex& index)
{
  Element::pointer item = rootItem;
  if (index.isValid())
  {
    item = static_cast<Element::pointer>(index.internalPointer());
  }

  beginRemoveRows(index, position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
  {
    item->removeElement(position);
  }
  endRemoveRows();
  return true;
}

bool TreeModel::insertRows(int position, int rows, const QModelIndex& index)
{
  Element::pointer item = rootItem;
  if (index.isValid())
  {
    item = static_cast<Element::pointer>(index.internalPointer());
  }
  beginInsertRows(index, position, position + rows - 1);
  for (int row = 0; row < rows; ++row)
  {
    Element::pointer newElement = new Element();
    item->addElement(position, newElement);
  }
  endInsertRows();
  return true;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
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
}
