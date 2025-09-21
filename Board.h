#ifndef BOARD_H
#define BOARD_H
#include "GameDef.h"
#include <QString> // 用于错误信息字符串

class Board {
public:
    // 初始化棋盘：空棋、阶段1、黑方落子、初始无结果
    Board() {
        for (int x = 0; x < 15; x++) {
            for (int y = 0; y < 15; y++) {
                grid[x][y] = EMPTY;
            }
        }
        currentStage = STAGE1_BLACK1;
        currentTurn = BLACK;
        gameResult = NONE; // 初始：游戏未结束
        lastError = "";    // 初始：无错误
    }

    // 核心接口：尝试落子（包含合法性判断、阶段规则、结果更新）
    // 返回值：true=落子成功，false=失败（失败原因通过getLastError获取）
    bool tryMove(int x, int y) {
        // 1. 游戏已结束，禁止落子
        if (gameResult != NONE) {
            lastError = "游戏已结束，无法继续落子";
            return false;
        }

        // 2. 检查坐标是否在棋盘内（0-14）
        if (x < 0 || x >= 15 || y < 0 || y >= 15) {
            lastError = "落子位置超出棋盘范围";
            return false;
        }

        // 3. 检查是否为空位
        if (grid[x][y] != EMPTY) {
            lastError = "该位置已有棋子，无法落子";
            return false;
        }

        // 4. 检查当前阶段的落子规则（核心：按阶段限制）
        if (!checkMoveLegal(x, y)) {
            // 错误信息已在checkMoveLegal中设置
            return false;
        }

        // 5. 执行落子（调用内部setChess，确保只有合法落子能修改棋盘）
        grid[x][y] = currentTurn;

        // 6. 落子后检查是否获胜
        if (checkWin(x, y)) {
            gameResult = (currentTurn == BLACK) ? BLACK_WIN : WHITE_WIN;
            return true;
        }

        // 7. 检查是否平局（棋盘满了）
        if (isBoardFull()) {
            gameResult = DRAW;
            return true;
        }

        // 8. 落子成功且未结束，切换阶段和落子方
        switchStageAndTurn();

        return true;
    }

    // 获取指定位置的棋子颜色（供MainWindow绘制）
    ChessColor getChess(int x, int y) const {
        if (x < 0 || x >= 15 || y < 0 || y >= 15) {
            return EMPTY;
        }
        return grid[x][y];
    }

    // 获取上次落子失败的原因（供MainWindow弹窗）
    QString getLastError() const {
        return lastError;
    }

    // 获取当前游戏阶段（供MainWindow状态栏）
    GameStage getCurrentStage() const {
        return currentStage;
    }

    // 获取当前落子方（供MainWindow状态栏）
    ChessColor getCurrentTurn() const {
        return currentTurn;
    }

    // 获取当前游戏结果（未结束/黑胜/白胜/平局）
    GameResult getGameResult() const {
        return gameResult;
    }

    // 判断游戏是否在进行中（未结束）
    bool isGameStarted() const {
        return gameResult == NONE;
    }

    // 清空棋盘，重新开始游戏
    void clear() {
        for (int x = 0; x < 15; x++) {
            for (int y = 0; y < 15; y++) {
                grid[x][y] = EMPTY;
            }
        }
        currentStage = STAGE1_BLACK1;
        currentTurn = BLACK;
        gameResult = NONE;
        lastError = "";
    }

private:
    ChessColor grid[15][15];   // 棋盘数据（私有，仅内部修改）
    GameStage currentStage;    // 当前游戏阶段
    ChessColor currentTurn;    // 当前落子方
    GameResult gameResult;     // 游戏结果（未结束/胜负/平局）
    QString lastError;         // 上次操作失败的原因

    // 辅助函数：检查当前阶段的落子是否合法（按规则限制）
    bool checkMoveLegal(int x, int y) {
        switch (currentStage) {
            case STAGE1_BLACK1:
                // 黑1必须落天元（7,7）
                if (x != 7 || y != 7) {
                    lastError = "黑1必须落在天元（中心位置）";
                    return false;
                }
                break;
            case STAGE3_BLACK3:
                // 黑3必须落在5-9行/列范围内（三手交换规则）
                if (x < 5 || x > 9 || y < 5 || y > 9) {
                    lastError = "黑3必须落在5-9范围内";
                    return false;
                }
                break;
            // 其他阶段（如白2、黑4等）无特殊限制，只需空位即可
            default:
                break;
        }
        return true;
    }

    // 辅助函数：检查最新落子是否形成五子连珠（胜负判定）
    bool checkWin(int x, int y) {
        ChessColor color = currentTurn; // 刚落子的颜色
        // 四个检查方向：水平、垂直、两个对角线
        const int dirs[4][2] = {{1,0}, {0,1}, {1,1}, {1,-1}};

        for (const auto& dir : dirs) {
            int count = 1; // 当前位置已有1个棋子
            int dx = dir[0];
            int dy = dir[1];

            // 正向检查（沿方向延伸）
            for (int i = 1; i < 5; ++i) {
                int nx = x + dx * i;
                int ny = y + dy * i;
                if (nx >=0 && nx <15 && ny >=0 && ny <15 && grid[nx][ny] == color) {
                    count++;
                } else {
                    break;
                }
            }

            // 反向检查（沿反方向延伸）
            for (int i = 1; i <5; ++i) {
                int nx = x - dx * i;
                int ny = y - dy * i;
                if (nx >=0 && nx <15 && ny >=0 && ny <15 && grid[nx][ny] == color) {
                    count++;
                } else {
                    break;
                }
            }

            // 五子连珠则获胜
            if (count >=5) {
                return true;
            }
        }
        return false;
    }

    // 辅助函数：检查棋盘是否已满（平局判定）
    bool isBoardFull() {
        for (int x = 0; x <15; ++x) {
            for (int y = 0; y <15; ++y) {
                if (grid[x][y] == EMPTY) {
                    return false; // 还有空位，未平局
                }
            }
        }
        return true; // 满了，平局
    }

    // 辅助函数：落子后切换阶段和落子方（按规则推进）
    void switchStageAndTurn() {
        switch (currentStage) {
            case STAGE1_BLACK1:
                currentStage = STAGE2_WHITE2;
                currentTurn = WHITE;
                break;
            case STAGE2_WHITE2:
                currentStage = STAGE3_BLACK3;
                currentTurn = BLACK;
                break;
            case STAGE3_BLACK3:
                currentStage = STAGE4_EXCHANGE; // 进入三手交换阶段
                currentTurn = WHITE; // 假设白方选择不交换，继续落子
                break;
            case STAGE4_EXCHANGE:
                currentStage = STAGE5_WHITE4; // 三手交换后，白4落子
                currentTurn = WHITE;
                break;
            // 后续阶段按规则继续添加（如STAGE5→STAGE6...）
            default:
                // 普通阶段：黑白交替落子
                currentTurn = (currentTurn == BLACK) ? WHITE : BLACK;
                break;
        }
    }
};

#endif // BOARD_H
