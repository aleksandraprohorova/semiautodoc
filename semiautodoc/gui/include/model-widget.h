#ifndef MODELWIDGET_H
#define MODELWIDGET_H

#include <QObject>
#include <QWidget>

#include <QTreeView>

#include "tree-model.h"
#include "parser/include/model.hpp"

class ModelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ModelWidget(QWidget *parent = nullptr);
    void setModel(Element::pointer model);
    std::string getName();
    Element::pointer getModel();

signals:

public slots:
    void removeRow();
    void addRow();
    void insertNode();
private:
    QTreeView* treeWidget;
    TreeModel* treeModel;
    Element::pointer currentModel;
    std::string name;
};

#endif // MODELWIDGET_H
