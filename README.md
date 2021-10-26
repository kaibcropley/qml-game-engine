# QML Game Engine
The purpose of this project is to develop a usable QML game engine. This is a personal project with the goal of being able to develop my own Qt / QML games.

# Design
The majority of the game logic is built in Qt C++ and is exposed to QML through signal/slots, qproperties and qinvokable functions. This is for a few reasons, but the highest of all being keeping applications as performant as possible.

Many UI objects are subclassed from C++ QtQuick classes. This is to give the UI elements any required game data, for example: GridBasedEntities.qml is the UI element of a grid games entity, but it is a subclass of GridEntity from gridentity.h/.cpp which contains the true gridPos (grid x/y positioning) and registered with the Entity Manager to gain access to things like path finding.

# Development Plans
The end goal of this project is to have a Qt Library that allows for easy development of multiple types of QML games

## Implemented

### Grid Game
Defined as any 2D game that requires a grid, with entities that can move around it.
- C++ grid creation and grid square management
- A* path finding for AI entities
- Player controlled movement
- Interaction between entities

### Phsyics Game
Defined as any 2D game that uses phsyics (Collisions, Gravity, etc.). The name may change because I'd like to include multiple game types in here, such as 2D platforms, side scrollers and top down games
- Collisions between Circles and Rectangles (Assuming no rotation has been done to the rectangle)
- Top Down movement, with player controls included

## Planned Implementation 
Largest thing to still do is turn this into a Qt Lib, currently it is structured as a Qt project until I feel I've built a large enough set of tools to release it as a library.

### Grid Game
- Some performance optimizations

### Phsyics Game
- Different movement types and controller types
- Better Sprite handling, likely with some state machine where the entity can set its sprite based on the current state that it's in
