#include "insertwindow.h"
#include "ui_insertwindow.h"
#include"QDebug"
#include"QStringList"
#include"database.h"
InsertWindow::InsertWindow(Database *db_,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InsertWindow)
{
    ui->setupUi(this);
    db=db_;
    setFixedSize(814,382);
    setWindowTitle("录入");
    labelfont.setPointSize(12);
    labelfont.setFamily("微软雅黑");
    setFont(labelfont);

    labelfont.setPointSize(10);
    ui->placeIn->setFont(labelfont);
    ui->relationCombo->setFont(labelfont);
    labelfont.setPointSize(9);
    ui->emailIn->setFont(labelfont);
    ui->hintlabel->setFont(labelfont);

    //年龄、电话只能输入数字
    QRegExp regexp("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regexp);
    ui->ageIn->setValidator(validator);
    ui->phoneIn->setValidator(validator);

    extraBoxDefault();
}

InsertWindow::~InsertWindow()
{
    delete ui;
}

void InsertWindow::extraBoxDefault()
{
    ui->schoolIn->setEnabled(false);
    ui->courseIn->setEnabled(false);
    ui->companyIn->setEnabled(false);
    ui->postIn->setEnabled(false);
    ui->callIn->setEnabled(false);
    ui->placeIn->setEnabled(false);
}

void InsertWindow::raiseError(int errCode)
{
    if(errCode==-1) QMessageBox::critical(this,"错误","信息录入失败！错误代码 "+QString::number(errCode)+":请选择\"Relation\"");
    if(errCode==1) QMessageBox::critical(this,"错误","信息录入失败！错误代码 "+QString::number(errCode)+":\"Name\"不能为空！");
    if(errCode==2) QMessageBox::critical(this,"错误","信息录入失败！错误代码 "+QString::number(errCode)+":\"Age\"不能为空！");
    if(errCode==3) QMessageBox::critical(this,"错误","信息录入失败！错误代码 "+QString::number(errCode)+":\"Gender\"不能为空！");
    if(errCode==4) QMessageBox::critical(this,"错误","信息录入失败！错误代码 "+QString::number(errCode)+":\"Birthday\"不能为空！");
    if(errCode==5) QMessageBox::critical(this,"错误","信息录入失败！错误代码 "+QString::number(errCode)+":\"Email\"不能为空！");
    if(errCode==6) QMessageBox::critical(this,"错误","信息录入失败！错误代码 "+QString::number(errCode)+":\"Phone\"不能为空！");
    if(errCode==7) QMessageBox::critical(this,"错误","信息录入失败！错误代码 "+QString::number(errCode)+":\"School\"不能为空！");
    if(errCode==8) QMessageBox::critical(this,"错误","信息录入失败！错误代码 "+QString::number(errCode)+":\"Course\"不能为空！");
    if(errCode==9) QMessageBox::critical(this,"错误","信息录入失败！错误代码 "+QString::number(errCode)+":\"Company\"不能为空！");
    if(errCode==10) QMessageBox::critical(this,"错误","信息录入失败！错误代码 "+QString::number(errCode)+":\"Post\"不能为空！");
    if(errCode==11) QMessageBox::critical(this,"错误","信息录入失败！错误代码 "+QString::number(errCode)+":\"Call\"不能为空！");
    if(errCode==12) QMessageBox::critical(this,"错误","信息录入失败！错误代码 "+QString::number(errCode)+":\"Place\"不能为空！");
    if(errCode==13) QMessageBox::critical(this,"错误","信息录入失败！错误代码 "+QString::number(errCode)+":年龄必须为正！");
    if(errCode==14) QMessageBox::critical(this,"错误","信息录入失败！错误代码 "+QString::number(errCode)+":电话号码必须为正！");
    if(errCode==15) QMessageBox::critical(this,"错误","信息录入失败！错误代码 "+QString::number(errCode)+":生日必须早于今天！");
    if(errCode==16) QMessageBox::critical(this,"错误","信息录入失败！错误代码 "+QString::number(errCode)+":邮箱地址格式错误！");
    if(errCode==17) QMessageBox::critical(this,"错误","信息录入失败！错误代码 "+QString::number(errCode)+":年龄不能超过200！");
}

void InsertWindow::on_relationCombo_currentIndexChanged(int idx)
{
    extraBoxDefault();
    switch(idx)
    {
    case 1:
        ui->schoolIn->setEnabled(true);
        return;
    case 2:
        ui->placeIn->setEnabled(true);
        return;
    case 3:
        ui->companyIn->setEnabled(true);
        return;
    case 4:
        ui->callIn->setEnabled(true);
        return;
    case 5:
        ui->courseIn->setEnabled(true);
        ui->schoolIn->setEnabled(true);
        return;
    case 6:
        ui->companyIn->setEnabled(true);
        ui->postIn->setEnabled(true);
        return;
    case 7:
        ui->companyIn->setEnabled(true);
        return;
    case 8:
        return;
    }
}

void InsertWindow::on_insertButton_clicked()
{
    QString relation=ui->relationCombo->currentText();
    QStringList basic,extra;
    basic<<ui->nameIn->text()<<ui->ageIn->text()<<ui->genderBox->currentText()<<ui->birthdayIn->date().toString("yyyy-MM-dd")
        <<ui->emailIn->text()<<ui->phoneIn->text();
    extra<<(ui->schoolIn->isEnabled()?ui->schoolIn->text():"Unabled")<<(ui->courseIn->isEnabled()?ui->courseIn->text():"Unabled")
        <<(ui->companyIn->isEnabled()?ui->companyIn->text():"Unabled")<<(ui->postIn->isEnabled()?ui->postIn->text():"Unabled")
       <<(ui->callIn->isEnabled()?ui->callIn->text():"Unabled")<<(ui->placeIn->isEnabled()?ui->placeIn->text():"Unabled")
      <<ui->remarkIn->toPlainText();
    int errCode=Database::insertion_check_fix(relation,basic,extra);
    if(errCode==0)
    {
        db->insert(relation,basic,extra);
        ui->hintlabel->setText("录入成功！");
    }
    else{
        ui->hintlabel->setText("录入失败！");
        raiseError(errCode);

    }
}
