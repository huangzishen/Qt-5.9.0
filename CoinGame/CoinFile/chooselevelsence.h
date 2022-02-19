#ifndef CHOOSELEVELSENCE_H
#define CHOOSELEVELSENCE_H

#include <QMainWindow>
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QPainter>
#include<mybutton.h>
#include<QTimer>
#include<QLabel>
#include "playscence.h"
#include <QSound>
class ChooseLevelSence:public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelSence(QWidget * parent = 0);

    // 重载paintEvent
    void paintEvent(QPaintEvent *event);

    // 游戏场景对象的指针
    PlayScence * playscence = NULL;

signals:
    // 自定义信号，告诉主场景，点击了返回
    void choosesceneBack();

};

#endif // CHOOSELEVELSENCE_H
