#include "student.h"

//Student::Student(QWidget *parent) : QWidget(parent)
//{

//}

Student::Student(QString m_id,QString m_name,QString m_password)
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
    back_btn->setText("注销登录");
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

void Student::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/2_login_picture.jpeg");
    painter.drawPixmap(0,0,pix.width(),pix.height(),pix);
}

// 学生申请预约
void Student::apply_order()
{
//    qDebug() << "申请预约";
    this->hide();

    QWidget * qwidget_apply = new QWidget;
    QComboBox * week_box = new QComboBox;
    QComboBox * day_box = new QComboBox;

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
        // 先判断机房是否还有空位
        bool com_is_empty = true;
        if(com_label->text() == "一号机房")
        {
            if((*this->com_1) == 0)
            {
                com_is_empty = false;
            }
        }
        else if(com_label->text() == "二号机房")
        {
            if((*this->com_2) == 0)
            {
                com_is_empty = false;
            }
        }
        else
        {
            if((*this->com_3) == 0)
            {
                com_is_empty = false;
            }
        }

        // 判断是否存在该预约
        bool order_not_exist = false;
        for(int i = 0;i < this->s_order_data->size();i++)
        {
            if( (*this->s_order_data)[i]["学号"] == this->id &&
                    (*this->s_order_data)[i]["姓名"] == this->name &&
                    (*this->s_order_data)[i]["日期"] == week_box->currentText() &&
                    (*this->s_order_data)[i]["时间段"] == day_box->currentText() &&
                    (*this->s_order_data)[i]["地点"] == com_box->currentText() )
            {
                order_not_exist = true;
                break;
            }
        }


        if(com_is_empty == true)
        {
            if(order_not_exist == false)
            {
                this->Save_order(week_box->currentText(),day_box->currentText(),com_box->currentText(),qwidget_apply);
            }
            else
            {
                QMessageBox::critical(qwidget_apply,"申请失败","已存在该预约!");
            }

        }
        else
        {
            QMessageBox::critical(qwidget_apply,"机房提示","该机房已满!");
        }
    });


    connect(back_btn,back_btn->clicked,[=](){
        qwidget_apply->hide();
        this->show();
    });

    qwidget_apply->show();
}

// 查看自身预约
void Student::check_self_order()
{
//    qDebug() << "查看自身预约";
    QWidget * qwidget_self = new QWidget;
    QTextEdit * display_self_order = new QTextEdit(qwidget_self);

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

    display_self_order->clear();

    QString str /*= "订单编号 学号 姓名 日期 时间段 地点 预约状态\n"*/;

    for(int i = 0;i < this->s_order_data->size();i++)
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
            else if((*this->s_order_data)[i]["状态"] == "2")
            {
                str += "取消预约";
            }
            else
            {
                str += "审核不通过";
            }

            str += "\n";
        }
    }

    // 设置字体大小
    QFont font;
    font.setPointSize(12);

    display_self_order->setFont(font);

    display_self_order->setText(str);

    qwidget_self->show();
}

// 查看所有预约
void Student::check_all_order()
{
//    qDebug() << "查看所有预约";
    this->hide();

    QWidget * qwidget_all = new QWidget;
    QTextEdit * display_all_order = new QTextEdit(qwidget_all);

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

    display_all_order->clear();

    QString str /*= "订单编号 学号 姓名 日期 时间段 地点 预约状态\n"*/;

    for(int i = 0;i < this->s_order_data->size();i++)
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
        else if((*this->s_order_data)[i]["状态"] == "2")
        {
            str += "取消预约";
        }
        else
        {
            str += "审核不通过";
        }

        str += "\n";
    }

    // 设置字体大小
    QFont font;
    font.setPointSize(12);

    display_all_order->setFont(font);

    display_all_order->setText(str);

    qwidget_all->show();
}

// 取消预约
void Student::cancel_order()
{
//    qDebug() << "取消预约";
    this->hide();
    QWidget * cancel_qwidget = new QWidget;
    QTextEdit * cancel_text = new QTextEdit;
    QComboBox * input_edit = new QComboBox;

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
        QString m_status = (*this->s_order_data)[QString(input_edit->currentText()).toInt() - 1]["状态"];
        QString com_num = (*this->s_order_data)[QString(input_edit->currentText()).toInt() - 1]["地点"];
        if(m_status == "0")
        {
            if(com_num == "一号机房")
            {
                (*this->com_1)++;
            }
            else if(com_num == "二号机房")
            {
                (*this->com_2)++;
            }
            else
            {
                (*this->com_3)++;
            }

        }

//        qDebug() << "--------- 取消预约后：------------";
//        qDebug() << "一号机房剩余：" << (*this->com_1)
//                 << "二号机房剩余：" << (*this->com_2)
//                 << "三号机房剩余：" << (*this->com_3);


        (*this->s_order_data)[QString(input_edit->currentText()).toInt() - 1]["状态"] = "2";
        this->Save_order();

        // 刷新TextEdit
        QString str = cancel_text->toPlainText();
        QStringList str_list = str.split("\n");
        str_list.removeAt(input_edit->currentIndex());// 如何移除该条记录

        // 再重新显示
        str = "";
        cancel_text->clear();
        for(QStringList::iterator it = str_list.begin();it != str_list.end();it++)
        {
            str += *it + "\n";
        }
        input_edit->removeItem(input_edit->currentIndex());

        cancel_text->setText(str);

        QMessageBox::information(cancel_qwidget,"提示信息","取消成功！");

    });

    QVBoxLayout * layout_input = new QVBoxLayout;
    layout_input->addWidget(label);
    layout_input->addWidget(cancel_text);
    layout_input->addWidget(label_input);
    layout_input->addWidget(input_edit);
    layout_input->addWidget(yes_btn);

    cancel_qwidget->setLayout(layout_input);

    cancel_text->clear();

    // 显示可取消预约的订单记录
    QString str /*= "订单编号 日期 时间段 地点 预约状态\n"*/;
    QStringList cox_list;
    for(int i = 0;i < this->s_order_data->size();i++)
    {
        if((*this->s_order_data)[i]["姓名"] == this->name)
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

    }

    input_edit->addItems(cox_list);

    // 设置显示的字体
    cancel_text->setFontPointSize(12);
    cancel_text->setText(str);

    cancel_qwidget->show();

//    qDebug() << "一号机房剩余：" << (*this->com_1)
//             << "二号机房剩余：" << (*this->com_2)
//             << "三号机房剩余：" << (*this->com_3);


}

// 保存预约信息
void Student::Save_order(QString m_week,QString m_day,QString m_pos, QWidget * parent)
{
//    qDebug() << m_week << " " << m_day << " " << m_pos;
    QMap<QString,QString> map;
    map.insert("学号",this->id);
    map.insert("姓名",this->name);
    map.insert("日期",m_week);
    map.insert("时间段",m_day);
    map.insert("地点",m_pos);
    map.insert("状态","1");

    QFile file(Orders_File);
    if(file.open(QIODevice::Append))
    {
        file.write(QString(this->id + " " + this->name + " " + m_week + " " + m_day + " " + m_pos + " " + "1").toUtf8());
        file.write("\r\n");
        (*this->s_order_data).insert(this->s_order_data->size(),map);
        QMessageBox::information(parent,"预约提示","预约成功！");

    }
    else
    {
        QMessageBox::critical(parent,"预约提示","预约失败！");
    }

    file.close();
}

// 保存取消预约后的信息
void Student::Save_order()
{
    QFile file(Orders_File);
    if(file.open(QIODevice::Truncate | QIODevice::WriteOnly))
    {
        QString str;
        for(int i = 0;i < this->s_order_data->size();i++)
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

//        qDebug() << "保存完成";
    }
}
