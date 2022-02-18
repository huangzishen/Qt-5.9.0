#include "manager.h"

//Manager::Manager(QWidget *parent) : QWidget(parent)
//{

//}


Manager::Manager(QString m_name,QString m_password)
{
    this->name = m_name;
    this->password = m_password;
    this->login_infos();

    // 生成管理员界面
    // 设置标题
    this->setWindowTitle("管理员");

    // 设置固定大小
    this->setFixedSize(600,300);

    // 界面文字
    QLabel * label = new QLabel;

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
    back_btn->setText("注销登录");
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
    add_people_btn->move(QPoint(40,150));

    connect(add_people_btn,add_people_btn->clicked,[=](){
        this->add_people();
    });

    // 查看所有人信息按钮
    QPushButton * check_info_btn = new QPushButton;
    check_info_btn->setParent(this);
    check_info_btn->setText("查看所有人信息");
    check_info_btn->setFixedSize(100,30);
    check_info_btn->move(QPoint(160,150));

    connect(check_info_btn,check_info_btn->clicked,[=](){
        this->check_info();
    });

    // 查看所有人的预约信息
    QPushButton * check_order_btn = new QPushButton;
    check_order_btn->setParent(this);
    check_order_btn->setText("查看所有预约信息");
    check_order_btn->setFixedSize(120,30);
    check_order_btn->move(QPoint(280,150));

    // 清空预约记录按钮
    QPushButton * clear_order_btn = new QPushButton;
    clear_order_btn->setParent(this);
    clear_order_btn->setText("清空预约记录");
    clear_order_btn->setFixedSize(120,30);
    clear_order_btn->move(QPoint(440,150));

    connect(clear_order_btn,clear_order_btn->clicked,[=](){
        this->clear_order();
    });

    this->show();

}

void Manager::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/2_login_picture.jpeg");
    painter.drawPixmap(0,0,pix.width(),pix.height(),pix);
}

// 添加账号
void Manager::add_people()
{
    this->hide();
//    qDebug() << "添加账号";
    QWidget * qwidget_1 = new QWidget;
    qwidget_1->setWindowTitle("添加账号");
    qwidget_1->setFixedSize(300,200);

    // 创建菜单栏
    QMenuBar * bar = new QMenuBar(qwidget_1);

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
        qwidget_1->hide();
//        qDebug() << "添加老师账号";
        this->add_qwidget(2);
    });

    connect(add_student,add_student->clicked,[=](){
        qwidget_1->hide();
//        qDebug() << "添加学生账号";
        this->add_qwidget(1);
    });

    connect(this,this->back_login,[=](){
        qwidget_1->show();
    });

    qwidget_1->show();
}

// 添加账号的窗口 1:学生，2:老师
void Manager::add_qwidget(int p_type)
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


    connect(yes_btn,yes_btn->clicked,[=](){
        this->save_info(p_type,line_edit_id->text(),line_edit_name->text(),line_edit_password->text(),qwidget_add);
    });

    QPushButton * back_btn = new QPushButton;
    back_btn->setText("退出");
    back_btn->setFixedSize(100,40);

    connect(back_btn,back_btn->clicked,[=](){
        qwidget_add->hide();
        emit this->back_login();
    });

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

    qwidget_add->show();
}

// 查看所有人账号信息
void Manager::check_info()
{
    this->hide();

    QWidget * qwidget_all = new QWidget;

    // 显示信息
    QTextEdit * display_s = new QTextEdit;
    QTextEdit * display_t = new QTextEdit;

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

    // 加载显示信息

    QString t_array = "";
    QString s_array = "";

    QMap<int,QMap<QString,QString>>::iterator it;
    for(it = this->teachers_infos.begin();it != this->teachers_infos.end();it++)
    {
        // | 学号 |             | 姓名 |            | 密码 |
        t_array += QString((*it)["职工号"] + " " + (*it)["姓名"] + " " + (*it)["密码"] + "\n");
    }

    display_t->setText(t_array);

    for(it = this->students_infos.begin();it != this->students_infos.end();it++)
    {
        s_array += QString((*it)["学号"] + " " + (*it)["姓名"] + " " + (*it)["密码"] + "\n");
    }

    display_s->setText(s_array);


    qwidget_all->show();
}

// 查看所有人的预约信息
void Manager::check_order()
{
//    qDebug() << "查看所有人的预约信息";
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

    for(int i = 0;i < this->m_order_data->size();i++)
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
        else if((*this->m_order_data)[i]["状态"] == "2")
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

// 加载老师学生的账号信息
void Manager::login_infos()
{
    // 加载老师的账号信息
    QFile t_file(Teachers_File);
    if(t_file.open(QIODevice::ReadOnly))
    {
        if(t_file.size() == 0)
        {
//            qDebug() << "教师文件为空！";
            return;
        }

        QString t_id;
        QString t_name;
        QString t_password;

        QMap<QString,QString> t_map;
        QByteArray t_array;
        for(int i = 0;;i++)
        {
            // 文件按行读取，读取完退出循环
            if(t_file.atEnd())
            {
                break;
            }

            t_array = t_file.readLine();

            if(t_array.size() == 0)
            {
                i--;
                continue;
            }

            t_array = t_array.mid(0,t_array.indexOf("\r"));
//            qDebug() << t_array;

            // 提取职工号
            t_id = t_array.mid(0,t_array.indexOf(" ",0));

            // 提取姓名
            t_name = t_array.mid(t_array.indexOf(" ",0) + 1,t_array.indexOf(" ",t_array.indexOf(" ",0) + 1) - t_array.indexOf(" ",0) - 1);

            // 提取密码
            t_password = t_array.mid(t_array.indexOf(" ",t_array.indexOf(" ",0) + 1) + 1,t_array.size() - t_array.indexOf(" ",t_array.indexOf(" ",0) + 1));

//            qDebug() << t_id << " " << t_name << " " << t_password;

            t_map.insert("职工号",t_id);
            t_map.insert("姓名",t_name);
            t_map.insert("密码",t_password);

            this->teachers_infos.insert(i,t_map);

        }
    }

    // 加载学生的账号信息
    QFile s_file(Students_File);
    if(s_file.open(QIODevice::ReadOnly))
    {
        if(s_file.size() == 0)
        {
//            qDebug() << "学生文件为空！";
            return;
        }

        QString s_id;
        QString s_name;
        QString s_password;

        QMap<QString,QString> s_map;
        QByteArray s_array;
        for(int i = 0;;i++)
        {
            // 文件按行读取，读取完退出循环
            if(s_file.atEnd())
            {
                break;
            }

            s_array = s_file.readLine();

            if(s_array.size() == 0)
            {
                i--;
                continue;
            }

            s_array = s_array.mid(0,s_array.indexOf("\r"));
//            qDebug() << s_array;

            // 提取学号
            s_id = s_array.mid(0,s_array.indexOf(" ",0));

            // 提取姓名
            s_name = s_array.mid(s_array.indexOf(" ",0) + 1,s_array.indexOf(" ",s_array.indexOf(" ",0)+1) - s_array.indexOf(" ",0) - 1);

            // 提取密码
            s_password = s_array.mid(s_array.indexOf(" ",s_array.indexOf(" ",0) + 1) + 1,s_array.size() - s_array.indexOf(" ",s_array.indexOf(" ",0) + 1));

//            qDebug() << s_id << " " << s_name << " " << s_password;

            s_map.insert("学号",s_id);
            s_map.insert("姓名",s_name);
            s_map.insert("密码",s_password);

            this->students_infos.insert(i,s_map);

        }
    }
}


// 清空预约记录
void Manager::clear_order()
{
//    qDebug() << "清空预约记录";

    QFile file(Orders_File);
    if(file.open(QIODevice::Truncate | QIODevice::WriteOnly))
    {
        QMessageBox::information(this,"清空预约记录","清空成功！");
    }
    else
    {
        QMessageBox::critical(this,"清空预约记录","清空失败！");
    }

    file.close();

}

// 保存添加进来的信息
void Manager::save_info(int p_type, QString m_id, QString m_name, QString m_password, QWidget * parent)
{
    QMap<int,QMap<QString,QString>>::iterator it;
    if(p_type == 1)
    {
        // 判断学号信息是否存在
        for(it = this->students_infos.begin();it != this->students_infos.end();it++)
        {
            if( (*it)["学号"] == m_id )
            {
                QMessageBox::information(parent,"提示","该学生已存在！");
                break;
            }
        }

        // 若信息不存在就保存信息
        if(it == this->students_infos.end())
        {
            QMap<QString,QString> map;
            map.insert("学号",m_id);
            map.insert("姓名",m_name);
            map.insert("密码",m_password);

            this->students_infos.insert(this->students_infos.size(),map);
            this->update_infos(p_type,m_id,m_name,m_password,parent);
        }
    }
    else
    {
        // 判断学号信息是否存在
        for(it = this->teachers_infos.begin();it != this->teachers_infos.end();it++)
        {
            if( (*it)["职工号"] == m_id )
            {
                QMessageBox::information(parent,"提示","该教师已存在！");
                break;
            }
        }

        // 若信息不存在就保存信息
        if(it == this->teachers_infos.end())
        {
            QMap<QString,QString> map;
            map.insert("职工号",m_id);
            map.insert("姓名",m_name);
            map.insert("密码",m_password);

            this->teachers_infos.insert(this->teachers_infos.size(),map);
            this->update_infos(p_type,m_id,m_name,m_password,parent);
        }
    }
}


// 更新添加进来的信息 1，学生 2，教师
void Manager::update_infos(int p_type, QString m_id, QString m_name, QString m_password, QWidget * parent)
{
    QString file_path;
    if(p_type == 1)
    {
        file_path = Students_File;
    }
    else
    {
        file_path = Teachers_File;
    }

    QFile file(file_path);
    if(file.open(QIODevice::Append | QIODevice::Text))
    {
//        file.write("\r\n");
        file.write(QString("%1 %2 %3\r\n").arg(m_id,m_name,m_password).toUtf8());
        QMessageBox::information(parent,"提示","添加成功");
    }
    else
    {
        QMessageBox::critical(parent,"错误","添加失败");
    }

    file.close();
}
