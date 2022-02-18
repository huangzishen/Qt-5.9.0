#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
#include<QDebug>
#include<QLabel>
#include<QPushButton>
#include<QPainter>
#include <QFont>
#include "login.h"
#include <manager_class.h>
#include <teacher_class.h>
#include <student_class.h>
#include "login.h"
#include "files.h"
#include <QDir>
#include <QFile>
#include <QMessageBox>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->is_file_exist();


    // 设置标题
    this->setWindowTitle("机房预约订单系统");

    // 登入界面大小
    this->setFixedSize(600,300);

    // 登入界面文字
    QLabel * label = new QLabel(this);

    // 字体设置
    QFont font;
    font.setFamily("宋体");
    font.setPointSize(20);// 设置字体大小
    font.setUnderline(true);// 添加文字下划线

    label->setFont(font);
    label->setText("欢迎来到机房预约订单系统");
    label->setFixedSize(400,30);
    label->move((this->width()-label->width()) * 0.5, 40);

    // 设置label上的文字对齐方式：水平剧中和垂直剧中
    label->setAlignment((Qt::AlignHCenter | Qt::AlignVCenter));



    QPixmap pix;
    // 学生登录按钮
    QPushButton * s_login_btn = new QPushButton;
    s_login_btn->setParent(this);
    s_login_btn->setText("学生登入");
    s_login_btn->move(130,150);

    // 添加背景图片
//    pix.load(":/res/s_login_btn_picture.jpeg");
//    pix.scaled(pix.width()*0.5,pix.height()*0.5);
//    s_login_btn->move(100,100);
//    s_login_btn->setFixedSize(pix.width(),pix.height());// 设置图片固定大小
//    s_login_btn->setStyleSheet("QPushButton{border:0px;}");// 设置不规则图片样式
//    s_login_btn->setIcon(pix);// 设置图标
//    s_login_btn->setIconSize(QSize(pix.width(),pix.height()));// 图标大小


    // 连接学生登入
    connect(s_login_btn,s_login_btn->clicked,[=]()
    {
        qDebug() << "学生登入!";
        this->hide();

        // 弹出对话框，输入学号，姓名，和学号
        Login * login = new Login(1);
        login->show();

        // 监听登入界面发出的退出信号
        connect(login,login->back_first_scence,[=](){
            login->hide();
            this->show();
        });

        // 监听登入界面发出的确认信号
        connect(login,login->info_yes,[=](){
            login->is_exist();
            if(login->successed == true)
            {
                qDebug() << "输入正确";
                login->hide();
                Student_Class * student = new Student_Class(login->id,login->name,login->password);
                student->s_order_data = &this->order_data;
                student->m_order_num = this->m_order_num;
                student->show();

                connect(student,student->back_first_scence,[=]()
                {
                    student->close();
                    delete student;
//                    student = NULL;
                    this->show();
                });
            }
            else
            {
                // 错误对话框
                QMessageBox::critical(this,"登入提示","输入有误！");
//                qDebug() << "输入有误";
            }
        });

    });

    // 教师登录按钮登录按钮
    QPushButton * t_login_btn = new QPushButton;
    t_login_btn->setParent(this);
    t_login_btn->setText("教师登入");
    t_login_btn->move(260,150);


    connect(t_login_btn,t_login_btn->clicked,[=]()
    {
        qDebug() << "教师登入!";
        this->hide();

        // 弹出对话框，输入职工号，姓名，和密码
        Login * login = new Login(2);
        login->show();

        // 监听登入界面发出的退出信号
        connect(login,login->back_first_scence,[=](){
            login->hide();
            this->show();
        });

        // 监听登入界面发出的确认信号
        connect(login,login->info_yes,[=](){
            login->is_exist();
            if(login->successed == true)
            {
//                qDebug() << "正确！";
                login->hide();
                Teacher_Class * teacher = new Teacher_Class(login->id,login->name,login->password);
                teacher->t_order_data = &this->order_data;
                teacher->m_order_num = this->m_order_num;
                teacher->show();

                connect(teacher,teacher->back_first_scence,[=]()
                {
                    teacher->close();
                    delete teacher;
//                    teacher = NULL;
                    this->show();
                });
            }
            else
            {
                // 弹出对话框
                QMessageBox::critical(this,"登入提示","输入有误");
//                qDebug() << "输入有误";
            }
        });



    });

    // 管理员登录按钮
    QPushButton * m_login_btn = new QPushButton;
    m_login_btn->setParent(this);
    m_login_btn->setText("管理员登入");
    m_login_btn->move(400,150);

    connect(m_login_btn,m_login_btn->clicked,[=]()
    {
        qDebug() << "管理员登入!";
        this->hide();

        // 弹出对话框，输入姓名，和密码
        Login * login = new Login(3);
        login->show();

        // 监听登入界面发出的退出信号
        connect(login,login->back_first_scence,[=](){
            login->hide();
            this->show();
        });

        // 监听登入界面发出的确认信号
        connect(login,login->info_yes,[=](){
            login->is_exist();
            if(login->successed == true)
            {
//                qDebug() << "输入正确";
                login->hide();// 隐藏登入界面
                // 姓名密码都正确，进入管理员界面
                Manager_Class * manager = new Manager_Class(login->name,login->password);
                manager->m_order_data = &this->order_data;
                manager->m_order_num = this->m_order_num;
                manager->show();

                connect(manager,manager->back_first_scence,[=](){
                    manager->hide();
                    delete manager;
//                    manager = NULL;
                    this->show();
                });
            }
            else
            {
                QMessageBox::critical(this,"登入提示","输入有误");
//                qDebug() << "输入有误";
            }
        });
    });


    // 退出按钮
    QPushButton * quit_system = new QPushButton;
    quit_system->setParent(this);
    quit_system->setText("退出");
    quit_system->setFixedSize(120,40);
    quit_system->move((this->width()-quit_system->width())*0.5,(this->height()-quit_system->height())*0.9);




    // 按下退出按钮即关闭登入系统
    connect(quit_system,quit_system->clicked,[=]()
    {
        this->close();
    });


    // 读取文件里的数据，保存到map容器中,方便后续的修改
    this->m_order_num = 0;// 一开始为0条数据
    QFile file(Orders_File);
    QByteArray array;// 保存每行读取的数据
    QString m_id;
    QString m_name;
    QString m_week;
    QString m_day;
    QString m_pos;
    QString m_status;

    QMap<QString,QString> map;
    if(file.open(QIODevice::ReadOnly))
    {
//        qDebug() << file.pos();
        // 先判断文件是否为空
        if(file.size())
        {
            while (!file.atEnd())
            {
                int start_pos = 0;
                int end_pos;

                // 每行的数据为 学号，姓名，日期，时间段，地点，预约状态（1为审核中，0为审核通过，-1为不通过）
                array = file.readLine();
                array = array.mid(0,array.indexOf("\r"));

                // 提取学号信息
                end_pos = array.indexOf(" ",start_pos);//学号的结束位置
                m_id = array.mid(start_pos,end_pos);// 获取学号

                // 提取姓名信息
                start_pos = array.indexOf(" ",end_pos+1);//姓名的结束位置
                m_name = array.mid(end_pos+1,start_pos-end_pos-1);//获取姓名

                // 提取日期信息
                end_pos = array.indexOf(" ",start_pos+1);// 日期的结束位置
                m_week = array.mid(start_pos+1,end_pos-start_pos-1);//获取日期

                // 提取时间段信息
                start_pos = array.indexOf(" ",end_pos+1);// 时间段的结束位置
                m_day = array.mid(end_pos+1,start_pos-end_pos-1);// 获取时间段

                // 提取地点信息
                end_pos = array.indexOf(" ",start_pos+1);// 地点的结束位置
                m_pos = array.mid(start_pos+1,end_pos-start_pos-1);// 获取地点

                // 提取状态信息
                start_pos = array.indexOf(" ",end_pos+1);// 状态的结束位置
                m_status = array.mid(end_pos+1,start_pos-end_pos-1);// 获取状态

    //            if(m_status == "1")
    //            {
    //                m_status = "审核中";
    //            }
    //            else if(m_status == "0")
    //            {
    //                m_status = "审核通过";
    //            }
    //            else
    //            {
    //                m_status = "审核不通过";
    //            }

    //            qDebug() << m_id.toUtf8().data() << " "
    //                     << m_name.toUtf8().data() << " "
    //                     << m_week.toUtf8().data() << " "
    //                     << m_day.toUtf8().data() << " "
    //                     << m_pos.toUtf8().data() << " "
    //                     << m_status.toUtf8().data();

                map.insert("学号",m_id);
                map.insert("姓名",m_name);
                map.insert("日期",m_week);
                map.insert("时间段",m_day);
                map.insert("地点",m_pos);
                map.insert("状态",m_status);
                this->order_data.insert(this->m_order_num,map);
                this->m_order_num++;

                map.clear();

            }
        }
        else
        {
            qDebug() << "文件为空";

        }


        qDebug() << "加载结束!";
    }
    else
    {
        qDebug() << "文件打开失败!";
    }

    file.close();


}

void Widget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/login_picture.jpeg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}

// 检查学生，教师，管理员，订单文件是否存在，不存在就在当前路径下创建
void Widget::is_file_exist()
{
    QStringList files_list;
    files_list<<Students_File<<Teachers_File<<Managers_File<<Orders_File;

    QDir tmp_check;
//    qDebug() << files_list.size();
//    qDebug() << tmp_check.currentPath();
    for(int i = 0;i < files_list.size();i++)
    {
        QFile file(files_list.at(i));
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        if(files_list.at(i) == Managers_File && file.size() == 0)
        {
            file.write(QByteArray("-1 admin 123456\r\n"));// 初始化管理员文件，由该默认管理员创建教师，学生账号
        }
        file.close();
    }

//    qDebug() << "初始化文件完成";

}

Widget::~Widget()
{
    delete ui;
}
