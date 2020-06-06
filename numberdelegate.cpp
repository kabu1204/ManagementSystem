#include "numberdelegate.h"
#include"QSpinBox"

numberDelegate::numberDelegate(int minimum_,int maximum_,QObject *parent): QItemDelegate(parent)
{
    minimum=minimum_;
    maximum=maximum_;
}

QWidget* numberDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSpinBox *editor =new QSpinBox(parent);
    editor->setMinimum(minimum);
    editor->setMaximum(maximum);
    return  editor;
}

void numberDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int value = index.model()->data(index, Qt::EditRole).toInt();
    QSpinBox *spinBox=static_cast<QSpinBox*>(editor);
    spinBox->setValue(value);
}

void numberDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox *spinBox =static_cast<QSpinBox*>(editor);
    spinBox->interpretText();
    int value =spinBox->value();
    model->setData(index, value, Qt::EditRole);
}

void numberDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
