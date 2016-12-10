//
//  functions.hpp
//  CG Project
//
//  Created by Varun Murthy Suravarapu on 04/05/16.
//  Copyright © 2016 Varun Murthy Suravarapu. All rights reserved.
//

#ifndef functions_h
#define functions_h

#include "tile.h"
#include <SDL2/SDL.h>
#include "players.h"

//Initializes All Necessary Libraries
bool InitLibraries ( void );

//Loads All Assets
bool LoadMedia( Tile* tiles[]);

//Closes All Libraries and Unneeded Files
void Close( Tile* tiles[]);

//Box collision detector
bool CheckCollision( SDL_Rect a, SDL_Rect b );

//Sets tiles from tile map
bool SetTiles( Tile *tiles[] );

//Checks collision box against set of tiles
bool TouchesWall( SDL_Rect box, Tile* tiles[] );

//Check collision between players
bool PlayerCollision( Kid* kid, Zombie* zombie );

//Finds the angle wrt X Axis; Given Any Two Points
double FindAngle (int x1, int x2, int y1, int y2);

//Sees If The Fireball Hits ANY Object
bool FireBallCollision( Kid* kid, Zombie* zombie, Tile* tiles[] );

//Sees If The Fireball Hits the Zombie
bool ProjectileImpact(Zombie* zombie);
#endif /* functions_h */
