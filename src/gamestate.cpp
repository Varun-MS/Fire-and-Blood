//
//  gamestate.cpp
//  CG Project 2.0
//
//  Created by Varun Murthy on 1/26/17.
//  Copyright © 2017 Varun Murthy. All rights reserved.
//

#include <stdio.h>
#include <SDL2/SDL.h>
#include "gamestate.h"
#include "globals.h"
#include "constants.h"
#include "players.h"
#include "functions.h"

StartScreen::StartScreen()
{
    //Loads Required Asset
    startScreen.LoadFromFile("./Assets/Screens/screen1.png");
}

StartScreen::~StartScreen()
{
    startScreen.Free();
}

void StartScreen::render()
{
    startScreen.Render(0,0);
}

void StartScreen::handle_events()
{
    while( SDL_PollEvent( &e ) )
    {
        //If the user has Xed out the window
        if( e.type == SDL_QUIT )
        {
            //Quit the program
            set_next_state( STATE_EXIT );
        }

        
        else if(e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                //exits the game if "q" is pressed
                case(SDLK_q):
                    set_next_state( STATE_EXIT );
                    break;
                    
                //restarts game with new map if "r" is pressed
                case(SDLK_r):
                    set_next_state( STATE_EXIT );
                    system("sh ./scripts/run.sh");
                    break;
                    
                //go to next screen if "enter" is pressed
                case(SDLK_RETURN):
                    //Move to the title screen
                    set_next_state( DESCRIPTION_SCREEN );
                    
            }
        }
    }
}

void StartScreen::logic()
{
    
}

DescScreen::DescScreen()
{
    //Loads Required Asset
    descScreen.LoadFromFile("./Assets/Screens/screen2.png");
}

DescScreen::~DescScreen()
{
    descScreen.Free();
}

void DescScreen::render()
{
    descScreen.Render(0,0);
}

void DescScreen::handle_events()
{
    while( SDL_PollEvent( &e ) )
    {
        //If the user has Xed out the window
        if( e.type == SDL_QUIT )
        {
            //Quit the program
            set_next_state( STATE_EXIT );
        }
        
        
        else if(e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                //exits the game if "q" is pressed
                case(SDLK_q):
                    set_next_state( STATE_EXIT );
                    break;
                    
                //restarts game with new map if "r" is pressed
                case(SDLK_r):
                    set_next_state( STATE_EXIT );
                    system("sh ./scripts/run.sh");
                    break;
                    
                //go to next screen if "enter" is pressed
                case(SDLK_RETURN):
                    //Move to the title screen
                    set_next_state( INSTRUCTION_SCREEN );
                    
            }
        }
    }
}

void DescScreen::logic()
{
    
}

InstrScreen::InstrScreen()
{
    //Loads Required Asset
    instrScreen.LoadFromFile("./Assets/Screens/screen3.png");
}

InstrScreen::~InstrScreen()
{
    instrScreen.Free();
}

void InstrScreen::render()
{
    instrScreen.Render(0,0);
}

void InstrScreen::handle_events()
{
    while( SDL_PollEvent( &e ) )
    {
        //If the user has Xed out the window
        if( e.type == SDL_QUIT )
        {
            //Quit the program
            set_next_state( STATE_EXIT );
        }
        
        
        else if(e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                //exits the game if "q" is pressed
                case(SDLK_q):
                    set_next_state( STATE_EXIT );
                    break;
                    
                //restarts game with new map if "r" is pressed
                case(SDLK_r):
                    set_next_state( STATE_EXIT );
                    system("sh ./scripts/run.sh");
                    break;
                    
                //go to next screen if "enter" is pressed
                case(SDLK_RETURN):
                    //Move to the title screen
                    set_next_state( IN_GAME );
                    
            }
        }
    }
}

void InstrScreen::logic()
{
    
}

InGame::InGame()
{
}

InGame::~InGame()
{
    startScreen.Free();
}

void InGame::render()
{
    //Handle Rendering
    //Clear screen
    SDL_SetRenderDrawColor( windowRenderer, 0x00, 0x00, 0x00, 0x00 );
    SDL_RenderClear( windowRenderer );
    
    //Render level
    for(int i=0; i<NUM_TILES; i++)
    {
        tileSet[i]->Render();
    }
    
    kid.Animate();

    zombie.Animate();
    
    
    if(fireBall.GetState() != INVISIBLE)
    {
        fireBall.Animate();
    }
    
    zombieHealthBar.LoadFromRenderedText(zombieHealthMessage, textColor);
    zombieHealthBar.Render(20,660);
    
    kidHealthBar.LoadFromRenderedText(kidHealthMessage, textColor);
    kidHealthBar.Render(340,660);
}

void InGame::handle_events()
{
    while( SDL_PollEvent( &e ) )
    {
        //If the user has Xed out the window
        if( e.type == SDL_QUIT )
        {
            //Quit the program
            set_next_state( STATE_EXIT );
        }
        
        
        else if(e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                //quits game if "q" pressed
                case(SDLK_q):
                    set_next_state( STATE_EXIT );
                    break;
                    
                //restarts game with new map if "r" is pressed
                case(SDLK_r):
                    set_next_state( STATE_EXIT );
                    system("sh ./scripts/run.sh");
                    break;
            }
        }
        
        //To Handle the Events of the Players, call their Respective Event Handlers
        kid.HandleEvent( e );
        zombie.HandleEvent( e );
    }
}

void InGame::logic()
{
    //Render characters
    kid.Move( tileSet );
    zombie.Move( tileSet );
    
    //If Players Collide, Instant Death to Kid. Zombie Prevails.
    if (PlayerCollision())
    {
        kid.SetState(DEAD);
        
        kid.SetHealth(0);
        
        //Modify the Player Health Message
        strcpy(kidHealthMessage, "Kid Health: ");
        snprintf(kidHealthStatus,5,"%d",kid.GetHealth());
        strcat(kidHealthMessage,kidHealthStatus);
    }
    
    //If Fireball is Visible
    if(fireBall.GetState() != INVISIBLE)
    {
        //If Explosion Not Triggered and Fireball is Travelling
        if(!TriggerExplosion() && fireBall.GetState() == TRAVEL)
        {
            fireBall.Move(); //Move the Fireball
        }
        
        else
        {
            //If Fireball has hit the wall, ie.Impact
            if (fireBall.GetState() != IMPACT)
            {
                //Change the state
                fireBall.SetState(IMPACT);
            
                //Start the Boom Animation.
                projectileBoomBoom.start();
            }
        }
        
        //If Fireball Hit Zombie
        if(HitZombie())
        {
            //Deduct 1000 from Zombie Health
            if(zombie.GetHealth() >= 1000)
                zombie.SetHealth(zombie.GetHealth() - 1000);
            else
                zombie.SetHealth(0);
            
            //Modify the Zombie Health Message
            strcpy(zombieHealthMessage, "Zombie Health: ");
            snprintf(zombieHealthStatus,5,"%d",zombie.GetHealth());
            strcat(zombieHealthMessage,zombieHealthStatus);
            
            //Timer to Make the Zombie Glow Purple when Hit
            deathTimer.start();
            hit = true;
            
            //Fireball becomes Invisible as soon as it hits the Zombie
            fireBall.SetState(INVISIBLE);
            
        }
    
    }
    
    if (projectileBoomBoom.getTicks() >= 250)
    {
        //As soon as the Boom animation is over, make the fireball disappear
        fireBall.SetState(INVISIBLE);
        projectileBoomBoom.stop();
    }
    
    //If Zombie's Health is 0 or less, then it is dead, and Kid Wins.
    if(zombie.GetHealth() <= 0)
    {
        zombie.SetHealth(0);
        zombie.SetState(DEAD);
        nextState = KID_WIN;
    }
    
    //Modify the Health Messages of the Players
    strcpy(kidHealthMessage, "Kid Health: ");
    snprintf(kidHealthStatus,5,"%d",kid.GetHealth());
    strcat(kidHealthMessage,kidHealthStatus);
    
    strcpy(zombieHealthMessage, "Zombie Health: ");
    snprintf(zombieHealthStatus,5,"%d",zombie.GetHealth());
    strcat(zombieHealthMessage,zombieHealthStatus);
    
    //If Kid's Health is 0 or less, then it is dead, and Zombie Wins.
    if(kid.GetHealth() <= 0)
    {
        kid.SetHealth(0);
        kid.SetState(DEAD);
        nextState = ZOMBIE_WIN;
    }
    
    //Make Zombie Stop Glowing, by making "Hit" false.
    if (deathTimer.getTicks() >= 500)
    {
        hit = false;
        deathTimer.stop();
    }
    
    if(hit)
    {
        zombie.isGlowing = true;
    }
}

KidWins::KidWins()
{
    //Loads Required Asset
    kidWin.LoadFromFile("./Assets/Screens/kid_wins.png");
}

KidWins::~KidWins()
{
    kidWin.Free();
}

void KidWins::render()
{
    kidWin.Render(0,0);
}

void KidWins::handle_events()
{
    while( SDL_PollEvent( &e ) )
    {
        //If the user has Xed out the window
        if( e.type == SDL_QUIT )
        {
            //Quit the program
            set_next_state( STATE_EXIT );
        }
        
        
        else if(e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                //quits game if "q" pressed
                case(SDLK_q):
                    set_next_state( STATE_EXIT );
                    break;
                    
                //restarts game with new map if "r" is pressed
                case(SDLK_r):
                    set_next_state( STATE_EXIT );
                    system("sh ./scripts/run.sh");
                    break;
            }
        }
    }
}

void KidWins::logic()
{
    
}

ZombieWins::ZombieWins()
{
    //Loads Required Asset
    zombieWin.LoadFromFile("./Assets/Screens/zombie_wins.png");
}

ZombieWins::~ZombieWins()
{
    zombieWin.Free();
}

void ZombieWins::render()
{
    zombieWin.Render(0,0);
}

void ZombieWins::handle_events()
{
    while( SDL_PollEvent( &e ) )
    {
        //If the user has Xed out the window
        if( e.type == SDL_QUIT )
        {
            //Quit the program
            set_next_state( STATE_EXIT );
        }
        
        
        else if(e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                case(SDLK_q):
                    set_next_state( STATE_EXIT );
                    break;
                    
                case(SDLK_r):
                    set_next_state( STATE_EXIT );
                    system("sh ./scripts/run.sh");
                    break;
            }
        }
    }
}

void ZombieWins::logic()
{
    
}


void set_next_state( int newState )
{
    //If the user doesn't want to exit
    if( nextState != STATE_EXIT )
    {
        //Set the next state
        nextState = newState;
    }
}

void change_state()
{
    //If the state needs to be changed
    if( nextState != STATE_NULL )
    {
        //Delete the current state, which consequently frees up resources
        if( nextState != STATE_EXIT )
        {
            delete currentState;
        }
        
        //Change the state
        switch( nextState )
        {
            case START_SCREEN:
                currentState = new StartScreen();
                break;
                
            case DESCRIPTION_SCREEN:
                currentState = new DescScreen();
                break;
                
            case INSTRUCTION_SCREEN:
                currentState = new InstrScreen();
                break;
                
            case IN_GAME:
                currentState = new InGame();
                break;
                
            case KID_WIN:
                currentState = new KidWins();
                break;
            
            case ZOMBIE_WIN:
                currentState = new ZombieWins();
                break;
        }
        
        //Change the current state ID
        stateID = nextState;
        
        //NULL the next state ID
        nextState = STATE_NULL;
    }
}

