#ifndef LEDVISUALISER_H
#define LEDVISUALISER_H

#include <QMainWindow>
#include <json/json.h>

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
    void on_toggleButton_clicked();
    void on_setRangeColor_clicked();
    void on_updateLocalGrad_clicked();
    void on_sendNewColButton_clicked();

private:
    Ui::LEDVisualiser *ui;
};
#endif // LEDVISUALISER_H
