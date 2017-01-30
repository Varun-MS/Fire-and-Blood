//
//  tile.hpp
//  CG Project
//
//  Created by Varun Murthy Suravarapu on 04/05/16.
//  Copyright © 2016 Varun Murthy Suravarapu. All rights reserved.
//

#ifndef tile_h
#define tile_h

#include <SDL2/SDL.h>

class Tile
{
public:
    //Constructor
    Tile(int x, int y, int tileType);
    
    //Draws The Tile
    void Render();
    
    //Returns The Tile Collider, for Collision Detection
    SDL_Rect GetRect();
    
    //Returns the Tile Type
    int GetType();
    
    //A Texture Index Associated With The Tile
    int texture;
    
private:
    //Tile Collision Box
    SDL_Rect collider;
    
    //X and Y Position of the Tile
    int posX, posY;
    
    //The Type of Tile
    int tileType;
};

#endif /* tile_hpp */
