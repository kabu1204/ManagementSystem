#include "countbymonth.h"
#include "ui_countbymonth.h"

CountByMonth::CountByMonth(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CountByMonth)
{
    ui->setupUi(this);
    setWindowTitle("统计");
    font.setPointSize(12);
    font.setFamily("微软雅黑");
    setFont(font);
}

CountByMonth::~CountByMonth()
{
    delete ui;
}

void CountByMonth::on_buttonBox_accepted()
{
    emit sendMonth(ui->monthBox->currentIndex()+1);
}

void CountByMonth::on_buttonBox_rejected()
{
    emit sendMonth(0);
}
