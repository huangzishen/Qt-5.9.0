#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

class Login : public QWidget
{
    Q_OBJECT
public:
//    explicit Login(QWidget *parent = nullptr);

    Login(int p_type);// 登入类型 1.学生 2.教师 3.管理员

    // 登入是否成功
    void is_login();

public:
    int p_type;
    QString l_id;
    QString l_name;
    QString l_password;

    bool login_successed;

signals:
    // 自定义信号，确认和退出
    void info_yes();
    void back_first_scence();

public slots:
};

#endif // LOGIN_H
