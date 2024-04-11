#pragma once
#include <vector>

extern const int EMPTY_TYPE;
extern const int SAND_TYPE;
extern const int SAND_TYPE_1;
extern const int SAND_TYPE_2;
extern const int SAND_TYPE_3;
extern const int STONE_TYPE;
extern const int STONE_TYPE_1;
extern const int STONE_TYPE_2;
extern const int ACID_TYPE;
extern const int ACID_TYPE_1;
extern const int ACID_TYPE_2;

class Grid {
    private :
        int rows;
        int columns;
        int cellDim;
        int randomRate;
        int materialType; //todo 0 for empty, 1 for sand
        std::vector<std::vector<int>> cells;
    public :
        Grid(int width, int height, int cellDim, int randomRate):   
            rows(height/cellDim), columns(width/cellDim), cellDim(cellDim), randomRate(randomRate), materialType(1),
            cells(rows, std::vector<int>(columns, EMPTY_TYPE))
            {};
        
        // Getters and setters
        int GetRows() { return rows; }
        int GetColumns() { return columns; }
        int GetRandomeRate() { return randomRate; }
        void SetRandomRate(int value) { randomRate = value; }
        void SetMaterialType(int value) { materialType = value; }

        // Operations on a cell
        bool IsEmpty(int x, int y);
        bool IsInBounds(int x, int y);
        bool IsAtLimit(int x, int y);
        bool IsAtLeftLimit(int x, int y);
        bool IsAtRightLimit(int x, int y);
        bool IsAtTopLimit(int x, int y);
        bool IsAtBottomLimit(int x, int y);
        int GetCell(int x, int y);
        void SetCell(int x, int y, int value);

        // Global Drawing operations
        void DrawGrid(bool running);
        void Randomize();
        void Clear();

        // Drawing materials
        void DrawMaterial(int x, int y, bool running);
        int GetRandomSandValue();
        int GetRandomStoneValue();
        int GetRandomAcidValue();

};