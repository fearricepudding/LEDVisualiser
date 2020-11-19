#include <sstream>
#include <iostream>
#include <string>
#include <json/json.h>

#include "colorselector.h"
#include "ui_colorselector.h"

colorSelector::colorSelector(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::colorSelector)
{
    ui->setupUi(this);
    connect(ui->RedSlider, SIGNAL(sliderMoved(int)), this, SLOT(updateRed(int)));
    connect(ui->RedSlider, SIGNAL(valueChanged(int)), this, SLOT(updateRed(int)));
    connect(ui->GreenSlider, SIGNAL(sliderMoved(int)), this, SLOT(updateGreen(int)));
    connect(ui->GreenSlider, SIGNAL(valueChanged(int)), this, SLOT(updateGreen(int)));
    connect(ui->BlueSlider, SIGNAL(sliderMoved(int)), this, SLOT(updateBlue(int)));
    connect(ui->BlueSlider, SIGNAL(valueChanged(int)), this, SLOT(updateBlue(int)));

}

Json::Value colorSelector::getSetColour(){
    Json::Value colour;

    colour["r"] = _red;
    colour["g"] = _green;
    colour["b"] = _blue;

    return colour;
}

void colorSelector::updateRed(int position){
    _red = position;
    updateMainColour();
}

void colorSelector::updateGreen(int position){
    _green = position;
    updateMainColour();
}

void colorSelector::updateBlue(int position){
    _blue = position;
    updateMainColour();
}

void colorSelector::updateMainColour(){
    std::stringstream gradientStylesheet;
    gradientStylesheet << "*{background-color:rgba(" << _red << ", " << _green << ", " << _blue << ", " << _opacity << ");}";
    std::cout << gradientStylesheet.str() << std::endl;
    ui->selectedColour->setStyleSheet(QString::fromStdString(gradientStylesheet.str()));
}

colorSelector::~colorSelector()
{
    delete ui;
}

