#ifndef INSERTWINDOW_H
#define INSERTWINDOW_H

#include <QWidget>

namespace Ui {
class InsertWindow;
}

class InsertWindow : public QWidget
{
    Q_OBJECT

public:
    explicit InsertWindow(QWidget *parent = nullptr);
    ~InsertWindow();

private slots:
    void on_relationCombo_currentIndexChanged(int index);

private:
    Ui::InsertWindow *ui;
    QFont labelfont;
    void extraBoxDefault();
};

#endif // INSERTWINDOW_H
