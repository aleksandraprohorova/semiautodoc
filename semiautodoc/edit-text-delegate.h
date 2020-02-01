#ifndef EDITTEXTDELEGATE_H
#define EDITTEXTDELEGATE_H

#include <QItemDelegate>

class EditTextDelegate : public QItemDelegate
{
public:
  EditTextDelegate(QObject* parent = 0);
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

#endif // EDITTEXTDELEGATE_H
