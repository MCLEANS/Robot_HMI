#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "dashboard.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LogIn; }
QT_END_NAMESPACE

class LogIn : public QMainWindow
{
    Q_OBJECT

public:
    LogIn(QWidget *parent = nullptr);
    ~LogIn();

private slots:
    void on_pushButton_login_clicked();

private:
    Ui::LogIn *ui;
    Dashboard *dashboard;
    QString USERNAME = "admin";
    QString PASSWORD = "1234";
};
#endif // LOGIN_H
