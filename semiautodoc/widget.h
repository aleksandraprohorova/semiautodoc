#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileSystemModel>
#include <QSplitter>
#include <unordered_map>

#include "tree-model.h"
#include "model-widget.h"

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
  void closeTab(int index);

private:
  Ui::Widget *ui;

  QString directory;
  QString fileToParse;

  QTreeView* fileSystemView;
  QFileSystemModel* fileSystemModel;

  QTabWidget* tabWidget;
  std::unordered_map<std::string, ModelWidget*> tabs;

  QSplitter* splitter;

  void parseFile();
};

#endif // WIDGET_H
