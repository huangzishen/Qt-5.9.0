#ifndef MAINSCENCE_H
#define MAINSCENCE_H

#include <QMainWindow>
#include <QPainter>
#include "chooselevelsence.h"
namespace Ui {
class MainScence;
}

class MainScence : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScence(QWidget *parent = 0);
    ~MainScence();

    // 画家事件
    void paintEvent(QPaintEvent *event);

    ChooseLevelSence * chooseScene = NULL;

private:
    Ui::MainScence *ui;
};

#endif // MAINSCENCE_H
