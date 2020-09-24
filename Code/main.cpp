#include "Widget.h"
#include "TestImage.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    w.show();

    TestImage oTest;
    oTest.start();

//    return a.exec();
    return 0;
}
