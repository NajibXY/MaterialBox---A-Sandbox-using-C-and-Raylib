#pragma once
#include <vector>

extern const int EMPTY_TYPE;
extern const int SAND_TYPE;

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
        bool IsInBounds(int x, int y);
        int GetCell(int x, int y);
        void SetCell(int x, int y, int value);

        // Global Drawing operations
        void DrawGrid();
        void Randomize();
        void Clear();

        // Drawing shapes
        void DrawMaterial(int x, int y);


};