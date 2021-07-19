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
    void fetch_data();

private:
    Ui::Dashboard *ui;
    QNetworkAccessManager* naManager = new QNetworkAccessManager(this);
    int inc_x_value = 0;

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
