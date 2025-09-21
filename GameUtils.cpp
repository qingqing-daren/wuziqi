#include "GameUtils.h"
#include "D:/guge/GameDef.h"
#include "D:/guge/Board.h"

//判断落子是否正确
bool GameUtils::isValidMove(Board board, int x, int y, ChessColor color) {
    // 1. 检查坐标是否在棋盘范围内
    if (x < 0 || x >= 15 || y < 0 || y >= 15) {
        return false;
    }

    // 2. 检查目标位置是否为空
    if (board.getChess(x, y) != EMPTY) {
        return false;
    }

    // 3. 检查特殊阶段的落子限制（黑3的5×5范围限制）
    int currentStep = board.getMoveCount();
    //%%%%%%%%%%这个函数还未定义，由lxt负责。。

    // 当前是第3手棋（黑3），因为已下了2手，即将下第3手
    if (currentStep == 2 && color == BLACK) {
        // 计算棋盘中心坐标（假设棋盘为19×19）
        int centerX = 7;
        int centerY = 7;

        // 5×5范围是中心坐标±2的区域
        bool in5x5Area = (x >= centerX - 2 && x <= centerX + 2 &&
                          y >= centerY - 2 && y <= centerY + 2);

        if (!in5x5Area) {
            return false;
        }
    }

    // 所有条件都满足，落子合法
    return true;
}
