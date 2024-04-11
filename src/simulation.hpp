#pragma once
#include "grid.hpp"

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

class Simulation {
    private :
        Grid grid;
        bool running;
        
    public :
        Simulation(int width, int height, int cellDim, int randomRate): 
            grid(width, height, cellDim, randomRate), running(true)
            {};

        // Getters and setters
        bool IsRunning() { return running; }
        void SetRunning(bool value) { running = value; }
        
        // Operations on the Grid
        void DrawGrid();
        void Randomize();
        void Clear();
        void SetRandomRate(int value);
        void SetMaterialType(int value);
        void DrawMaterial(int x, int y);
        void SetCell(int x, int y, int value);
        
        // Simulation update logic
        int CountLiveNeighbours(int x, int y);
        void Update();
        int GetRandomSandValue();
        int GetRandomAcidValue();
        void UpdateSandLogic();
        void UpdateSandLogicOnCell(int x, int y, Grid& newGrid);  
        void UpdateAcidLogic();
        void UpdateAcidLogicOnCell(int x, int y, Grid& newGrid);
        void UpdateStoneLogic();
        void UpdateStoneLogicOnCell(int x, int y, Grid& newGrid);
};