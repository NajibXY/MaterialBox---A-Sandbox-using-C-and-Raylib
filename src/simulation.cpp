#include "simulation.hpp"
#include <raylib.h>
#include <iostream>

// Draw the grid
void Simulation::DrawGrid() {
    grid.DrawGrid();
}

// Randomize the grid
void::Simulation::Randomize() {
    grid.Randomize();
}

// Clear the grid
void::Simulation::Clear() {
    grid.Clear();
}

// Set the random rate of the grid
void::Simulation::SetRandomRate(int value) {
    grid.SetRandomRate(value);
}

// Set the shape index of the grid
void::Simulation::SetMaterialType(int value) {
    grid.SetMaterialType(value);
}

// Draw the material near the specified coordinates
void::Simulation::DrawMaterial(int x, int y) {
    grid.DrawMaterial(x, y, running);
}

// Set the value of the cell at (x, y) in the grid
void Simulation::SetCell(int x, int y, int value) {
    grid.SetCell(x, y, value);
}

// Update the simulation
void Simulation::Update() {
    // Order of logics is important 
    UpdateSandLogic();
    UpdateAcidLogic();
    UpdateStoneLogic();
}

// -------------------------------------------- STONE LOGIC --------------------------------------------

// Update the stone logic on grid
void Simulation::UpdateStoneLogic() {
    int number_of_stone_grains = 0;
    // Create a new grid to store the updated values
    Grid newGrid = grid;

    int firstHalf = grid.GetColumns()/2;
    for (int i = grid.GetRows() - 1; i > -1; i--) {
        for (int j = 0; j < firstHalf; j++) {
            if (grid.GetCell(i, j) ==  STONE_TYPE_1 || grid.GetCell(i, j) ==  STONE_TYPE_2) {
                UpdateStoneLogicOnCell(i, j, newGrid);
                number_of_stone_grains++;
            }
        }
    }
    for (int i = grid.GetRows() - 1; i > -1; i--) {
        for (int j = grid.GetColumns()-1; j >= firstHalf; j--) {
            if (grid.GetCell(i, j) ==  STONE_TYPE_1 || grid.GetCell(i, j) ==  STONE_TYPE_2) {
                UpdateStoneLogicOnCell(i, j, newGrid);
                number_of_stone_grains++;
            }
        }
    }
    // Update the grid with the new values
    grid = newGrid;
    // std::cout << "Number of Stone grains: " << number_of_stone_grains << std::endl;
}

// Update logic for a stone cell
void Simulation::UpdateStoneLogicOnCell(int x, int y, Grid& newGrid) {
    // If the cell is stone
    // Check if Acid below or at the sides
    if (newGrid.IsAcid(x + 1, y) || newGrid.IsAcid(x + 1, y - 1) || newGrid.IsAcid(x + 1, y + 1) || newGrid.IsAcid(x, y - 1) || newGrid.IsAcid(x, y + 1)) {
        int randomPenetration = GetRandomValue(0, 200);
        if (randomPenetration == 0) {
            newGrid.SetCell(x, y, EMPTY_TYPE);
        }
    }
}

// -------------------------------------------- SAND LOGIC --------------------------------------------

// Update the sand logic on grid
void Simulation::UpdateSandLogic() {
    int number_of_sand_grains = 0;
    // Create a new grid to store the updated values
    Grid newGrid = grid;

    int firstHalf = grid.GetColumns()/2;
    for (int i = grid.GetRows() - 1; i > -1; i--) {
        for (int j = 0; j < firstHalf; j++) {
            if (grid.GetCell(i, j) ==  SAND_TYPE_1 || grid.GetCell(i, j) ==  SAND_TYPE_2 || grid.GetCell(i, j) ==  SAND_TYPE_3) {
                UpdateSandLogicOnCell(i, j, newGrid);
                number_of_sand_grains++;
            }
        }
    }
    for (int i = grid.GetRows() - 1; i > -1; i--) {
        for (int j = grid.GetColumns()-1; j >= firstHalf; j--) {
            if (grid.GetCell(i, j) ==  SAND_TYPE_1 || grid.GetCell(i, j) ==  SAND_TYPE_2 || grid.GetCell(i, j) ==  SAND_TYPE_3) {
                UpdateSandLogicOnCell(i, j, newGrid);
                number_of_sand_grains++;
            }
        }
    }
    // Update the grid with the new values
    grid = newGrid;
    // std::cout << "Number of Sand grains: " << number_of_sand_grains << std::endl;
}

// Update logic for a sand cell
void Simulation::UpdateSandLogicOnCell(int x, int y, Grid& newGrid) {
    // If the cell is sand
    // Check if Acid below or at the sides
    if (newGrid.IsAcid(x + 1, y) || newGrid.IsAcid(x + 1, y - 1) || newGrid.IsAcid(x + 1, y + 1) || newGrid.IsAcid(x, y - 1) || newGrid.IsAcid(x, y + 1)) {
        int randomPenetration = GetRandomValue(0, 200);
        if (randomPenetration == 0) {
            newGrid.SetCell(x, y, EMPTY_TYPE);
        }
    }
    // Check if the cell is not at the limit of the grid
    else if (!newGrid.IsAtBottomLimit(x, y) || newGrid.IsEmpty(x + 1, y)) { 
        // Empty below
        // Check if the cell below is empty or below right or below left
        if (newGrid.IsEmpty(x + 1, y)) {
            newGrid.SetCell(x, y, EMPTY_TYPE);
            newGrid.SetCell(x + 1, y, GetRandomSandValue());
        } else if (newGrid.IsEmpty(x + 1, y - 1) && newGrid.IsEmpty(x + 1, y + 1)) {
            int randomDirection = GetRandomValue(0, 1);
            if (randomDirection == 0) {
                newGrid.SetCell(x, y, EMPTY_TYPE);
                newGrid.SetCell(x + 1, y - 1, GetRandomSandValue());
            } else {
                newGrid.SetCell(x, y, EMPTY_TYPE);
                newGrid.SetCell(x + 1, y + 1, GetRandomSandValue());
            }
        } else if (newGrid.IsEmpty(x + 1, y - 1)) {
            newGrid.SetCell(x, y, EMPTY_TYPE);
            newGrid.SetCell(x + 1, y - 1, GetRandomSandValue());
        } else if (newGrid.IsEmpty(x + 1, y + 1)) {
            newGrid.SetCell(x, y, EMPTY_TYPE);
            newGrid.SetCell(x + 1, y + 1, GetRandomSandValue());
        }
    } 
}

// -------------------------------------------- ACID LOGIC --------------------------------------------

// Update the acid logic on grid
void Simulation::UpdateAcidLogic() {
    int number_of_acid_grains = 0;
    // Create a new grid to store the updated values
    Grid newGrid = grid;

    int firstHalf = grid.GetColumns()/2;
    for (int i = grid.GetRows() - 1; i > -1; i--) {
        for (int j = 0; j < firstHalf; j++) {
            if (grid.GetCell(i, j) ==  ACID_TYPE_1 || grid.GetCell(i, j) ==  ACID_TYPE_2) {
                UpdateAcidLogicOnCell(i, j, newGrid);
                number_of_acid_grains++;
            }
        }
    }
    for (int i = grid.GetRows() - 1; i > -1; i--) {
        for (int j = grid.GetColumns()-1; j >= firstHalf; j--) {
            if (grid.GetCell(i, j) ==  ACID_TYPE_1 || grid.GetCell(i, j) ==  ACID_TYPE_2) {
                UpdateAcidLogicOnCell(i, j, newGrid);
                number_of_acid_grains++;
            }
        }
    }
    // Update the grid with the new values
    grid = newGrid;
    // std::cout << "Number of Acid grains: " << number_of_acid_grains << std::endl;
}

// Update logic for an acid cell
void Simulation::UpdateAcidLogicOnCell(int x, int y, Grid& newGrid) {
    // Same movement as sand with a bit more randomness
    // Acid effects on below cells
    int randomPenetration = GetRandomValue(0, 200);
    int randomDelta = GetRandomValue(0, 1);
    int delta = 1;
    if (randomDelta == 0) {
        delta = -1;
    }
    if (newGrid.IsInBounds(x + 1, y) && newGrid.GetCell(x + 1, y) != ACID_TYPE_1 && newGrid.GetCell(x + 1, y) != ACID_TYPE_2){
        if (newGrid.IsEmpty(x + 1, y)) {
            randomPenetration = 0;
        }
        if (randomPenetration == 0) {
            newGrid.SetCell(x, y, EMPTY_TYPE);
            newGrid.SetCell(x + 1, y, GetRandomAcidValue());
        }
    } else if (newGrid.IsInBounds(x + 1, y + delta) && newGrid.GetCell(x + 1, y + delta) != ACID_TYPE_1 && newGrid.GetCell(x + 1, y + delta) != ACID_TYPE_2) {
        if (newGrid.IsEmpty(x + 1, y + delta)) {
            randomPenetration = 0;
        }
        if (randomPenetration == 0) {
            newGrid.SetCell(x, y, EMPTY_TYPE);
            newGrid.SetCell(x + 1, y + delta, GetRandomAcidValue());
        }
    } else if (!newGrid.IsAtLimit(x, y) 
    && newGrid.IsInBounds(x, y + delta) && newGrid.GetCell(x, y + delta) != ACID_TYPE_1 && newGrid.GetCell(x, y + delta) != ACID_TYPE_2) {
        int random = GetRandomValue(0, 10);
        if (random == 0) {
            newGrid.SetCell(x, y, EMPTY_TYPE);
            newGrid.SetCell(x, y + delta, GetRandomAcidValue());
        }
    }
}

// -------------------------------------------- Randomizers --------------------------------------------

// Get a random sand type
int Simulation::GetRandomSandValue() {
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

// Get a random sand type
int Simulation::GetRandomAcidValue() {
    int randomAcid = GetRandomValue(0, 1);
    if (randomAcid == 0) {
        return ACID_TYPE_1;
    } else {
        return ACID_TYPE_2;
    }
    return ACID_TYPE_1;
}