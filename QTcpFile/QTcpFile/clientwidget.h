#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H
#define SEND_MAX 4*1024

#include <QWidget>
#include <QTcpSocket>
#include <QFile>
namespace Ui {
class clientWidget;
}

class clientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit clientWidget(QWidget *parent = 0);

    void paintEvent(QPaintEvent  *);

    void send_data();


    ~clientWidget();

private slots:
    void on_connect_btn_clicked();

    void on_choose_btn_clicked();

    void on_send_btn_clicked();

    void on_close_btn_clicked();

private:
    Ui::clientWidget *ui;

    QTcpSocket * tcp_socket;

    QFile file;
    QString file_name;
    qint64 file_size;

    bool is_head;// 判断是否为头部信息

    qint64 sent_data;// 已发送数据大小
    qint64 receive_size;// 收到的数据大小
};

#endif // CLIENTWIDGET_H
