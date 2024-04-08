#include "simulation.hpp"
#include <raylib.h>

void Simulation::DrawGrid() {
    grid.DrawGrid(running);
}

void::Simulation::Randomize() {
    // Randomize the grid
    grid.Randomize();
}

void::Simulation::Clear() {
    // Clear the grid
    grid.Clear();
}

void::Simulation::SetRandomRate(int value) {
    // Set the random rate of the grid
    grid.SetRandomRate(value);
}

void::Simulation::SetMaterialType(int value) {
    // Set the shape index of the grid
    grid.SetMaterialType(value);
}

void::Simulation::DrawMaterial(int x, int y) {
    // Draw the material near the specified coordinates
    grid.DrawMaterial(x, y, running);
}

void Simulation::SetCell(int x, int y, int value) {
    // Set the value of the cell at (x, y) in the grid
    grid.SetCell(x, y, value);
}

int Simulation::CountLiveNeighbours(int x, int y) {
    // Define the number of live neighbours
    int liveNeighbours = 0;

    // Define the coordinates of the neighbours in a TOROIDAL grid
    int neighbourCoordinates[8][2] = {
        {(x-1 + grid.GetRows()) % grid.GetRows(), (y-1 + grid.GetColumns()) % grid.GetColumns()},
        {x, (y-1 + grid.GetColumns()) % grid.GetColumns()},
        {(x+1) % grid.GetRows(), (y-1 + grid.GetColumns()) % grid.GetColumns()},
        {(x-1 + grid.GetRows()) % grid.GetRows(), y},
        {(x+1) % grid.GetRows(), y},
        {(x-1 + grid.GetRows()) % grid.GetRows(), (y+1) % grid.GetColumns()},
        {x, (y+1) % grid.GetColumns()},
        {(x+1) % grid.GetRows(), (y+1) % grid.GetColumns()}
    };

    // Loop through the neighbours
    for (int i = 0; i < 8; i++) {
        // Get the coordinates of the neighbour and its value
        liveNeighbours += grid.GetCell(neighbourCoordinates[i][0], neighbourCoordinates[i][1]);
    }

    // Return the number of live neighbours
    return liveNeighbours;
}

void Simulation::Update() {
    // Create a new grid to store the updated values
    Grid newGrid = grid;

    // Loop through the cells in the grid
    for (int i = 0; i < grid.GetRows(); i++) {
        for (int j = 0; j < grid.GetColumns(); j++) {
            switch (grid.GetCell(i, j)) {
                // ---------------------- SAND LOGIC ----------------------
                case 11: case 12: case 13:
                    UpdateSandLogic(i, j, newGrid);
                    break;
                default :
                    break;
            }
        }
    }

    // Update the grid with the new values
    grid = newGrid;
}

void Simulation::UpdateSandLogic(int x, int y, Grid& newGrid) {
    // If the cell is sand
    // Check if the cell is not at the limit of the grid
    if (!grid.IsAtLimit(x, y) || grid.IsEmpty(x + 1, y)) {
        // Check if the cell below is empty or below right or below left
        // Reset initial cell & 
        // Apply random sand type to future cell
        if (grid.GetCell(x + 1, y) == EMPTY_TYPE) {
            newGrid.SetCell(x, y, EMPTY_TYPE);
            newGrid.SetCell(x + 1, y, GetRandomSandValue());
        } else if (grid.GetCell(x + 1, y - 1) == EMPTY_TYPE) {
            newGrid.SetCell(x, y, EMPTY_TYPE);
            newGrid.SetCell(x + 1, y - 1, GetRandomSandValue());
        } else if (grid.GetCell(x + 1, y + 1) == EMPTY_TYPE) {
            newGrid.SetCell(x, y, EMPTY_TYPE);
            newGrid.SetCell(x + 1, y + 1, GetRandomSandValue());
        }
    }
}

int Simulation::GetRandomSandValue() {
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