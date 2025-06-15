# 🧠 Memory Match Game  
A feature-rich memory matching card game built with C++ and Raylib, designed to challenge players concentration with multiple difficulty levels. This project demonstrates object-oriented programming principles, custom data structures, and clean game state management.

## 🎯 Overview
Memory Match Game challenges players to find matching pairs of cards across three difficulty levels (Easy, Medium, Hard). Built with Raylib, it demonstrates object-oriented programming principles through custom implementations of strings (`MyStr`) and dynamic arrays (`MyVector`). The game tracks player moves and provides visual feedback for an engaging experience.

## 🗺 Flowchart
[![Memory Match Game Flowchart](Assets/Images/flowchart.png)  ](https://github.com/bscs24066/Memory-Match-Game/blob/main/Flowchart.png?raw=true)
*Visual representation of game states and transitions*

## ✨ Features
- *Difficulty Levels*:  
  - Easy (4 pairs)  
  - Medium (6 pairs)  
  - Hard (8 pairs)  
- *Move Counter*: Tracks player efficiency  
- *Custom Data Structures*:  
  - `MyStr`: Lightweight string implementation  
  - `MyVector`: Template-based dynamic array  
- *Visual Feedback*: Card-flip animations and match highlighting  
- *Polymorphic Design*: Extensible level system through `GameLevel` hierarchy  

## 🧩 UML Diagram  
[![Memory Match UML](Assets/Images/uml.png)  ](https://github.com/bscs24066/Memory-Match-Game/blob/main/UML.png?raw=true)


## 🛠️ Technical Implementation
- **OOP Principles**:  
  - Inheritance via `GameLevel` base class  
  - Encapsulation in card/board logic  
- **Memory Management**:  
  - RAII for texture handling  
  - Manual memory management in `MyVector`  
- **Raylib Integration**:  
  - Texture-based rendering  
  - Collision detection for card clicks  
