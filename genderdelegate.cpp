#include "genderdelegate.h"

genderDelegate::genderDelegate(QObject *parent): QItemDelegate(parent) {}

QWidget* genderDelegate::createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index)const
{
    QComboBox *editor =  new  QComboBox(parent);
    editor->addItem( "Female" );
    editor->addItem( "Male" );
    return editor;
}

void  genderDelegate::setEditorData(QWidget *editor,const QModelIndex &index)  const
{
   QString text = index.model()->data(index, Qt::EditRole).toString();
   QComboBox *comboBox =static_cast <QComboBox*>(editor);
   int textidx = comboBox->findText(text);
   comboBox->setCurrentIndex(textidx);
}

void  genderDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index)  const
{
   QComboBox *comboBox = static_cast<QComboBox*>(editor);
   QString text = comboBox->currentText();
   model->setData(index, text, Qt::EditRole);
}

void  genderDelegate::updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option,const QModelIndex &index)const
{
   editor->setGeometry(option.rect);
}
