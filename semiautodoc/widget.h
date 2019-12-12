#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTreeWidget>

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
  void parseFile();
  void saveDocument();

private:
  Ui::Widget *ui;

  QString fileToParse;

  QLineEdit* labelFileToParse;
  QTreeView* treeWidget;

  TreeModel* treeModel;

  Element::pointer model;

};

#endif // WIDGET_H
