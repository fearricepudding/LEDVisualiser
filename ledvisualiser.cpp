#include "ledvisualiser.h"
#include "./ui_ledvisualiser.h"
#include "http_request.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <qt/QtWidgets/QLabel>

/**
 * @brief send toggle signal to LEDController
 *
 * @return void
 */
void LEDVisualiser::toggle(){
    try{
        http_request toggle("192.168.1.222:8080/toggle");
        toggle.POST();
    }catch(Json::LogicError e){
        std::cout << "Json logic error: " << e.what() << std::endl;
    };
};

/**
 * @brief Get pixel buffer from LEDController
 *
 * @return void
 */
void LEDVisualiser::getPixels(){
    http_request status("192.168.1.222:8080/status");
    Json::Value statusResponse = status.GET();
    Json::Value pixels = statusResponse["pixels"];
    _pixels = pixels;
};

/**
 * @brief Update the ui gradient with the stored pixels
 *
 * @return void
 */
void LEDVisualiser::LEDGetGradient(){
    Json::Value pixels = _pixels;
    std::stringstream gradientStylesheet;
    gradientStylesheet << "* {color: qlineargradient(spread:pad, x1:0 y1:0, x2:1 y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 rgba(0,0,0,0),";
    for (Json::Value::ArrayIndex i = 0; i != pixels.size(); i++){
        double stoper = i*0.52356020942;
        double stop = stoper/100;
        gradientStylesheet << "stop:" << std::setprecision(2) << stop << " rgba(" << pixels[i]["r"].asString() << "," << pixels[i]["g"].asString() << "," << pixels[i]["b"] << ",255),";
    };
    gradientStylesheet << "stop:1 rgba(0,0,0,0));}";
    ui->gradient->setStyleSheet(QString::fromStdString(gradientStylesheet.str()));
    _pixels = pixels;
};

/**
 * @brief Update the range of pixels locally
 *
 * @return void
 */
void LEDVisualiser::updateLocalGradRange(){
    int fromRange = ui->fromSlider->value();
    int toRange = ui->toSlider->value();
    QColor newColor = ui->colorPicker->color();
    int r;
    int g;
    int b;
    int a;
    newColor.getRgb(&r, &g, &b, &a);
    for (Json::Value::ArrayIndex i = fromRange; i != toRange; i++){
        _pixels[i]["r"] = r;
        _pixels[i]["g"] = g;
        _pixels[i]["b"] = b;
    };
};

LEDVisualiser::LEDVisualiser(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LEDVisualiser){
    ui->setupUi(this);
    getPixels();
    LEDGetGradient();
};

LEDVisualiser::~LEDVisualiser(){
    delete ui;
};

void LEDVisualiser::on_toggleButton_clicked(){
    toggle();
};

void LEDVisualiser::on_setRangeColor_clicked(){
    updateLocalGradRange();
    LEDGetGradient();
};

void LEDVisualiser::on_updateLocalGrad_clicked(){
    getPixels();
    LEDGetGradient();
};

/**
 * @brief Send local pixel buffer to LEDController
 *
 * @return void
 */
void LEDVisualiser::on_sendNewColButton_clicked(){
    http_request newColors("192.168.1.222:8080/newPixels");
    std::stringstream colorString;
    colorString << "pixels=" << _pixels;
    newColors.POST(colorString.str());
};
