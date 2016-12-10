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

int main( int argc, char* args[] )
{
    if ( !InitLibraries() )
    {
        printf("\nFailed to Initialize!\n");
    }
    
    else
    {
        //The level tiles
        Tile* tileSet[ NUM_TILES ];
        
        //Load media
        if( !LoadMedia(tileSet) )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop flag
            bool quit = false;
            
            //DEBUG
            bool projectileAlive = false;
            
            //Event handler
            SDL_Event e;
            
            //Create Our Playable Character Objects
            Kid kid;
            Zombie zombie;
            LTimer deathTimer;
            
            //Animation Frame Data
            int kidFrameNum = 0;
            int zombieFrameNum = 0;
            int fireBallFrameNum = 0;
              
            //Player States
            playerstates kidState = IN_PLAY;
            playerstates zombieState = IN_PLAY;
            bool hit = false;

            //Fireball State
            projectilestates fireBallState = TRAVEL;
            
            //colour modulation for highlighting collisions
            Uint8 kidR = 255;
            Uint8 kidG = 255;
            Uint8 kidB = 255;
            Uint8 zombieR = 255;
            Uint8 zombieG = 255;
            Uint8 zombieB = 255;

	    		//The frames per second timer
			LTimer fpsTimer;

			//The frames per second cap timer
			LTimer capTimer;

			//Start counting frames per second
			int countedFrames = 0;
			fpsTimer.start();
            
            //Game States
            gamestates gameState = START_SCREEN;
            
            //While application is running
            while( !quit )
            {
                //Handle events
                while( SDL_PollEvent( &e ) != 0 )
                {
                    
                                //Start cap timer
				capTimer.start();
		    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    
                    switch(gameState)
                    {
                        case START_SCREEN:
                            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
                            {
                                gameState = DESCRIPTION_SCREEN;
                            }
                            break;
                        
                        case DESCRIPTION_SCREEN:
                            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
                            {
                                gameState = INSTRUCTION_SCREEN;
                            }
                            break;
                            
                        case INSTRUCTION_SCREEN:
                            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
                            {
                                gameState = IN_GAME;
                            }
                            break;
                            
                        default:
                            //Handle Input For The Players
                            if(e.type == SDL_KEYDOWN)
			    {				
				switch(e.key.keysym.sym)
                            	{
					case(SDLK_ESCAPE):                                	
						quit = true;
						break;
					case(SDLK_r):
						system("sh run.sh");
						quit = true;
						break;							
                            	}
			    }

			    kid.HandleEvent( e );
                            zombie.HandleEvent( e );
                            break;
                    }
                }

				//Calculate and correct fps
				float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
				if( avgFPS > 2000000 )
				{
					avgFPS = 0;
				}
                
                
                //Handle Logic
                switch(gameState)
                {
                    case IN_GAME:
                        default:
                        //Get Current State of Players
                        kidState = kid.GetState();
                        zombieState = zombie.GetState();
                        
                        //Render characters
                        kid.Move(tileSet, &kidR, &kidG, &kidB, kidState);
                        zombie.Move(tileSet, &zombieR, &zombieG, &zombieB);
                        
                        if(projectileCreated)
                        {
                            //timer.start();
                            fireBall = new FireBall(kid.GetXPos(),kid.GetYPos(),kid.GetAngle());
                            projectileCreated = false;
                            projectileAlive = true;
                            //projectileAllowed = false;
                        }
                        
                        //Update Player States
                        if (PlayerCollision(&kid, &zombie))
                        {
                            kid.SetState(DEAD);
                            kidHealth = 0;
                            strcpy(kidHealthMessage, "Kid Health: ");
                            snprintf(kidHealthStatus,5,"%d",kidHealth);
                            strcat(kidHealthMessage,kidHealthStatus);
                        }
                        
                        if(projectileAlive)
                        {
                            fireBall->Move();
                            if(!FireBallCollision(&kid, &zombie, tileSet))
                            {
                                projectileAlive = true;
                            }
                            
                            else
                            {
                                if(ProjectileImpact(&zombie))
                                {
                                    if(zombieHealth >= 1000)
                                        zombieHealth -= 1000;
                                    else
                                        zombieHealth = 0;
                                    strcpy(zombieHealthMessage, "Zombie Health: ");
                                    snprintf(zombieHealthStatus,5,"%d",zombieHealth);
                                    strcat(zombieHealthMessage,zombieHealthStatus);
                                    deathTimer.start();
                                    hit = true;
                                    
                                    if(zombieHealth <= 0)
                                    {
                                        zombie.SetState(DEAD);
                                    }
                                }
                                
                                projectileAlive = false;
                                delete fireBall;
                            }
                        }
                        
                        strcpy(kidHealthMessage, "Kid Health: ");
                        snprintf(kidHealthStatus,5,"%d",kidHealth);
                        strcat(kidHealthMessage,kidHealthStatus);
                        
                        strcpy(zombieHealthMessage, "Zombie Health: ");
                        snprintf(zombieHealthStatus,5,"%d",zombieHealth);
                        strcat(zombieHealthMessage,zombieHealthStatus);
                        
                        if(zombieHealth <= 0)
                        {
                            zombieHealth = 0;
                            zombie.SetState(DEAD);
                            gameState = KID_WIN;
                        }
                        
                        if(kidHealth <= 0)
                        {
                            kidHealth = 0;
                            kid.SetState(DEAD);
                            gameState = ZOMBIE_WIN;
                        }
                        
                        if (deathTimer.getTicks() >= 500)
                        {
                            hit = false;
                        }
                        
                        if(hit)
                        {
                            zombieG = 32;
                        }
                        
                        else
                        {
                            zombieG = 255;
                        }
                        break;
                }

                //Handle Rendering
                //Clear screen
                SDL_SetRenderDrawColor( windowRenderer, 0x00, 0x00, 0x00, 0x00 );
                SDL_RenderClear( windowRenderer );
                
                switch(gameState)
                {
                    case START_SCREEN:
                        startScreen.LoadFromFile("./Assets/Screens/screen1.png");
                        startScreen.Render(0,0);
                        break;
                        
                    case DESCRIPTION_SCREEN:
                        startScreen.Free();
                        descScreen.LoadFromFile("./Assets/Screens/screen2.png");
                        descScreen.Render(0,0);
                        break;
                        
                    case INSTRUCTION_SCREEN:
                        descScreen.Free();
                        instrScreen.LoadFromFile("./Assets/Screens/screen3.png");
                        instrScreen.Render(0,0);
                        break;
                    
                    case IN_GAME:
                        instrScreen.Free();
                        
                        //Handle Rendering
                        //Clear screen
                        SDL_SetRenderDrawColor( windowRenderer, 0x00, 0x00, 0x00, 0x00 );
                        SDL_RenderClear( windowRenderer );

                        //Render level
                        for(int i=0; i<NUM_TILES; i++)
                        {
                            tileSet[i]->Render();
                        }
                        
                        kid.Animate(kidFrameNum, kidR, kidG, kidB, kidState);
                        zombie.Animate(zombieFrameNum, zombieState, zombieR, zombieG, zombieB);
                        
                        if(projectileAlive)
                        {
                            if(!FireBallCollision(&kid, &zombie, tileSet))
                            {
                                fireBall -> Animate(fireBallFrameNum, fireBallState);
                            }
                            
                            else
                            {
                                fireBall -> Animate(fireBallFrameNum, fireBallState);
                            }
                        }
                        
                        //Go to next frame
                        kidFrameNum++;
                        zombieFrameNum++;
                        fireBallFrameNum++;
                        
                        //Cycle animations
                        if( kidFrameNum/4 >= KID_MOVE_ANIMATION_FRAMES )
                        {
                            kidFrameNum = 0;
                        }
                        
                        if( zombieFrameNum/4 >= ZOMBIE_MOVE_ANIMATION_FRAMES )
                        {
                            zombieFrameNum = 0;
                        }
                        
                        if( fireBallFrameNum/24 >= FIREBALL_TRAVEL_ANIMATION_FRAMES )
                        {
                            fireBallFrameNum = 0;
                        }
                        
                        zombieHealthBar.LoadFromRenderedText(zombieHealthMessage, textColor);
                        zombieHealthBar.Render(20,660);
                        
                        kidHealthBar.LoadFromRenderedText(kidHealthMessage, textColor);
                        kidHealthBar.Render(340,660);
                        break;
                        
                    case ZOMBIE_WIN:
                        zombieWin.LoadFromFile("./Assets/Screens/zombie_wins.png");
                        zombieWin.Render(0,0);
                        break;
                    
                    case KID_WIN:
                        kidWin.LoadFromFile("./Assets/Screens/kid_wins.png");
                        kidWin.Render(0,0);
                        break;
                }
                
                //Update screen
                SDL_RenderPresent( windowRenderer );

						++countedFrames;

				//If frame finished early
				int frameTicks = capTimer.getTicks();
				if( frameTicks < SCREEN_TICK_PER_FRAME )
				{
					//Wait remaining time
					SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
				}
            }
        }
        //Free resources and Close SDL
        Close( tileSet );
    }
    return 0;
}





