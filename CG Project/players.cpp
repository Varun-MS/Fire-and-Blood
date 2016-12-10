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

int Player::GetXPos()
{
    return posX;
}

int Player::GetYPos()
{
    return posY;
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
}

void Kid::HandleEvent( SDL_Event& e)
{
    int x,y;
    
    SDL_GetMouseState( &x, &y );
    
    angle = FindAngle(y, posY, posX, x);
    
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


    else if(e.type == SDL_MOUSEBUTTONDOWN && clickEnabled)
    {
        projectileCreated = true;
        clickEnabled = false;
        projectileTimer.start();

    }
    
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

void Kid::Move( Tile* tiles[], Uint8* r, Uint8* g, Uint8* b, playerstates state )
{
    //Move the Kid left or right
    posX += velX;
    collider.x += velX;

    
    //If the Kid collided or went too far to the left or right
    if( ( posX < 0 ) || ( posX + KID_WIDTH > SCREEN_WIDTH ))
    {
        //Move back
        posX -= velX;
        collider.x -= velX;
    }
    
    if(TouchesWall(collider, tiles) )
    {
        //Move back
        posX -= velX;
        collider.x -= velX;
        *g = 32;
        if(kidHealth == 0)
        {
            this->SetState(DEAD);
        }
        if(kidHealth>=25)
            kidHealth -= 25;
        strcpy(kidHealthMessage, "Kid Health: ");
        snprintf(kidHealthStatus,5,"%d",kidHealth);
        strcat(kidHealthMessage,kidHealthStatus);
    }
    
    else
    {
        *g = 255;
    }
    
    //Move the Kid up or down
    posY += velY;
    collider.y += velY;;
    
    //If the Kid collided or went too far up or down
    if( ( posY < 0 ) || ( posY + KID_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        posY -= velY;
        collider.y -= velY;
    }
    
    if(TouchesWall(collider, tiles) )
    {
        //Move back
        posY -= velY;
        collider.y -= velY;
        *g = 32;
        if(kidHealth == 0)
        {
            this->SetState(DEAD);
        }
        if(kidHealth >= 25)
            kidHealth -= 25;
        strcpy(kidHealthMessage, "Kid Health: ");
        snprintf(kidHealthStatus,5,"%d",kidHealth);
        strcat(kidHealthMessage,kidHealthStatus);
    }
}

void Kid::Animate(int frameNum, Uint8 r, Uint8 g, Uint8 b, playerstates state)
{
    //Animation Data
    SDL_Rect* currentFrame;
    
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
    
    kidSpriteSheet.SetColor( r, g, b );
    kidSpriteSheet.Render(posX,posY,currentFrame,angle,NULL,SDL_FLIP_NONE);
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

void Zombie::Move( Tile* tiles[], Uint8* r, Uint8* g, Uint8* b )
{
    
    //Move the Zombie left or right
    posX += velX;
    collider.x += velX;
    
    //If the Zombie collided or went too far to the left or right
    if( ( posX < 0 ) || ( posX + ZOMBIE_WIDTH > SCREEN_WIDTH ))
    {
        //Move back
        posX -= velX;
        collider.x -= velX;
    }
    
    if(TouchesWall(collider, tiles) )
    {
        //Move back
        posX -= velX;
        collider.x -= velX;
        *g = 32;
        if(zombieHealth == 0)
        {
            this->SetState(DEAD);
        }
        if(zombieHealth >= 25)
            zombieHealth -= 25;
        strcpy(zombieHealthMessage, "Zombie Health: ");
        snprintf(zombieHealthStatus,5,"%d",zombieHealth);
        strcat(zombieHealthMessage,zombieHealthStatus);
    }
    
    else
    {
        *g = 255;
    }
    
    //Move the Zombie up or down
    posY += velY;
    collider.y += velY;;
    
    //If the Zombie collided or went too far up or down
    if( ( posY < 0 ) || ( posY + ZOMBIE_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        posY -= velY;
        collider.y -= velY;
    }
    
    if(TouchesWall(collider, tiles) )
    {
        //Move back
        posY -= velY;
        collider.y -= velY;
        *g = 32;
        if(zombieHealth == 0)
        {
            this->SetState(DEAD);
        }
        if(zombieHealth >= 25)
            zombieHealth -= 25;
        strcpy(zombieHealthMessage, "Zombie Health: ");
        snprintf(zombieHealthStatus,5,"%d",zombieHealth);
        strcat(zombieHealthMessage,zombieHealthStatus);
    }
}

void Zombie::Animate( int frameNum, playerstates state, Uint8 r, Uint8 g, Uint8 b )
{
    //Animation Data
    SDL_Rect* currentFrame;
    
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

    
    zombieSpriteSheet.SetColor( r, g, b );

    zombieSpriteSheet.Render(posX,posY,currentFrame,angle,NULL,SDL_FLIP_NONE);

}    

