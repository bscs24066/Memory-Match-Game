#pragma once
#include "MyStr.h"

class Card {
public:
    int id;              
    bool isMatched;      
    bool isFlipped;      
    MyStr symbol;       


    Card() : id(0), isMatched(false), isFlipped(false), symbol("") {}


    void flip() {
        isFlipped = !isFlipped;
    }

    
    void reset() {
        isMatched = false;
        isFlipped = false;
    }
};