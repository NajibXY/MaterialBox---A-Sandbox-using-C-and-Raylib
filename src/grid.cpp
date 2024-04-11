#include <raylib.h>
#include "grid.hpp"
//todo drop
using namespace std;
#include <iostream>

bool Grid::IsInBounds(int x, int y) {
    return x >= 0 && x < rows && y >= 0 && y < columns;
}

bool Grid::IsAtLimit(int x, int y) {
    return x == 0 || x == rows - 1 || y == 0 || y == columns - 1;
}

bool Grid::IsAtLeftLimit(int x, int y) {
    return y == 0;
}

bool Grid::IsAtRightLimit(int x, int y) {
    return y == columns - 1;
}

bool Grid::IsAtTopLimit(int x, int y) {
    return x == 0;
}

bool Grid::IsAtBottomLimit(int x, int y) {
    return x == rows - 1;
}

int Grid::GetCell(int x, int y) {
    // if(!IsInBounds(x, y)) {
    //     // Wrap around toroidal coordinates
    //     int wrappedX = (x + rows) % rows;
    //     int wrappedY = (y + columns) % columns;
    //     return cells[wrappedX][wrappedY];
    // }
    return cells[x][y]; 
}

bool Grid::IsEmpty(int x, int y) {
    if (IsInBounds(x, y)) {
        return cells[x][y] == EMPTY_TYPE;
    }
    return false;
}

void Grid::SetCell(int x, int y, int value) {
    if(IsInBounds(x, y) &&  (IsEmpty(x, y) || value == ACID_TYPE_1 || value == ACID_TYPE_2)) {
        cells[x][y] = value;
    } else if (IsInBounds(x, y) && value == EMPTY_TYPE) {
        cells[x][y] = value;
    }
}

void Grid::DrawGrid(bool running) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            Color color; 
            switch(cells[i][j]) {
                case 11: case 12: case 13:
                    // if (!running) {
                    //     color = ORANGE;
                    // }
                    //todo arrange to gold and orange colors
                    if (cells[i][j] == SAND_TYPE_1) {
                        color = YELLOW;
                    } else if (cells[i][j] == SAND_TYPE_2) {
                        color = GOLD;
                    } else {
                        color = ORANGE;
                    } 
                    DrawRectangle(j*cellDim, i*cellDim, cellDim, cellDim, color);
                    break;
                case 21: case 22:
                    if (cells[i][j] == STONE_TYPE_1) {
                        color = DARKGRAY;
                    } else {
                        color = GRAY;
                    }
                    DrawRectangle(j*cellDim, i*cellDim, cellDim-1, cellDim-1, color);
                    break;
                case 31: case 32:
                    if (cells[i][j] == ACID_TYPE_1) {
                        // color = Color{184, 218, 50, 255};
                        color = Color{87, 218, 50, 255};
                    } else {
                        color = LIME;
                    }
                    DrawRectangle(j*cellDim, i*cellDim, cellDim, cellDim, color);
                    break;
                default :
                    color = BLACK;
                    DrawRectangle(j*cellDim, i*cellDim, cellDim, cellDim, color);
                    break; 
            }
        }
    }
    
}

void Grid::Randomize() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            //todo randomize types
            int random = randomRate > 0 ? GetRandomValue(0, randomRate - 1) : 1;
            if (random == 0) {
                random = GetRandomValue(0, 2);
                if (random == 0) {
                    cells[i][j] = GetRandomSandValue();
                } else if (random == 1){
                    //todo construct stone structures ?
                    cells[i][j] = GetRandomStoneValue();
                }  else {
                    cells[i][j] = GetRandomAcidValue();
                }
            } else {
                cells[i][j] = EMPTY_TYPE;
            }
        }
    }
}

void Grid::Clear() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cells[i][j] = EMPTY_TYPE;
        }
    }
}

void Grid::DrawMaterial(int x, int y, bool running) {
    //todo add more materials
    int materialToDraw = EMPTY_TYPE;
    if (materialType == SAND_TYPE) {
        int random = GetRandomValue(0, 2);
        if (random == 0) {
            materialToDraw = SAND_TYPE_1;
        } else if (random == 1) {
            materialToDraw = SAND_TYPE_2;
        } else {
            materialToDraw = SAND_TYPE_3;
        }
    } else if (materialType == STONE_TYPE) {
        int random = GetRandomValue(0, 1);
        if (random == 0) {
            materialToDraw = STONE_TYPE_1;
        } else {
            materialToDraw = STONE_TYPE_2;
        }
    } else if (materialType == ACID_TYPE) {
        int random = GetRandomValue(0, 1);
        if (random == 0) {
            materialToDraw = ACID_TYPE_1;
        } else {
            materialToDraw = ACID_TYPE_2;
        }
    }
    // todo
    // Add some drawing constraints logic ?
    if (running && IsInBounds(x, y)) {
        if (materialType == SAND_TYPE || materialType == ACID_TYPE) {
            SetCell(x, y, materialToDraw);
            SetCell(x+1, y-1, materialToDraw);
            SetCell(x+1, y+1, materialToDraw); 
        }
        else if (materialType == STONE_TYPE) {
            SetCell(x, y, materialToDraw);
            SetCell(x, y+1, materialToDraw);
            SetCell(x+1, y, materialToDraw);
            SetCell(x+1, y+1, materialToDraw); 
        }
    } else if (IsInBounds(x, y)) {
        SetCell(x, y, materialToDraw);
        SetCell(x, y+1, materialToDraw);
        SetCell(x+1, y, materialToDraw);
        SetCell(x+1, y+1, materialToDraw); 
    }
    

    // if (IsInBounds(x, y)) {
    //     if (shapeIndex == 3) {
    //         SetCell(x, y, 1);
    //     } else if (shapeIndex == 1) { // Glider
    //         SetCell(x, y, 1);
    //         SetCell((x + 1) % rows, y, 1);
    //         SetCell((x + 2) % rows, y, 1);
    //         SetCell((x + 2) % rows, (y + 1) % columns, 1);
    //         SetCell((x + 1) % rows, (y + 2) % columns, 1);
    //     } else if (shapeIndex == 2) { // Blinker
    //         int random = GetRandomValue(0, 3); // Randomly choose orientation between vertical blinker, horizontal blinker, angel blinker and another type of blinkers
    //         if (random == 0) { // 
    //             SetCell(x, y, 1);
    //             SetCell(x, (y + 1) % columns, 1);
    //             SetCell(x, (y + 2) % columns, 1);
    //         } else if (random == 1) {
    //             SetCell(x, y, 1);
    //             SetCell((x + 1) % rows, y, 1);
    //             SetCell((x + 2) % rows, y, 1);
    //         } else if (random == 2) {
    //             SetCell((x + rows) % rows, (y) % columns, 1);
    //             SetCell((x + rows) % rows, (y + 1) % columns, 1);
    //             SetCell((x + 1) % rows, (y + 1) % columns, 1);
    //             SetCell((x + 2) % rows, (y + 2) % columns, 1);
    //             SetCell((x - 1 + rows) % rows, (y + 2) % columns, 1);
    //             SetCell((x + rows) % rows, (y + 3) % columns, 1);
    //             SetCell((x + rows) % rows, (y + 4) % columns, 1);
    //             SetCell((x + 1) % rows, (y + 3) % columns, 1);
    //         } else  {
    //             SetCell(x, y, 1);
    //             SetCell(x, (y + 1) % columns, 1);
    //             SetCell(x, (y + 2) % columns, 1);
    //             SetCell(x, (y + 3) % columns, 1);
    //             SetCell(x, (y + 4) % columns, 1);
    //             SetCell((x + 1) % rows, y, 1);
    //             SetCell((x + 1) % rows, (y + 4) % columns, 1);
    //             SetCell((x + 2) % rows, (y + 1) % columns, 1);
    //             SetCell((x + 2) % rows, (y + 2) % columns, 1);
    //             SetCell((x + 2) % rows, (y + 3) % columns, 1);
    //         }
    //     } else if (shapeIndex == 4) { // Glider Gun
    //         SetCell(x, y, 1);
    //         SetCell(x, (y + 1) % columns, 1);
    //         SetCell((x - 1 + rows) % rows, y, 1);
    //         SetCell((x - 1 + rows) % rows, (y + 1) % columns, 1);

    //         SetCell(x, (y + 10) % columns, 1);
    //         SetCell((x - 1 + rows) % rows, (y + 10) % columns, 1);
    //         SetCell((x + 1) % rows, (y + 10) % columns, 1);
    //         SetCell((x + 2) % rows, (y + 11) % columns, 1);
    //         SetCell((x + 3) % rows, (y + 12) % columns, 1);
    //         SetCell((x + 3) % rows, (y + 13) % columns, 1);
    //         SetCell((x + 2) % rows, (y + 15) % columns, 1);
    //         SetCell((x + 1) % rows, (y + 16) % columns, 1);
    //         SetCell(x, (y + 16) % columns, 1);
    //         SetCell(x, (y + 17) % columns, 1);
    //         SetCell((x - 1 + rows) % rows, (y + 16) % columns, 1);
    //         SetCell((x - 2 + rows) % rows, (y + 15) % columns, 1);
    //         SetCell(x, (y + 14) % columns, 1);
    //         SetCell((x - 3 + rows) % rows, (y + 13) % columns, 1);
    //         SetCell((x - 3 + rows) % rows, (y + 12) % columns, 1);
    //         SetCell((x - 2 + rows) % rows, (y + 11) % columns, 1);

    //         SetCell((x - 1 + rows) % rows, (y + 20) % columns, 1);
    //         SetCell((x - 2 + rows) % rows, (y + 20) % columns, 1);
    //         SetCell((x - 3 + rows) % rows, (y + 20) % columns, 1);
    //         SetCell((x - 1 + rows) % rows, (y + 21) % columns, 1);
    //         SetCell((x - 2 + rows) % rows, (y + 21) % columns, 1);
    //         SetCell((x - 3 + rows) % rows, (y + 21) % columns, 1);
    //         SetCell((x - 4 + rows) % rows, (y + 22) % columns, 1);
    //         SetCell((x - 4 + rows) % rows, (y + 24) % columns, 1);
    //         SetCell((x - 5 + rows) % rows, (y + 24) % columns, 1);
    //         SetCell(x, (y + 22) % columns, 1);
    //         SetCell(x, (y + 24) % columns, 1);
    //         SetCell((x + 1) % rows, (y + 24) % columns, 1);

    //         SetCell((x - 3 + rows) % rows, (y + 34) % columns, 1);
    //         SetCell((x - 2 + rows) % rows, (y + 34) % columns, 1);
    //         SetCell((x - 3 + rows) % rows, (y + 35) % columns, 1);
    //         SetCell((x - 2 + rows) % rows, (y + 35) % columns, 1);
    //     } else if (shapeIndex == 5) { // Pulsar
    //         SetCell((x + rows) % rows, y, 1);
    //         SetCell((x - 1 + rows) % rows, y, 1);
    //         SetCell((x - 2 + rows) % rows, y, 1);
    //         SetCell((x - 4 + rows) % rows, (y + 2) % columns, 1);
    //         SetCell((x - 4 + rows) % rows, (y + 3) % columns, 1);
    //         SetCell((x - 4 + rows) % rows, (y + 4) % columns, 1);
    //         SetCell((x - 4 + rows) % rows, (y + 8) % columns, 1);
    //         SetCell((x - 4 + rows) % rows, (y + 9) % columns, 1);
    //         SetCell((x - 4 + rows) % rows, (y + 10) % columns, 1);
    //         SetCell((x - 2 + rows) % rows, (y + 12) % columns, 1);
    //         SetCell((x - 1 + rows) % rows, (y + 12) % columns, 1);
    //         SetCell((x + rows) % rows, (y + 12) % columns, 1);
    //         SetCell((x + 4) % rows, (y + 12) % columns, 1);
    //         SetCell((x + 5) % rows, (y + 12) % columns, 1);
    //         SetCell((x + 6) % rows, (y + 12) % columns, 1);
    //         SetCell((x + 8) % rows, (y + 10) % columns, 1);
    //         SetCell((x + 8) % rows, (y + 9) % columns, 1);
    //         SetCell((x + 8) % rows, (y + 8) % columns, 1);
    //         SetCell((x + 8) % rows, (y + 4) % columns, 1);
    //         SetCell((x + 8) % rows, (y + 3) % columns, 1);
    //         SetCell((x + 8) % rows, (y + 2) % columns, 1);
    //         SetCell((x + 6) % rows, y, 1);
    //         SetCell((x + 5) % rows, y, 1);
    //         SetCell((x + 4) % rows, y, 1);

    //         SetCell((x + 1) % rows, (y + 2) % columns, 1);
    //         SetCell((x + 1) % rows, (y + 3) % columns, 1);
    //         SetCell((x + 1) % rows, (y + 4) % columns, 1);
    //         SetCell((x + 3) % rows, (y + 2) % columns, 1);
    //         SetCell((x + 3) % rows, (y + 3) % columns, 1);
    //         SetCell((x + 3) % rows, (y + 4) % columns, 1);
    //         SetCell((x + 1) % rows, (y + 8) % columns, 1);
    //         SetCell((x + 1) % rows, (y + 9) % columns, 1);
    //         SetCell((x + 1) % rows, (y + 10) % columns, 1);
    //         SetCell((x + 3) % rows, (y + 8) % columns, 1);
    //         SetCell((x + 3) % rows, (y + 9) % columns, 1);
    //         SetCell((x + 3) % rows, (y + 10) % columns, 1);

    //         SetCell(x, (y + 5) % columns, 1);
    //         SetCell((x - 1 + rows) % rows, (y + 5) % columns, 1);
    //         SetCell((x - 2 + rows) % rows, (y + 5) % columns, 1);
    //         SetCell(x, (y + 7) % columns, 1);
    //         SetCell((x - 1 + rows) % rows, (y + 7) % columns, 1);
    //         SetCell((x - 2 + rows) % rows, (y + 7) % columns, 1);

    //         SetCell((x + 4) % rows, (y + 5) % columns, 1);
    //         SetCell((x + 5) % rows, (y + 5) % columns, 1);
    //         SetCell((x + 6) % rows, (y + 5) % columns, 1);
    //         SetCell((x + 4) % rows, (y + 7) % columns, 1);
    //         SetCell((x + 5) % rows, (y + 7) % columns, 1);
    //         SetCell((x + 6) % rows, (y + 7) % columns, 1);
    //     }
    // }
}

int Grid::GetRandomSandValue() {
    // Get a random sand type
    int randomSand = GetRandomValue(0, 2);
    if (randomSand == 0) {
        return SAND_TYPE_1;
    } else if (randomSand == 1) {
        return SAND_TYPE_2;
    } else {
        return SAND_TYPE_3;
    }
    return SAND_TYPE_1;
}

int Grid::GetRandomStoneValue() {
    // Get a random sand type
    int randomStone = GetRandomValue(0, 1);
    if (randomStone == 0) {
        return STONE_TYPE_1;
    } else {
        return STONE_TYPE_2;
    }
    return STONE_TYPE_1;
}

int Grid::GetRandomAcidValue() {
    // Get a random sand type
    int randomAcid = GetRandomValue(0, 1);
    if (randomAcid == 0) {
        return ACID_TYPE_1;
    } else {
        return ACID_TYPE_2;
    }
    return ACID_TYPE_1;
}