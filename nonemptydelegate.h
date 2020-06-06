#ifndef NONEEMPTYDELEGATE_H
#define NONEEMPTYDELEGATE_H

#include <QWidget>
#include"QItemDelegate"

class nonEmptyDelegate : public QItemDelegate
{
public:
    nonEmptyDelegate();
    QWidget *createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index)const;
    void setEditorData(QWidget *editor,const QModelIndex &index)const;
    virtual void setModelData(QWidget *editor,QAbstractItemModel *model,const QModelIndex &index)const;
    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option,const QModelIndex &index)const;

};

#endif // NONEEMPTYDELEGATE_H
