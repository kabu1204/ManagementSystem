#ifndef COUNTBYMONTH_H
#define COUNTBYMONTH_H

#include <QDialog>

namespace Ui {
class CountByMonth;
}

class CountByMonth : public QDialog
{
    Q_OBJECT

public:
    explicit CountByMonth(QWidget *parent = nullptr);
    ~CountByMonth();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::CountByMonth *ui;
    QFont font;
signals:
    void sendMonth(int month);
};

#endif // COUNTBYMONTH_H
