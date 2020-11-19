#ifndef COLORSELECTOR_H
#define COLORSELECTOR_H

#include <QMainWindow>
#include <json/json.h>

namespace Ui {
class colorSelector;
}

class colorSelector : public QMainWindow
{
    Q_OBJECT

public:
    explicit colorSelector(QWidget *parent = nullptr);
    ~colorSelector();
    Json::Value getSetColour();

private slots:
    void updateRed(int);
    void updateGreen(int);
    void updateBlue(int);

private:
    Ui::colorSelector *ui;
    void updateMainColour();
    int _red=0;
    int _green=0;
    int _blue=0;
    int _opacity=255;
};

#endif // COLORSELECTOR_H
