#include "widget.h"
#include "ui_widget.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QTreeWidget>
#include <QFileDialog>
#include <QLabel>
#include <QList>
#include <QLineEdit>
#include <QTextStream>
#include <QPalette>
#include <QMenuBar>


#include <iostream>
#include <fstream>

#include "parser.hpp"
#include "tree-model.h"
#include "edit-text-delegate.h"

Widget::Widget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Widget)
{
  ui->setupUi(this);
  
  setWindowTitle("Semiautodoc");

  QMenuBar* menuBar = new QMenuBar;
  QMenu*  fileMenu = new QMenu("File");

  fileMenu->addAction("Open file",
                      this,
                      SLOT(selectFileForParsing()),
                      Qt::CTRL + Qt::Key_Q
                     );
  fileMenu->addSeparator();
  fileMenu->addAction("Open directory",
                      this,
                      SLOT(selectDirectory()));
  fileMenu->addSeparator();
  fileMenu->addAction("Save as markdown",
                         this,
                         SLOT(saveDocument()));
  menuBar->addMenu(fileMenu);

  QVBoxLayout* mainLayout = new QVBoxLayout;

  mainLayout->setMenuBar(menuBar);

  fileSystemModel = new QFileSystemModel;

  treeWidget = new QTreeView;
  fileSystemView = new QTreeView;
  //treeWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
  //fileSystemView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QHBoxLayout* layoutForTreeWidget = new QHBoxLayout;

  layoutForTreeWidget->addWidget(fileSystemView);
  layoutForTreeWidget->addWidget(treeWidget);

  mainLayout->addLayout(layoutForTreeWidget);
  setLayout(mainLayout);

  showMaximized();

}

Widget::~Widget()
{
  delete ui;
}

void Widget::selectFileForParsing()
{
  QString path = QFileDialog::getOpenFileName(this, tr("open file"));
  fileToParse = path;

  parseFile();
}

void Widget::selectDirectory()
{
  QString path = QFileDialog::getExistingDirectory(0, "Directory Dialog", "");
  std::cerr << path.toStdString() << "\n";
  fileSystemModel->setRootPath(path);
  fileSystemView->setModel(fileSystemModel);
  fileSystemView->setRootIndex(fileSystemModel->index(path));
  fileSystemView->show();
  std::cerr << fileSystemModel->rootPath().toStdString() <<"\n";
  for (int i = 1; i < fileSystemModel->columnCount(); i++)
  {
    fileSystemView->hideColumn(i);
  }
  connect(fileSystemView, SIGNAL(clicked(QModelIndex)),this, SLOT(selectFileForParsing(QModelIndex)));
}

void Widget::parseFile()
{
  model = Parser::parse(fileToParse.toStdString());
  treeModel = new TreeModel(model,treeWidget);

  treeWidget->setModel(treeModel);

  EditTextDelegate* editTextDelegate = new EditTextDelegate(treeWidget);
  treeWidget->setItemDelegateForColumn(0, editTextDelegate);
  treeWidget->setItemDelegateForColumn(1, editTextDelegate);

  treeWidget->show();

  model->show(std::cerr);
}

void Widget::selectFileForParsing(QModelIndex index)
{
  auto path = fileSystemModel->fileInfo(index).filePath();
  fileToParse = path;
  parseFile();
}
void showMarkdown(Element::pointer model, std::ostream& out)
{
  if (!model || model->getListOfElements().empty())
  {
    return;
  }
  for (auto element: model->getListOfElements())
  {
    out << "### " << element->getName() <<  "\n";
    if (!element->getDescription().empty())
    {
      out << element->getDescription() << "\n";
    }
    if (element->isComposite())
    {
      out << "\n|Name|Description|\n|-|-|\n";
      for (auto innerElement: element->getListOfElements())
      {
        out << "|" << innerElement->getName() << "|" << innerElement->getDescription() << "|\n";
      }
      for (auto innerElement: element->getListOfElements())
      {
        showMarkdown(innerElement, out);
      }

    }

  }
}
void Widget::saveDocument()
{
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"));
  if (!fileName.isNull())
  {

    QFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Truncate))
    {
        std::ofstream fout(fileName.toStdString());
        showMarkdown(model, fout);
    }
  }
}
