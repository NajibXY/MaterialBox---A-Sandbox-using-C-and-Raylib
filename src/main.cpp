#include <raylib.h>
#include "simulation.hpp"
#include <iostream>
#include <cmath>
#include <string>
#include "raylib.h"

// Simulation consts

extern const int EMPTY_TYPE = 0;
extern const int SAND_TYPE = 1;
extern const int SAND_TYPE_1 = 11;
extern const int SAND_TYPE_2 = 12;
extern const int SAND_TYPE_3 = 13;
extern const int STONE_TYPE = 2;
extern const int STONE_TYPE_1 = 21;
extern const int STONE_TYPE_2 = 22;
extern const int ACID_TYPE = 3;
extern const int ACID_TYPE_1 = 31;
extern const int ACID_TYPE_2 = 32;


const int MENU_W = 420;
const int WIDTH_W = 1300; // MAX 1920 - 420 = 1500
const int HEIGHT_W = 900; // MAX 1080
const int CELL_DIM = 6;
const int INITIAL_RANDOM_RATE = 3;
const int INITIAL_FRAMERATE = 60;
const int MAX_FRAMERATE = 1000;
const int SUBMAX_FRAMERATE = 640;
const int MIN_FRAMERATE =  30;
//todo add shapes
const std::string SAND_NAME = "SAND";
const std::string EMPTY_NAME = "EMPTY";
const std::string STONE_NAME = "STONE";
const std::string ACID_NAME = "ACID";

// Simulation variables
int FRAMERATE = INITIAL_FRAMERATE;
int RANDOM_RATE = INITIAL_RANDOM_RATE;
std::string CURRENT_MATERIAL = SAND_NAME;
Color CURRENT_MATERIAL_TEXT_COLOR = GOLD;
std::string SIMULATION_STATUS = "Initialized";

float btn_height_1 = 0;
float btn_width_1 = 0;
Rectangle btnBounds;

void DrawControlText() {
    int i=1;
    DrawText("  Controls", WIDTH_W+60, 30*i, 40, WHITE);
    i++;
    DrawText("  ---------", WIDTH_W+60, 30*i, 40, WHITE);
    i+=2;
    // Refresh rate controls
    DrawText("Space : Start/Stop simulation", WIDTH_W+30, 30*i, 20, BLUE);
    i++;
    DrawText("S : Slow down simulation", WIDTH_W+30, 30*i, 20, BLUE);
    i++;
    DrawText("D : Accelerate simulation", WIDTH_W+30, 30*i, 20, BLUE);
    i++;
    DrawText("F : Reset refresh rate", WIDTH_W+30, 30*i, 20, BLUE);
    i++;
    DrawText("G (when paused) : Play step", WIDTH_W+30, 30*i, 20, BLUE);
    i+=2;
    // Randomization controls
    DrawText("R : Randomize grid", WIDTH_W+30, 30*i, 20, YELLOW);
    i++;
    DrawText("E : Clear grid", WIDTH_W+30, 30*i, 20, YELLOW);
    i+=2;
    // Shape controls
    DrawText("Arrows or O/P to navigate materials", WIDTH_W+30, 30*i, 20, WHITE);
    i++;
    DrawText((""+CURRENT_MATERIAL+"").c_str(), WIDTH_W+100, 30*i, 40, CURRENT_MATERIAL_TEXT_COLOR);
    btn_height_1 = (30*i)-5;
    btn_width_1 = WIDTH_W+30;
    i+=3;
    DrawText("Left click (hold) : Draw material", WIDTH_W+30, 30*i, 20, GREEN);
    i++;

    // Simulation info
    DrawText(("Simulation status : " + SIMULATION_STATUS).c_str(), WIDTH_W + 30, HEIGHT_W - 110, 20, GRAY);
    DrawText(("Current refresh rate : " + std::to_string(FRAMERATE) + "/sec").c_str(), WIDTH_W + 30, HEIGHT_W - 50, 20, GRAY);
}

int main()
{
    Color GREY = {29,29,29,255};

    // Initialisation of window
    InitWindow(WIDTH_W + MENU_W, HEIGHT_W, "MaterialBox");
    SetTargetFPS(INITIAL_FRAMERATE);

    Simulation simulation(WIDTH_W, HEIGHT_W, CELL_DIM, RANDOM_RATE);

    // Load arrow images
    Image arrow_left = LoadImage("assets/arrow_left.png"); 
    Image arrow_right = LoadImage("assets/arrow_right.png"); 
    Texture2D button_left_texture = LoadTextureFromImage(arrow_left); 
    Texture2D button_right_texture = LoadTextureFromImage(arrow_right); 

    /* ------------ Simulation loop ------------*/
    while (WindowShouldClose() == false)
    {   
        // Event Handling 
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            std::cout << "PRESSED" << std::endl;
            Vector2 mousePos = GetMousePosition();
            if (CheckCollisionPointRec(mousePos, btnBounds)){
                std::cout << "COLLISION" << std::endl;
                // Navigate materials right to left
                if (CURRENT_MATERIAL == EMPTY_NAME) {
                    CURRENT_MATERIAL = ACID_NAME;
                    CURRENT_MATERIAL_TEXT_COLOR = LIME;
                    simulation.SetMaterialType(ACID_TYPE);
                } else if (CURRENT_MATERIAL == ACID_NAME) {
                    CURRENT_MATERIAL = STONE_NAME;
                    CURRENT_MATERIAL_TEXT_COLOR = WHITE;
                    simulation.SetMaterialType(STONE_TYPE);
                } else if (CURRENT_MATERIAL == STONE_NAME){
                    CURRENT_MATERIAL = SAND_NAME;
                    CURRENT_MATERIAL_TEXT_COLOR = GOLD;
                    simulation.SetMaterialType(SAND_TYPE);
                } else if (CURRENT_MATERIAL == SAND_NAME){
                    CURRENT_MATERIAL = EMPTY_NAME;
                    CURRENT_MATERIAL_TEXT_COLOR = RED;
                    simulation.SetMaterialType(EMPTY_TYPE);
                } else {
                    CURRENT_MATERIAL = ACID_NAME;
                    CURRENT_MATERIAL_TEXT_COLOR = LIME;
                    simulation.SetMaterialType(ACID_TYPE);
                }
            }
        }
        else if (IsKeyPressed(KEY_R)) {
            // Randomize the grid
            simulation.Randomize();
        }  
        else if (IsKeyPressed(KEY_SPACE)) {
            // Start/Stop simulation
            simulation.SetRunning(!simulation.IsRunning());
            simulation.IsRunning() ? SIMULATION_STATUS = "Running" : SIMULATION_STATUS = "Paused";
        }
        else if(IsKeyPressed(KEY_G) && !simulation.IsRunning()) {
            // Play step
            simulation.Update();
        }
        else if (IsKeyPressed(KEY_D)) {
            // Accelerate simulation
            if (FRAMERATE < MAX_FRAMERATE) FRAMERATE = round(FRAMERATE*2) >= MAX_FRAMERATE ? MAX_FRAMERATE : round(FRAMERATE*2), SetTargetFPS(FRAMERATE);
        }
        else if (IsKeyPressed(KEY_S)) {
            // Slow down simulation
            FRAMERATE = (FRAMERATE == MAX_FRAMERATE) ? SUBMAX_FRAMERATE : (FRAMERATE > MIN_FRAMERATE) ? round(FRAMERATE/2) : FRAMERATE;
            SetTargetFPS(FRAMERATE);
        }
        else if (IsKeyPressed(KEY_F)) {
            // Reset refresh rate
            FRAMERATE = INITIAL_FRAMERATE;
            SetTargetFPS(INITIAL_FRAMERATE);
        }
        else if (IsKeyPressed(KEY_E)) {
            // Clear the grid
            simulation.Clear();
        }
        else if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            // Draw selected shape
            Vector2 mousePos = GetMousePosition();
            simulation.DrawMaterial(mousePos.y/CELL_DIM, mousePos.x/CELL_DIM);
        }
        else if (IsKeyPressed(KEY_O)) {
            // Navigate materials right to left
            if (CURRENT_MATERIAL == EMPTY_NAME) {
                CURRENT_MATERIAL = ACID_NAME;
                CURRENT_MATERIAL_TEXT_COLOR = LIME;
                simulation.SetMaterialType(ACID_TYPE);
            } else if (CURRENT_MATERIAL == ACID_NAME) {
                CURRENT_MATERIAL = STONE_NAME;
                CURRENT_MATERIAL_TEXT_COLOR = WHITE;
                simulation.SetMaterialType(STONE_TYPE);
            } else if (CURRENT_MATERIAL == STONE_NAME){
                CURRENT_MATERIAL = SAND_NAME;
                CURRENT_MATERIAL_TEXT_COLOR = GOLD;
                simulation.SetMaterialType(SAND_TYPE);
            } else if (CURRENT_MATERIAL == SAND_NAME){
                CURRENT_MATERIAL = EMPTY_NAME;
                CURRENT_MATERIAL_TEXT_COLOR = RED;
                simulation.SetMaterialType(EMPTY_TYPE);
            } else {
                CURRENT_MATERIAL = ACID_NAME;
                CURRENT_MATERIAL_TEXT_COLOR = LIME;
                simulation.SetMaterialType(ACID_TYPE);
            }
        }
        else if (IsKeyPressed(KEY_P)) {
            // Navigate materials left to right
            if (CURRENT_MATERIAL == EMPTY_NAME) {
                CURRENT_MATERIAL = SAND_NAME;
                CURRENT_MATERIAL_TEXT_COLOR = GOLD;
                simulation.SetMaterialType(SAND_TYPE);
            } else if (CURRENT_MATERIAL == SAND_NAME) {
                CURRENT_MATERIAL = STONE_NAME;
                CURRENT_MATERIAL_TEXT_COLOR = WHITE;
                simulation.SetMaterialType(STONE_TYPE);
            } else if (CURRENT_MATERIAL == STONE_NAME){
                CURRENT_MATERIAL = ACID_NAME;
                CURRENT_MATERIAL_TEXT_COLOR = LIME;
                simulation.SetMaterialType(ACID_TYPE);
            } else if (CURRENT_MATERIAL == ACID_NAME){
                CURRENT_MATERIAL = EMPTY_NAME;
                CURRENT_MATERIAL_TEXT_COLOR = RED;
                simulation.SetMaterialType(EMPTY_TYPE);
            } else {
                CURRENT_MATERIAL = SAND_NAME;
                CURRENT_MATERIAL_TEXT_COLOR = GOLD;
                simulation.SetMaterialType(SAND_TYPE);
            }
        }

        // State update
        if (simulation.IsRunning()) {
            simulation.Update();
        }
        
        // Object drawing
        BeginDrawing();
            DrawControlText();
            Vector2 position = (Vector2){btn_width_1,btn_height_1};
            Vector2 position2 = (Vector2){btn_width_1+200,btn_height_1};
            btnBounds = { position.x, position.y, (float)button_left_texture.width*0.1, button_left_texture.height*0.1 };
            DrawTextureEx(button_left_texture, position, 0.0, 0.1, WHITE);
            DrawTextureEx(button_right_texture, position2, 0.0, 0.1, WHITE);
            ClearBackground(GREY);
            simulation.DrawGrid();
        EndDrawing();
    }
    
    UnloadImage(arrow_left);
    UnloadImage(arrow_right);
    UnloadTexture(button_left_texture);  // Unload button texture
    UnloadTexture(button_right_texture);  // Unload button texture
    // Closing window
    CloseWindow();
    return 0;
}

