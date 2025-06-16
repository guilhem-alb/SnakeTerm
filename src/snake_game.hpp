// Here is an implementation of SnakeGame class meant to coordinate the Snake and Board class
#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <string>
#include "board.hpp"
#include "snake.hpp"

class SnakeGame {
public:
    SnakeGame();
    int getScore() {return score_;};
    void updateGame();
    void endGame();
    
private:
    int score_ = 0;
    
    Board game_board_;
    Snake player_snake_;

    // key recognition handling
    Direction mapKey(char input[], int input_size); // returns the key associated with the input string
    void setCursor();
    void resolveColision(CellType board_cell_type); // execute action based on the encountered cell and updates board
    void incrementScore() {score_++;};
    void skipNLines(int n); // makes room on the terminal
};

#endif // SNAKE_GAME_H