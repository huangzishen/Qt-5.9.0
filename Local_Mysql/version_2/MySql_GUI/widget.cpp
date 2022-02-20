#include "widget.h"
#include "ui_widget.h"
#include <iterator>
#include <QSqlRecord>
#include <QSqlError>
#include <QDialog>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("本地MySql界面操作");

    QDesktopWidget * desktop = QApplication::desktop();

    // 未连接数据库，关闭，增删改查按钮,都不可使用
    ui->close_btn->setEnabled(false);
    ui->add_btn->setEnabled(false);
    ui->drop_btn->setEnabled(false);
    ui->modifiy_btn->setEnabled(false);
    ui->select_btn->setEnabled(false);
    ui->table_btn->setEnabled(false);

    // 位置在屏幕水平剧中，偏上方
    this->move((desktop->width() - this->width())/2,(desktop->height() - this->height()) * 0.1);
    this->setFixedSize(470,700);


//    qDebug() << QSqlDatabase::drivers();

    // 连接本地数据库
    this->m_db = QSqlDatabase::addDatabase("QMYSQL");
    this->m_db.setHostName("127.0.0.1");

    // 默认输入
    ui->name_edit->setText("root");
    ui->password_edit->setEchoMode(QLineEdit::Password);
    ui->password_edit->setText("hjh123789");
    ui->choose_edit->setText("text");


    // 关闭窗口时，若未关闭数据库连接就主动关闭与数据库的连接
    connect(this,this->destroyed,[=](){
        if(this->m_db.isOpen())
        {
            this->m_db.close();
        }
    });

    this->thread_fun = new MyThread;
    this->table_type = &this->thread_fun->table_type;

    // 创建子线程
    this->thread = new QThread(this);
    // 将线程处理函数加入到子线程
    this->thread_fun->moveToThread(this->thread);


    // 用信号 - 槽的方式连接子线程的线程处理函数
    connect(this,this->start_thread,this->thread_fun,this->thread_fun->table_struct);

    // 手动关闭子线程
    connect(this,this->stop_thread,[=](){
        this->thread->quit();
        this->thread->wait();
    });

    // 关闭窗口，若线程还没关闭，就关闭线程
    connect(this,this->destroyed,[=](){
        if(this->thread->isRunning())
        {
            this->thread->quit();
            this->thread->wait();
        }

        if(this->m_db.isOpen())
        {
            this->m_db.close();
        }
    });

    connect(this->thread_fun,this->thread_fun->isDone,this,this->deal_thread_done);


}

void Widget::paintEvent(QPaintEvent *)
{
    QPixmap pix;
    QPainter painter(this);

    pix.load(":/images/mysql_background.jpeg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_login_btn_clicked()
{
    // 获取登录名，密码，数据库
    this->m_db.setUserName(ui->name_edit->text());
    this->m_db.setPassword(ui->password_edit->text());
    this->m_db.setDatabaseName(ui->choose_edit->text());
    if(this->m_db.open())
    {
        QMessageBox::information(this,"提示","数据库连接成功！");
    }
    else
    {
        QMessageBox::critical(this,"提示","数据库连接失败！");
        return;
    }

    // 添加当前数据库存在的表
    ui->comboBox->addItems(this->m_db.tables());

    // 成功连接数据库，关闭数据库可使用
    ui->close_btn->setEnabled(true);
    ui->table_btn->setEnabled(true);

    // 不能再次点击连接数据库
    ui->login_btn->setEnabled(false);


}

void Widget::on_close_btn_clicked()
{
    this->m_db.close();
    ui->comboBox->clear();
    QMessageBox::information(this,"提示","关闭数据库成功！");

    // 关闭数据库，所有按钮都不可用，除连接数据库按钮
    ui->close_btn->setEnabled(false);
    ui->add_btn->setEnabled(false);
    ui->drop_btn->setEnabled(false);
    ui->modifiy_btn->setEnabled(false);
    ui->select_btn->setEnabled(false);
    ui->table_btn->setEnabled(false);

    // 连接数据库 按钮可以使用
    ui->login_btn->setEnabled(true);

    ui->textEdit->clear();
}

void Widget::on_add_btn_clicked()
{
    // 创建添加数据的窗口
    QWidget * add_widget = new QWidget;
    add_widget->setWindowTitle("添加数据");

    // 设置模态
    add_widget->setWindowModality(Qt::ApplicationModal);

    // 关闭添加窗口，添加窗口上的控件将一起释放
    connect(add_widget,add_widget->destroyed,[=](){
        delete add_widget;
    });

    // 通过字段创建label，保存到QMap容器中,<QLabel地址,对应的QLineEdit地址>
//    QMap<QString,QMap<QLabel*,QLineEdit*>> qmap;
    int i = 0;
    QMap<QLabel*,QLineEdit*> map;
    QString sql = QString("insert into %1(").arg(ui->comboBox->currentText());
    for(QMap<QString,QString>::iterator it = this->table_type->begin();it != this->table_type->end();it++)
    {
        QLabel * label = new QLabel(add_widget);
        QLineEdit * edit = new QLineEdit(add_widget);
        map.insert(label,edit);
//        qmap.insert(it.key(),map);
//        map.clear();

        sql = sql + it.key() + ",";
        label->setText(it.key());
        label->setFixedSize(100,24);
        label->setAlignment(Qt::AlignHCenter);
        label->move(5 + i * 105,6);

        edit->setFixedSize(100,24);
        edit->move(label->x(),label->y() + label->height() + 4);



        i++;
    }

    sql = sql.left(sql.length() - 1) + ") values(";
//    qDebug() << sql;
    add_widget->setFixedSize(120*map.size(),120);

    // 添加按钮
    QPushButton * yes_btn = new QPushButton(add_widget);
    yes_btn->setText("确认添加");
    yes_btn->setFixedSize(60,30);
    yes_btn->move((add_widget->width() - yes_btn->width())/2, 80);

    connect(yes_btn,yes_btn->clicked,[=](){
        // 获取lindedit的内容
        QString tmp_sql(sql);
        for(QMap<QLabel*,QLineEdit*>::const_iterator it = map.begin();it != map.end();it++)
        {
            tmp_sql = tmp_sql + it.value()->text() + ",";
        }

        tmp_sql = tmp_sql.left(tmp_sql.length() - 1) + ");";
        qDebug() << tmp_sql;

//        qDebug() << tmp_sql;

        // 执行sql添加语句
        QSqlQuery query;
        if(query.exec(tmp_sql))
        {
            QMessageBox::information(add_widget,"添加信息","添加成功！");

        }
        else
        {
            QMessageBox::critical(add_widget,"错误提示","有误");
        }

    });






    add_widget->show();
}

void Widget::on_drop_btn_clicked()
{
    // 创建删除数据的窗口
    QWidget * drop_widget = new QWidget;
    drop_widget->setWindowTitle("删除数据");
    drop_widget->setFixedSize(480,300);

    connect(drop_widget,drop_widget->destroyed,[=](){
        delete drop_widget;
    });

    // 设置模态
    drop_widget->setWindowModality(Qt::ApplicationModal);

    // 查找数据先
    QLabel * label = new QLabel(drop_widget);
    label->setFixedSize(100,24);
    label->setText("删除数据的信息：");
    label->move(6,6);

    QComboBox * box = new QComboBox(drop_widget);
    box->setFixedHeight(24);
    box->move(label->x() + label->width(),6);

    box->addItems(QStringList(this->table_type->keys()));

    QLineEdit * edit = new QLineEdit(drop_widget);
    edit->setFixedHeight(24);
    edit->move(box->x() + box->width(),6);

    // 添加确定按钮
    QPushButton * yes_btn = new QPushButton(drop_widget);
    yes_btn->setText("确定");
    yes_btn->setFixedHeight(24);
    yes_btn->move(drop_widget->width() - yes_btn->width(),6);

    // 添加显示信息
    QTextEdit * disploy_edit = new QTextEdit(drop_widget);
    disploy_edit->setReadOnly(true);
    disploy_edit->move(6,34);

    disploy_edit->setFixedSize(yes_btn->x() + yes_btn->width() - 10,drop_widget->height() - disploy_edit->y() - 4);


    connect(yes_btn,yes_btn->clicked,[=](){
       if(edit->text() != "")
       {
           QSqlQuery query;
           if(query.exec(QString("delete from %1 where %2=%3").arg(ui->comboBox->currentText()).arg(box->currentText()).arg(edit->text())))
           {
               QMessageBox::information(drop_widget,"提示","删除成功！");
           }

       }
       else
       {
           QMessageBox::warning(drop_widget,"警告","删除信息不能为空！");
       }
    });


    drop_widget->show();

}

void Widget::on_modifiy_btn_clicked()
{
    // 创建修改数据的窗口
    QWidget * modifiy_widget = new QWidget;
    modifiy_widget->setWindowTitle("修改数据");
    modifiy_widget->setFixedSize(400,300);

    modifiy_widget->setWindowModality(Qt::ApplicationModal);

    connect(modifiy_widget,modifiy_widget->destroyed,[=](){
        delete modifiy_widget;
    });

    QStringList box_list = QStringList(this->table_type->keys());

    // 搜索信息：添加label，下拉框和按钮
    QLabel * reserch_label = new QLabel(modifiy_widget);
    reserch_label->setText("搜索的关键字：");
    reserch_label->move(6,20);
    reserch_label->setFixedSize(130,22);
    QComboBox * box = new QComboBox(modifiy_widget);
    box->addItems(box_list);
    box->move(reserch_label->x() + reserch_label->width() + 4, reserch_label->y());
    QLineEdit * edit = new QLineEdit(modifiy_widget);
    edit->move(box->x() + box->width(),reserch_label->y());
    edit->setFixedSize(100,22);

    // 修改信息：添加label，下拉框和按钮
    QLabel * modify_label = new QLabel(modifiy_widget);
    modify_label->setText("修改的关键字：");
    modify_label->move(6,50);
    modify_label->setFixedSize(130,22);
    QComboBox * modifiy_box = new QComboBox(modifiy_widget);
    modifiy_box->addItems(box_list);
    modifiy_box->move(modify_label->x() + modify_label->width() + 4, modify_label->y());
    QLineEdit * modifiy_edit = new QLineEdit(modifiy_widget);
    modifiy_edit->move(modifiy_box->x() + modifiy_box->width(),modify_label->y());
    modifiy_edit->setFixedSize(100,22);

    // 添加按钮
    QPushButton * yes_btn = new QPushButton(modifiy_widget);
    QPushButton * back_btn = new QPushButton(modifiy_widget);
    yes_btn->setText("确认修改");
    back_btn->setText("返回");
    yes_btn->move(modifiy_widget->width() / 2 - yes_btn->width(),modifiy_widget->height() * 0.8);
    back_btn->move(modifiy_widget->width() / 2,modifiy_widget->height() * 0.8);

    connect(back_btn,back_btn->clicked,[=](){
        modifiy_widget->close();
    });

    connect(yes_btn,yes_btn->clicked,[=](){
        if(box->currentText() == modifiy_box->currentText())
        {
            QMessageBox::warning(modifiy_widget,"提示","搜索和修改的关键字不能一样！");
        }
        else
        {
            // 判断输入内容是否为空
            if(edit->text() == "" || modifiy_edit->text() == "")
            {
                QMessageBox::warning(modifiy_widget,"提示","输入不能为空！");
            }
            else
            {
                // 获取搜索的edit和修改的edit
                QString sql(QString("update %1 set %2=%3 where %4=%5;").arg(ui->comboBox->currentText()).arg(modifiy_box->currentText()).arg(modifiy_edit->text()).arg(box->currentText()).arg(edit->text()));
                qDebug() << sql;
                QSqlQuery query;
                if(query.exec(sql))
                {
                    QMessageBox::information(modifiy_widget,"提示","修改成功！");
                }
                else
                {
                    QMessageBox::critical(modifiy_widget,"提示","修改失败!");
                }

            }

        }

    });




    modifiy_widget->show();
}

void Widget::on_select_btn_clicked()
{
    ui->textEdit->clear();

//    qDebug() << "查找数据";
//    qDebug() << "主线程：" << QThread::currentThread();

    // 查找所有信息
    QSqlQuery query;
    if(query.exec(QString("select * from %1;").arg(ui->comboBox->currentText())))
    {
        // 判断该表是否有数据
        if(query.size() != 0)
        {
            QString str = "";
            while(query.next())
            {
                for(int i = 0;i < this->table_type->size();i++)
                {
                    str = str + query.value(i).toString() + " ";
                }
                ui->textEdit->append(str);
                str = "";
            }
        }
        else
        {
            ui->textEdit->append(QString("%1为空").arg(ui->comboBox->currentText()));
        }

    }
    else
    {
        QMessageBox::critical(this,"错误","查询语句有误！");
    }





}

void Widget::deal_thread_done()
{
    emit this->stop_thread();

    // 成功连接表以后，增删改查按钮可以使用
    ui->add_btn->setEnabled(true);
    ui->drop_btn->setEnabled(true);
    ui->modifiy_btn->setEnabled(true);
    ui->select_btn->setEnabled(true);

//    for(QMap<QString,QString>::iterator it = this->table_type->begin();it != this->table_type->end();it++)
//    {
//        qDebug() << it.key() << " " << it.value();
//    }
}

void Widget::on_table_btn_clicked()
{
    this->thread->start();

    emit this->start_thread(&this->m_db,ui->comboBox->currentText());

    ui->textEdit->clear();

}
