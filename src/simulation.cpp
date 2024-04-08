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
                case 11: case 12: case 13:
                    if (grid.GetCell(i + 1, j) == EMPTY_TYPE) {
                        // Reset initial cell
                        newGrid.SetCell(i, j, 0);
                        // Apply random sand type to future cell
                        int random = GetRandomValue(0, 2);
                        if (random == 0) {
                            newGrid.SetCell(i + 1, j, SAND_TYPE_1);
                        } else if (random == 1) {
                            newGrid.SetCell(i + 1, j, SAND_TYPE_2);
                        } else if (random == 2) {
                            newGrid.SetCell(i + 1, j, SAND_TYPE_3);
                        }
                    // } else if (grid.GetCell(i + 1, j - 1) == EMPTY_TYPE) {
                    //     newGrid.SetCell(i, j, EMPTY_TYPE);
                    //     newGrid.SetCell(i + 1, j - 1, SAND_TYPE);
                    // } else if (grid.GetCell(i + 1, j + 1) == EMPTY_TYPE) {
                    //     newGrid.SetCell(i, j, EMPTY_TYPE);
                    //     newGrid.SetCell(i + 1, j + 1, SAND_TYPE);
                    }
                    break;
                default :
                    break;
            }
            // // Get the number of live neighbours for the cell
            // int liveNeighbours = CountLiveNeighbours(i, j);

            // // Update the cell value based on the rules of the Game of Life
            // if (grid.GetCell(i, j) == 0) {
            //     if (liveNeighbours == 3) {
            //         // Reproduction
            //         newGrid.SetCell(i, j, 1);
            //     } else {
            //         // No change
            //         newGrid.SetCell(i, j, 0);
            //     }
            // } else {
            //     if (liveNeighbours + grid.GetCell(i, j) < 3 || liveNeighbours + grid.GetCell(i, j)  > 4) {
            //         // Underpopulation and Overpopulation
            //         newGrid.SetCell(i, j, 0);
            //     } else {
            //         // Survival
            //         newGrid.SetCell(i, j, grid.GetCell(i, j));
            //     }
            // }
        }
    }

    // Update the grid with the new values
    grid = newGrid;
}