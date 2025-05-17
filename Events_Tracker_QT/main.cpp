#include "Events_Tracker_QT.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Events_Tracker_QT w;
    w.show();
    return a.exec();
}
