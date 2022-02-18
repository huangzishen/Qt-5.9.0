#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>

#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QTimer>
namespace Ui {
class serverWidget;
}

class serverWidget : public QWidget
{
    Q_OBJECT

public:
    explicit serverWidget(QWidget *parent = 0);

    void paintEvent(QPaintEvent *);

    void send_data();

    ~serverWidget();


private slots:
    void on_choose_btn_clicked();

    void on_send_btn_clicked();

    void on_close_btn_clicked();

private:
    Ui::serverWidget *ui;

    QTcpServer * tcp_server;
    QTcpSocket * tcp_socket;

    QFile file;
    QString file_name;
    qint64 file_size;

    bool is_head;

    qint64 receive_size;// 收到的数据大小
    qint64 sent_data;// 发送的数据大小
};

#endif // SERVERWIDGET_H
