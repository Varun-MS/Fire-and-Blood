//
//  fireball.hpp
//  CG Project
//
//  Created by Varun Murthy Suravarapu on 04/05/16.
//  Copyright © 2016 Varun Murthy Suravarapu. All rights reserved.
//

#ifndef fireball_h
#define fireball_h

#include <SDL2/SDL.h>
#include "constants.h"

class FireBall
{
    public:    
        //Fireball Constructor
        FireBall();
    
        //Animates and Displays the FireBall
        void Animate();
    
        //Returns the FireBall Collider
        SDL_Rect GetRect();
    
        //Moves the FireBall Based On Player Orientation When Fired
        void Move();
    
        //Sets the FireBall's Postion
        void SetPos(int, int);
    
        //Sets the FireBall's Postion
        void SetAngle(int);
    
        //Returns and Sets Player State
        projectilestates GetState();
    
        //Sets the Player State to a Particular Value in the State Enumeration
        void SetState(projectilestates);
    
    private:
        //The X and Y offsets of the FireBall
        int posX, posY;
        
        //The velocity of the FireBall, along each axis
        int velX, velY;
        
        //Angle FireBall is Facing
        double angle;
        
        //FireBall's collision box
        SDL_Rect collider;
    
        //Tells FireBall Which Frame from the SpriteSheet to Use for Animation
        int frameNum;
    
        //State of the Fireball
        projectilestates state;
};


#endif /* fireball_h */
