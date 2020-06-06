#ifndef NUMBERDELEGATE_H
#define NUMBERDELEGATE_H

#include <QWidget>
#include"QItemDelegate"

class numberDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    numberDelegate(int minimum_=1,int maximum_=200,QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index)const;
    void setEditorData(QWidget *editor,const QModelIndex &index)const;
    void setModelData(QWidget *editor,QAbstractItemModel *model,const QModelIndex &index)const;
    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option,const QModelIndex &index)const;

private:
    int minimum;
    int maximum;
};

#endif // NUMBERDELEGATE_H
