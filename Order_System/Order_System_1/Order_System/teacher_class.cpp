#include "teacher_class.h"
#include <QMenuBar>
#include <QMenu>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QPoint>
#include <QLabel>
#include <QDebug>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QComboBox>
#include "files.h"
#include <QFile>
//Teacher_Class::Teacher_Class(QWidget * parent) : QMainWindow(parent)
Teacher_Class::Teacher_Class(QString m_id,QString m_name,QString m_password)
{
    this->id = m_id;
    this->name = m_name;
    this->password = m_password;

    // 设置标题
    this->setWindowTitle("教师");

    // 设置固定大小
    this->setFixedSize(600,300);

    // 添加返回按钮
    QPushButton * back_btn = new QPushButton;
    back_btn->setParent(this);
    back_btn->setText("返回");
    back_btn->setFixedSize(80,20);
    back_btn->move(QPoint((this->width() - back_btn->width())/2,this->height() * 0.8));

    // 返回初始界面
    connect(back_btn,back_btn->clicked,[=](){
        emit this->back_first_scence();
    });

    // 教师界面标语
    // 字体设置
    QFont font;
    font.setFamily("宋体");
    font.setPointSize(20);// 设置字体大小
    font.setUnderline(true);// 添加文字下划线


    QLabel * label = new QLabel(this);
    label->setFont(font);
    label->setText("欢迎教师："+this->name);
    label->setAlignment(Qt::AlignHCenter);
    label->setFixedSize(200,40);
    label->move((this->width()-label->width())/2,this->height()*0.3);


    // 添加查看所有预约按钮
    QPushButton * check_all_order_btn = new QPushButton(this);
    check_all_order_btn->setText("查看所有预约");
    check_all_order_btn->setFixedSize(100,30);
    check_all_order_btn->move(this->width()*0.2,this->height()*0.5);

    connect(check_all_order_btn,check_all_order_btn->clicked,[=](){
        this->check_all_order();
    });

    // 添加审核预约按钮
    QPushButton * agree_order_btn = new QPushButton(this);
    agree_order_btn->setText("审核预约");
    agree_order_btn->setFixedSize(100,30);
    agree_order_btn->move(this->width()*0.7,this->height()*0.5);

    connect(agree_order_btn,agree_order_btn->clicked,[=](){
        this->agree_order();
    });

}

void Teacher_Class::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/2_login_picture.jpeg");
    painter.drawPixmap(0,0,pix.width(),pix.height(),pix);
}

// 查看所有预约
void Teacher_Class::check_all_order()
{
    qDebug() << "查看所有预约";
    this->hide();

//    static bool exist_qwidget_all = false;
    QWidget * qwidget_all = new QWidget;
    QTextEdit * display_all_order = new QTextEdit(qwidget_all);

//    if(exist_qwidget_all == false)
//    {
        qwidget_all->setWindowTitle("所有预约信息");
        qwidget_all->setFixedSize(400,660);
        QMenuBar * bar = new QMenuBar(qwidget_all);
        QAction * action = bar->addAction("退出");

        // 将所有预约信息在textedit中显示
        display_all_order->move(20,30);
        display_all_order->setFixedSize(360,600);

        connect(action,action->triggered,[=](){
            qwidget_all->hide();
            this->show();
        });

//        exist_qwidget_all = true;
//    }

    display_all_order->clear();

    QString str /*= "订单编号 学号 姓名 日期 时间段 地点 预约状态\n"*/;

    for(int i = 0;i < this->m_order_num;i++)
    {

        str += QString::number(i+1) + " "
                + (*this->t_order_data)[i]["学号"] + " "
                + (*this->t_order_data)[i]["姓名"] + " "
                + (*this->t_order_data)[i]["日期"] + " "
                + (*this->t_order_data)[i]["时间段"] + " "
                + (*this->t_order_data)[i]["地点"] + " ";

        if((*this->t_order_data)[i]["状态"] == "1")
        {
            str += "审核中";
        }
        else if((*this->t_order_data)[i]["状态"] == "0")
        {
            str += "审核通过";
        }
        else
        {
            str += "审核不通过";
        }

        str += "\n";
    }

    display_all_order->setText(str);


    qwidget_all->show();
}

// 审核预约
void Teacher_Class::agree_order()
{
    qDebug() << "审核预约";
    this->hide();

    QWidget * widget_agree = new QWidget;
    widget_agree->setFixedSize(300,600);
    widget_agree->setWindowTitle("审核预约");

    // 退出按钮菜单
    QMenuBar * bar = new QMenuBar(widget_agree);
    bar->setFixedSize(widget_agree->width(),24);
    QAction * action = bar->addAction("退出");

    connect(action,action->triggered,[=](){
        widget_agree->hide();
        this->show();
    });

    // 显示预约信息
    QTextEdit * agree_text = new QTextEdit;
    agree_text->setFixedSize(260,400);
//    agree_text->move(20,40);
    QString str = "";
    QStringList str_list;
    for(int i = 0;i < this->m_order_num;i++)
    {
        str += QString::number(i+1) + " " +
                (*this->t_order_data)[i]["学号"] + " " +
                (*this->t_order_data)[i]["姓名"] + " " +
                (*this->t_order_data)[i]["日期"] + " " +
                (*this->t_order_data)[i]["时间段"] + " ";
        if((*this->t_order_data)[i]["状态"] == "1")
        {
            str = str + "审核中" + "\n";
        }
        else if((*this->t_order_data)[i]["状态"] == "0")
        {
            str = str + "审核通过" + "\n";
        }
        else
        {
            str = str + "审核不通过" + "\n";
        }

        str_list<<QString::number(i+1);


    }
    agree_text->setText(str.toUtf8());


    QComboBox * box = new QComboBox;
    box->addItems(str_list);

    // 添加审核通过和不通过按钮,水平布局
    QPushButton * pass_btn = new QPushButton;
    QPushButton * unpass_btn = new QPushButton;

    pass_btn->setText("审核通过");
    unpass_btn->setText("审核不通过");

    connect(pass_btn,pass_btn->clicked,[=](){
        (*this->t_order_data)[box->currentText().toInt()-1]["状态"] = "0";
        QString str_pass = "";
        for(int i = 0;i < this->m_order_num;i++)
        {
            str_pass += QString::number(i+1) + " " +
                    (*this->t_order_data)[i]["学号"] + " " +
                    (*this->t_order_data)[i]["姓名"] + " " +
                    (*this->t_order_data)[i]["日期"] + " " +
                    (*this->t_order_data)[i]["时间段"] + " ";
            if((*this->t_order_data)[i]["状态"] == "1")
            {
                str_pass = str_pass + "审核中" + "\n";
            }
            else if((*this->t_order_data)[i]["状态"] == "0")
            {
                str_pass = str_pass + "审核通过" + "\n";
            }
            else
            {
                str_pass = str_pass + "审核不通过" + "\n";
            }
         }
        agree_text->clear();
        agree_text->setText(str_pass.toUtf8());
//        box->removeItem(box->currentIndex());
        this->Save_order();
        qDebug() << "审核通过";
    });

    connect(unpass_btn,unpass_btn->clicked,[=](){
        (*this->t_order_data)[box->currentText().toInt()-1]["状态"] = "-1";
        QString str_unpass = "";
        for(int i = 0;i < this->m_order_num;i++)
        {
            str_unpass += QString::number(i+1) + " " +
                    (*this->t_order_data)[i]["学号"] + " " +
                    (*this->t_order_data)[i]["姓名"] + " " +
                    (*this->t_order_data)[i]["日期"] + " " +
                    (*this->t_order_data)[i]["时间段"] + " ";
            if((*this->t_order_data)[i]["状态"] == "1")
            {
                str_unpass = str_unpass + "审核中" + "\n";
            }
            else if((*this->t_order_data)[i]["状态"] == "0")
            {
                str_unpass = str_unpass + "审核通过" + "\n";
            }
            else
            {
                str_unpass = str_unpass + "审核不通过" + "\n";
            }
         }
        agree_text->clear();
        agree_text->setText(str_unpass.toUtf8());
//        box->removeItem(box->currentIndex());
        this->Save_order();
        qDebug() << "审核不通过";
    });


    QHBoxLayout * layout_btn = new QHBoxLayout;
    layout_btn->addWidget(pass_btn);
    layout_btn->addWidget(unpass_btn);


    // 整体布局做垂直布局
    QVBoxLayout * layout_all = new QVBoxLayout;
    layout_all->addWidget(agree_text);
    layout_all->addWidget(box);
    layout_all->addLayout(layout_btn);
    widget_agree->setLayout(layout_all);

    widget_agree->show();
}

// 保存审核预约的结果
void Teacher_Class::Save_order()
{
    QFile file(Orders_File);
    if(file.open(QIODevice::WriteOnly))
    {
        QString str;
        for(int i = 0;i < this->m_order_num;i++)
        {
            str = (*this->t_order_data)[i]["学号"] + " " +
                    (*this->t_order_data)[i]["姓名"] + " " +
                    (*this->t_order_data)[i]["日期"] + " " +
                    (*this->t_order_data)[i]["时间段"] + " " +
                    (*this->t_order_data)[i]["地点"] + " " +
                    (*this->t_order_data)[i]["状态"] + "\r\n";
            file.write(str.toUtf8());
        }

        file.close();

        qDebug() << "保存完成";
    }
}

