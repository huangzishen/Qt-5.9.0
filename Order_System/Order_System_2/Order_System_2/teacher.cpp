#include "teacher.h"

//Teacher::Teacher(QWidget *parent) : QWidget(parent)
//{

//}


Teacher::Teacher(QString m_id,QString m_name,QString m_password)
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
    back_btn->setText("注销登录");
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

void Teacher::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/2_login_picture.jpeg");
    painter.drawPixmap(0,0,pix.width(),pix.height(),pix);
}

// 查看所有预约
void Teacher::check_all_order()
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

    for(int i = 0;i < this->t_order_data->size();i++)
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
        else if((*this->t_order_data)[i]["状态"] == "2")
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

// 审核预约
void Teacher::agree_order()
{
//    qDebug() << "审核预约";
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
    for(int i = 0;i < this->t_order_data->size();i++)
    {
        if((*this->t_order_data)[i]["状态"] == "2")
        {
            continue;
        }
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
        QString m_status = (*this->t_order_data)[box->currentText().toInt()-1]["状态"];
        QString com_num = (*this->t_order_data)[box->currentText().toInt()-1]["地点"];

        // 判断机房是否还有位置
        bool com_is_empty = true;
        if(m_status != "0")
        {
            if(com_num == "一号机房")
            {
                if((*this->com_1) == 0)
                {
                    com_is_empty = false;
                }
                else
                {
                    (*this->com_1)--;
                }
            }
            else if(com_num == "二号机房")
            {
                if((*this->com_2) == 0)
                {
                    com_is_empty = false;
                }
                else
                {
                    (*this->com_2)--;
                }
            }
            else
            {
                if((*this->com_3) == 0)
                {
                    com_is_empty = false;
                }
                else
                {
                    (*this->com_3)--;
                }
            }

            if(com_is_empty)
            {
                (*this->t_order_data)[box->currentText().toInt()-1]["状态"] = "0";
                QString str_pass = "";
                for(int i = 0;i < this->t_order_data->size();i++)
                {
                    str_pass += QString::number(i+1) + " " +
                            (*this->t_order_data)[i]["学号"] + " " +
                            (*this->t_order_data)[i]["姓名"] + " " +
                            (*this->t_order_data)[i]["日期"] + " " +
                            (*this->t_order_data)[i]["时间段"] + " " +
                            (*this->t_order_data)[i]["地点"] + " ";
                    if((*this->t_order_data)[i]["状态"] == "1")
                    {
                        str_pass = str_pass + "审核中" + "\n";
                    }
                    else if((*this->t_order_data)[i]["状态"] == "0")
                    {
                        str_pass = str_pass + "审核通过" + "\n";
                    }
                    else if((*this->t_order_data)[i]["状态"] == "-1")
                    {
                        str_pass = str_pass + "审核不通过" + "\n";
                    }
                 }
                agree_text->clear();
                agree_text->setText(str_pass.toUtf8());
                this->Save_order();
                QMessageBox::information(widget_agree,"审核提示","审核通过成功！");
//                qDebug() << "一号机房剩余：" << (*this->com_1)
//                         << "二号机房剩余：" << (*this->com_2)
//                         << "三号机房剩余：" << (*this->com_3);
            }
            else
            {
                QMessageBox::critical(widget_agree,"审核提示","该机房已满！！！");
            }


        }
        else
        {
            QMessageBox::information(widget_agree,"审核提示","该预约已通过，请勿重复点击！");
        }

    });

    connect(unpass_btn,unpass_btn->clicked,[=](){
        QString m_status = (*this->t_order_data)[box->currentText().toInt()-1]["状态"];
        QString com_num = (*this->t_order_data)[box->currentText().toInt()-1]["地点"];

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

        (*this->t_order_data)[box->currentText().toInt()-1]["状态"] = "-1";

        QString str_unpass = "";
        for(int i = 0;i < this->t_order_data->size();i++)
        {
            if((*this->t_order_data)[i]["状态"] == "2")
            {
                continue;
            }
            else
            {
                str_unpass += QString::number(i+1) + " " +
                        (*this->t_order_data)[i]["学号"] + " " +
                        (*this->t_order_data)[i]["姓名"] + " " +
                        (*this->t_order_data)[i]["日期"] + " " +
                        (*this->t_order_data)[i]["时间段"] + " " +
                        (*this->t_order_data)[i]["地点"] + " ";
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

         }
        agree_text->clear();
        agree_text->setText(str_unpass.toUtf8());
        this->Save_order();
        QMessageBox::information(widget_agree,"审核提示","审核不通过成功！");

//        qDebug() << "一号机房剩余：" << (*this->com_1)
//                 << "二号机房剩余：" << (*this->com_2)
//                 << "三号机房剩余：" << (*this->com_3);
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
void Teacher::Save_order()
{
    QFile file(Orders_File);
    if(file.open(QIODevice::WriteOnly))
    {
        QString str;
        for(int i = 0;i < this->t_order_data->size();i++)
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

//        qDebug() << "保存完成";
    }

}
