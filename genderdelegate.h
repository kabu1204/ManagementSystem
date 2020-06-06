#ifndef GENDERDELEGATE_H
#define GENDERDELEGATE_H
#include"QItemDelegate"
#include"QComboBox"
#include"QWidget"

class genderDelegate : public QItemDelegate
{
    Q_OBJECT
public :
    genderDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index)const;
    void setEditorData(QWidget *editor,const QModelIndex &index)const;
    void setModelData(QWidget *editor,QAbstractItemModel *model,const QModelIndex &index)const;
    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option,const QModelIndex &index)const;
};

#endif // GENDERDELEGATE_H
