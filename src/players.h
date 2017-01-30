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

//Base Class is called Player, which defines common functions between both players.
class Player
{
    public:
        //Player Constructor that Initializes Common Traits.
        Player();
    
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
    
        //Determines whether the Player is Glowing Red
        bool isGlowing;
    
        //View and Set Player Health
        int GetHealth();
        void SetHealth(int);
    
    
    
    protected: //Inherited Classes Will Inherit as Private
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
    
        //Used to Modulate the Texture Colors
        Uint8 r,g,b;
    
        //Makes the Player Glow Red if Necessary
        void changeColor();
    
        //Sets the Particular Frame of the SpriteSheet to be Displayed
        int frameNum;
    
        //Health of the Player
        int health;
    
};

//The Protagonist Behaviour Wrapper Class, inherited from Player Class, and defines Kid Specific Functions.
class Kid : public Player
{
    public:
        //Initializes the variables
        Kid();
    
        //Takes key presses and adjusts the Kid's velocity
        void HandleEvent( SDL_Event& e );
    
        //Moves the Kid and checks collision with appropriate Tiles
        void Move( Tile* tiles[]);
        
        //Displays and Animates Kid On Screen
        void Animate();
};

//The Antagonist Behaviour Wrapper Class, inherited from Player Class, and defines Zombie Specific Functions.
class Zombie : public Player
{
    public:
        //Initializes the variables
        Zombie();
    
        //Takes key presses and adjusts the Zombie's velocity
        void HandleEvent( SDL_Event& e );
        
        //Moves the Zombie and checks collision with appropriate Tiles
        void Move( Tile* tiles[] );
    
        //Displays and Animates the Zombie On Screen
        void Animate();
};

#endif /* players_h */
