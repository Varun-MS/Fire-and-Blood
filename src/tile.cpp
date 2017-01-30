//
//  tile.cpp
//  CG Project
//
//  Created by Varun Murthy Suravarapu on 04/05/16.
//  Copyright © 2016 Varun Murthy Suravarapu. All rights reserved.
//

#include "tile.h"
#include "constants.h"
#include "globals.h"

Tile::Tile(int x, int y, int tileType)
{
    posX = x;
    posY = y;
    
    this->tileType = tileType;
    
    collider.x=posX;
    collider.y=posY;
    collider.w=TILE_WIDTH;
    collider.h=TILE_HEIGHT;
}

void Tile::Render()
{
    SDL_Rect * currentTile;
    
    currentTile = &tilesRects[texture];
    
    tilesSpriteSheet.Render(posX,posY,currentTile,NULL,NULL,SDL_FLIP_NONE);
}

SDL_Rect Tile::GetRect()
{
    return collider;
}

int Tile::GetType()
{
    return tileType;
}


