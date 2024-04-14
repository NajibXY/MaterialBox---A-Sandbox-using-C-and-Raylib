# MaterialBox - a C++ Sandbox with the Raylib library

## Author: [Najib El khadir](https://github.com/NajibXY)
## French Version [README-fr](https://github.com/NajibXY/MaterialBox---A-Sandbox-using-CPP-and-Raylib/blob/master/README-fr.md)

## 1. Motivations

<img align="right" src="https://github.com/NajibXY/MaterialBox---A-Sandbox-using-CPP-and-Raylib/blob/master/assets/gifs/main.gif">

As part of my experimentations with the Raylib library, and always focusing on cellular automata, I reworked my project of Game of Life simulation ([Game of Life in C++ with the Raylib library](https://github.com/NajibXY/Game-Of-Life-using-CPP-and-Raylib/blob/master/README.md)) and developed another project : MaterialBox, an interactive sandbox where the user can play with different materials. </br></br>
This sandbox simulates several physical rules, and I found great pleasure in getting mesmerized with the renders it can produce.
</br> </br> </br> </br>

## 2. Technologies used

- C++14
- Raylib library for video game development: I've been wanting to test this easy-to-use library for a while, which offers very good tools for the development of 2D games (and more generally, interfaces).
- The template used for configuring the Raylib project comes from this repository: https://github.com/educ8s/Raylib-CPP-Starter-Template-for-VSCODE-V2

## 3. Game Rules

- The user can draw multiple materials by holding down the left mouse button.
- The user can choose the material to draw by following the instructions on the control window.
- Each material has its specific activity rules and interacts with other materials.

#### Implemented user Controls

- Grid randomization (Key R) : randomization adds randomly placed sand particles and randomly generated stone structures in the canvas
- Grid cleaning (Key E)
- Game acceleration and deceleration (Keys S, D & F)
- Pause / Resume the game (Space key)
- Play a refresh step (Key G)
- Change the selected material (Keys O/P or Left/Right or Clicks on the appropriate buttons)
![](https://github.com/NajibXY/MaterialBox---A-Sandbox-using-CPP-and-Raylib/blob/master/assets/gifs/random.gif)

## 4. Implemented Materials

### Sand

- Basic material of the simulation
- Propagates like sand in the real world
- Gets blocked by stone and seeps wherever it can
- Dissolves gradually in acid  
![](https://github.com/NajibXY/MaterialBox---A-Sandbox-using-CPP-and-Raylib/blob/master/assets/gifs/sand.gif)

### Stone

- Forms static blocks on the drawing grid 
- Blocks the passage of sand
- When randomizing the canvas, randomly generated stone structures are placed
- Dissolves gradually upon contact with acid   
![](https://github.com/NajibXY/MaterialBox---A-Sandbox-using-CPP-and-Raylib/blob/master/assets/gifs/stone.gif)

### Acid

- Spreads more easily than sand
- Gradually corrodes stone
- Gradually dissolves sand
- Forms visually unpredictable puddles
- Simple random rules make the behavior of this material particularly satisfying to observe   
![](https://github.com/NajibXY/MaterialBox---A-Sandbox-using-CPP-and-Raylib/blob/master/assets/gifs/acid.gif)

### Empty Space

- Empty spaces can be reintroduced by selecting the "Empty" material
- This affects the simulation regardless of whether it is paused or not
- It's actually quite fun to pause the simulation, add some empty space, then resume the simulation and observe what happens   
![](https://github.com/NajibXY/MaterialBox---A-Sandbox-using-CPP-and-Raylib/blob/master/assets/gifs/empty.gif)

## 5. Possible Improvements

- Add more materials ! And more interactions between them !!! (Fire, water, gas, etc.)
- Add sounds when selecting materials; and make the selection buttons more interactive
- Make the grid size customizable
- Add a velocity grid to give acceleration to the particles of different materials when relevant
- Use Classes and more object-oriented programming instead of the values used in the main grid of the simulation (even though the simulation is currently greatly designed to be smooth and efficient)
- Add counters

</br>
</br>

## 6. Running the Project

- If you simply want to have fun with the simulation, you can download the .exe file from the main repository: [materialbox.exe](https://github.com/NajibXY/MaterialBox---A-Sandbox-using-CPP-and-Raylib/blob/master/materialbox.exe)

## Compilation, duplication, and improvement of the project

### Prerequisites

- Installation of C++ (preferably 14)
- Installation of Raylib for C++: https://www.raylib.com/

### Steps

- Download or Fork the project
- Open the project in VS Code via the main.code-workspace file
- Press F5 to compile and run
- From there, you can make any modifications you want to the project fork
