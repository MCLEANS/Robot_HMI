#include "dashboard.h"
#include "ui_dashboard.h"

#include <QPalette>

Dashboard::Dashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);

    /*
     * Execute the request packet slot every second
     */
    QTimer *timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(fetch_data()));
    timer->start(100); //time specified in ms

    /*
     * Timer to pull the thingspeak data
     */
    QTimer *timer_1 = new QTimer(this);
    QObject::connect(timer_1, SIGNAL(timeout()), this, SLOT(fetch_data_thingspeak()));
    timer_1->start(15000); //time specified in ms

    /*
     * Vibration graph
    */
    ui->plot_vibration->addGraph();
    ui->plot_vibration->graph(0)->setScatterStyle(QCPScatterStyle::ssNone);
    ui->plot_vibration->graph(0)->setLineStyle(QCPGraph::lsLine);

    /*
     *  x_axis graph
    */
    /* clockwise */
    ui->plot_x_axis->addGraph();
    ui->plot_x_axis->graph(0)->setScatterStyle(QCPScatterStyle::ssNone);
    ui->plot_x_axis->graph(0)->setLineStyle(QCPGraph::lsLine);
    /* anticlockwise */
    ui->plot_x_axis->addGraph();
    ui->plot_x_axis->graph(1)->setScatterStyle(QCPScatterStyle::ssNone);
    ui->plot_x_axis->graph(1)->setLineStyle(QCPGraph::lsLine);

    /*
     *  y_axis graph
    */
    /* clockwise */
    ui->plot_y_axis->addGraph();
    ui->plot_y_axis->graph(0)->setScatterStyle(QCPScatterStyle::ssNone);
    ui->plot_y_axis->graph(0)->setLineStyle(QCPGraph::lsLine);
    /* anticlockwise */
    ui->plot_y_axis->addGraph();
    ui->plot_y_axis->graph(1)->setScatterStyle(QCPScatterStyle::ssNone);
    ui->plot_y_axis->graph(1)->setLineStyle(QCPGraph::lsLine);


}

void Dashboard::fetch_data(){
    QNetworkRequest request;
    QMetaObject::Connection connRet = QObject::connect(naManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    Q_ASSERT(connRet);

    request.setUrl(QUrl("https://predict-data-api.herokuapp.com/data/real-time"));
    QNetworkReply* reply = naManager->get(request);
}

void Dashboard::fetch_data_thingspeak(){
    qDebug()<<"Fetching data from ThingSpeak";
    QNetworkRequest request;
    QMetaObject::Connection connRet = QObject::connect(naManager_1, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished_thingspeak(QNetworkReply*)));
    Q_ASSERT(connRet);

    request.setUrl(QUrl("https://api.thingspeak.com/channels/1450251/feeds/last.json?api_key=NRXASN52OX8O60H8&results=2"));
    QNetworkReply* reply_thingspeak = naManager_1->get(request);
}

void Dashboard::requestFinished_thingspeak(QNetworkReply* reply_thingspeak) {

    /* Get the http status code */
    QVariant statusCode = reply_thingspeak->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    /* Check if the status code is valid */
    if(statusCode.isValid()){
        /* valid status code */
    }
    else{
        /* Invalid status code */
    }

    QVariant reason = reply_thingspeak->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    /* Check for the status reason */
    if(reason.isValid()){
       /* Valid reason */
    }
    else{
      /* Invalid reason */
    }

    QNetworkReply::NetworkError err = reply_thingspeak->error();
    if(err != QNetworkReply::NoError) {
        /* Network error */
    }
    else {
        /* Get the server response */
        QString response = reply_thingspeak->readAll();
        qDebug()<<response;
        bool ok;
        /* Convert response string to JSON object */
        QtJson::JsonObject result = QtJson::parse(response, ok).toMap();
        /* Check whether the parsing process was successful */
        if(!ok) {
         }
        else{
            /* converted to json */
            int payload = result["field1"].toInt() ;
            prev_7 = prev_6;
            prev_6 = prev_5;
            prev_5 = prev_4;
            prev_4 = prev_3;
            prev_3 = prev_2;
            prev_2 = prev_1;
            prev_1 = prev_0;
            prev_0 = payload;

            if( payload == 1){
                /* Change button to green */
                QPalette pal = ui->pushButton_indicator->palette();
                pal.setColor(QPalette::Button, QColor(Qt::green));
                ui->pushButton_indicator->setStyleSheet("border:2px solid #ff0000;");
                ui->pushButton_indicator->setAutoFillBackground(true);
                ui->pushButton_indicator->setPalette(pal);
                ui->pushButton_indicator->update();
            }
            else{
                /* Change button to red */
                if(prev_0 == 0 && prev_1 == 0 && prev_2 == 0 && prev_3 == 0 && prev_4 == 0 && prev_5 == 0){
                    QPalette pal = ui->pushButton_indicator->palette();
                    pal.setColor(QPalette::Button, QColor(Qt::red));
                    ui->pushButton_indicator->setStyleSheet("border:2px solid #ff0000;");
                    ui->pushButton_indicator->setAutoFillBackground(true);
                    ui->pushButton_indicator->setPalette(pal);
                    ui->pushButton_indicator->update();
                }
            }
        }
      }
    reply_thingspeak->deleteLater();
    }

void Dashboard::requestFinished(QNetworkReply* reply) {
    /* Get the http status code */
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    /* Check if the status code is valid */
    if(statusCode.isValid()){
        ui->lineEdit_response->setStyleSheet("color: green");
        ui->lineEdit_response->setText(statusCode.toString());
    }
    else{
        ui->lineEdit_response->setStyleSheet("color: red");
        ui->lineEdit_response->setText("INVALID RESPONSE");
    }

    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    /* Check for the status reason */
    if(reason.isValid()){
        ui->lineEdit_status->setStyleSheet("color: green");
        ui->lineEdit_status->setText(reason.toString());
    }
    else{
       ui->lineEdit_status->setStyleSheet("color: red");
       ui->lineEdit_status->setText("INVALID STATUS");
    }

    QNetworkReply::NetworkError err = reply->error();
    if(err != QNetworkReply::NoError) {
        ui->lineEdit_network->setStyleSheet("color: red");
        ui->lineEdit_network->setText(reply->errorString());
    }
    else {
        ui->lineEdit_network->setStyleSheet("color: green");
        ui->lineEdit_network->setText("AVAILABLE");
        /* Get the server response */
        QString response = reply->readAll();
        bool ok;
        /* Convert response string to JSON object */
        QtJson::JsonObject result = QtJson::parse(response, ok).toMap();
        /* Check whether the parsing process was successful */
        if(!ok) {
         }
        else{
            plot(result["xClockWise"].toInt(),result["xAntiClockWise"].toInt(),result["yClockWise"].toInt(),result["yAntiClockWise"].toInt(),result["vibration"].toInt(),result["noise"].toInt());
            }
        }
    reply->deleteLater();
    }

void Dashboard::plot(int x_clockwise, int x_anticlockwise, int y_clockwise, int y_anticlockwise, int vibration, int noise){
    inc_x_value +=1;


  /*  if(x_value.size() == 100){
        vibration_y_value.clear();
        x_axis_clk_y_value.clear();
        x_axis_aclk_y_value.clear();
        y_axis_clk_y_value.clear();
        y_axis_aclk_y_value.clear();
        x_value.clear();
    } */

    x_value.append(inc_x_value);
    vibration_y_value.append(vibration);
    x_axis_clk_y_value.append(x_clockwise);
    x_axis_aclk_y_value.append(x_anticlockwise);
    y_axis_clk_y_value.append(y_clockwise);
    y_axis_aclk_y_value.append(y_anticlockwise);

    /* Robot vibration plot */
    ui->plot_vibration->graph(0)->setData(x_value,vibration_y_value);
    ui->plot_vibration->xAxis->setRange(inc_x_value-20, inc_x_value);
   // else ui->plot_vibration->xAxis->setRange(inc_x_value-20, inc_x_value);
    ui->plot_vibration->yAxis->setRange(0, 500);
    ui->plot_vibration->yAxis->setLabel("Amplitude");
    ui->plot_vibration->xAxis->setLabel("VIBRATION");
    ui->plot_vibration->replot();
    ui->plot_vibration->update();

    /* Robot x axis plot */
    ui->plot_x_axis->graph(0)->setData(x_value,x_axis_clk_y_value);
    ui->plot_x_axis->graph(0)->setPen(QPen(Qt::blue));
    ui->plot_x_axis->xAxis->setRange(inc_x_value-20, inc_x_value);
    ui->plot_x_axis->yAxis->setRange(0, 25);
    //ui->plot_x_axis->graph(0)->rescaleAxes();

    ui->plot_x_axis->graph(1)->setData(x_value,x_axis_aclk_y_value);
    ui->plot_x_axis->graph(1)->setPen(QPen(Qt::red));
    ui->plot_x_axis->yAxis->setLabel("Tilt Angle (degrees)");
    ui->plot_x_axis->xAxis->setLabel("ROBOT X AXIS");
    //ui->plot_x_axis->graph(1)->rescaleAxes();
    ui->plot_x_axis->replot();
    ui->plot_x_axis->update();

    /* Robot y axis plot */
    ui->plot_y_axis->graph(0)->setData(x_value,y_axis_clk_y_value);
    ui->plot_y_axis->graph(0)->setPen(QPen(Qt::blue));
    ui->plot_y_axis->xAxis->setRange(inc_x_value-20, inc_x_value);
    ui->plot_y_axis->yAxis->setRange(0, 25);
    //ui->plot_y_axis->graph(0)->rescaleAxes();

    ui->plot_y_axis->graph(1)->setData(x_value,y_axis_aclk_y_value);
    ui->plot_y_axis->graph(1)->setPen(QPen(Qt::red));
    //ui->plot_y_axis->graph(1)->rescaleAxes();
    ui->plot_y_axis->yAxis->setLabel("Tilt Angle (degrees)");
    ui->plot_y_axis->xAxis->setLabel("ROBOT Y AXIS");
    ui->plot_y_axis->replot();
    ui->plot_y_axis->update();
}

Dashboard::~Dashboard()
{
    delete ui;
}
