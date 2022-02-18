#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>


class Login:public QWidget
{
    Q_OBJECT
public:
//    explicit Login(QWidget * parent = 0);
    Login(int p_type);

    void login();

    // 验证输入的信息，在学生，教师，管理员文件中是否存在
    void is_exist();

public:
    int p_type;
    QString id;
    QString name;
    QString password;

    bool successed;





signals:
    // 自定义信号，确认和退出
    void info_yes();
    void back_first_scence();
};

#endif // LOGIN_H
