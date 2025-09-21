//#include "mainwindow.h"
//#include "ui_mainwindow.h"
//#include "GameDef.h" // 新增：包含GameDef.h
//#include "Board.h"   // 新增：包含Board.h
//#include <QDebug>
//#include <QPainter>
//#include <QPen>

//MainWindow::MainWindow(QWidget *parent)
//: QMainWindow(parent)
//, ui(new Ui::MainWindow)
////, currentColor(BLACK)  // 初始化：黑先（符合规则）
////, gameStarted(true)    // 游戏默认开始
//{
//ui->setupUi(this);

//// 原有代码（鼠标追踪、窗口大小等）...
//this->centralWidget()->setMouseTracking(true);
//this->setMouseTracking(true);
//int windowWidth = cellsize*(B_Size-1) + 2*marginw;
//int windowHeight = cellsize*(B_Size-1) + 2*marginh;
//this->setFixedSize(windowWidth, windowHeight);
//setWindowTitle("五子棋");

//}

//void MainWindow::paintEvent(QPaintEvent *event)
//{
//    //调用父类的paintEvent函数，确保窗口正常刷新
//    QMainWindow::paintEvent(event);//Qt绘图规范，必须放在最前面

//    //构建绘图工具，创建画家类
//   QPainter painter(this);


//   //设置抗锯齿
//   painter.setRenderHint(QPainter::Antialiasing,true);

//   //绘制棋盘背景
//    int bwidth=cellsize*(B_Size-1);      //计算棋盘长宽
//    int bheigth=cellsize*(B_Size-1);
//    painter.fillRect(getStartX(),getStartY(),bwidth,bheigth,QColor(227, 235, 205));

//    //创建画笔对象
//    QPen qpen;
//    qpen.setColor(Qt::black); // 画笔颜色设为黑色
//        qpen.setWidth(2);        // 线条宽度1像素
//        painter.setPen(qpen);    // 将画笔交给画家

//    // 绘制横线
//    for (int i = 0; i < B_Size; i++) {
//     painter.drawLine(
//                  getStartX(),          // 横线起点X（左边缘）
//                   getStartY() + i * cellsize,                // 横线Y坐标
//                   getStartX() + bwidth,  // 横线终点X（右边缘）
//                   getStartY() + i * cellsize                // 横线Y坐标（和起点相同，保证水平）
//               );
//           }

//     // 绘制竖线
//     for (int x = 0; x < B_Size; x++) {
//      painter.drawLine(
//      getStartX() + x * cellsize,                // 竖线X坐标
//      getStartY(),          // 竖线起点Y（上边缘）
//      getStartX() + x * cellsize,                // 竖线X坐标（和起点相同，保证垂直）
//      getStartY() + bheigth  // 竖线终点Y（下边缘）
//               );
//           }

//     //绘制天元和星位（围棋标准点位）
//         qpen.setWidth(10);         // 加粗画笔
//         painter.setPen(qpen);     // 更新画笔设置

//         // 画天元（7, 7）
//         painter.drawEllipse(QPoint(getStartX() + 7 * cellsize,getStartY() + 7 * cellsize),
//                             3, 3);

//         // 四个星位（x=3,y=3；x=3,y=11；x=11,y=3；x=11,y=11）
//         painter.drawEllipse(QPoint(getStartX() + 3 * cellsize,getStartY() + 3 * cellsize),3,3);
//         painter.drawEllipse(QPoint(getStartX() + 3 * cellsize,getStartY() + 11 * cellsize),3,3);
//         painter.drawEllipse(QPoint(getStartX() + 11 * cellsize,getStartY() + 3 * cellsize),3,3);
//         painter.drawEllipse(QPoint(getStartX() + 11 * cellsize,getStartY() + 11 * cellsize),3,3);


//         // 绘制悬停点坐标
//         if(flag && (row1>=0 && row1<B_Size) && (col1>=0 && col1<B_Size) && (gameBoard.getChess(row1, col1) == EMPTY))
//         {
//             // 1. 保存当前画笔状态（避免影响后续绘图，比如棋子、天元）
//             painter.save();

//             // 2. 设置悬停点样式：浅灰色实心圆（醒目且不刺眼）
//             QBrush hoverBrush(QColor(123,139,111,150));
//             QPen hoverPen(Qt::transparent);  // 隐藏边框（只显示填充色，更简洁）
//             painter.setBrush(hoverBrush);    // 应用画刷（填充色）
//             painter.setPen(hoverPen);        // 应用画笔（边框色）

//             // 3. 计算悬停点坐标（和棋盘格子坐标保持一致，用getStartX()/getStartY()）
//             int hoverX = getStartX() + row1 * cellsize;
//             int hoverY = getStartY() + col1 * cellsize;
//             int hoverRadius = cellsize / 5;  // 悬停点半径

//             // 4. 绘制悬停点
//             painter.drawEllipse(QPoint(hoverX, hoverY), hoverRadius, hoverRadius);

//             // 5. 恢复之前的画笔状态（避免影响后续绘制，比如天元、棋子）
//             painter.restore();
//         }

//         for (int row = 0; row < B_Size; ++row) {  // 遍历棋盘行
//             for (int col = 0; col < B_Size; ++col) {  // 遍历棋盘列
//                 // 从Board中获取当前位置的棋子颜色
//                 ChessColor chessColor = gameBoard.getChess(row, col);

//                 // 只绘制有棋子的位置（非EMPTY）
//                 if (chessColor != EMPTY) {
//                     // 1. 保存当前绘图状态（避免影响其他元素）
//                     painter.save();

//                     // 2. 计算棋子在窗口中的坐标（和棋盘交叉点对齐）
//                     int chessX = getStartX() + row * cellsize;
//                     int chessY = getStartY() + col * cellsize;

//                     // 3. 设置棋子样式（黑棋/白棋区分）
//                     if (chessColor == BLACK) {
//                         // 黑棋：黑色填充，无额外边框（或黑色边框）
//                         painter.setBrush(Qt::black);          // 填充色（画刷）
//                         painter.setPen(QPen(Qt::black, 1));   // 边框色（画笔）
//                     } else {
//                         // 白棋：白色填充，黑色边框（区分棋盘背景）
//                         painter.setBrush(Qt::white);          // 填充色（画刷）
//                         painter.setPen(QPen(Qt::black, 1));   // 边框色（画笔，突出白棋）
//                     }

//                     // 4. 绘制圆形棋子：半径 = 格子一半 - 2（避免和网格线重叠）
//                     int chessRadius = cellsize / 2 - 2;
//                     painter.drawEllipse(
//                         QPoint(chessX, chessY),  // 棋子中心（棋盘交叉点）
//                         chessRadius,             // 水平半径
//                         chessRadius              // 垂直半径（和水平相同，保证正圆）
//                     );

//                     // 5. 恢复之前的绘图状态
//                     painter.restore();
//                 }
//             }
//         }
//}


//void MainWindow::mouseMoveEvent(QMouseEvent *event)
//{
//    int row = (event->x() - getStartX() + cellsize/2) / cellsize;
//    int col = (event->y() - getStartY() + cellsize/2) / cellsize;

//    if((row>=0 && row<B_Size) && (col>=0 && col<B_Size))
//    {
//        // 优化：只要在棋盘内，无论行列是否变化，都更新状态并触发重绘
//        row1 = row;
//        col1 = col;
//        flag = true;
//        update();  // 强制重绘，确保悬停点立即显示
//    }
//    else
//    {
//        flag = false;
//        row1 = -1;
//        col1 = -1;
//        update();
//    }
//}

//// mainwindow.cpp 新增鼠标点击事件函数
//void MainWindow::mousePressEvent(QMouseEvent *event)
//{
//    // 1. 只处理左键点击，且游戏已开始
//    if (event->button() != Qt::LeftButton || !gameStarted) {
//        return;
//    }

//    // 2. 将鼠标点击的屏幕坐标，转换为棋盘行列号（和悬停点逻辑一致）
//    int row = (event->x() - getStartX() + cellsize/2) / cellsize;
//    int col = (event->y() - getStartY() + cellsize/2) / cellsize;

//    // 3. 检查落子合法性：在棋盘内 + 该位置为空
//    bool isLegal = (row >= 0 && row < B_Size)
//                && (col >= 0 && col < B_Size)
//                && (gameBoard.getChess(row, col) == EMPTY);

//    if (isLegal) {
//        // 4. 合法则落子：调用Board的setChess存入棋子数据
//        gameBoard.setChess(row, col, currentColor);

//        // 5. 切换落子方（黑→白，白→黑）
//        currentColor = (currentColor == BLACK) ? WHITE : BLACK;

//        // 6. 触发重绘，让新落的棋子显示在界面上
//        update();
//    }
//}

//MainWindow::~MainWindow()
//{
//    delete ui;
//}
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GameDef.h"
#include "Board.h"
#include <QPainter>
#include <QPen>
#include <QMessageBox>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 开启鼠标追踪（悬停点功能需要）
    this->centralWidget()->setMouseTracking(true);
    this->setMouseTracking(true);

    // 设置窗口大小
    int windowWidth = cellsize * (B_Size - 1) + 2 * marginw;
    int windowHeight = cellsize * (B_Size - 1) + 2 * marginh;
    this->setFixedSize(windowWidth, windowHeight);
    setWindowTitle("五子棋");

    // 初始化状态栏显示
    updateStatusBar();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event); // 调用父类方法确保正常刷新
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿

    // 1. 绘制棋盘背景
    int bwidth = cellsize * (B_Size - 1);
    int bheight = cellsize * (B_Size - 1);
    painter.fillRect(getStartX(), getStartY(), bwidth, bheight, QColor(227, 235, 205));

    // 2. 绘制网格线
    QPen qpen(Qt::black, 2);
    painter.setPen(qpen);
    // 横线
    for (int i = 0; i < B_Size; ++i) {
        painter.drawLine(
            getStartX(),
            getStartY() + i * cellsize,
            getStartX() + bwidth,
            getStartY() + i * cellsize
        );
    }
    // 竖线
    for (int i = 0; i < B_Size; ++i) {
        painter.drawLine(
            getStartX() + i * cellsize,
            getStartY(),
            getStartX() + i * cellsize,
            getStartY() + bheight
        );
    }

    // 3. 绘制天元和星位
    qpen.setWidth(10);
    painter.setPen(qpen);
    // 天元（7,7）
    painter.drawEllipse(QPoint(getStartX() + 7 * cellsize, getStartY() + 7 * cellsize), 3, 3);
    // 星位（3,3）（3,11）（11,3）（11,11）
    painter.drawEllipse(QPoint(getStartX() + 3 * cellsize, getStartY() + 3 * cellsize), 3, 3);
    painter.drawEllipse(QPoint(getStartX() + 3 * cellsize, getStartY() + 11 * cellsize), 3, 3);
    painter.drawEllipse(QPoint(getStartX() + 11 * cellsize, getStartY() + 3 * cellsize), 3, 3);
    painter.drawEllipse(QPoint(getStartX() + 11 * cellsize, getStartY() + 11 * cellsize), 3, 3);

    // 4. 绘制悬停点（仅在空位置显示）
    if (flag && row1 >= 0 && row1 < B_Size && col1 >= 0 && col1 < B_Size
        && gameBoard.getChess(row1, col1) == EMPTY) {
        painter.save();
        QBrush hoverBrush(QColor(123, 139, 111, 150));
        painter.setBrush(hoverBrush);
        painter.setPen(Qt::transparent);
        int hoverX = getStartX() + row1 * cellsize;
        int hoverY = getStartY() + col1 * cellsize;
        painter.drawEllipse(QPoint(hoverX, hoverY), cellsize / 5, cellsize / 5);
        painter.restore();
    }

    // 5. 绘制棋子（数据完全来自Board）
    for (int row = 0; row < B_Size; ++row) {
        for (int col = 0; col < B_Size; ++col) {
            ChessColor color = gameBoard.getChess(row, col);
            if (color == EMPTY) continue;

            painter.save();
            int chessX = getStartX() + row * cellsize;
            int chessY = getStartY() + col * cellsize;
            int radius = cellsize / 2 - 2;

            // 黑棋/白棋样式区分
            if (color == BLACK) {
                painter.setBrush(Qt::black);
                painter.setPen(QPen(Qt::black, 1));
            } else {
                painter.setBrush(Qt::white);
                painter.setPen(QPen(Qt::black, 1));
            }

            painter.drawEllipse(QPoint(chessX, chessY), radius, radius);
            painter.restore();
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    // 计算悬停点坐标（仅处理界面坐标转换）
    int row = (event->x() - getStartX() + cellsize / 2) / cellsize;
    int col = (event->y() - getStartY() + cellsize / 2) / cellsize;

    if (row >= 0 && row < B_Size && col >= 0 && col < B_Size) {
        row1 = row;
        col1 = col;
        flag = true;
    } else {
        flag = false;
        row1 = col1 = -1;
    }
    update(); // 触发重绘
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // 仅处理左键点击且游戏在进行中
    if (event->button() != Qt::LeftButton || !gameBoard.isGameStarted()) {
        return;
    }

    // 转换点击坐标为棋盘行列
    int row = (event->x() - getStartX() + cellsize / 2) / cellsize;
    int col = (event->y() - getStartY() + cellsize / 2) / cellsize;

    // 调用Board接口处理落子逻辑（不关心内部规则）
    bool success = gameBoard.tryMove(row, col);

    if (!success) {
        // 落子失败：显示Board返回的错误原因
        QMessageBox::warning(this, "操作无效", gameBoard.getLastError());
    } else {
        // 落子成功：检查游戏结果
        GameResult result = gameBoard.getGameResult();
        if (result != NONE) {
            QString msg;
            switch (result) {
                case BLACK_WIN: msg = "黑方获胜！"; break;
                case WHITE_WIN: msg = "白方获胜！"; break;
                case BLACK_FORBIDDEN: msg = "黑方禁手负，白方获胜！"; break;
                case DRAW: msg = "平局！"; break;
                default: break;
            }
            QMessageBox::information(this, "游戏结束", msg);
        }
        // 更新界面状态
        updateStatusBar();
        update();
    }
}

void MainWindow::updateStatusBar()
{
    // 从Board获取当前游戏状态并显示
    GameStage stage = gameBoard.getCurrentStage();
    ChessColor turn = gameBoard.getCurrentTurn();

    QString stageText;
    switch (stage) {
        case STAGE1_BLACK1: stageText = "黑1落子（必须落天元）"; break;
        case STAGE2_WHITE2: stageText = "白2落子"; break;
        case STAGE3_BLACK3: stageText = "黑3落子（限5-9范围）"; break;
        case STAGE4_EXCHANGE: stageText = "三手交换，白方选择是否交换"; break;
        default: stageText = "正常对局";
    }

    QString turnText = (turn == BLACK) ? "黑方" : "白方";
    ui->statusbar->showMessage(QString("当前阶段：%1 | 当前回合：%2").arg(stageText).arg(turnText));
}

MainWindow::~MainWindow()
{
    delete ui;
}
