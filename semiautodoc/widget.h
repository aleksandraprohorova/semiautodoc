#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTreeWidget>
#include <QFileSystemModel>

#include "tree-model.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
  Q_OBJECT

public:
  explicit Widget(QWidget *parent = nullptr);
  ~Widget();

public slots:
  void selectFileForParsing();
  void selectDirectory();
  void selectFileForParsing(QModelIndex index);
  void saveDocument();

  void removeRow();
  void addRow();

private:
  Ui::Widget *ui;

  QString directory;
  QString fileToParse;

  QLineEdit* labelFileToParse;
  QTreeView* treeWidget;

  TreeModel* treeModel;
  QFileSystemModel* fileSystemModel;

  Element::pointer model;

  QTreeView* fileSystemView;

  void parseFile();

};

#endif // WIDGET_H
