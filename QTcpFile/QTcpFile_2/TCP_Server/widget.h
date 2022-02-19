#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QTimer>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#define SEND_MAX 4*1024
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);

    void send_data();

    ~Widget();

private slots:
    void on_choose_btn_clicked();

    void on_send_btn_clicked();

    void on_close_btn_clicked();

private:
    Ui::Widget *ui;

    QTcpServer * tcp_server;
    QTcpSocket * tcp_socket;

    QFile file;
    QString file_name;
    qint64 file_size;

    bool is_head;

    qint64 receive_size;// 收到的数据大小
    qint64 sent_data;// 发送的数据大小
};

#endif // WIDGET_H
