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
  //setWindowIcon(QIcon());

  QVBoxLayout* verticalLayout = new QVBoxLayout;
  QPushButton* buttonSelectFileForParsing = new QPushButton("выбор файла");
  QPushButton* buttonSelectDirectory = new QPushButton("выбор директории");
  QPushButton* buttonParseFile = new QPushButton("пропарсить");
  QPushButton* buttonSave = new QPushButton("Сохранить как markdown-файл");
  labelFileToParse = new QLineEdit();
  fileSystemModel = new QFileSystemModel;

  /*buttonSelectFileForParsing->setFlat(true);
  buttonParseFile->setFlat(true);
  buttonSave->setFlat(true);*/

  verticalLayout->addWidget(buttonSelectDirectory);
  verticalLayout->addWidget(buttonSelectFileForParsing);
  verticalLayout->addWidget(labelFileToParse);
  verticalLayout->addWidget(buttonParseFile);
  verticalLayout->addWidget(buttonSave);
  verticalLayout->setAlignment(Qt::AlignTop);

  /*QPalette palette;
  palette.setColor(QPalette::Background, Qt::white);
  setAutoFillBackground(true);
  setPalette(palette);*/


  treeWidget = new QTreeView;
  fileSystemView = new QTreeView;
  treeWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
  fileSystemView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QHBoxLayout* layoutForTreeWidget = new QHBoxLayout;

  layoutForTreeWidget->addWidget(fileSystemView);
  layoutForTreeWidget->addWidget(treeWidget);


  QHBoxLayout* mainLayout = new QHBoxLayout(this);

  mainLayout->addLayout(layoutForTreeWidget);
  mainLayout->addLayout(verticalLayout);

  showMaximized();

  connect(buttonSelectDirectory, SIGNAL(clicked()), this, SLOT(selectDirectory()));
  connect(buttonSelectFileForParsing, SIGNAL(clicked()), this, SLOT(selectFileForParsing()));
  connect(buttonParseFile, SIGNAL(clicked()), this, SLOT(parseFile()));
  connect(buttonSave, SIGNAL(clicked()), this, SLOT(saveDocument()));

}

Widget::~Widget()
{
  delete ui;
}

void Widget::selectFileForParsing()
{
  QString path = QFileDialog::getOpenFileName(this, tr("open file"));
  fileToParse = path;
  labelFileToParse->setText(path);
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
  labelFileToParse->setText(path);
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
        //QTextStream out(&file);
        std::ofstream fout(fileName.toStdString());
        showMarkdown(model, fout);
        //model->show(fout);
    }
  }
}
