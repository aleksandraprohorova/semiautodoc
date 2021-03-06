#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>

#include "element.hpp"

class TreeModel : public QAbstractItemModel
{
  Q_OBJECT

public:
  TreeModel(const Element::pointer model, QObject* parent = nullptr);
  ~TreeModel() override;

  // Header:
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

  QModelIndex index(int row, int column,
                    const QModelIndex &parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex &index) const override;

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  Qt::ItemFlags flags(const QModelIndex& index) const override;
  bool setData(const QModelIndex& index, const QVariant& value, int role) override;
  
  bool removeRows(int position, int rows, const QModelIndex& index = QModelIndex());
  bool insertRows(int position, int rows, const QModelIndex& index = QModelIndex());

private:
  Element* rootItem;
};

#endif // TREEMODEL_H
