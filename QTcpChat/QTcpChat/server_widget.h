#ifndef SERVER_WIDGET_H
#define SERVER_WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>

#include <QDebug>
#include <QMessageBox>
namespace Ui {
class Server_Widget;
}

class Server_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Server_Widget(QWidget *parent = 0);
    ~Server_Widget();

private slots:
    void on_close_btn_clicked();

    void on_send_btn_clicked();

private:
    Ui::Server_Widget *ui;

    QTcpServer * tcp_server;
    QTcpSocket * tcp_socket;
};

#endif // SERVER_WIDGET_H
