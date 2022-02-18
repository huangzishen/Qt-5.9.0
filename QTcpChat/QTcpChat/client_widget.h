#ifndef CLIENT_WIDGET_H
#define CLIENT_WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class Client_Widget;
}

class Client_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Client_Widget(QWidget *parent = 0);
    ~Client_Widget();

private slots:
    void on_connect_btn_clicked();

    void on_close_btn_clicked();

    void on_send_btn_clicked();

private:
    Ui::Client_Widget *ui;

    QTcpSocket * tcp_socket;
};

#endif // CLIENT_WIDGET_H
