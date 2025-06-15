#include "raylib.h"
#include "Board.h"
#include "Player.h"
#include "GameLevel.h"
#include <ctime>

int screenWidth = 800;
int screenHeight = 600;

const int CARD_WIDTH = 100;
const int CARD_HEIGHT = 60;
const int PADDING = 10;

enum GameState { HOME, PLAYING, ASK_NEXT, END_GAME };

void drawBoard(Board& board) {
    int cardsPerRow = 4;
    int cardsPerCol = board.cards.size() / cardsPerRow;
    int totalWidth = cardsPerRow * (CARD_WIDTH + PADDING) - PADDING;
    int totalHeight = cardsPerCol * (CARD_HEIGHT + PADDING) - PADDING;

    int startX = (screenWidth - totalWidth) / 2;
    int startY = (screenHeight - totalHeight) / 2;

    for (int i = 0; i < board.cards.size(); i++) {
        int row = i / cardsPerRow;
        int col = i % cardsPerRow;
        int x = startX + col * (CARD_WIDTH + PADDING);
        int y = startY + row * (CARD_HEIGHT + PADDING);

        Rectangle rect = { (float)x, (float)y, CARD_WIDTH, CARD_HEIGHT };
        DrawRectangleRounded(rect, 0.2f, 5, LIGHTGRAY);
        if (board.cards[i].isFlipped || board.cards[i].isMatched)
            DrawText(board.cards[i].symbol.c_str(), x + 10, y + 20, 20, DARKBLUE);
        else
            DrawText("??", x + 30, y + 20, 20, RED);
    }
}

int getCardClicked(Board& board, int mouseX, int mouseY) {
    int cardsPerRow = 4;
    int cardsPerCol = board.cards.size() / cardsPerRow;
    int totalWidth = cardsPerRow * (CARD_WIDTH + PADDING) - PADDING;
    int totalHeight = cardsPerCol * (CARD_HEIGHT + PADDING) - PADDING;
    int startX = (screenWidth - totalWidth) / 2;
    int startY = (screenHeight - totalHeight) / 2;

    for (int i = 0; i < board.cards.size(); i++) {
        int row = i / cardsPerRow;
        int col = i % cardsPerRow;
        int x = startX + col * (CARD_WIDTH + PADDING);
        int y = startY + row * (CARD_HEIGHT + PADDING);
        Rectangle rect = { (float)x, (float)y, CARD_WIDTH, CARD_HEIGHT };
        if (CheckCollisionPointRec({ (float)mouseX, (float)mouseY }, rect))
            return i;
    }
    return -1;
}

int main() {
    srand(time(0));
    InitWindow(screenWidth, screenHeight, "Memory Match Game");
    SetTargetFPS(60);

    Image bgImage = LoadImage("background.png");
    ImageResize(&bgImage, screenWidth, screenHeight);
    Texture2D background = LoadTextureFromImage(bgImage);
    UnloadImage(bgImage);

    Texture2D playBtn = LoadTexture("playbutton.png");
    Texture2D yesBtn = LoadTexture("yesbutton.png");
    Texture2D noBtn = LoadTexture("nobutton.png");

    Rectangle playButton = { (screenWidth - 64) / 2, 400, 64, 64 };
    Rectangle yesButton = { (screenWidth / 2) - 100, 300, 64, 64 };
    Rectangle noButton = { (screenWidth / 2) + 40, 300, 64, 64 };

    GameState state = HOME;
    Player player;
    Board board;
    GameLevel* levels[3] = { new EasyLevel(), new MediumLevel(), new HardLevel() };
    int currentLevel = 0;

    int first = -1, second = -1;
    bool waiting = false;
    float waitTime = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();
        DrawTexture(background, 0, 0, WHITE);

        if (state == HOME) {
            DrawText("Memory Match Game", (screenWidth - MeasureText("Memory Match Game", 30)) / 2, 200, 30, WHITE);
            DrawTexture(playBtn, playButton.x, playButton.y, WHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (CheckCollisionPointRec(GetMousePosition(), playButton)) {
                    levels[currentLevel]->setup(board);
                    player.moves = 0;
                    state = PLAYING;
                }
            }
        }
        else if (state == PLAYING) {
            drawBoard(board);
            DrawText(TextFormat("Moves: %d", player.moves), 10, 10, 20, WHITE);

            if (waiting) {
                waitTime += GetFrameTime();
                if (waitTime > 1.0f) {
                    if (!board.checkMatch(first, second)) {
                        board.cards[first].flip();
                        board.cards[second].flip();
                    }
                    first = second = -1;
                    waiting = false;
                    waitTime = 0;
                }
            }
            else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                int clicked = getCardClicked(board, GetMouseX(), GetMouseY());
                if (clicked != -1 && !board.cards[clicked].isFlipped && !board.cards[clicked].isMatched) {
                    board.cards[clicked].flip();
                    if (first == -1)
                        first = clicked;
                    else if (second == -1 && clicked != first) {
                        second = clicked;
                        player.incrementMoves();
                        waiting = true;
                    }
                }
            }

            if (board.allMatched()) {
                state = (currentLevel == 2) ? END_GAME : ASK_NEXT;
            }
        }
        else if (state == ASK_NEXT) {
            DrawText(TextFormat("Level %s Complete!", levels[currentLevel]->getName().c_str()),
                (screenWidth - MeasureText(TextFormat("Level %s Complete!", levels[currentLevel]->getName().c_str()), 20)) / 2, 150, 20, GREEN);
            DrawText("Continue to next level?", (screenWidth - MeasureText("Continue to next level?", 20)) / 2, 200, 20, WHITE);

            DrawTexture(yesBtn, yesButton.x, yesButton.y, GREEN);

            DrawTexture(noBtn, noButton.x, noButton.y, RED);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (CheckCollisionPointRec(GetMousePosition(), yesButton)) {
                    currentLevel++;
                    levels[currentLevel]->setup(board);
                    player.moves = 0;
                    first = second = -1;
                    waiting = false;
                    waitTime = 0;
                    state = PLAYING;
                }
                else if (CheckCollisionPointRec(GetMousePosition(), noButton)) {
                    break;
                }
            }
        }
        else if (state == END_GAME) {
            DrawText("You completed all levels!", (screenWidth - MeasureText("You completed all levels!", 25)) / 2, 200, 25, WHITE);
        }

        EndDrawing();
    }

    UnloadTexture(background);
    UnloadTexture(playBtn);
    UnloadTexture(yesBtn);
    UnloadTexture(noBtn);
    CloseWindow();
    return 0;
}