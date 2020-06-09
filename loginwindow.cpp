#include "loginwindow.h"
#include "ui_loginwindow.h"
#include"database.h"
#include"QSqlQuery"
#include"QMessageBox"
#include"QSqlRecord"

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setWindowTitle("登录");
    font.setFamily("微软雅黑");
    font.setPointSize(11);
    setFont(font);
    font.setPointSize(9);
    ui->hintlabel_1->setFont(font);
    ui->hintlabel_2->setFont(font);
    ui->hintlabel_1->setStyleSheet("color:red;");
    ui->hintlabel_2->setStyleSheet("color:red;");
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    if(ui->usernameIn->text().isEmpty()||ui->passwdIn->text().isEmpty())
        QMessageBox::warning(this,"警告","用户名和密码不能为空");
    else if(passwd.isEmpty())
        QMessageBox::critical(this,"错误","用户名不存在");
    else if(ui->passwdIn->text()!=passwd)
        QMessageBox::critical(this,"错误","用户名或密码错误");
    else emit loginSuccess();
}

void LoginWindow::on_usernameIn_editingFinished()
{
    if(ui->usernameIn->text().isEmpty())
        ui->hintlabel_1->setText("请输入用户名！");
    else
    {
        query.prepare("SELECT passwd FROM users WHERE username=\'"+ui->usernameIn->text()+"\'");
        query.exec();
        qDebug()<<"SELECT passwd FROM users WHERE username=\'"+ui->usernameIn->text()+"\'";
        if(query.isActive())
        {
            query.seek(0);
            QSqlRecord record=query.record();
            passwd=record.value("passwd").toString();
        }
        else passwd="";
    }
}

void LoginWindow::on_usernameIn_textChanged(const QString &arg1)
{
    ui->hintlabel_1->setText("");
    ui->hintlabel_2->setText("");
}

void LoginWindow::on_passwdIn_editingFinished()
{
    if(ui->passwdIn->text().isEmpty())
        ui->hintlabel_2->setText("请输入密码！");
}

void LoginWindow::on_passwdIn_textChanged(const QString &arg1)
{
    ui->hintlabel_2->setText("");
}
