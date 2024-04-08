#include <raylib.h>
#include "grid.hpp"

bool Grid::IsInBounds(int x, int y) {
    return x >= 0 && x < rows && y >= 0 && y < columns;
}

int Grid::GetCell(int x, int y) {
    if(!IsInBounds(x, y)) {
        // Wrap around toroidal coordinates
        int wrappedX = (x + rows) % rows;
        int wrappedY = (y + columns) % columns;
        return cells[wrappedX][wrappedY];
    }
    return cells[x][y]; 
}

void Grid::SetCell(int x, int y, int value) {
    if(IsInBounds(x, y)) {
        cells[x][y] = value;
    } else {
        // Wrap around toroidal coordinates
        int wrappedX = (x + rows) % rows;
        int wrappedY = (y + columns) % columns;
        cells[wrappedX][wrappedY] = value;
    }
}

void Grid::DrawGrid() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            Color color; 
            switch(cells[i][j]) {
                case 1 :
                    color = YELLOW;
                    break;
                default :
                    color = BLACK;
            }
            DrawRectangle(j*cellDim, i*cellDim, cellDim-1, cellDim-1, color);
        }
    }
}

void Grid::Randomize() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int random = randomRate > 0 ? GetRandomValue(0, randomRate - 1) : 1;
            //todo randomize types
            cells[i][j] = (random == 0) ? SAND_TYPE : 0;
        }
    }
}

void Grid::Clear() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cells[i][j] = 0;
        }
    }
}

void Grid::DrawMaterial(int x, int y) {
    if (IsInBounds(x, y)) {
        SetCell(x, y, materialType);
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