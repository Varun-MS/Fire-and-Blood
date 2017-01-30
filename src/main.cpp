//
//  main.cpp
//  CG Project
//
//  Created by Varun Murthy Suravarapu on 03/04/16.
//  Copyright © 2016 Varun Murthy Suravarapu. All rights reserved.
//

//C++ Header Files
#include <stdio.h>

//SDL Header Files
#include <SDL2/SDL.h>

//Project Header Files
#include "globals.h"
#include "functions.h"
#include "gamestate.h"

int main( int argc, char* args[] )
{
    //initialize all necessary libraries
    if ( !InitLibraries() )
    {
        printf("\nFailed to Initialize!\n");
    }
    
    else
    {        
        //Load media
        if( !LoadMedia(tileSet) )
        {
            printf( "Failed to load media!\n" );
        }
        
        else
        {
            //Uses the concept of a Finite State Machine to switch between various Game States. Each state has its own unique logic for event handling, logic etc. The Game Object is Created in "globals.cpp"
            stateID = START_SCREEN;
            currentState = new StartScreen();
            
            while( stateID != STATE_EXIT )
            {
                //Do state event handling
                currentState->handle_events();
                
                //Do state logic
                currentState->logic();
                
                //Change state if needed
                change_state();
                
                //Do state rendering
                currentState->render();
                
                //Update screen
                SDL_RenderPresent( windowRenderer );

            }

        }
        //Free resources and Close SDL
        Close( tileSet );
    }
    return 0;
}





