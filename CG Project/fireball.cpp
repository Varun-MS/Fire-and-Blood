//
//  fireball.cpp
//  CG Project
//
//  Created by Varun Murthy Suravarapu on 04/05/16.
//  Copyright © 2016 Varun Murthy Suravarapu. All rights reserved.
//

#include "fireball.h"
#include "globals.h"

FireBall::FireBall(int x, int y, double angle)
{
    posX = x;
    posY = y;
    collider.x = x+20;
    collider.y = y+20;
    collider.w = FIREBALL_WIDTH-40;
    collider.h = FIREBALL_HEIGHT-40;
    
    this -> angle = angle;
}

void FireBall::Animate(int frameNum, projectilestates state)
{
    //Animation Data
    SDL_Rect* currentFrame;
    
    switch(state)
    {
        case TRAVEL: currentFrame = &fireBallTravel[frameNum/24]; break;
        case IMPACT: currentFrame = &fireBallImpact[frameNum]; break;
    }
    
    fireBallSpriteSheet.Render(posX,posY,currentFrame,angle,NULL,SDL_FLIP_NONE);
}

SDL_Rect FireBall::GetRect()
{
    return collider;
}

void FireBall::Move()
{    
    velX = FIREBALL_VEL * sin(angle*(PI/180));
    velY = FIREBALL_VEL * -cos(angle*(PI/180));
    
    posX += velX;
    collider.x += velX;
    
    posY += velY;
    collider.y += velY;
}

