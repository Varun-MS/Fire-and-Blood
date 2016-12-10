//
//  players.hpp
//  CG Project
//
//  Created by Varun Murthy Suravarapu on 04/05/16.
//  Copyright © 2016 Varun Murthy Suravarapu. All rights reserved.
//

#ifndef players_h
#define players_h

#include <SDL2/SDL.h>
#include "constants.h"
#include "tile.h"

class Player
{
    public:
        //Returns Angle of Player
        double GetAngle();
        
        //Returns The Players Collision Rectangle
        SDL_Rect GetRect();
        
        //Returns and Sets Player State
        playerstates GetState();
    
        //Sets the Player State to a Particular Value in the State Enumeration
        void SetState(playerstates);
    
        //Returns X Position of the Player
        int GetXPos();
        
        //Returns Y Position of the Player
        int GetYPos();
    
    protected: //Do Inherited Classes Will Inherit as Private
        //Player State Variable
        playerstates state;
        
        //The X and Y offsets of the Player
        int posX, posY;
        
        //The velocity of the Player
        int velX, velY;
        
        //Angle Kid is Facing
        double angle;
        
        //Kid's collision box
        SDL_Rect collider;
};

//The Protagonist Behaviour Wrapper Class
class Kid : public Player
{
    public:
        //Initializes the variables
        Kid();
    
        //Takes key presses and adjusts the Kid's velocity
        void HandleEvent( SDL_Event& e);
    
        //Moves the Kid and checks collision with appropriate Tiles
        void Move( Tile* tiles[], Uint8*, Uint8*, Uint8*, playerstates state );
        
        //Displays and Animates Kid On Screen
        void Animate(int frameNum, Uint8 r, Uint8 g, Uint8 b, playerstates state );
};

//The Antagonist Behaviour Wrapper Class
class Zombie : public Player
{
    public:
        //Initializes the variables
        Zombie();
    
        //Takes key presses and adjusts the Zombie's velocity
        void HandleEvent( SDL_Event& e );
        
        //Moves the Zombie and checks collision with appropriate Tiles
        void Move( Tile* tiles[], Uint8*, Uint8*, Uint8* );
    
        //Displays and Animates the Zombie On Screen
        void Animate(int frameNum, playerstates state, Uint8 r, Uint8 g, Uint8 b);
};

#endif /* players_h */
