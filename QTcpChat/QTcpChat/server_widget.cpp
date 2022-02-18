#include "server_widget.h"
#include "ui_server_widget.h"



Server_Widget::Server_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server_Widget)
{
    ui->setupUi(this);

    // 未和客户端连接按钮都不能使用
    ui->send_btn->setEnabled(false);
    ui->close_btn->setEnabled(false);

    this->setWindowTitle("服务器：8888");

    this->tcp_socket = NULL;

    this->tcp_server = new QTcpServer(this);

    this->tcp_server->listen(QHostAddress::Any,8888);

    // 取出建立好连接的套接字
    connect(this->tcp_server,this->tcp_server->newConnection,[=](){
        this->tcp_socket = this->tcp_server->nextPendingConnection();

        // 获取连接的ip，port，name
        QString ip = this->tcp_socket->peerAddress().toString();
        quint16 port = this->tcp_socket->peerPort();
        QString name = this->tcp_socket->peerName();
        // 显示
        ui->read_edit->setText(QString("[%1: %2: %3]: 连接成功！").arg(name).arg(ip).arg(port));
        // 连接成功，按钮可以使用
        ui->send_btn->setEnabled(true);
        ui->close_btn->setEnabled(true);

        // 当断开连接时，按钮都不可以使用
        connect(this->tcp_socket,this->tcp_socket->disconnected,[=](){
            this->tcp_socket->close();
            this->tcp_socket = NULL;
            ui->read_edit->append("和服务器断开连接！");
            ui->send_btn->setEnabled(false);
            ui->close_btn->setEnabled(false);
        });

        // 接收客户端发送的信息
        connect(this->tcp_socket,this->tcp_socket->readyRead,[=](){
            ui->read_edit->append(QString("客户端：%1").arg(QString(this->tcp_socket->readAll())));
        });

    });

    // 当关闭程序时，连接未断开
    connect(this,this->destroyed,[=](){
        if(this->tcp_socket != NULL)
        {
            this->tcp_socket->disconnectFromHost();
        }
    });


}

Server_Widget::~Server_Widget()
{
    delete ui;
}

void Server_Widget::on_close_btn_clicked()
{
    this->tcp_socket->disconnectFromHost();
}

void Server_Widget::on_send_btn_clicked()
{
    // 获取聊天框中的信息
    QString str = ui->input_edit->toPlainText();
    // 发送信息
    this->tcp_socket->write(str.toUtf8());

    ui->read_edit->append(str);
}
