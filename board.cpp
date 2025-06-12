#include "board.hpp"

#include <cassert>
#include <random>
#include <iostream>

// fills the grid_ edges
Board::Board() {
    // fills bottom and top row
    for(int i = 0; i < kSizeX; i++) {
        grid_[i][0] = CellType::Wall;
        grid_[i][kSizeY - 1] = CellType::Wall;
    }
    // fills left and right row
    for(int i = 0; i < kSizeY; i++) {
        grid_[0][i] = CellType::Wall;
        grid_[kSizeX - 1][i] = CellType::Wall;
    }
}

// getters and setters

int Board::getWidth() {
    return kSizeX;
}

int Board::getHeight() {
    return kSizeY;
}

CellType Board::getCell(int x, int y) {
    assert(isValidPosition(x, y));
    return grid_[x][y];
}

void Board::setCell(int x, int y, CellType cell_type) {
    assert(isValidPosition(x, y));
    grid_[x][y] = cell_type;
}

// checks if position is in bounds
bool Board::isValidPosition(int x, int y) {
    return (x < kSizeX) && (x >= 0) && (y < kSizeY) && (y >= 0);
}

int Board::generateRandomNumInRange(int i, int j) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(i, j);
    return distrib(gen);
}

std::array<int, 2> Board::generateRandomPos() {
    std::array<int, 2> pos = {generateRandomNumInRange(0, kSizeX), 
    generateRandomNumInRange(0, kSizeY)};
    return pos;
}

bool Board::isPath(std::array<int, 2> pos) {
    return getCell(pos.at(0), pos.at(1)) == CellType::Path;
}

void Board::generateFood() {
    std::array pos = generateRandomPos();
    // make sure the cell is free to use
    while(!isPath(pos)) {
        pos = generateRandomPos();
    }
    setCell(pos.at(0), pos.at(1), CellType::Food);
}

void Board::print() {
    for(int i = 0; i < kSizeX; i++) {
        for(int j = 0; j < kSizeY; j++) {
            // Pick color
            switch (grid_[i][j])
            {
            case CellType::Path:
                std::cout << "\e[0;30m"; // Black
                break;
            case CellType::Wall:
                std::cout << "\e[0;37m"; // White
                break;
            case CellType::Food:
                std::cout << "\e[0;31m"; // Red
                break;
            case CellType::Snake:
                std::cout << "\e[0;33m"; // Yellow
                break;
            default:
                break;
            }
            // print character
            std::cout << "█";
        }
        std::cout << '\n';
    }
    std::cout << "\x1b[0m"; // reset color
}