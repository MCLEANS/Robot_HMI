#include "login.h"
#include "ui_login.h"

#include <QMessageBox>
#include <QDesktopWidget>

LogIn::LogIn(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LogIn)
{
    ui->setupUi(this);
}

LogIn::~LogIn()
{
    delete ui;
}


void LogIn::on_pushButton_login_clicked()
{
    /*
    if((ui->lineEdit_username->text().isEmpty()) || (ui->lineEdit_password->text().isEmpty())){
        QMessageBox::warning(this,
                             "Required Field",
                             "All fields are requied",
                             QMessageBox::Ok,
                             QMessageBox::Ok);
    }
    else{
        if((ui->lineEdit_username->text() == USERNAME) && (ui->lineEdit_password->text() == PASSWORD)){
            hide();
            dashboard = new Dashboard(this);
            dashboard->show();
        }
        else{
            QMessageBox::warning(this,
                                 "Invalid Login",
                                 "Incorrect Username or Password, try again!",
                                 QMessageBox::Ok,
                                 QMessageBox::Ok);
            ui->lineEdit_username->clear();
            ui->lineEdit_password->clear();
        }
    }
  */
    hide();
    dashboard = new Dashboard(this);
    QDesktopWidget *desktop = QApplication::desktop();

    int WIDTH = 820;
    int HEIGHT = 480;

    int screenWidth = desktop->width();
    int screenHeight = desktop->height();

    int x = (screenWidth - WIDTH) / 2;
    int y = (screenHeight - HEIGHT) / 2;

    dashboard->resize(WIDTH, HEIGHT);
    dashboard->move( x, y );
    dashboard->show();
}
