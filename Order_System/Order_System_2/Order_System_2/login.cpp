#include "login.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFile>
#include "files.h"
#include <QDebug>
//Login::Login(QWidget *parent) : QWidget(parent)
//{

//}

// 登入类型 1.学生 2.教师 3.管理员
Login::Login(int p_type)
{
    this->p_type = p_type;
    this->login_successed = false;

    this->setWindowTitle("登入");
    this->setFixedSize(300,180);

    // 生成登入界面
    // 非管理员登入
    if(this->p_type != 3)
    {

        // 学号
        QLabel * label_1 = new QLabel(this);
        if(this->p_type == 1)
        {
            label_1->setText("学 号：");
        }
        else
        {
            label_1->setText("职工号：");
        }

        label_1->setFixedSize(40,20);
        QLineEdit * line_1 = new QLineEdit(this);
        line_1->setFixedSize(this->width() / 4 * 3,20);

        QHBoxLayout * layout_1 = new QHBoxLayout;
        layout_1->addWidget(label_1);
        layout_1->addWidget(line_1);


        // 姓名
        QLabel * label_2 = new QLabel(this);
        label_2->setText("姓 名：");
        label_2->setFixedSize(40,20);
        QLineEdit * line_2 = new QLineEdit(this);
        line_2->setFixedSize(this->width() / 4 * 3,20);

        QHBoxLayout * layout_2 = new QHBoxLayout;
        layout_2->addWidget(label_2);
        layout_2->addWidget(line_2);


        // 密码
        QLabel * label_3 = new QLabel;
        label_3->setText("密 码：");
        label_3->setFixedSize(40,20);

        QLineEdit * line_3 = new QLineEdit;
        // 隐藏输入的密码
        line_3->setEchoMode(QLineEdit::Password);
        line_3->setFixedSize(this->width() / 4 * 3,20);

        QHBoxLayout * layout_3 = new QHBoxLayout;
        layout_3->addWidget(label_3);
        layout_3->addWidget(line_3);


        // 添加按钮，确认和退出
        QPushButton * yes_btn = new QPushButton;
        yes_btn->setText("确认");

        // 连接确认按钮
        connect(yes_btn,yes_btn->clicked,[=](){
            this->l_id = line_1->text();
            this->l_name = line_2->text();
            this->l_password = line_3->text();
            this->is_login();// 是否登入成功
            emit this->info_yes();
        });

        QPushButton * quit_btn = new QPushButton;
        quit_btn->setText("退出");

        // 连接退出按钮
        connect(quit_btn,quit_btn->clicked,[=](){
            emit this->back_first_scence();
        });

        // 测试
        line_1->setText("1");
        line_2->setText("h");
        line_3->setText("1");


        // 将两个按钮水平布局
        QHBoxLayout * layout_btn = new QHBoxLayout;
        layout_btn->addWidget(yes_btn);
        layout_btn->addWidget(quit_btn);


        // 整体布局
        QVBoxLayout * layout_4 = new QVBoxLayout(this);
        layout_4->addLayout(layout_1);
        layout_4->addLayout(layout_2);
        layout_4->addLayout(layout_3);
        layout_4->addLayout(layout_btn);

        // 将布局添加到窗口
        this->setLayout(layout_4);

    }
    else// 管理员登入页面加载
    {
        // 姓名
        QLabel * label_2 = new QLabel;
        label_2->setText("姓 名：");
        label_2->setFixedSize(40,20);
        QLineEdit * line_2 = new QLineEdit;
        line_2->setFixedSize(this->width() / 4 * 3,20);
        line_2->setText("admin");

        QHBoxLayout * layout_2 = new QHBoxLayout;
        layout_2->addWidget(label_2);
        layout_2->addWidget(line_2);


        // 密码
        QLabel * label_3 = new QLabel;
        label_3->setText("密 码：");
        label_3->setFixedSize(40,20);

        QLineEdit * line_3 = new QLineEdit;
        // 隐藏输入的密码
        line_3->setEchoMode(QLineEdit::Password);
        line_3->setText("123456");
        line_3->setFixedSize(this->width() / 4 * 3,20);

        QHBoxLayout * layout_3 = new QHBoxLayout;
        layout_3->addWidget(label_3);
        layout_3->addWidget(line_3);


        // 添加按钮，确认和退出
        QPushButton * yes_btn = new QPushButton;
        yes_btn->setText("确认");

        // 连接确认按钮
        connect(yes_btn,yes_btn->clicked,[=](){
            this->l_id = "-1";
            this->l_name = line_2->text();
            this->l_password = line_3->text();
            this->is_login();
            emit this->info_yes();
        });

        QPushButton * quit_btn = new QPushButton;
        quit_btn->setText("退出");

        // 连接退出按钮
        connect(quit_btn,quit_btn->clicked,[=](){
            emit this->back_first_scence();
        });

        // 将两个按钮水平布局
        QHBoxLayout * layout_btn = new QHBoxLayout;
        layout_btn->addWidget(yes_btn);
        layout_btn->addWidget(quit_btn);

        // 整体布局
        QVBoxLayout * layout_4 = new QVBoxLayout(this);
        layout_4->addLayout(layout_2);
        layout_4->addLayout(layout_3);
        layout_4->addLayout(layout_btn);

        // 将布局添加到窗口
        this->setLayout(layout_4);
    }

    this->show();
}

// 登入是否成功
void Login::is_login()
{
    // 文件路径
    QString file_path;

    if(this->p_type == 3)
    {
        // 代码中的默认管理员设置。 账号中姓名：admin，密码：123456
        if(this->l_name == "admin" && this->l_password == "123456")
        {
            this->login_successed = true;
            return;
        }
        else
        {
            file_path = Managers_File;
        }
    }
    else if(this->p_type == 2)
    {
        file_path = Teachers_File;
    }
    else
    {
        file_path = Students_File;
    }

    // 读取文件信息
    QFile file(file_path);

    file.open(QIODevice::ReadOnly);// 只读方式

    // 创建三个变量进行对比输入的信息
    QString m_id;
    QString m_name;
    QString m_password;

    QByteArray array = "";
    while(!file.atEnd())
    {
        int start_index = 0;// 需要截取的数据开始下标
        int end_index = 0;// 和结束下标
        array = file.readLine();// 一行一行读
        if(array.size() == 0)
        {
            continue;
        }
        array = array.mid(0,array.indexOf("\r"));

        // 获取每行中的详细数据
        end_index = array.indexOf(" ",start_index);// 2
        m_id = array.mid(start_index,end_index - start_index).data();

        start_index = array.indexOf(" ",end_index+1);// 8
        m_name = array.mid(end_index+1,start_index - end_index - 1).data();

        end_index = array.indexOf(" ",start_index+1);
        m_password = array.mid(start_index+1,end_index - start_index).data();


        // 判断信息是否正确
        if((this->l_id == m_id && this->l_name == m_name && this->l_password == m_password) && (m_id != " " && m_name != " " && m_password != " "))
        {
//            qDebug() << m_id << "\t" << m_name << "\t" << m_password;
            this->login_successed = true;
//            qDebug() << "信息正确";
            break;
        }
    }

    // 关闭文件
    file.close();
}
