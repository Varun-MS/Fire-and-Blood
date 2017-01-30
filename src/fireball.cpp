//
//  fireball.cpp
//  CG Project
//
//  Created by Varun Murthy Suravarapu on 04/05/16.
//  Copyright © 2016 Varun Murthy Suravarapu. All rights reserved.
//

#include "fireball.h"
#include "globals.h"

//Fireball Constructor
FireBall::FireBall()
{
    frameNum = 0;
    state = INVISIBLE;
}

//Animates Fireball Based on its State
void FireBall::Animate()
{
    //Animation Data
    SDL_Rect* currentFrame;
    
    //Animation Frame only Updated if Fireball Visible
    if (state != INVISIBLE)
    {
        frameNum++;
    }
    
    //Animates based on Fireball State
    if (state == TRAVEL)
    {
        if( frameNum/4 >= FIREBALL_TRAVEL_ANIMATION_FRAMES )
        {
            frameNum = 0;
        }
    }
    
    if (state == IMPACT)
    {
        if( frameNum/4 >= FIREBALL_IMPACT_ANIMATION_FRAMES )
        {
            frameNum = 6;
        }
    }
    
    //Renders the Fireballs Based on their state. If the Fireball is invisible no rendering occurs.
    switch(state)
    {
        case TRAVEL: currentFrame = &fireBallTravel[frameNum/4];
                     fireBallSpriteSheet.Render(posX,posY,currentFrame,angle,NULL,SDL_FLIP_NONE);
                     break;
        case IMPACT: currentFrame = &fireBallImpact[frameNum/4];
                     fireBallSpriteSheet.Render(posX,posY,currentFrame,angle,NULL,SDL_FLIP_NONE);
                     break;
        case INVISIBLE:
        default: ;
    }
}

//Collision Rectangle for Fireball
SDL_Rect FireBall::GetRect()
{
    return collider;
}

//Depending on direction Player is Facing when Fireball Fired, X and Y velocity od the Fireball is Determined, and moved appropriately
void FireBall::Move()
{    
    velX = FIREBALL_VEL * sin(angle*(PI/180));
    velY = FIREBALL_VEL * -cos(angle*(PI/180));
    
    posX += velX;
    collider.x += velX;
    
    posY += velY;
    collider.y += velY;
}

//The following two functions are called when the Fireball needs to moved or "spawned" at the player's position
void FireBall::SetPos(int x, int y)
{
    posX = x;
    posY = y;
    
    collider.x = x+20;
    collider.y = y+20;
    collider.w = FIREBALL_WIDTH-40;
    collider.h = FIREBALL_HEIGHT-40; 
}

void FireBall::SetAngle(int angle)
{
    this -> angle = angle;
}

//Used to Manipulate the Fireball's Internal State
void FireBall::SetState(projectilestates state)
{
    this -> state = state;
}

projectilestates FireBall::GetState()
{
    return state;
}

