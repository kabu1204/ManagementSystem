#include "searchbybirthday.h"
#include "ui_searchbybirthday.h"
#include"QSqlQueryModel"
#include"QSqlTableModel"
#include"QMessageBox"
#include"utils.h"
#include"QDate"
#include"readonlydelegate.h"
#include"QDebug"

SearchByBirthday::SearchByBirthday(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchByBirthday)
{
    ui->setupUi(this);
    font.setPointSize(11);
    font.setFamily("微软雅黑");
    setFont(font);
    setWindowTitle("Search by birthday");

    readOnly=new ReadOnlyDelegate(this);

    ui->daysIn->setValidator(new QIntValidator(0,365, this));
}

SearchByBirthday::~SearchByBirthday()
{
    delete ui;
}

int SearchByBirthday::pre_search(int days)
{
    int count=0,idx=-1;
    QSqlQueryModel *model=new QSqlQueryModel(this);
    QString sql;
    for(int i=0;i<relations().size();i++)
    {
        sql="SELECT birthday FROM "+relations()[i];
        model->setQuery(sql);
        qDebug()<<sql<<model->rowCount();
        for(int j=0;j<model->rowCount();j++)
        {
            QModelIndex modelIDX=model->index(j,0);
            QDate birthday=model->data(modelIDX).toDate();
            qDebug()<<birthday;
            QDate currentDate=QDate::currentDate();
            if(!birthday.setDate(currentDate.year(),birthday.month(),birthday.day()))
                continue;
            else if((currentDate.daysTo(birthday)<=days)&&(currentDate.daysTo(birthday)>=0))
            {
                count++;
                idx=i;
                break;
            }
        }
        if(count>1)
            break;
    }
    if(count==0) return -1;
    else if(count==1) return idx;
    else return -2;
}

QSqlQueryModel* SearchByBirthday::queryModel()
{
    QSqlQueryModel *model=new QSqlQueryModel(this);
    QString sql="SELECT relation,name,age,gender,birthday,email,phone FROM classmates";
    for(int i=1;i<relations().size();i++)
        sql+=(" UNION SELECT relation,name,age,gender,birthday,email,phone FROM "+relations()[i]);
    qDebug()<<sql;
    model->setQuery(sql);
    return model;
}

QSqlTableModel* SearchByBirthday::tableModel(int idx)
{
    QSqlTableModel *model=new QSqlTableModel(this);
    model->setTable(relations()[idx]);
    model->select();
    return model;
}

int SearchByBirthday::setTableView(QTableView *table,int days)
{
    int results=table->model()->rowCount();
    int n=results;
    setReadOnly(table);
    for(int i=0;i<n;i++)
    {
        QModelIndex modelIDX=table->model()->index(i,4);
        QDate birthday=table->model()->data(modelIDX).toDate();
        QDate currentDate=QDate::currentDate();
        if(!birthday.setDate(currentDate.year(),birthday.month(),birthday.day())
                ||(currentDate.daysTo(birthday)>days)
                ||(currentDate.daysTo(birthday)<0))
        {
            table->setRowHidden(i,true);
            results--;
        }
    }
    table->setColumnHidden(0,true);
    return results;
}

void SearchByBirthday::on_searchButton_clicked()
{
    int days=ui->daysIn->text().toInt();
    int idx=pre_search(days);
    qDebug()<<idx;
    if(idx==-1)
        QMessageBox::warning(this,"Warning","Found no results");
    else if(idx==-2)
    {
        QSqlQueryModel *model=queryModel();
        ui->tableView->setModel(model);
        int results=setTableView(ui->tableView,days);
        qDebug()<<results;
        ui->hintlabel->setText("Found "+QString::number(results)
                               +" results in more than one relations, so only show part of information");
    }
    else
    {
        QSqlTableModel* model=tableModel(idx);
        ui->tableView->setModel(model);
        int results=setTableView(ui->tableView,days);
        ui->hintlabel->setText("Found "+QString::number(results)+" result(s) in \'"+relations()[idx]+"\'");
    }
}
