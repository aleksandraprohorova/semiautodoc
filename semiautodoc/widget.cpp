#include "widget.h"
#include "ui_widget.h"

#include <QHBoxLayout>
#include <QFileDialog>
#include <QMenuBar>

#include <iostream>
#include <fstream>
#include <QToolTip>

#include "parser.hpp"
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

  QHBoxLayout* mainLayout = new QHBoxLayout;

  mainLayout->setMenuBar(menuBar);

  fileSystemModel = new QFileSystemModel;
  fileSystemView = new QTreeView;

  tabWidget = new QTabWidget(this);
  tabWidget->setUpdatesEnabled(false);
  tabWidget->setMovable(true);
  tabWidget->setTabsClosable(true);

  splitter = new QSplitter(Qt::Horizontal);
  splitter->addWidget(fileSystemView);
  splitter->addWidget(tabWidget);
  splitter->setStretchFactor(0, 0.5);
  splitter->setStretchFactor(1, 1);

  mainLayout->addWidget(splitter);
  setLayout(mainLayout);

  showMaximized();

  connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));

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

  fileSystemModel->setRootPath(path);
  fileSystemView->setModel(fileSystemModel);
  fileSystemView->setRootIndex(fileSystemModel->index(path));

  for (int i = 1; i < fileSystemModel->columnCount(); i++)
  {
    fileSystemView->hideColumn(i);
  }

  connect(fileSystemView, SIGNAL(clicked(QModelIndex)),this, SLOT(selectFileForParsing(QModelIndex)));
}

void Widget::parseFile()
{
  Element::pointer model = Parser::parse(fileToParse.toStdString());

  auto it = tabs.find(fileToParse.toStdString());
  ModelWidget* modelWidget = (it == tabs.end()) ? new ModelWidget : it->second;

  modelWidget->setModel(model);
  tabs[fileToParse.toStdString()] = modelWidget;

  QStringList l = fileToParse.split('/');

  tabWidget->addTab(modelWidget, l.back());
  tabWidget->setTabToolTip(tabWidget->indexOf(modelWidget), fileToParse);
  tabWidget->setUpdatesEnabled(true);
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
  auto widget = (ModelWidget*)tabWidget->currentWidget();
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"));
  if (!fileName.isNull())
  {
    QFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Truncate))
    {
        std::ofstream fout(fileName.toStdString());
        showMarkdown(widget->getModel(), fout);
    }
  }
}

void Widget::closeTab(int index)
{
    auto widget = (ModelWidget*)tabWidget->currentWidget();
    tabs.erase(widget->getName());
    tabWidget->removeTab(index);
}
