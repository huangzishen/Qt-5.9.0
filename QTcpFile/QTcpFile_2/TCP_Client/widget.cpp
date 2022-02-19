#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QThread>
#include <QTimer>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("客户端");
    this->setFixedSize(600,500);

    this->is_head = true;

    // 初始进度条为0
    ui->progressBar->setValue(0);

    // 没连接服务器不能使用按钮
    ui->choose_btn->setEnabled(false);
    ui->send_btn->setEnabled(false);
    ui->close_btn->setEnabled(false);

    this->tcp_socket = NULL;

    ui->ip_edit->setText("127.0.0.1");
    ui->port_edit->setText("8888");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_connect_btn_clicked()
{
    this->tcp_socket = new QTcpSocket(this);

    QString ip = ui->ip_edit->text();
    quint16 port = ui->port_edit->text().toInt();

    // 主动和服务器建立连接
    this->tcp_socket->connectToHost(QHostAddress(ip),port);

    ui->connect_btn->setEnabled(false);

    connect(this->tcp_socket,this->tcp_socket->connected,[=](){
        ui->textEdit->append("成功和服务器连接！");

        // 成功连接服务器，可以使用选择文件按钮,断开连接按钮
        ui->choose_btn->setEnabled(true);
        ui->close_btn->setEnabled(true);


    });

    connect(this->tcp_socket,this->tcp_socket->readyRead,[=](){
        QByteArray array = this->tcp_socket->readAll();
        qint64 len;

        // 先判断是否为头部信息
        if(this->is_head == true)
        {
            this->is_head = false;
            this->receive_size = 0;

            this->file_name = QString(array).section("##",0,0);
            this->file_size = QString(array).section("##",1,1).toInt();

            ui->textEdit->append(QString("接收文件：%1,大小 %2 kb").arg(this->file_name).arg(this->file_size / 1024));

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
            // 接收文件信息
            len = this->file.write(array);
            this->receive_size += len;

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



    // 主动与服务器断开连接
    connect(this->tcp_socket,this->tcp_socket->disconnected,[=](){
        this->tcp_socket->disconnectFromHost();
        this->tcp_socket->close();
        this->tcp_socket = NULL;

        ui->close_btn->setEnabled(false);

        ui->textEdit->append("与服务器断开连接！");
        ui->choose_btn->setEnabled(false);
        ui->connect_btn->setEnabled(true);
    });
}

void Widget::on_send_btn_clicked()
{
    this->sent_data = 0;

    ui->progressBar->setMaximum(this->file_size / 1024);// 进度条最大值
    ui->progressBar->setMinimum(0);// 进度条最小值

//    qDebug() << "开始发送文件";

    // 发送文件的时候，不能点击选择文件按钮
    ui->choose_btn->setEnabled(false);

    // 先发送头信息（文件名##文件大小）
    QString head = QString("%1##%2").arg(this->file_name).arg(this->file_size);
    this->tcp_socket->write(head.toUtf8());


    // 间隔20毫秒发送文件内容，确保头部信息发送完成
    QTimer::singleShot(20,[=](){
        // 然后发送实际的文件数据
        this->send_data();
    });

    ui->send_btn->setEnabled(false);

}

void Widget::on_choose_btn_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this,"请选择文件","../");
    if(file_path == "")
    {
        QMessageBox::information(this,"提示","未选择文件");
        return;
    }

    this->file.setFileName(file_path);
    if(!this->file.open(QIODevice::ReadOnly))
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

void Widget::send_data()
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

void Widget::on_close_btn_clicked()
{
    this->tcp_socket->disconnectFromHost();
}
