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
     //弹出每回合的提示
const char* GameUtils::getStageTip(GameStage1 stage) {
    switch (stage) {
        case STAGE1_START:
            return "游戏开始，黑方先行";
        case STAGE2_BLACK_TURN:
            return "黑方回合，请落子";
        case STAGE3_WHITE_TURN:
            return "白方回合，请落子";
        case STAGE4_EXCHANGE1:
            return "白方请选择是否交换颜色";
        case STAGE5_BLACK_WIN:
            return "黑方获胜！游戏结束";
        case STAGE6_WHITE_WIN:
            return "白方获胜！游戏结束";
        case STAGE7_DRAW:
            return "平局！游戏结束";
        default:
            return "未知阶段";
    }
}
