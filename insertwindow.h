#ifndef INSERTWINDOW_H
#define INSERTWINDOW_H

#include <QWidget>
#include"database.h"

namespace Ui {
class InsertWindow;
}

class InsertWindow : public QWidget
{
    Q_OBJECT

public:
    explicit InsertWindow(Database *db_,QWidget *parent = nullptr);
    ~InsertWindow();

private slots:
    void on_relationCombo_currentIndexChanged(int index);

    void on_insertButton_clicked();

private:
    Ui::InsertWindow *ui;
    QFont labelfont;
    Database *db;
    void extraBoxDefault();
    void raiseError(int errCode);
};

#endif // INSERTWINDOW_H
