#pragma once
#include "MyStr.h"

class Player {
public:
    MyStr name;
    int moves;

    Player() : moves(0) {}

    void incrementMoves() {
        moves++;
    }

    void resetMoves() {
        moves = 0;
    }
};