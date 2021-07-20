#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>

#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

#include "json.h"


namespace Ui {
class Dashboard;
}

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();

private slots:
    void requestFinished(QNetworkReply* reply);
    void requestFinished_thingspeak(QNetworkReply* reply);
    void fetch_data();
    void fetch_data_thingspeak();

private:
    Ui::Dashboard *ui;
    QNetworkAccessManager* naManager = new QNetworkAccessManager(this);
    QNetworkAccessManager* naManager_1 = new QNetworkAccessManager(this);
    int inc_x_value = 0;

    int prev_0 = 1;
    int prev_1 = 1;
    int prev_2 = 1;
    int prev_3 = 1;
    int prev_4 = 1;
    int prev_5 = 1;
    int prev_6 = 1;
    int prev_7 = 1;



    QVector<double> vibration_y_value;
    QVector<double> x_axis_clk_y_value;
    QVector<double> x_axis_aclk_y_value;
    QVector<double> y_axis_clk_y_value;
    QVector<double> y_axis_aclk_y_value;
    QVector<double> x_value;

    QString previous_packet_id = "";

    void plot(int x_clockwise,
              int x_anticlockwise,
              int y_clockwise,
              int y_anticlockwise,
              int vibration,
              int noise);
};

#endif // DASHBOARD_H
