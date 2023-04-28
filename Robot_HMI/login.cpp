#include "login.h"
#include "ui_login.h"

#include <QMessageBox>
#include <QScreen>

LogIn::LogIn(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LogIn)
{
    ui->setupUi(this);
    ui->lineEdit_username->setText(USERNAME);
    ui->lineEdit_password->setText(PASSWORD);
}

LogIn::~LogIn()
{
    delete ui;
}


void LogIn::on_pushButton_login_clicked()
{

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
            QScreen *desktop = QApplication::primaryScreen();

            int WIDTH = 820;
            int HEIGHT = 480;

            QRect screen_geometry = desktop->geometry();

            int screenWidth = screen_geometry.width();
            int screenHeight = screen_geometry.height();

            int x = (screenWidth - WIDTH) / 2;
            int y = (screenHeight - HEIGHT) / 2;

            dashboard->resize(WIDTH, HEIGHT);
            dashboard->move( x, y );
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
}
