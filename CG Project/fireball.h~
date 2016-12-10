//
//  fireball.hpp
//  CG Project
//
//  Created by Varun Murthy Suravarapu on 04/05/16.
//  Copyright © 2016 Varun Murthy Suravarapu. All rights reserved.
//

#ifndef fireball_h
#define fireball_h

#include "constants.h"
#include <SDL2/SDL.h>

class FireBall
{
    public:
        //FireBall Constructor
        FireBall(int, int, double);
    
        //Animates and Displays the FireBall
        void Animate(int frameNum, projectilestates state);
    
        //Returns the FireBall Collider
        SDL_Rect GetRect();
    
        //Moves the FireBall Based On Player Orientation When Fired
        void Move();
    
    private:
        //The X and Y offsets of the FireBall
        int posX, posY;
        
        //The velocity of the FireBall, along each axis
        int velX, velY;
        
        //Angle FireBall is Facing
        double angle;
        
        //FireBall's collision box
        SDL_Rect collider;
};


#endif /* fireball_hpp */
