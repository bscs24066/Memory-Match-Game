#pragma once
#include "MyVector.h"
#include "Card.h"
#include <cstdlib> 

class Board {
public:
    MyVector<Card> cards;
    int size;

    void generateBoard(int levelSize) {
        size = levelSize;
        cards.clear();

        
        for (int i = 0; i < size; i++) {
            Card c1, c2;
            c1.id = c2.id = i;
            c1.symbol = c2.symbol = MyStr("[#") + MyStr(i) + MyStr("]");
            cards.push_back(c1);
            cards.push_back(c2);
        }

        shuffle();
    }

    void shuffle() {
        for (int i = 0; i < cards.size(); i++) {
            int j = rand() % cards.size();
            Card temp = cards[i];
            cards[i] = cards[j];
            cards[j] = temp;
        }
    }

    void display() {
        for (int i = 0; i < cards.size(); i++) {
            if (cards[i].isMatched || cards[i].isFlipped)
                std::cout << " " << cards[i].symbol << " ";
            else
                std::cout << " [??] ";

            if ((i + 1) % 4 == 0) std::cout << "\n";
        }
    }

    bool checkMatch(int i, int j) {
        if (cards[i].id == cards[j].id && i != j) {
            cards[i].isMatched = true;
            cards[j].isMatched = true;
            return true;
        }
        return false;
    }

    void resetFlips() {
        for (int i = 0; i < cards.size(); i++) {
            if (!cards[i].isMatched) {
                cards[i].isFlipped = false;
            }
        }
    }

    bool allMatched() {
        for (int i = 0; i < cards.size(); i++) {
            if (!cards[i].isMatched) return false;
        }
        return true;
    }
};