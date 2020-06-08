#include "nonemptydelegate.h"
#include"QLineEdit"
#include"QMessageBox"


nonEmptyDelegate::nonEmptyDelegate()
{

}

QWidget* nonEmptyDelegate::createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index)const
{
    QLineEdit* editor=new QLineEdit(parent);
    return editor;
}

void nonEmptyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString text = index.model()->data(index, Qt::EditRole).toString();
    QLineEdit *lineEdit=static_cast<QLineEdit*>(editor);
    lineEdit->setText(text);
}

void nonEmptyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineEdit=static_cast<QLineEdit*>(editor);
    if(lineEdit->text().isEmpty())
    {
        QMessageBox::warning(nullptr,"警告","内容不能为空！");
        return;
    }
    model->setData(index, lineEdit->text(), Qt::EditRole);
}

void nonEmptyDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
