#include "manager_class.h"
#include <QMenuBar>
#include <QMenu>
#include <QDebug>
#include <QPushButton>
#include <QPoint>
#include <QLabel>
#include <QLineEdit>
//Manager_Class::Manager_Class(QWidget * parent) : QMainWindow(parent)
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFile>
#include <QDir>
#include <QTextLine>
#include <QTextEdit>
#include "files.h"
#include <QMessageBox>
Manager_Class::Manager_Class(QString m_name,QString m_password)
{

    // 设置标题
    this->setWindowTitle("管理员");

    // 设置固定大小
    this->setFixedSize(600,300);

    // 界面文字
    QLabel * label = new QLabel;

    this->name = m_name;
    this->password = m_password;

    // 字体设置
    QFont font;
    font.setFamily("宋体");
    font.setPointSize(20);// 设置字体大小
    font.setUnderline(true);// 添加文字下划线

    label->setFont(font);
    label->setParent(this);
    label->setText("欢迎管理员："+this->name);
    label->setFixedSize(400,30);
    label->move((this->width()-label->width()) * 0.5, 80);

    // 设置label上的文字对齐方式：水平剧中和垂直剧中
    label->setAlignment((Qt::AlignHCenter | Qt::AlignVCenter));


    // 添加返回按钮
    QPushButton * back_btn = new QPushButton;
    back_btn->setParent(this);
    back_btn->setText("返回");
    back_btn->setFixedSize(80,20);
    back_btn->move(QPoint((this->width() - back_btn->width())/ 2,this->height() * 0.8));

    // 返回初始界面
    connect(back_btn,back_btn->clicked,[=](){
        emit this->back_first_scence();
    });

    // 添加账号按钮
    QPushButton * add_people_btn = new QPushButton;
    add_people_btn->setParent(this);
    add_people_btn->setText("添加账号");
    add_people_btn->setFixedSize(100,30);
    add_people_btn->move(QPoint(50,150));

    // 连接添加账号按钮
    connect(add_people_btn,add_people_btn->clicked,[=](){
        this->add_people();
    });


    // 查看所有人信息按钮
    QPushButton * check_info_btn = new QPushButton;
    check_info_btn->setParent(this);
    check_info_btn->setText("查看所有人信息");
    check_info_btn->setFixedSize(100,30);
    check_info_btn->move(QPoint(250,150));

    // 连接查看所有人信息按钮
    connect(check_info_btn,check_info_btn->clicked,[=](){
        this->check_info();
    });


    // 查看所有人的预约信息
    QPushButton * check_order_btn = new QPushButton;
    check_order_btn->setParent(this);
    check_order_btn->setText("查看所有预约信息");
    check_order_btn->setFixedSize(120,30);
    check_order_btn->move(QPoint(400,150));

    // 连接所有人的预约信息
    connect(check_order_btn,check_order_btn->clicked,[=](){
        this->check_order();
    });


}

void Manager_Class::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/2_login_picture.jpeg");
    painter.drawPixmap(0,0,pix.width(),pix.height(),pix);
}

// 添加账号
void Manager_Class::add_people()
{
//    qDebug() << "添加账号";
    this->hide();

    static bool exist_qwidget_1 = false;// 防止每次调用都会新建窗口
    QWidget * qwidget_1 = new QWidget;
    if(exist_qwidget_1 == false)
    {
        qwidget_1->setWindowTitle("添加账号");
        qwidget_1->setFixedSize(300,200);

        // 创建菜单栏
        QMenuBar * bar = new QMenuBar(qwidget_1);
//        qwidget_1->;
        // 创建返回菜单
        QAction * back_action = bar->addAction("返回");

        // 连接返回菜单
        connect(back_action,back_action->triggered,[=](){
            qwidget_1->hide();
            this->show();
        });


        QPushButton * add_student = new QPushButton(qwidget_1);
        add_student->setText("添加学生账号");
        add_student->setFixedSize(qwidget_1->width(),(qwidget_1->height() - 20) / 2);
        add_student->move(QPoint(0,20));

        QPushButton * add_teacher = new QPushButton(qwidget_1);
        add_teacher->setText("添加老师账号");
        add_teacher->setFixedSize(qwidget_1->width(),(qwidget_1->height() - 20) / 2);
        add_teacher->move(QPoint(0,qwidget_1->height()-add_student->height()));

        connect(add_teacher,add_teacher->clicked,[=](){
            qDebug() << "添加老师账号";
            this->add_qwidget(2);

        });

        connect(add_student,add_student->clicked,[=](){
//            qDebug() << "添加学生账号";
            this->add_qwidget(1);
        });
    }


    qwidget_1->show();
}

// 查看所有人账号信息
void Manager_Class::check_info()
{
//    qDebug() << "查看所有人信息";
    this->hide();

    static bool exist_qwidget_all = false;
    static QWidget * qwidget_all = new QWidget;

    // 显示信息
    static QTextEdit * display_s = new QTextEdit;
    static QTextEdit * display_t = new QTextEdit;

    if(exist_qwidget_all == false)// 只需要布局一次
    {
        qwidget_all->setWindowTitle("学生和教师信息");
        qwidget_all->setFixedSize(630,440);
        QMenuBar * bar = new QMenuBar(qwidget_all);
        QAction * action = bar->addAction("退出");
        bar->setFixedSize(40,24);

        connect(action,action->triggered,[=]()
        {
            qwidget_all->hide();
            this->show();
        });

        // 显示学生和老师的信息
        QLabel * s_label = new QLabel;
        s_label->setText("|------------------| 学生信息 |----------------|\n"
                         "| 学号 |             | 姓名 |            | 密码 |");
        s_label->setAlignment(Qt::AlignCenter);
        s_label->setFixedSize(310,34);



        display_s->setFixedWidth(300);


        QVBoxLayout * layout_s = new QVBoxLayout;
        layout_s->addWidget(s_label);
        layout_s->addWidget(display_s);


        QLabel * t_label = new QLabel;
        t_label->setText("|-------------------| 教师信息 |-----------------|\n"
                         "| 职工号 |             | 姓名 |            | 密码 |");
        t_label->setAlignment(Qt::AlignCenter);
        t_label->setFixedSize(310,34);


        display_t->setFixedWidth(300);

        QVBoxLayout * layout_t = new QVBoxLayout;
        layout_t->addWidget(t_label);
        layout_t->addWidget(display_t);

        QHBoxLayout * layout_all = new QHBoxLayout;
        layout_all->addLayout(layout_s);
        layout_all->addLayout(layout_t);

        qwidget_all->setLayout(layout_all);

        exist_qwidget_all = true;// 表示已经布局完成
    }

//    qDebug() << Students_File << "\n" << Teachers_File;

    // 加载显示信息
    QFile s_file(Students_File);
    if(s_file.open(QIODevice::ReadOnly | QIODevice::Text))// 只读方式
    {
//        qDebug() << s_file.readAll();
        display_s->setText(QString(s_file.readAll()));
    }
    else
    {
        qDebug() << "打开学生文件失败";
    }




    QFile t_file(Teachers_File);
    if(t_file.open(QIODevice::ReadOnly | QIODevice::Text))// 只读方式
    {
//        qDebug() << t_file.readAll();
        display_t->setText(QString(t_file.readAll()));
    }
    else
    {
        qDebug() << "打开教师文件失败！";
    }


    s_file.close();
    t_file.close();

    qwidget_all->show();
}

// 查看所有人的预约信息
void Manager_Class::check_order()
{
    qDebug() << "查看所有预约";
    this->hide();

    static bool exist_qwidget_all = false;
    static QWidget * qwidget_all = new QWidget;
    static QTextEdit * display_all_order = new QTextEdit(qwidget_all);

    if(exist_qwidget_all == false)
    {
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

        exist_qwidget_all = true;
    }

    display_all_order->clear();

    QString str /*= "订单编号 学号 姓名 日期 时间段 地点 预约状态\n"*/;

    for(int i = 0;i < this->m_order_num;i++)
    {

        str += QString::number(i+1) + " "
                + (*this->m_order_data)[i]["学号"] + " "
                + (*this->m_order_data)[i]["姓名"] + " "
                + (*this->m_order_data)[i]["日期"] + " "
                + (*this->m_order_data)[i]["时间段"] + " "
                + (*this->m_order_data)[i]["地点"] + " ";

        if((*this->m_order_data)[i]["状态"] == "1")
        {
            str += "审核中";
        }
        else if((*this->m_order_data)[i]["状态"] == "0")
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

void Manager_Class::add_qwidget(int p_type)
{
    QWidget * qwidget_add = new QWidget;
    qwidget_add->setFixedSize(300,200);
    QLabel * label_id = new QLabel;

    if(p_type == 1)
    {
        qwidget_add->setWindowTitle("添加学生账号");
        label_id->setText("请输入学号：");
    }
    else
    {
        qwidget_add->setWindowTitle("添加老师账号账号");
        label_id->setText("请输入职工号：");
    }

    label_id->setFixedSize(qwidget_add->width() * 0.3,20);

    QLineEdit * line_edit_id = new QLineEdit;
    line_edit_id->setFixedSize(qwidget_add->width() * 0.6, 20);

    // 将id和输入id 水平布局
    QHBoxLayout * layout_id = new QHBoxLayout;
    layout_id->addWidget(label_id);
    layout_id->addWidget(line_edit_id);


    QLabel * label_name = new QLabel;
    label_name->setText("请输入姓名：");
    label_name->setFixedSize(qwidget_add->width() * 0.3,20);

    QLineEdit * line_edit_name = new QLineEdit;
    line_edit_name->setFixedSize(qwidget_add->width() * 0.6, 20);

    // 将姓名和输入姓名 水平布局
    QHBoxLayout * layout_name = new QHBoxLayout;
    layout_name->addWidget(label_name);
    layout_name->addWidget(line_edit_name);


    QLabel * label_password = new QLabel;
    label_password->setText("请输入密码：");
    label_password->setFixedSize(qwidget_add->width() * 0.3,20);

    QLineEdit * line_edit_password = new QLineEdit;
    line_edit_password->setFixedSize(qwidget_add->width() * 0.6, 20);

    // 将密码和输入密码 水平布局
    QHBoxLayout * layout_password = new QHBoxLayout;
    layout_password->addWidget(label_password);
    layout_password->addWidget(line_edit_password);

    // 添加确认按钮和返回按钮,并水平布局
    QPushButton * yes_btn = new QPushButton;
    yes_btn->setText("确认");
    yes_btn->setFixedSize(100,40);

    QPushButton * back_btn = new QPushButton;
    back_btn->setText("退出");
    back_btn->setFixedSize(100,40);

    QHBoxLayout * layout_btn = new QHBoxLayout;
    layout_btn->addWidget(yes_btn);
    layout_btn->addWidget(back_btn);


    // 将id，姓名，密码，按钮 垂直布局
    QVBoxLayout * layout = new QVBoxLayout;
    layout->addLayout(layout_id);
    layout->addLayout(layout_name);
    layout->addLayout(layout_password);
    layout->addLayout(layout_btn);

    // 设置布局
    qwidget_add->setLayout(layout);

    connect(back_btn,back_btn->clicked,[=]{
        qDebug() << "返回";
        qwidget_add->hide();
        this->add_people();
    });

    connect(yes_btn,yes_btn->clicked,[=]{
        qDebug() << "正确";
        // 获取输入的id，姓名，密码,追加到相应的文件
        QString file_path;
        QString array;
        if(p_type == 1)// 学生
        {
            file_path = Students_File;
        }
        else// 老师
        {
            file_path = Teachers_File;
        }

        array = line_edit_id->text() + " " +
                line_edit_name->text() + " " +
                line_edit_password->text();

        QFile file(file_path);
        if(file.open(QIODevice::WriteOnly | QIODevice::Append))
        {
            file.write(array.toUtf8().data());
            file.write("\r\n");// 文件换行
            QMessageBox::information(qwidget_add,"添加信息","添加成功！");
        }
        else
        {
            QMessageBox::critical(qwidget_add,"添加信息","添加失败！");
//            qDebug() << "打开失败";
        }

        file.close();


//        qDebug() << "添加成功！";
    });

    qwidget_add->show();
}
