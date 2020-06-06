#include "searchbyname.h"
#include "ui_searchbyname.h"
#include"QFont"
#include"QMessageBox"
#include"QSqlQueryModel"
#include"utils.h"
#include"QDebug"

SearchByName::SearchByName(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchByName)
{
    ui->setupUi(this);
    setWindowTitle("Search by name");
    font.setPointSize(10);
    font.setFamily("微软雅黑");
    setFont(font);

}

SearchByName::~SearchByName()
{
    delete ui;
}

int SearchByName::pre_search(QString name)
{
    int count=0;
    int idx=-1;
    QSqlQueryModel *model=new QSqlQueryModel(this);
    QString sql;
    for(int i=0;i<relations().size();i++)
    {
        sql="SELECT name,relation FROM "+relations()[i]+" WHERE name=\'"+name+"\'";
        qDebug()<<sql;
        model->setQuery(sql);
        if(model->rowCount()>0)
        {
            count++;
            idx=i;
        }
    }
    if(count==0) return -1;
    else if(count==1) return idx;
    else return -2;
}

QSqlTableModel* SearchByName::tableModel(int idx,QString name)
{
    QSqlTableModel *model=new QSqlTableModel(this);
    model->setTable(relations()[idx]);
    model->setFilter(QObject::tr("name='%1'").arg(name));
    model->select();
    return model;
}

QSqlQueryModel* SearchByName::queryModel(QString name)
{
    QSqlQueryModel *model=new QSqlQueryModel(this);
    QString sql="SELECT relation,name,age,gender,birthday,email,phone FROM classmates WHERE name=\'"+name+"\'";
    for(int i=1;i<relations().size();i++)
    {
        QString tail=" UNION SELECT relation,name,age,gender,birthday,email,phone FROM "+relations()[i]+" WHERE name=\'"+name+"\'";
        sql+=tail;
    }
    model->setQuery(sql);
    return model;
}

void SearchByName::on_searchButton_clicked()
{
    QString name=ui->nameIn->text();
    if(name.isEmpty())
    {
        QMessageBox::warning(this,"Warning!","Please input the name!");
        return;
    }
    else
    {
        int idx=pre_search(name);
        if(idx==-1)
        {
            QMessageBox::warning(this,"Warning!","Found no result!");
            return;
        }
        else if(idx==-2)
        {
            QSqlQueryModel *model=queryModel(name);
            ui->tableView->setModel(model);
            ui->hintlabel->setText("Found "+QString::number(model->rowCount())+" results in more than one relations, "
                                                                               "so only show part of information");
        }
        else
        {
            QSqlTableModel *model=tableModel(idx,name);
            ui->tableView->setModel(model);
            ui->hintlabel->setText("Found "+QString::number(model->rowCount())+" result(s) in \""+relations()[idx]+"\"");
        }
    }
}
