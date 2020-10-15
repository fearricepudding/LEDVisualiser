#include "ledvisualiser.h"

#include <QApplication>
#include <curl/curl.h>
#include <json/json.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LEDVisualiser w;
    w.show();
    return a.exec();
}
