#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "cell.hpp"

class Board{
public:
    Board(); // fills the grid edges
    
    int getWidth();
    int getHeight();
    CellType getCell(int x, int y);
    void setCell(int x, int y, CellType cell_type);
    void generateFood();
    void print();
private:
    // Dimensions
    static constexpr int kSizeX = 20;
    static constexpr int kSizeY = 50;
    // game board
    CellType grid_[kSizeX][kSizeY] = {{CellType::Path}};
    // methods
    bool isValidPosition(int x, int y);
    int generateRandomNumInRange(int i, int j);
    std::array<int, 2> generateRandomPos();
    bool isPath(std::array<int, 2> pos);
};
#endif // BOARD_H