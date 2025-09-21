#ifndef BOARD_H
#define BOARD_H
#include "GameDef.h" // 包含GameDef.h，因为要用里面的枚举

class Board {
public:
    // 初始化棋盘：空棋、阶段1、黑方落子
    Board() {
        for (int x = 0; x < 15; x++) { // 15×15棋盘
            for (int y = 0; y < 15; y++) {
                grid[x][y] = EMPTY;
            }
        }
        currentStage = STAGE1_BLACK1;
        currentTurn = BLACK;
    }

    // 读棋盘：获取(x,y)的棋子颜色
    ChessColor getChess(int x, int y) {
        if (x < 0 || x >= 15 || y < 0 || y >= 15) {
            return EMPTY; // 越界返回空
        }
        return grid[x][y];
    }

    // 写棋盘：落子（成功返回true，失败返回false）
    bool setChess(int x, int y, ChessColor color) {
        if (x < 0 || x >= 15 || y < 0 || y >= 15) {
            return false; // 越界
        }
        if (grid[x][y] != EMPTY) {
            return false; // 已有棋子
        }
        grid[x][y] = color;
        return true;
    }

    // 切换游戏阶段
    void setStage(GameStage stage) {
        currentStage = stage;
    }
    GameStage getStage() {
        return currentStage;
    }

    // 切换当前落子方
    void setTurn(ChessColor turn) {
        currentTurn = turn;
    }
    ChessColor getTurn() {
        return currentTurn;
    }

    // 清空棋盘（重新开始）
    void clear() {
        for (int x = 0; x < 15; x++) {
            for (int y = 0; y < 15; y++) {
                grid[x][y] = EMPTY;
            }
        }
        currentStage = STAGE1_BLACK1;
        currentTurn = BLACK;
    }

private:
    ChessColor grid[15][15]; // 棋盘数据（私有，不允许外部直接改）
    GameStage currentStage;  // 当前阶段
    ChessColor currentTurn;  // 当前落子方
};

#endif // BOARD_H
