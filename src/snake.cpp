#include "snake.hpp"

#include <cassert>
#include <iostream>


Snake::Snake(int x, int y) { 
    assert(x - kBaseSnakeLenght >= 0); // to make sure tail stays inbound 
    // expends the snake left of the initial coordinates
    for(int i = 0; i < kBaseSnakeLenght; i++) {
        body_.push_back(SnakeCell(x - i, y, Direction::East));
    }
    
}

// returns position of head in the form of [x, y]
std::array<int, 2> Snake::getHeadPos() { 
    return std::array<int, 2> {body_.front().getX(), body_.front().getY()};
}

// returns position of head in the form of [x, y]
std::array<int, 2> Snake::getTailPos() { 
    return std::array<int, 2> {body_.back().getX(), body_.back().getY()};
}


// this might cause unintended behaviour if the snake doesn't move as fast as he eats(should be impossible)
// !! careful not to print the snake on the board between this step and the movement (always call this after move())!!
void Snake::growBack() {
    assert(!body_.empty());

    int new_x = body_.back().getX(), new_y = body_.back().getY();
    Direction growing_direction = body_.back().getFacingDirection();
    switch(growing_direction) {
    case Direction::East:
        new_y--;
        break;
    case Direction::West:
        new_y++;
        break;
    case Direction::South:
        new_x--;
        break;
    case Direction::North:
        new_x++;
        break;
    default:
        std::cout << "Unexpected Direction value";
        exit(EXIT_FAILURE);
    }
    body_.push_back(SnakeCell(new_x, new_y, growing_direction));
}

bool Snake::isBackwardsDirection(Direction new_direction) {
    switch (body_.front().getFacingDirection())
    {
    case Direction::West:
        if(new_direction == Direction::East)
            return true;
        else
            return false;
    case Direction::East:
        if(new_direction == Direction::West)
            return true;
        else
            return false;
    case Direction::North:
        if(new_direction == Direction::South)
            return true;
        else
            return false;
    case Direction::South:
        if(new_direction == Direction::North)
            return true;
        else
            return false;
    default:
        std::cout << "unexpected direction value in isBackwardsDirection()";
        exit(EXIT_FAILURE);
    }
}

void Snake::move(Direction direction) {
    assert(!body_.empty()); // error handling

    int new_x = body_.front().getX(), new_y = body_.front().getY();

    if(direction == Direction::None || isBackwardsDirection(direction)) { // then the snake moves the same way as before
        direction = body_.front().getFacingDirection();
    }
    switch (direction) {
    case Direction::East:
        new_y++;
        break;
    case Direction::West:
        new_y--;
        break;
    case Direction::South:
        new_x++;
        break;
    case Direction::North:
        new_x--;
        break;
    default:
        std::cout << "Unexpected Direction value";
        exit(EXIT_FAILURE);
    }
    SnakeCell newHead(new_x, new_y, direction);
    body_.push_front(newHead);
    body_.pop_back();
}

Snake::SnakeCell::SnakeCell(int x, int y, Direction movement) {
    coord_x_ = x;
    coord_y_ = y;
    facing_direction_ = movement;
}

Direction Snake::SnakeCell::getFacingDirection() {
    return facing_direction_;
}

int Snake::SnakeCell::getX() {
    return coord_x_;
}

int Snake::SnakeCell::getY() {
    return coord_y_;
}