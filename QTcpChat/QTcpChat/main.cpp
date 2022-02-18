#include "server_widget.h"
#include <QApplication>
#include "client_widget.h"
#include <QDesktopWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDesktopWidget * desktop = QApplication::desktop();
    Server_Widget w;
    Client_Widget w2;

    w.move(desktop->width()/2 - w.width(),desktop->height() * 0.1);

    w2.move(desktop->width()/2,desktop->height() * 0.1);

    w.show();
    w2.show();

    return a.exec();
}
