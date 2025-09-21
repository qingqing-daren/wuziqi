//#ifndef MAINWINDOW_H
//#define MAINWINDOW_H

//#include <QMainWindow>
//#include<QMouseEvent>
//#include "Board.h"



//QT_BEGIN_NAMESPACE
//namespace Ui { class MainWindow; }
//QT_END_NAMESPACE

//class MainWindow : public QMainWindow
//{
//    Q_OBJECT

//public:
//    MainWindow(QWidget *parent = nullptr);
//    ~MainWindow();

//protected:
//    //棋盘绘制函数
//    void paintEvent(QPaintEvent *event) override;
//    //鼠标移动事件函数（处理悬浮点）
//    void mouseMoveEvent(QMouseEvent *event) override;
//    // 鼠标点击事件函数（处理落子）
//        void mousePressEvent(QMouseEvent *event) override;

//private:
//    Ui::MainWindow *ui;
//    //棋盘规格
//    const int B_Size=15;
//    //单位间距
//    const int cellsize=60;
//    //棋盘左右间距
//    const int marginw=60;
//    //棋盘上下间距
//    const int marginh=40;
//    //计算棋盘起始位置函数
//    int getStartX() const {return marginw;};

//    int getStartY() const {return marginh;};

//    //悬停点
//    int row1=-1;
//    int col1=-1;
//    //是否需要绘制悬停点
//    bool flag=false;
//    Board gameBoard;

////    // 当前落子方（BLACK/WHITE，来自GameDef.h）
////    ChessColor currentColor;
////    // 游戏是否开始（可选，用于控制开局流程）
////        bool gameStarted;

//};
//#endif // MAINWINDOW_H
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include "Board.h"
#include "GameDef.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::MainWindow *ui;
    // 界面相关变量（仅你的职责）
    const int B_Size = 15;
    const int cellsize = 60;
    const int marginw = 40;
    const int marginh = 20;
    int row1 = -1;
    int col1 = -1;
    bool flag = false;
    // 协作变量（调用Board模块）
    Board gameBoard;

    // 辅助函数（界面相关）
    int getStartX() const { return marginw; }
    int getStartY() const { return marginh; }
    void updateStatusBar(); // 更新状态栏
};

#endif // MAINWINDOW_H
