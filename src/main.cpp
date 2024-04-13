#include <raylib.h>
#include "simulation.hpp"
#include <iostream>
#include <cmath>
#include <string>
#include "raylib.h"

// Simulation shared consts
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

// Simulation consts
const int MENU_W = 420;
const int WIDTH_W = 1300; // MAX 1920 - 420 = 1500
const int HEIGHT_W = 900; // MAX 1080
const int CELL_DIM = 6;
const int INITIAL_RANDOM_RATE = 3;
const int INITIAL_FRAMERATE = 60;
const int MAX_FRAMERATE = 960;
const int SUBMAX_FRAMERATE = 480;
const int MIN_FRAMERATE =  15;
const std::string STATUS_RUNNING = "RUNNING";
const std::string STATUS_PAUSED = "PAUSED";
//todo add shapes
const std::string SAND_NAME = "SAND";
const std::string EMPTY_NAME = "EMPTY";
const std::string STONE_NAME = "STONE";
const std::string ACID_NAME = "ACID";

// Initialization of Simulation variables
int current_framerate = INITIAL_FRAMERATE;
int current_random_rate = INITIAL_RANDOM_RATE;
std::string current_material = SAND_NAME;
Color current_material_text_color = GOLD;
std::string simulation_status = STATUS_RUNNING;
float btn_height_1 = 0;
float btn_width_1 = 0;
Rectangle btnBounds, btnBounds2;

// Drawing menu function
void DrawControlText(Font& jupiter_crash) {
    int i=1;
    DrawTextEx(jupiter_crash,"  CONTROLS", (Vector2){WIDTH_W+60, (float)(30*i)}, 60, 3, WHITE);
    i+=4;
    // Refresh rate controls
    DrawTextEx(jupiter_crash,"Space - Start/Pause Game",(Vector2){WIDTH_W+30, (float)(30*i)}, 35, 3, RED);
    i++;
    DrawTextEx(jupiter_crash,"S - Slow down", (Vector2){WIDTH_W+30, (float)(30*i)}, 35, 3, BLUE);
    i++;
    DrawTextEx(jupiter_crash,"D - Accelerate", (Vector2){WIDTH_W+30, (float)(30*i)}, 35, 3, BLUE);
    i++;
    DrawTextEx(jupiter_crash,"F - Reset refresh rate", (Vector2){WIDTH_W+30, (float)(30*i)}, 35, 3, BLUE);
    i++;
    DrawTextEx(jupiter_crash,"G (when paused) - Play step", (Vector2){WIDTH_W+30, (float)(30*i)}, 35, 3, BLUE);
    i+=2;
    // Randomization controls
    DrawTextEx(jupiter_crash,"R - Randomize grid", (Vector2){WIDTH_W+30, (float)(30*i)}, 35, 3, YELLOW);
    i++;
    DrawTextEx(jupiter_crash,"E - Clear grid", (Vector2){WIDTH_W+30, (float)(30*i)}, 35, 3, YELLOW);
    i+=3;
    // Shape controls
    DrawTextEx(jupiter_crash,"Arrows or O/P to navigate materials", (Vector2){WIDTH_W+10, (float)(30*i)}, 30, 2, WHITE);
    i+=2;
    DrawTextEx(jupiter_crash,(""+current_material+"").c_str(), (Vector2){WIDTH_W+100, (float)(30*i)}, 35, 15, current_material_text_color);
    btn_height_1 = (float)(30*i)-7;
    btn_width_1 = WIDTH_W+20;
    i+=2;
    DrawTextEx(jupiter_crash,"Left click (hold) - Draw material", (Vector2){WIDTH_W+30, (float)(30*i)}, 25, 2, GREEN);
    i++;
    // Simulation info
    DrawTextEx(jupiter_crash,("Game status - " + simulation_status).c_str(), (Vector2){WIDTH_W + 30, HEIGHT_W - 90}, 35, 3, GRAY);
    DrawTextEx(jupiter_crash,("Current refresh rate - " + std::to_string(current_framerate) + "/sec").c_str(), (Vector2){WIDTH_W + 30, HEIGHT_W - 50}, 30, 3, GRAY);
}

// Drawing menu buttons function
void DrawControlButtons(Texture2D button_left_texture, Texture2D button_right_texture) {
    Vector2 position = (Vector2){btn_width_1,btn_height_1};
    Vector2 position2 = (Vector2){btn_width_1+45,btn_height_1};
    btnBounds = { position.x, position.y, (float)(button_left_texture.width)*0.1f, (float)(button_left_texture.height)*0.1f };
    btnBounds2 = { position2.x, position2.y, (float)(button_right_texture.width)*0.1f, (float)(button_right_texture.height)*0.1f };
    DrawTextureEx(button_left_texture, position, 0.0, 0.1, WHITE);
    DrawTextureEx(button_right_texture, position2, 0.0, 0.1, WHITE);
}

// Change material event functions
void ChangeMaterialToLeft(Simulation& simulation) {
    if (current_material == EMPTY_NAME) {
        current_material = ACID_NAME;
        current_material_text_color = LIME;
        simulation.SetMaterialType(ACID_TYPE);
    } else if (current_material == ACID_NAME) {
        current_material = STONE_NAME;
        current_material_text_color = WHITE;
        simulation.SetMaterialType(STONE_TYPE);
    } else if (current_material == STONE_NAME){
        current_material = SAND_NAME;
        current_material_text_color = GOLD;
        simulation.SetMaterialType(SAND_TYPE);
    } else if (current_material == SAND_NAME){
        current_material = EMPTY_NAME;
        current_material_text_color = RED;
        simulation.SetMaterialType(EMPTY_TYPE);
    } else {
        current_material = ACID_NAME;
        current_material_text_color = LIME;
        simulation.SetMaterialType(ACID_TYPE);
    }
}

void ChangeMaterialToRight(Simulation& simulation) {
    if (current_material == EMPTY_NAME) {
        current_material = SAND_NAME;
        current_material_text_color = GOLD;
        simulation.SetMaterialType(SAND_TYPE);
    } else if (current_material == SAND_NAME) {
        current_material = STONE_NAME;
        current_material_text_color = WHITE;
        simulation.SetMaterialType(STONE_TYPE);
    } else if (current_material == STONE_NAME){
        current_material = ACID_NAME;
        current_material_text_color = LIME;
        simulation.SetMaterialType(ACID_TYPE);
    } else if (current_material == ACID_NAME){
        current_material = EMPTY_NAME;
        current_material_text_color = RED;
        simulation.SetMaterialType(EMPTY_TYPE);
    } else {
        current_material = SAND_NAME;
        current_material_text_color = GOLD;
        simulation.SetMaterialType(SAND_TYPE);
    }
}

// Event handling function
void EventHandling(Simulation& simulation) {
    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_O)
        || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), btnBounds))) {
            // Navigate materials right to left
            ChangeMaterialToLeft(simulation);
    }
    
    else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_P)
            || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), btnBounds2))) {
        // Navigate materials left to right
        ChangeMaterialToRight(simulation);
    }
    else if (IsKeyPressed(KEY_R)) {
        // Randomize the grid
        simulation.Randomize();
    }  
    else if (IsKeyPressed(KEY_SPACE)) {
        // Start/Stop simulation
        simulation.SetRunning(!simulation.IsRunning());
        simulation.IsRunning() ? simulation_status = STATUS_RUNNING : simulation_status = STATUS_PAUSED;
    }
    else if(IsKeyPressed(KEY_G) && !simulation.IsRunning()) {
        // Play step
        simulation.Update();
    }
    else if (IsKeyPressed(KEY_D)) {
        // Accelerate simulation
        if (current_framerate < MAX_FRAMERATE) current_framerate = round(current_framerate*2) >= MAX_FRAMERATE ? MAX_FRAMERATE : round(current_framerate*2), SetTargetFPS(current_framerate);
    }
    else if (IsKeyPressed(KEY_S)) {
        // Slow down simulation
        current_framerate = (current_framerate == MAX_FRAMERATE) ? SUBMAX_FRAMERATE : (current_framerate > MIN_FRAMERATE) ? round(current_framerate/2) : current_framerate;
        SetTargetFPS(current_framerate);
    }
    else if (IsKeyPressed(KEY_F)) {
        // Reset refresh rate
        current_framerate = INITIAL_FRAMERATE;
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
}

/* ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------ Main ------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------ */
int main() {
    // Initialisation of window
    InitWindow(WIDTH_W + MENU_W, HEIGHT_W, "MaterialBox");
    SetTargetFPS(INITIAL_FRAMERATE);

    Simulation simulation(WIDTH_W, HEIGHT_W, CELL_DIM, current_random_rate);

    // Loading assets
    Image arrow_left = LoadImage("assets/arrow_left.png"); 
    Image arrow_right = LoadImage("assets/arrow_right.png"); 
    Texture2D button_left_texture = LoadTextureFromImage(arrow_left); 
    Texture2D button_right_texture = LoadTextureFromImage(arrow_right); 
    Font jupiter_crash = LoadFont("assets/fonts/jupiterc.ttf");

    Color GREY = {29,29,29,255};

    /* ------------ Simulation loop ------------ */
    while (WindowShouldClose() == false)
    {   
        // Event Handling 
        EventHandling(simulation);

        // State update
        if (simulation.IsRunning()) {
            simulation.Update();
        }
        
        // Object drawing
        BeginDrawing();
            DrawControlText(jupiter_crash);
            DrawControlButtons(button_left_texture, button_right_texture);
            ClearBackground(GREY);
            simulation.DrawGrid();
        EndDrawing();
    }
    
    // Unloading assets
    UnloadImage(arrow_left);
    UnloadImage(arrow_right);
    UnloadFont(jupiter_crash);
    UnloadTexture(button_left_texture);  // Unload button texture
    UnloadTexture(button_right_texture);  // Unload button texture

    // Closing window
    CloseWindow();
    return 0;
}

