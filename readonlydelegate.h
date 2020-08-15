#ifndef READONLYDELEGATE_H
#define READONLYDELEGATE_H

#include<QItemDelegate>
#include"QMessageBox"

class ReadOnlyDelegate: public QItemDelegate
{

public:
    ReadOnlyDelegate(QWidget *parent = nullptr):QItemDelegate(parent)
    {}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const override
    {
        Q_UNUSED(parent)
        Q_UNUSED(option)
        Q_UNUSED(index)
        return nullptr;
    }
};

class EditErrorDelegate: public ReadOnlyDelegate
{

public:
    EditErrorDelegate(QWidget *parent = nullptr):ReadOnlyDelegate(parent)
    {}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const override
    {
        Q_UNUSED(parent)
        Q_UNUSED(option)
        Q_UNUSED(index)
        if(index.column()==1)
            QMessageBox::warning(parent,"警告","姓名不可编辑！");
        else if(index.column()==4)
            QMessageBox::warning(parent,"警告","出生日期不可编辑！");
        else QMessageBox::warning(parent,"警告","人际关系不可编辑！");
        return nullptr;
    }
};

#endif // READONLYDELEGATE_H
