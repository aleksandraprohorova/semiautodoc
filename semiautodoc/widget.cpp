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
  

  QVBoxLayout* verticalLayout = new QVBoxLayout;
  QPushButton* buttonSelectFileForParsing = new QPushButton("выбор файла");
  QPushButton* buttonParseFile = new QPushButton("пропарсить");
  QPushButton* buttonSave = new QPushButton("Сохранить как текстовый файл");
  labelFileToParse = new QLineEdit();

  verticalLayout->addWidget(buttonSelectFileForParsing);
  verticalLayout->addWidget(buttonParseFile);
  verticalLayout->addWidget(labelFileToParse);
  verticalLayout->addWidget(buttonSave);
  verticalLayout->setAlignment(Qt::AlignTop);

  //treeWidget = new QTreeWidget;
  //treeWidget->setHeaderLabel("Классы и функции");

  treeWidget = new QTreeView;
  treeWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
  QVBoxLayout* layoutForTreeWidget = new QVBoxLayout;
  layoutForTreeWidget->addWidget(treeWidget);


  QHBoxLayout* mainLayout = new QHBoxLayout(this);

  mainLayout->addLayout(layoutForTreeWidget);
  mainLayout->addLayout(verticalLayout);

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
        model->show(fout);
    }
  }
}
