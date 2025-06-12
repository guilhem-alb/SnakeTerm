#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include <array>
#include "direction.hpp"

class Snake {
public:
    Snake(int x, int y); // !!always be careful of board size when constructing snake
    std::array<int, 2> getHeadPos(); // returns position of head in the form of [x, y]
    std::array<int, 2> getTailPos();
    void growBack();
    void move(Direction direction); // updates head and tail pos
private:
    static constexpr int kBaseSnakeLenght = 2;
    int lenght_ = kBaseSnakeLenght;
    
    class SnakeCell { // handles individual blocks logic
    public:
        SnakeCell(int x, int y, Direction movement);
        Direction getFacingDirection();
        int getX();
        int getY();
    private:
        Direction facing_direction_; // To know where to grow the snake
        int coord_x_;
        int coord_y_;
    }; // class SnakeCell
    std::deque<SnakeCell> body_;

    SnakeCell getHead();
};

#endif // SNAKE_H