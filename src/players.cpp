//
//  players.cpp
//  CG Project
//
//  Created by Varun Murthy Suravarapu on 04/05/16.
//  Copyright © 2016 Varun Murthy Suravarapu. All rights reserved.
//

#include "players.h"
#include "functions.h"
#include "globals.h"
#include "constants.h"

Player::Player()
{
    frameNum = 0;
    health = 4000;
}

int Player::GetXPos()
{
    return posX;
}

int Player::GetYPos()
{
    return posY;
}

void Player::changeColor()
{
    if (isGlowing)
        g = 32;
    
    else
        g = 255;
}

int Player::GetHealth()
{
    return health;
}

void Player::SetHealth(int health)
{
    this->health = health;
}


Kid::Kid()
{
    //Initialize the offsets
    posX = 100;
    posY = 100;
    
    //Set collision box dimension
    collider.w = KID_WIDTH-40;
    collider.h = KID_HEIGHT-40;
    collider.x = posX+20;
    collider.y = posY+20;
    
    //Initialize the velocity
    velX = 0;
    velY = 0;
    
    //Initialize the angle
    angle = 0;
    
    //Initialize Default State
    state = IN_PLAY;
    
    //Make Sure Kid is Not Glowing
    r = 255;
    g = 255;
    b = 255;
    isGlowing = false;
}

void Kid::HandleEvent( SDL_Event& e)
{
    int x,y;
    
    SDL_GetMouseState( &x, &y );
    
    //We compute "angle" to make the player "look" at the mouse cursor
    angle = FindAngle(y, posY, posX, x);
    
    //Adjusts velocity of kid based on keys pressed. Kid uses WASD controls for movement.
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w: velY -= KID_VEL; break;
            case SDLK_s: velY += KID_VEL; break;
            case SDLK_a: velX -= KID_VEL; break;
            case SDLK_d: velX += KID_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w: velY += KID_VEL; break;
            case SDLK_s: velY -= KID_VEL; break;
            case SDLK_a: velX += KID_VEL; break;
            case SDLK_d: velX -= KID_VEL; break;
        }
    }

    //If Left Click, the Fireball is Spawned at Player Position, and it is no longer invisible and begins to travel.
    else if(e.type == SDL_MOUSEBUTTONDOWN && clickEnabled)
    {
        fireBall.SetPos(kid.GetXPos(),kid.GetYPos());
        fireBall.SetAngle(kid.GetAngle());
        fireBall.SetState(TRAVEL);
        clickEnabled = false;
        projectileTimer.start();
    }
    
    //We do not want players to spam the Left Click for Projectiles, so we disable in-game Left Clicks for a Second, using a Timer, whose behavious is specified in the Timer Class
    if(!clickEnabled && projectileTimer.getTicks()<=1000)
    {
        SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_DISABLE);
    }
    
    else
    {
        projectileTimer.stop();
        clickEnabled = true;
        SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_ENABLE);
    }
}

void Kid::Move( Tile* tiles[] )
{
    //Move the Kid left or right
    posX += velX;
    collider.x += velX;
    
    //If Kid Touches Wall
    if(TouchesWall(collider, tiles) )
    {
        isGlowing = true;
        
        //Move back
        posX -= velX;
        collider.x -= velX;
        
        //If Health has reached zero
        if(kid.GetHealth() == 0)
        {
            SetState(DEAD);
        }
        
        //Subtract 25 from health every time Kid touches lava.
        if(kid.GetHealth() >= 25)
            kid.SetHealth(kid.GetHealth() - 25);
        
        //Modified the String that Displays the Kids Health
        strcpy(kidHealthMessage, "Kid Health: ");
        snprintf(kidHealthStatus,5,"%d",kid.GetHealth());
        strcat(kidHealthMessage,kidHealthStatus);
    }
    
    //Move the Kid up or down
    posY += velY;
    collider.y += velY;
    
    if(TouchesWall(collider, tiles))
    {
        //Make the kid glow red
        isGlowing = true;
        
        //Move back
        posY -= velY;
        collider.y -= velY;
        
        //If Health has reached zero
        if(kid.GetHealth() == 0)
        {
            SetState(DEAD);
        }
        
        //Subtract 25 from health every time Kid touches lava.
        if(kid.GetHealth() >= 25)
            kid.SetHealth(kid.GetHealth() - 25);
        
        //Modified the String that Displays the Kids Health
        strcpy(kidHealthMessage, "Kid Health: ");
        snprintf(kidHealthStatus,5,"%d",kid.GetHealth());
        strcat(kidHealthMessage,kidHealthStatus);
    }

    
    //If the Kid collided or went too far to the left or right, ensures he cannot move off screen
    if( ( posX < 0 ) || ( posX + KID_WIDTH > SCREEN_WIDTH ))
    {
        //Move back
        posX -= velX;
        collider.x -= velX;
    }
    
    //If the Kid collided or went too far up or down
    if( ( posY < 0 ) || ( posY + KID_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        posY -= velY;
        collider.y -= velY;
    }
}

void Kid::Animate()
{
    //Animation Data
    SDL_Rect* currentFrame;
    
    frameNum++;
    
    //Cycle animations
    if( frameNum/4 >= KID_MOVE_ANIMATION_FRAMES )
    {
        frameNum = 0;
    }
    
    switch (state)
    {
        case IN_PLAY:
            if(velX !=0 || velY !=0)
                currentFrame = &kidMove[frameNum/4];
            
            else
                currentFrame = &kidMove[0];
            break;
        
        case DEAD:
            currentFrame = &kidDeath[0];
            break;
        
        default:
            if(velX !=0 || velY !=0)
                currentFrame = &kidMove[frameNum/4];
            
            else
                currentFrame = &kidMove[0];
            break;
    }
    
    //Changes Color based on value of isGlowing Variable
    changeColor();
    
    kidSpriteSheet.SetColor( r, g, b );
    kidSpriteSheet.Render(posX,posY,currentFrame,angle,NULL,SDL_FLIP_NONE);
    
    //After Rendering 1 Frame as Glowing, Stop Making Player Glow
    isGlowing = false;
}

double Player::GetAngle()
{
    return angle;
}

SDL_Rect Player::GetRect()
{
    return collider;
}

void Player::SetState(playerstates state)
{
    this -> state = state;
}

playerstates Player::GetState()
{
    return state;
}

Zombie::Zombie()
{
    //Initialize the offsets
    posX = 500;
    posY = 500;
    
    //Set collision box dimension
    collider.w = ZOMBIE_WIDTH-40;
    collider.h = ZOMBIE_HEIGHT-40;
    collider.x = posX+20;
    collider.y = posY+20;
    
    //Initialize the velocity
    velX = 0;
    velY = 0;
    
    //Initialize the angle
    angle = 0;
    
    //Initialize Default State
    state = IN_PLAY;
    
    //Make sure Zombie is Not Glowing
    r = 255;
    g = 255;
    b = 255;
    isGlowing = false;
}

void Zombie::HandleEvent( SDL_Event& e )
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: velY -= ZOMBIE_VEL; angle = 180.0; break;
            case SDLK_DOWN: velY += ZOMBIE_VEL; angle = 0.0; break;
            case SDLK_LEFT: velX -= ZOMBIE_VEL; angle = 90.0; break;
            case SDLK_RIGHT: velX += ZOMBIE_VEL; angle = 270.0; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: velY += ZOMBIE_VEL; break;
            case SDLK_DOWN: velY -= ZOMBIE_VEL; break;
            case SDLK_LEFT: velX += ZOMBIE_VEL; break;
            case SDLK_RIGHT: velX -= ZOMBIE_VEL; break;
        }
    }
}

void Zombie::Move( Tile* tiles[] )
{
    
    //Move the Zombie left or right
    posX += velX;
    collider.x += velX;
    
    if(TouchesWall(collider, tiles) )
    {
        isGlowing = true;
        
        //Move back
        posX -= velX;
        collider.x -= velX;
        
        if(zombie.GetHealth() == 0)
        {
            SetState(DEAD);
        }
        
        if(zombie.GetHealth() >= 25)
            zombie.SetHealth(zombie.GetHealth() - 25);
        
        strcpy(zombieHealthMessage, "Zombie Health: ");
        snprintf(zombieHealthStatus,5,"%d",zombie.GetHealth());
        strcat(zombieHealthMessage,zombieHealthStatus);
    }
    
    //Move the Zombie up or down
    posY += velY;
    collider.y += velY;
    
    if(TouchesWall(collider, tiles) )
    {
        isGlowing = true;
        
        //Move back
        posY -= velY;
        collider.y -= velY;
        
        if(zombie.GetHealth() == 0)
        {
            SetState(DEAD);
        }
        
        if(zombie.GetHealth() >= 25)
            zombie.SetHealth(zombie.GetHealth() - 25);
        
        strcpy(zombieHealthMessage, "Zombie Health: ");
        snprintf(zombieHealthStatus,5,"%d",zombie.GetHealth());
        strcat(zombieHealthMessage,zombieHealthStatus);
    }
    
    //If the Zombie collided or went too far to the left or right
    if( ( posX < 0 ) || ( posX + ZOMBIE_WIDTH > SCREEN_WIDTH ))
    {
        //Move back
        posX -= velX;
        collider.x -= velX;
    }
    
    //If the Zombie collided or went too far up or down
    if( ( posY < 0 ) || ( posY + ZOMBIE_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        posY -= velY;
        collider.y -= velY;
    }
}

void Zombie::Animate()
{
    //Animation Data
    SDL_Rect* currentFrame;
    
    frameNum++;
    
    if( frameNum/4 >= ZOMBIE_MOVE_ANIMATION_FRAMES )
    {
        frameNum = 0;
    }
    
    switch (state)
    {
        case DEAD:
            currentFrame = &zombieDeath[0];
            break;
        
        case IN_PLAY:
            if(velX !=0 || velY !=0)
                currentFrame = &zombieMove[frameNum/4];
            
            else
                currentFrame = &zombieMove[0];
            break;
        
        default:
            if(velX !=0 || velY !=0)
                currentFrame = &zombieMove[frameNum/4];
            
            else
                currentFrame = &zombieMove[0];
            break;
    }

    //Changes Color based on value of isGlowing Variable
    changeColor();
    
    zombieSpriteSheet.SetColor( r, g, b );

    zombieSpriteSheet.Render(posX,posY,currentFrame,angle,NULL,SDL_FLIP_NONE);
    
    //After Rendering 1 Frame as Glowing, Stop Making Player Glow
    isGlowing = false;
}    

