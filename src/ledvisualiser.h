#ifndef LEDVISUALISER_H
#define LEDVISUALISER_H

#include <QMainWindow>
#include <json/json.h>
#include "colorselector.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LEDVisualiser; }
QT_END_NAMESPACE

class LEDVisualiser : public QMainWindow
{
    Q_OBJECT

public:
    LEDVisualiser(QWidget *parent = nullptr);
    ~LEDVisualiser();
    void toggle();
    void LEDGetGradient();
    Json::Value _pixels;
    void updateLocalGradRange();
    void getPixels();

private slots:
    void sendToggle();
    void setRange();
    void updateLocalGrad();
    void sendNewGrad();
    void openColorSelector();

private:
    Ui::LEDVisualiser *ui;
    colorSelector *csw = new colorSelector();
};
#endif // LEDVISUALISER_H
