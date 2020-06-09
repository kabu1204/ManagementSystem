#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include"QSqlQuery"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_loginButton_clicked();

    void on_usernameIn_editingFinished();

    void on_usernameIn_textChanged(const QString &arg1);

    void on_passwdIn_editingFinished();

    void on_passwdIn_textChanged(const QString &arg1);

private:
    Ui::LoginWindow *ui;
    QFont font;
    QSqlQuery query;
    QString username;
    QString passwd;
    int checkValidation(QString username,QString passwd);

signals:
    void loginSuccess();
};

#endif // LOGINWINDOW_H
