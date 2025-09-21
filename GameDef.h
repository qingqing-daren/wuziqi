#ifndef GAMEDEF_H
#define GAMEDEF_H

// 棋子颜色：0空、1黑、2白
enum ChessColor {
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
};

// 游戏阶段
enum GameStage {
    STAGE1_BLACK1,   // 黑1落天元
    STAGE2_WHITE2,   // 白2落子
    STAGE3_BLACK3,   // 黑3落子（5×5范围）
    STAGE4_EXCHANGE, // 三手交换
    STAGE5_WHITE4,   // 白4落子
    STAGE6_BLACK5_N, // 五手N打（黑选候选点）
    STAGE7_WHITE_CHOOSE, // 白选黑5点
    STAGE8_NORMAL,   // 正常对局
    STAGE_END        // 游戏结束
};

// 胜负结果
enum GameResult {
    NONE,           // 未分胜负
    BLACK_WIN,      // 黑胜
    WHITE_WIN,      // 白胜
    DRAW,           // 平局
    BLACK_FORBIDDEN // 黑禁手负
};
struct Point{
    int x,y;
    Point(int x_=-1,int y_=-1):x(x_),y(y_){}
};

#endif // GAMEDEF_H
