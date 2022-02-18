#include "widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    this->com_1 = MAX_COMPUTER_1;
    this->com_2 = MAX_COMPUTER_2;
    this->com_3 = MAX_COMPUTER_3;

    ui->setupUi(this);

    // 检查学生，教师，管理员，订单文件是否存在，不存在就创建
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

    // 连接学生登入
    connect(s_login_btn,s_login_btn->clicked,[=](){
//        qDebug() << "学生登入";
        this->hide();
        Login * login = new Login(1);

        login->setAttribute(Qt::WA_DeleteOnClose);

        connect(login,login->back_first_scence,[=](){
            this->show();
            delete login;
        });

        // 若登入成功，发出信号，进入学生的界面
        connect(login,login->info_yes,[=](){
            if(login->login_successed == true)
            {
                login->hide();
                emit enter_student(login->l_id,login->l_name,login->l_password);
            }
            else
            {
                QMessageBox::critical(login,"错误","学号或姓名或密码错误!!!");
            }

        });
    });

    // 教师登录按钮登录按钮
    QPushButton * t_login_btn = new QPushButton;
    t_login_btn->setParent(this);
    t_login_btn->setText("教师登入");
    t_login_btn->move(260,150);

    // 连接教师登入
    connect(t_login_btn,t_login_btn->clicked,[=](){
//        qDebug() << "教师登入";
        this->hide();
        Login * login = new Login(2);

        login->setAttribute(Qt::WA_DeleteOnClose);

        connect(login,login->back_first_scence,[=](){
            this->show();
            delete login;
        });

        // 若登入成功，发出信号，进入教师的界面
        connect(login,login->info_yes,[=](){
            if(login->login_successed == true)
            {
                login->hide();
                emit enter_teacher(login->l_id,login->l_name,login->l_password);

            }
            else
            {
                QMessageBox::critical(login,"错误","职工号或姓名或密码错误!!!");
            }

        });
    });

    // 管理员登录按钮
    QPushButton * m_login_btn = new QPushButton;
    m_login_btn->setParent(this);
    m_login_btn->setText("管理员登入");
    m_login_btn->move(400,150);

    // 连接管理员登入
    connect(m_login_btn,m_login_btn->clicked,[=](){
//        qDebug() << "管理员登入";
        this->hide();
        Login * login = new Login(3);

        login->setAttribute(Qt::WA_DeleteOnClose);

        connect(login,login->back_first_scence,[=](){
            this->show();
            delete login;
        });

        // 若登入成功，发出信号，进入管理员的界面
        connect(login,login->info_yes,[=](){
            if(login->login_successed == true)
            {
                login->hide();
                emit this->enter_manager(login->l_name,login->l_password);
            }
            else
            {
                QMessageBox::critical(login,"错误","姓名或密码错误!!!");
            }

        });

    });

    // 退出按钮
    QPushButton * quit_system = new QPushButton;
    quit_system->setParent(this);
    quit_system->setText("退出");
    quit_system->setFixedSize(120,40);
    quit_system->move((this->width()-quit_system->width())*0.5,(this->height()-quit_system->height())*0.9);



    // 各自的操作界面
    connect(this,this->enter_student,this,this->student);
    connect(this,this->enter_teacher,this,this->teacher);
    connect(this,this->enter_manager,this,this->manager);


    // 按下退出按钮即关闭登入系统
    connect(quit_system,quit_system->clicked,[=]()
    {
        this->close();
    });



    // 读取订单文件里的数据，保存到map容器中
    this->m_order_num = 0;// 一开始为0条数据
    QByteArray array;// 保存每行读取的数据
    QString m_id;
    QString m_name;
    QString m_week;// 日期
    QString m_day;// 时间段
    QString m_pos;// 地点
    QString m_status;// 预约状态

    QMap<QString,QString> map;// 保存的是单挑数据

    // 开始文件读取
    QFile file(Orders_File);
    if(file.open(QIODevice::ReadOnly))// 只读
    {
        // 先判断文件是否为空
        if(file.size() != 0)
        {
            while (!file.atEnd())
            {
                int start_pos = 0;
                int end_pos;

                // 每行的数据为 学号，姓名，日期，时间段，地点，预约状态（1为审核中，0为审核通过，-1为不通过,-2为取消预约）
                array = file.readLine();
                if(array.size() == 2)
                {
                    continue;
                }
                else
                {
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

                    if(m_status == "0")
                    {
                        if(m_pos == "一号机房")
                        {
                            this->com_1--;
                        }
                        else if(m_pos == "二号机房")
                        {
                            this->com_2--;
                        }
                        else
                        {
                            this->com_3--;
                        }
                    }

                    map.insert("学号",m_id);
                    map.insert("姓名",m_name);
                    map.insert("日期",m_week);
                    map.insert("时间段",m_day);
                    map.insert("地点",m_pos);
                    map.insert("状态",m_status);

                    this->order_data.insert(this->m_order_num,map);
                    this->m_order_num++;

                    map.clear();// 为下次添加做清空

                }

            }
        }
    }

    file.close();

//    qDebug() << "-------------- 加载 ------------------";
//    qDebug() << "一号机房剩余：" << this->com_1
//             << "二号机房剩余：" << this->com_2
//             << "三号机房剩余：" << this->com_3;
}


// 重写,登入界面背景加载
void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/login_picture.jpeg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

// 检查学生，教师，管理员，订单文件是否存在
void Widget::is_file_exist()
{
    QStringList files_list;
    files_list<<Students_File<<Teachers_File<<Managers_File<<Orders_File;

    QDir tmp_check;
    if(tmp_check.exists("files") == false)
    {
        tmp_check.mkdir("files");// 创建文件夹
        tmp_check.setCurrent(tmp_check.currentPath() + "/files");// 修改当前路径
//        qDebug() << tmp_check.currentPath();
    }


    for(int i = 0;i < files_list.size();i++)
    {
        QFile file(files_list.at(i));
        file.open(QIODevice::ReadWrite);
        file.close();
    }

}


// 进入学生
void Widget::student(QString id, QString name,QString password)
{
//    qDebug() << "进入学生界面";
    Student * s = new Student(id,name,password);
    s->s_order_data = &this->order_data;
    s->com_1 = &this->com_1;
    s->com_2 = &this->com_2;
    s->com_3 = &this->com_3;
    s->show();

    // 返回初始化场景
    connect(s,s->back_first_scence,[=](){
        s->hide();
        this->show();
    });
}

// 进入教师
void Widget::teacher(QString id, QString name,QString password)
{
//    qDebug() << "进入教师界面";
    Teacher * t = new Teacher(id,name,password);
    t->t_order_data = &this->order_data;
    t->com_1 = &this->com_1;
    t->com_2 = &this->com_2;
    t->com_3 = &this->com_3;
    t->show();

    // 返回初始化场景
    connect(t,t->back_first_scence,[=](){
        t->hide();
        this->show();
    });
}

// 进入管理员
void Widget::manager(QString name,QString password)
{
//    qDebug() << "进入管理员界面";
    Manager * m = new Manager(name,password);
    m->m_order_data = &this->order_data;

    m->show();

    // 返回初始化场景
    connect(m,m->back_first_scence,[=](){
        m->hide();
        this->show();
    });
}

Widget::~Widget()
{
    delete ui;
}
