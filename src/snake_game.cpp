#include "snake_game.hpp"

#include <cassert>
#include <iostream>
#include <unistd.h>
#include <termios.h>

// convert input to key
Direction SnakeGame::mapKey(char input[], int input_size) {
    if(input_size != 3) {
        if(input[0] == 'q') // key 'q' exits the game
            endGame(); // program terminates here
        // else
        return Direction::None;
    }
    else if(input[0] != '\x1b' || input[1] !='[') {
        return Direction::None;
    }
    else {
        switch (input[2])
        {
        case 'A':
            return Direction::North;
            break;
        case 'B':
            return Direction::South;
            break;
        case 'C':
            return Direction::East;
            break;
        case 'D':
            return Direction::West;
            break;
        default:
            std::cout << "\nunknown\n";
            return Direction::None;
        }
    }
} 

SnakeGame::SnakeGame() 
    : game_board_(),
    // init snake in the middle of the board
    player_snake_((game_board_.getWidth() / 2), (game_board_.getHeight() / 2))
{
    // put snake on board
    std::array<int, 2> snake_tail_pos = player_snake_.getTailPos();
    std::array<int, 2> snake_head_pos = player_snake_.getHeadPos();
    game_board_.setCell(snake_tail_pos.at(0), snake_tail_pos.at(1), CellType::Snake);
    game_board_.setCell(snake_head_pos.at(0), snake_head_pos.at(1), CellType::Snake);

    game_board_.generateFood();

    skipNLines(game_board_.getHeight()); // position cursor to make room for printing
}

void SnakeGame::skipNLines(int n) {
    for(int i = 0; i < n; i++) {
        std::cout << "\n";
    }
}

// moves cursor to top left to print the next frame
void SnakeGame::setCursor() {
    std::cout << "\x1b[" << game_board_.getHeight() <<"F" << std::flush; 
}

void SnakeGame::resolveColision(CellType board_cell_type) {
    switch (board_cell_type)
    {
    case CellType::Food: {
        //update snake
        player_snake_.growBack();
        // update board
        std::array<int, 2> snake_tail_pos = player_snake_.getTailPos();
        game_board_.setCell(snake_tail_pos.at(0), snake_tail_pos.at(1), CellType::Snake);
        game_board_.generateFood();
        incrementScore();
        break;
    }
    case CellType::Snake:
    case CellType::Wall:
        endGame();
    default:
    // do nothing
        break;
    }
}

void SnakeGame::updateGame() {
    // get player input
    char buf[3];
    int buf_size = read(STDIN_FILENO, buf, 3);
    Direction input_direction = mapKey(buf, buf_size);
    tcflush(STDIN_FILENO, TCIFLUSH); // flush buffer to avoid setting movement for subsequent frames
    // remove tail
    std::array<int, 2> snake_tail_pos = player_snake_.getTailPos();
    game_board_.setCell(snake_tail_pos.at(0), snake_tail_pos.at(1), CellType::Path);
    player_snake_.move(input_direction); // change snake
    // check colision
    std::array<int, 2> snake_head_pos = player_snake_.getHeadPos();
    resolveColision(game_board_.getCell(snake_head_pos.at(0), snake_head_pos.at(1)));
    // add head
    game_board_.setCell(snake_head_pos.at(0), snake_head_pos.at(1), CellType::Snake);
    setCursor();
    game_board_.print();
}


// prints scores and closes program
void SnakeGame::endGame() {
    std::cout << "\ngame over\n";
    std::cout << "score = " << this->getScore() <<"\n";
    exit(EXIT_SUCCESS); 
}