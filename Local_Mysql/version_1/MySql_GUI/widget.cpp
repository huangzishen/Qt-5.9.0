#include "widget.h"
#include "ui_widget.h"
#include <iterator>
#include <QSqlRecord>
#include <QSqlError>
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


    qDebug() << QSqlDatabase::drivers();

    // 连接本地数据库
    this->m_db = QSqlDatabase::addDatabase("QMYSQL");
    this->m_db.setHostName("127.0.0.1");

    // 默认输入
    ui->name_edit->setText("root");
    ui->password_edit->setEchoMode(QLineEdit::Password);
    ui->password_edit->setText("123");
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

//    qDebug() << "增加数据";

}

void Widget::on_drop_btn_clicked()
{
//    qDebug() << "删除数据";

}

void Widget::on_modifiy_btn_clicked()
{
//    qDebug() << "修改数据";

}

void Widget::on_select_btn_clicked()
{
    ui->textEdit->clear();

//    qDebug() << "查找数据";
    qDebug() << "主线程：" << QThread::currentThread();

    QSqlQuery query;
    if(query.exec(QString("desc %1;").arg(ui->comboBox->currentText())))
    {
        // 获取字段个数
        int num = query.size();

        QString line_array = "";

        query.exec(QString("select * from %1").arg(ui->comboBox->currentText()));
        while (query.next())
        {
            for(int i = 0;i < num;i++)
            {
                line_array += query.value(i).toString();
                line_array += " ";
            }
            ui->textEdit->append(line_array);
            line_array = "";
        }

    }
    else
    {
        QMessageBox::critical(this,"查询出错",query.lastError().text());
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

    for(QMap<QString,QString>::iterator it = this->table_type->begin();it != this->table_type->end();it++)
    {
        qDebug() << it.key() << " " << it.value();
    }
}

void Widget::on_table_btn_clicked()
{
    this->thread->start();

    emit this->start_thread(&this->m_db,ui->comboBox->currentText());

    ui->textEdit->clear();

}
