#include "client_widget.h"
#include "ui_client_widget.h"


#include <QHostAddress>

Client_Widget::Client_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client_Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("客户端");

    // 未连接按钮都不能使用
    ui->send_btn->setEnabled(false);
    ui->close_btn->setEnabled(false);

    this->tcp_socket = NULL;

    // 设置默认ip和端口
    ui->ip_edit->setText("127.0.0.1");
    ui->port_edit->setText("8888");
}

Client_Widget::~Client_Widget()
{
    delete ui;
}

void Client_Widget::on_connect_btn_clicked()
{
    this->tcp_socket = new QTcpSocket(this);

    // 获取ip，端口
    QString ip = ui->ip_edit->text();
    quint16 port = ui->port_edit->text().toInt();
    // 主动和服务器连接
    this->tcp_socket->connectToHost(QHostAddress(ip),port);
    // 如果连接成功，按钮可以使用
    connect(this->tcp_socket,this->tcp_socket->connected,[=](){
        ui->read_edit->setText("成功和服务器连接！");
        ui->send_btn->setEnabled(true);
        ui->close_btn->setEnabled(true);

        // 接收服务器发送的信息
        connect(this->tcp_socket,this->tcp_socket->readyRead,[=](){
            ui->read_edit->append(QString("服务器：%1").arg(QString(this->tcp_socket->readAll())));
        });
    });

    // 当断开连接时，按钮都不可以使用
    connect(this->tcp_socket,this->tcp_socket->disconnected,[=](){
        this->tcp_socket->close();
        this->tcp_socket = NULL;
        ui->read_edit->append("和服务器断开连接！");
        ui->send_btn->setEnabled(false);
        ui->close_btn->setEnabled(false);
    });

    // 当关闭程序时，连接未断开
    connect(this,this->destroyed,[=](){
        if(this->tcp_socket != NULL)
        {
            this->tcp_socket->disconnectFromHost();
        }
    });


}

void Client_Widget::on_close_btn_clicked()
{
    this->tcp_socket->disconnectFromHost();
}

void Client_Widget::on_send_btn_clicked()
{
    // 获取聊天框的内容
    QString str = ui->input_edit->toPlainText();
    // 发送信息
    this->tcp_socket->write(str.toUtf8());

    ui->read_edit->append(str);
}
