#include "serverwidget.h"
#include "ui_serverwidget.h"
#include <QPixmap>
#include <QPainter>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#define SEND_MAX 4*1024
serverWidget::serverWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::serverWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("服务器：8888");
    this->setFixedSize(600,500);

    ui->progressBar->setValue(0);

    // 没连接服务器不能使用按钮
    ui->choose_btn->setEnabled(false);
    ui->send_btn->setEnabled(false);
    ui->close_btn->setEnabled(false);

    this->is_head = true;

    this->tcp_socket = NULL;

    this->tcp_server = new QTcpServer(this);

    this->tcp_server->listen(QHostAddress::Any,8888);

    connect(this->tcp_server,this->tcp_server->newConnection,[=](){
        // 取出建立好连接的套接字
        this->tcp_socket = this->tcp_server->nextPendingConnection();

        QString ip = this->tcp_socket->peerAddress().toString();
        quint16 port = this->tcp_socket->peerPort();
        QString name = this->tcp_socket->peerName();

        ui->textEdit->append(QString("[%1：%2：%3] : 成功连接！").arg(ip).arg(port).arg(name));

        // 成功连接服务器，可以使用选择文件按钮,断开连接按钮
        ui->choose_btn->setEnabled(true);
        ui->close_btn->setEnabled(true);

        // 连接客户端的发送数据
        connect(this->tcp_socket,this->tcp_socket->readyRead,[=](){

            QByteArray array = this->tcp_socket->readAll();
            qint64 len;// 每次写进文件的大小

            // 先判断是否为头文件
            if(this->is_head == true)
            {
                ui->textEdit->append("开始接收文件!");
                this->is_head = false;
                this->receive_size = 0;// 初始化已收到的文件大小

                // 先解析头文件
                this->file_name = QString(array).section("##",0,0);
                this->file_size = QString(array).section("##",1,1).toInt();
                ui->textEdit->append( QString("%1，%2 字节").arg(this->file_name).arg(this->file_size));


                // 在本地打开文件，没有就创建该文件
                this->file.setFileName(this->file_name);

                if(!this->file.open(QIODevice::WriteOnly))
                {
                    QMessageBox::critical(this,"文件提示","服务器文件打开失败！");
                    return;
                }


            }
            else
            {
                len = this->file.write(array);
                this->receive_size += len;

//                qDebug() << QString("发送的文件内容大小：%1，已收到大小：%2 字节").arg(len).arg(this->receive_size);


                // 判断文件是否发送完成
                if(this->receive_size == this->file_size)
                {
                    this->file.close();
                    ui->textEdit->append("文件接收完毕！");
                    QMessageBox::information(this,"成功","文件接收完毕！");
                    this->is_head = true;


                }
            }
        });

        // 服务器主动和客户端断开连接
        connect(this->tcp_socket,this->tcp_socket->disconnected,[=](){
            ui->choose_btn->setEnabled(false);
            ui->send_btn->setEnabled(false);
            ui->close_btn->setEnabled(false);

            ui->textEdit->append("客户端已断开连接！");

            this->tcp_socket->disconnectFromHost();
            this->tcp_socket->close();
            this->tcp_socket = NULL;
        });

    });



}


void serverWidget::paintEvent(QPaintEvent *)
{
//    QPixmap pix;
//    QPainter painter(this);

//    pix.load(":/image/1.jpeg");

//    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

serverWidget::~serverWidget()
{
    delete ui;
}

// 选择文件按钮
void serverWidget::on_choose_btn_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this,"请选择文件","../");
    if(file_path == "")
    {
        QMessageBox::information(this,"提示","未选择文件");
        return;
    }

    this->file.setFileName(file_path);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,"错误","文件打开失败！");
        return;
    }

    QFileInfo file_info(file);

    this->file_name = file_info.fileName();
    this->file_size = file_info.size();

    // 选择完文件，发送文件按钮可以使用
    ui->send_btn->setEnabled(true);

    ui->textEdit->append(QString("文件名称：%1，文件大小：%2 字节").arg(this->file_name).arg(this->file_size));
}

void serverWidget::on_send_btn_clicked()
{
    // 发送文件时，不能点击选择文件按钮
    ui->choose_btn->setEnabled(false);
    this->sent_data = 0;

    // 设置进度条
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(this->file_size / 1024);
    ui->progressBar->setMinimum(0);

    // 首先发送头部信息
    QString head = QString("%1##%2").arg(this->file_name).arg(this->file_size);
    this->tcp_socket->write(head.toUtf8());

    // 然后发送文件信息,20毫秒发送，确保头部信息发送成功
    QTimer::singleShot(20,[=](){
        this->send_data();
    });

}

void serverWidget::send_data()
{
    qint64 len;// 每次发送数据的长度
    qint64 send_data;
    char buf[SEND_MAX];// 每次发送文件大小
    do
    {

        buf[SEND_MAX] = {0};

        // 读取文件
        len = this->file.read(buf,sizeof(buf));

        // 发送数据，读多少，发多少
        send_data = this->tcp_socket->write(buf,len);
        this->sent_data += send_data;

        // 更新进度条
        ui->progressBar->setValue(this->sent_data / 1024);


    }while(len > 0);

//     判断发送数据是否完成
    if(this->sent_data == this->file_size)
    {
        ui->textEdit->append("文件发送完毕！");
        QMessageBox::information(this,"文件传输","发送完毕！");
        this->file.close();
        ui->send_btn->setEnabled(false);
        ui->choose_btn->setEnabled(true);

        this->sent_data = 0;
    }
    else
    {
        QMessageBox::critical(this,"文件传输","发送出错！请重新传输！");
    }
}

void serverWidget::on_close_btn_clicked()
{
    this->tcp_socket->disconnectFromHost();
}
