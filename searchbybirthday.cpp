#include "searchbybirthday.h"
#include "ui_searchbybirthday.h"
#include"QSqlQueryModel"
#include"qsqldatemodel.h"
#include"QSqlTableModel"
#include"QMessageBox"
#include"utils.h"
#include"QDate"
#include"readonlydelegate.h"
#include"QDebug"
#include"QFileDialog"

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
        for(int j=0;j<model->rowCount();j++)
        {
            QModelIndex modelIDX=model->index(j,0);
            QDate birthday=model->data(modelIDX).toDate();
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

QSqlDateQueryModel* SearchByBirthday::DateQeuryModel()
{
    QSqlDateQueryModel *model=new QSqlDateQueryModel(this);
    QString sql="SELECT relation,name,age,gender,birthday,email,phone FROM classmates";
    for(int i=1;i<relations().size();i++)
        sql+=(" UNION SELECT relation,name,age,gender,birthday,email,phone FROM "+relations()[i]);
    model->setQuery(sql);
    return model;
}

QSqlDateTableModel* SearchByBirthday::DateTableModel(int idx)
{
    QSqlDateTableModel *model=new QSqlDateTableModel(this);
    model->setTable(relations()[idx]);
    model->select();
    return model;
}

int SearchByBirthday::setTableView(QTableView *table,int days,int idx)
{
    int results=table->model()->rowCount();
    int n=results;
    QAbstractItemModel *model=table->model();
    if(idx==-2)
    {
        QSqlDateQueryModel *DatequeryModel=DateQeuryModel();
        table->setModel(DatequeryModel);
        for(int i=0;i<n;i++)
        {
            QModelIndex modelIDX=model->index(i,4);
            QDate birthday=model->data(modelIDX).toDate();
            QDate currentDate=QDate::currentDate();
            if(!birthday.setDate(currentDate.year(),birthday.month(),birthday.day())
                    ||(currentDate.daysTo(birthday)>days)
                    ||(currentDate.daysTo(birthday)<0))
            {
                table->setRowHidden(i,true);
                results--;
            }
        }
    }
    else
    {
        QSqlDateTableModel *DatetableModel=DateTableModel(idx);
        table->setModel(DatetableModel);
        for(int i=0;i<n;i++)
        {
            QModelIndex modelIDX=model->index(i,4);
            QDate birthday=model->data(modelIDX).toDate();
            QDate currentDate=QDate::currentDate();
            if(!birthday.setDate(currentDate.year(),birthday.month(),birthday.day())
                    ||(currentDate.daysTo(birthday)>days)
                    ||(currentDate.daysTo(birthday)<0))
            {
                table->setRowHidden(i,true);
                results--;
            }
        }
    }
    setReadOnly(table);
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    table->setColumnWidth(4,150);
    return results;
}

void SearchByBirthday::on_searchButton_clicked()
{
    int days=ui->daysIn->text().toInt();
    int idx=pre_search(days);
    if(idx==-1)
    {
        QMessageBox::warning(this,"Warning","Found no results");
        return;
    }
    else if(idx==-2)
    {
        QSqlQueryModel *model=queryModel();
        ui->tableView->setModel(model);
        int results=setTableView(ui->tableView,days);
        ui->hintlabel->setText("Found "+QString::number(results)
                               +" results in more than one relations, so only show part of information");
    }
    else
    {
        QSqlTableModel* model=tableModel(idx);
        ui->tableView->setModel(model);
        int results=setTableView(ui->tableView,days,idx);
        ui->tableView->setColumnHidden(0,true);
        ui->hintlabel->setText("Found "+QString::number(results)+" result(s) in \'"+relations()[idx]+"\'");
    }
    ui->emaillabel->setText("now select a person a generate a sample of email");
}

void SearchByBirthday::on_emailButton_clicked()
{
    int curRow=ui->tableView->currentIndex().row();
    QModelIndex idx;
    QString name="";
    QString text=":\n\t祝生日快乐，健康幸福。\n\t\t\t\tYCY";
    idx=ui->tableView->model()->index(curRow,1);
    name=ui->tableView->model()->data(idx).toString();
    if(name.isEmpty())
    {
        QMessageBox::warning(this,"Warning","Please select a row!");
        return;
    }
    else
    {
        text=name+text;
        QString filepath=QFileDialog::getSaveFileName(this,"Save","./email_to_"+name+".txt","Text Files(*.txt)");
        QFile file(filepath);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream output(&file);
        output<<text;
        file.close();
        ui->emaillabel->setText("File has been saved to "+filepath);
    }
}
