#include "serverwidget.h"
#include <QApplication>
#include "clientwidget.h"

#include <QDesktopWidget>
#include <QDebug>
#include <QThread>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDesktopWidget * desktop = QApplication::desktop();
//    qDebug() << desktop->width() << " " << desktop->height();
    serverWidget w;
    clientWidget w2;
    w.move(desktop->width() / 2 - w.width(),(desktop->height() - w.height()) * 0.3);
    w.show();


    w2.move(desktop->width() / 2,(desktop->height() - w2.height()) * 0.3);
    w2.show();




    return a.exec();
}
