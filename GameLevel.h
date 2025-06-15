#pragma once
#include "Board.h"

class GameLevel {
public:
    virtual void setup(Board& board) = 0;
    virtual MyStr getName() = 0;
};


class EasyLevel : public GameLevel {
public:
    void setup(Board& board) override {
        board.generateBoard(4);
    }

    MyStr getName() override {
        return MyStr("Easy");
    }
};

class MediumLevel : public GameLevel {
public:
    void setup(Board& board) override {
        board.generateBoard(6);
    }

    MyStr getName() override {
        return MyStr("Medium");
    }
};


class HardLevel : public GameLevel {
public:
    void setup(Board& board) override {
        board.generateBoard(8);
    }

    MyStr getName() override {
        return MyStr("Hard");
    }
};