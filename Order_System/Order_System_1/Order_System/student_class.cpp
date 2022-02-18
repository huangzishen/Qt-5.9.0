#include "student_class.h"
#include <QMenuBar>
#include <QMenu>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QPoint>
#include <QLabel>
#include <QFont>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QComboBox>
#include "files.h"
#include <QLineEdit>
#include <QTextEdit>
#include <QTabWidget>
#include <QFont>
#include <QMessageBox>
//Student_Class::Student_Class(QWidget * parent) : QMainWindow(parent)
Student_Class::Student_Class(QString m_id,QString m_name,QString m_password)
{
    this->id = m_id;
    this->name = m_name;
    this->password = m_password;

    // 设置标题
    this->setWindowTitle("学生");

    // 设置固定大小
    this->setFixedSize(600,300);

    // 添加返回按钮
    QPushButton * back_btn = new QPushButton;
    back_btn->setParent(this);
    back_btn->setText("返回");
    back_btn->setFixedSize(80,20);
    back_btn->move(QPoint((this->width() - back_btn->width()) * 0.5,this->height() * 0.8));

    // 返回初始界面
    connect(back_btn,back_btn->clicked,[=](){
        emit this->back_first_scence();
    });

    // 学生界面标语
    // 字体设置
    QFont font;
    font.setFamily("宋体");
    font.setPointSize(20);// 设置字体大小
    font.setUnderline(true);// 添加文字下划线


    QLabel * label = new QLabel(this);
    label->setFont(font);
    label->setText("欢迎学生："+this->name);
    label->setAlignment(Qt::AlignHCenter);
    label->setFixedSize(200,40);
    label->move((this->width()-label->width())/2,this->height()*0.3);

    // 添加申请预约按钮
    QPushButton * apply_order_btn = new QPushButton(this);
    apply_order_btn->setText("申请预约");
    apply_order_btn->setFixedSize(100,30);
    apply_order_btn->move(this->width()*0.1, this->height()*0.5);

    connect(apply_order_btn,apply_order_btn->clicked,[=](){
        this->apply_order();
    });

    // 添加查看自身预约按钮
    QPushButton * check_self_order_btn = new QPushButton(this);
    check_self_order_btn->setText("查看自身预约");
    check_self_order_btn->setFixedSize(100,30);
    check_self_order_btn->move(this->width()*0.3,this->height()*0.5);

    connect(check_self_order_btn,check_self_order_btn->clicked,[=](){
        this->check_self_order();
    });


    // 添加查看所有预约按钮
    QPushButton * check_all_order_btn = new QPushButton(this);
    check_all_order_btn->setText("查看所有预约");
    check_all_order_btn->setFixedSize(100,30);
    check_all_order_btn->move(this->width()*0.5,this->height()*0.5);

    connect(check_all_order_btn,check_all_order_btn->clicked,[=](){
        this->check_all_order();
    });

    // 添加取消预约按钮
    QPushButton * cancel_order_btn = new QPushButton(this);
    cancel_order_btn->setText("取消预约");
    cancel_order_btn->setFixedSize(100,30);
    cancel_order_btn->move(this->width()*0.7,this->height()*0.5);

    connect(cancel_order_btn,cancel_order_btn->clicked,[=](){
        this->cancel_order();
    });

}

void Student_Class::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/2_login_picture.jpeg");
    painter.drawPixmap(0,0,pix.width(),pix.height(),pix);
}

// 学生申请预约
void Student_Class::apply_order()
{
    qDebug() << "申请预约";
    this->hide();

//    bool exist_qwidget_apply = false;
    QWidget * qwidget_apply = new QWidget;
    QComboBox * week_box = new QComboBox;
    QComboBox * day_box = new QComboBox;
//    if(exist_qwidget_apply == false)
//    {
        qwidget_apply->setWindowTitle("申请预约");
        qwidget_apply->setFixedSize(400,200);

        QFont font;
        font.setFamily("宋体");
        font.setPointSize(20);
        QLabel * label = new QLabel;
        label->setFont(font);
        label->setText("请选择预约时间：");

        label->setFixedSize(300,40);
        label->setAlignment(Qt::AlignHCenter);

        QHBoxLayout * layout_label = new QHBoxLayout;
        layout_label->addWidget(label);

        // 日期: 周一至周五
        QLabel * week_label = new QLabel;
        week_label->setText("选择日期：");
        week_label->setFixedSize(80,30);


        QStringList strlist_week;
        strlist_week<<"周一"<<"周二"<<"周三"<<"周四"<<"周五";
        week_box->addItems(strlist_week);

        QHBoxLayout * layout_week = new QHBoxLayout;
        layout_week->addWidget(week_label);
        layout_week->addWidget(week_box);

        // 时间段: 上午，下午
        QLabel * day_label = new QLabel;
        day_label->setText("选择时间段：");
        day_label->setFixedSize(80,30);


        QStringList strlist_day;
        strlist_day<<"上午"<<"下午";
        day_box->addItems(strlist_day);

        QHBoxLayout * layout_day = new QHBoxLayout;
        layout_day->addWidget(day_label);
        layout_day->addWidget(day_box);


        // 地点: 一号机房，二号机房，三号机房
        QLabel * com_label = new QLabel;
        com_label->setText("机房：");
        com_label->setFixedSize(80,30);

        QComboBox * com_box = new QComboBox;
        QStringList strlist_com;
        strlist_com<<"一号机房"<<"二号机房"<<"三号机房";
        com_box->addItems(strlist_com);

        QHBoxLayout * layout_com = new QHBoxLayout;
        layout_com->addWidget(com_label);
        layout_com->addWidget(com_box);


        // 将日期，时间段，机房水平布局
        QHBoxLayout * layout_input = new QHBoxLayout;
        layout_input->addLayout(layout_week);
        layout_input->addLayout(layout_day);
        layout_input->addLayout(layout_com);

        // 添加确认按钮和退出按钮，并水平布局
        QPushButton * yes_btn = new QPushButton;
        yes_btn->setText("确认");
        yes_btn->setFixedSize(80,30);

        QPushButton * back_btn = new QPushButton;
        back_btn->setText("退出");
        back_btn->setFixedSize(80,30);

        QHBoxLayout * layout_btn = new QHBoxLayout;
        layout_btn->addWidget(yes_btn);
        layout_btn->addWidget(back_btn);

        // 将所有控件垂直布局到一起
        QVBoxLayout * layout_all = new QVBoxLayout;
        layout_all->addLayout(layout_label);
        layout_all->addLayout(layout_input);
        layout_all->addLayout(layout_btn);

        qwidget_apply->setLayout(layout_all);

        // 将申请的预约写入文件
        connect(yes_btn,yes_btn->clicked,[=](){
//            qDebug() << week_box->currentText() << " "
//                     << day_box->currentText() << " "
//                     << com_box->currentText();
            this->write_s_file(week_box->currentText(),day_box->currentText(),com_box->currentText(),qwidget_apply);
        });

        connect(back_btn,back_btn->clicked,[=](){
//            qDebug() << "返回";
            qwidget_apply->hide();
            this->show();
        });

//        exist_qwidget_apply = true;
//    }

    qwidget_apply->show();
}

// 将预约信息写入文件
void Student_Class::write_s_file(QString week,QString day,QString pos,QWidget * widget)
{
    QMap<QString,QString> map;
    map.insert("学号",this->id);
    map.insert("姓名",this->name);
    map.insert("日期",week);
    map.insert("时间段",day);
    map.insert("地点",pos);
    map.insert("状态","1");

    QFile file(Orders_File);
    if(file.open(QIODevice::Append))
    {
        file.write(QString(this->id + " " + this->name + " " + week + " " + day + " " + pos + " " + "1").toUtf8());
        file.write("\r\n");
        QMessageBox::information(widget,"预约提示","预约成功！");
        this->s_order_data->insert(this->m_order_num,map);
        this->m_order_num++;

//    qDebug() << "预约成功！";
    }
    else
    {
        QMessageBox::critical(widget,"预约提示","预约失败！");
    }

    file.close();


}

// 查看自身预约
void Student_Class::check_self_order()
{
    qDebug() << "查看自身预约";
    this->hide();

//    bool exist_qwidget_self = false;
    QWidget * qwidget_self = new QWidget;
    QTextEdit * display_self_order = new QTextEdit(qwidget_self);

//    if(exist_qwidget_self == false)
//    {
        qwidget_self->setWindowTitle("自身预约信息");
        qwidget_self->setFixedSize(400,600);
        QMenuBar * bar = new QMenuBar(qwidget_self);
        QAction * action = bar->addAction("退出");

        // 将自身预约信息在textedit中显示
        display_self_order->move(20,30);
        display_self_order->setFixedSize(360,500);

        connect(action,action->triggered,[=](){
            qwidget_self->hide();
            this->show();
        });


//        exist_qwidget_self = true;
//    }

    display_self_order->clear();

    QString str /*= "订单编号 学号 姓名 日期 时间段 地点 预约状态\n"*/;

    for(int i = 0;i < this->m_order_num;i++)
    {

        if((*this->s_order_data)[i]["姓名"] == this->name)
        {
            str += QString::number(i+1) + " "
                    + (*this->s_order_data)[i]["日期"] + " "
                    + (*this->s_order_data)[i]["时间段"] + " "
                    + (*this->s_order_data)[i]["地点"] + " ";

            if((*this->s_order_data)[i]["状态"] == "1")
            {
                str += "审核中";
            }
            else if((*this->s_order_data)[i]["状态"] == "0")
            {
                str += "审核通过";
            }
            else
            {
                str += "审核不通过";
            }

            str += "\n";
        }
    }

    display_self_order->setText(str);

    qwidget_self->show();
}

// 查看所有预约
void Student_Class::check_all_order()
{
    qDebug() << "查看所有预约";
    this->hide();

//    bool exist_qwidget_all = false;
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
                + (*this->s_order_data)[i]["学号"] + " "
                + (*this->s_order_data)[i]["姓名"] + " "
                + (*this->s_order_data)[i]["日期"] + " "
                + (*this->s_order_data)[i]["时间段"] + " "
                + (*this->s_order_data)[i]["地点"] + " ";

        if((*this->s_order_data)[i]["状态"] == "1")
        {
            str += "审核中";
        }
        else if((*this->s_order_data)[i]["状态"] == "0")
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

// 取消预约
void Student_Class::cancel_order()
{
    qDebug() << "取消预约";
    this->hide();

//    bool exist_cancel_qwidget = false;
    QWidget * cancel_qwidget = new QWidget;
    QTextEdit * cancel_text = new QTextEdit;
    QComboBox * input_edit = new QComboBox;
//    if(exist_cancel_qwidget == false)
//    {
        cancel_qwidget->setWindowTitle("取消预约");
        cancel_qwidget->setFixedSize(400,700);

        QMenuBar * bar = new QMenuBar(cancel_qwidget);
        bar->setFixedSize(cancel_qwidget->width(),30);
        QAction * action = bar->addAction("退出");

        connect(action,action->triggered,[=](){
            cancel_qwidget->hide();
            this->show();
        });

        QFont font;
        font.setFamily("宋体");
        font.setPointSize(20);

        QLabel * label = new QLabel(cancel_qwidget);
        label->setFixedSize(cancel_qwidget->width(),30);
        label->setText("可取消预约如下:");
        label->setFont(font);
        label->move(0,40);
        label->setAlignment(Qt::AlignHCenter);

        cancel_text->setReadOnly(true);
        cancel_text->setFixedSize(360,500);
        cancel_text->move(QPoint(20,80));

        // 添加输入框和确认按钮和刷新按钮
        QLabel * label_input = new QLabel;
        label_input->setText("请选择需要取消的订单编号:");
        label_input->setFixedSize(360,20);

        QPushButton * yes_btn = new QPushButton;
        yes_btn->setText("确认取消");


        connect(yes_btn,yes_btn->clicked,[=](){
            (*this->s_order_data)[QString(input_edit->currentText()).toInt() - 1]["状态"] = "-1";
            // 修改文件中的数据
            QFile file(Orders_File);
            file.open(QIODevice::WriteOnly | QIODevice::Truncate);
            QString array;
            while(this->m_order_num--)
            {
                array = (*this->s_order_data)[this->m_order_num]["学号"] + " " +
                        (*this->s_order_data)[this->m_order_num]["姓名"] + " " +
                        (*this->s_order_data)[this->m_order_num]["日期"] + " " +
                        (*this->s_order_data)[this->m_order_num]["时间段"] + " " +
                        (*this->s_order_data)[this->m_order_num]["地点"] + " " +
                        (*this->s_order_data)[this->m_order_num]["状态"] + "\r\n";

                file.write(array.toUtf8());

            }

            file.close();

            // 刷新TextEdit
            QString str = cancel_text->toPlainText();
//            qDebug() << str;
            QStringList str_list = str.split("\n");
            //                                  1
//            qDebug() << str_list.at(input_edit->currentIndex()).indexOf(" ");// 获取要取消的订单编号下标+1

//            qDebug() << str_list.at(input_edit->currentIndex()).mid(0,str_list.at(input_edit->currentIndex()).indexOf(" ")).toInt();// 获取int类型的订单编号下标

//            (*this->s_order_data)[str_list.at(input_edit->currentIndex()).mid(0,str_list.at(input_edit->currentIndex()).indexOf(" ")).toInt() - 1]["状态"] = "-1";

            str_list.removeAt(input_edit->currentIndex());// 如何移除该条记录

            // 再重新显示
            str = "";
            cancel_text->clear();
            for(QStringList::iterator it = str_list.begin();it != str_list.end();it++)
            {
                str += *it + "\n";
//                qDebug() << *it;
            }
            input_edit->removeItem(input_edit->currentIndex());

            cancel_text->setText(str);

            QMessageBox::information(cancel_qwidget,"提示信息","取消成功！");
//            qDebug() << "取消成功！";
        });

        QVBoxLayout * layout_input = new QVBoxLayout;
        layout_input->addWidget(label);
        layout_input->addWidget(cancel_text);
        layout_input->addWidget(label_input);
        layout_input->addWidget(input_edit);
        layout_input->addWidget(yes_btn);

        cancel_qwidget->setLayout(layout_input);

//    }

    cancel_text->clear();

    // 显示可取消预约的订单记录
    QString str /*= "订单编号 日期 时间段 地点 预约状态\n"*/;
    QStringList cox_list;
    for(int i = 0;i < this->m_order_num;i++)
    {
        if((*this->s_order_data)[i]["状态"] == "0" || (*this->s_order_data)[i]["状态"] == "1")
        {
            str += QString::number(i+1) + " "
                    + (*this->s_order_data)[i]["日期"] + " "
                    + (*this->s_order_data)[i]["时间段"] + " "
                    + (*this->s_order_data)[i]["地点"] + " ";

            if((*this->s_order_data)[i]["状态"] == "1")
            {
                str += "审核中";
            }
            else
            {
                str += "审核通过";
            }

            str += "\n";

            cox_list<<QString::number(i+1);
        }

    }

    input_edit->addItems(cox_list);

    // 设置显示的字体
    cancel_text->setFontPointSize(18);
    cancel_text->setText(str);

    cancel_qwidget->show();

}

void Student_Class::Save_order()
{
    QFile file(Orders_File);
    if(file.open(QIODevice::Truncate))
    {
        QString str;
        for(int i = 0;i < this->m_order_num;i++)
        {
            str = (*this->s_order_data)[i]["学号"] + " " +
                    (*this->s_order_data)[i]["姓名"] + " " +
                    (*this->s_order_data)[i]["日期"] + " " +
                    (*this->s_order_data)[i]["时间段"] + " " +
                    (*this->s_order_data)[i]["地点"] + " " +
                    (*this->s_order_data)[i]["状态"] + "\r\n";
            file.write(str.toUtf8());
        }

        file.close();

        qDebug() << "保存完成";
    }
}
