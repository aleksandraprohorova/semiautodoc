#include "edit-text-delegate.h"

#include <QTextEdit>
#include <iostream>

EditTextDelegate::EditTextDelegate(QObject* parent):
  QItemDelegate(parent)
{
  std::cerr << __PRETTY_FUNCTION__ << "\n";
}

QWidget* EditTextDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
  std::cerr << __PRETTY_FUNCTION__ << "\n";
  QTextEdit* editText = new QTextEdit(index.data().toString(), parent);
  return editText;
}

void EditTextDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
  std::cerr << __PRETTY_FUNCTION__ << "\n";
  QString value = index.model()->data(index).toString();
  QTextEdit *editText = static_cast<QTextEdit*> (editor);
  editText->setText(value);
}

void EditTextDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
  std::cerr << __PRETTY_FUNCTION__ << "\n";
  QTextEdit *editText = static_cast<QTextEdit*> (editor);
  if (!editText->toPlainText().isEmpty())
  {
    model->setData(index,editText->toPlainText());
  }
}
