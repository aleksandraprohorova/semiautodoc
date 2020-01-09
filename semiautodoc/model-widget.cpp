#include "model-widget.h"

#include <QHBoxLayout>
#include <QPushButton>
#include "edit-text-delegate.h"

ModelWidget::ModelWidget(QWidget *parent) : QWidget(parent)
{
    treeWidget = new QTreeView;

    QHBoxLayout* layoutForButtonsForEditing = new QHBoxLayout;
    QPushButton* buttonRemoveRow = new QPushButton("Remove row");
    QPushButton* buttonAddRow = new QPushButton("Insert row");
    QPushButton* buttonInsertNode = new QPushButton("Insert node");

    layoutForButtonsForEditing->addWidget(buttonRemoveRow);
    layoutForButtonsForEditing->addWidget(buttonAddRow);
    layoutForButtonsForEditing->addWidget(buttonInsertNode);

    QVBoxLayout* layoutForEditing = new QVBoxLayout;

    layoutForEditing->addWidget(treeWidget);
    layoutForEditing->addLayout(layoutForButtonsForEditing);

    connect(buttonRemoveRow, SIGNAL(clicked()), this, SLOT(removeRow()));
    connect(buttonAddRow, SIGNAL(clicked()), this, SLOT(addRow()));
    connect(buttonInsertNode, SIGNAL(clicked()), this, SLOT(insertNode()));

    setLayout(layoutForEditing);
}

void ModelWidget::setModel(Element::pointer model)
{
    name = model->getName();
    currentModel = model;
    treeModel = new TreeModel(currentModel,treeWidget);
    treeWidget->setModel(treeModel);

    for (int i = 0;i < treeModel->columnCount(); ++i)
    {
        treeWidget->resizeColumnToContents(i);
    }

    EditTextDelegate* editTextDelegate = new EditTextDelegate(treeWidget);
    treeWidget->setItemDelegateForColumn(0, editTextDelegate);
    treeWidget->setItemDelegateForColumn(1, editTextDelegate);
}

std::string ModelWidget::getName()
{
    return name;
}

Element::pointer ModelWidget::getModel()
{
    return currentModel;
}

void ModelWidget::removeRow()
{
  QModelIndex index = treeWidget->selectionModel()->currentIndex();
  treeWidget->model()->removeRows(index.row(), 1, index.parent());
}

void ModelWidget::addRow()
{
  QModelIndex index = treeWidget->selectionModel()->currentIndex();
  treeWidget->model()->insertRows(index.row(), 1, index.parent());
}

void ModelWidget::insertNode()
{
  QModelIndex index = treeWidget->selectionModel()->currentIndex();
  treeWidget->model()->insertRows(1, 1, index);
}
