#ifndef GAMEUTILS_H
#define GAMEUTILS_H

#include "D:/guge/GameDef.h"
#include "D:/guge/Board.h"

class GameUtils {
   bool isValidMove(Board board, int x, int y, ChessColor color);
    static const char* getStageTip(GameStage1 stage);
};


#endif // GAMEUTILS_H
