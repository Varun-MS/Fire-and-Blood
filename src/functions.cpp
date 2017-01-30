//
//  functions.cpp
//  CG Project
//
//  Created by Varun Murthy Suravarapu on 04/05/16.
//  Copyright © 2016 Varun Murthy Suravarapu. All rights reserved.
//

#include "functions.h"
#include "globals.h"
#include <SDL2/SDL_image.h>
#include <fstream>

bool InitLibraries ( void )
{
    //Initialization flag
    bool success = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }
        
        //Create window
        mainWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( mainWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create vsynced renderer for window
            windowRenderer = SDL_CreateRenderer( mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if( windowRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( windowRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
        //Initialize SDL_True Type Fonts, used for Displaying the Health of the Players
        if( TTF_Init() == -1 )
        {
            printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
            success = false;
        }
    }
    
    return success;
}

bool LoadMedia( Tile* tiles[])
{
    //Loading success flag
    bool success = true;
    
    //Load kid texture/spritesheet
    if( !kidSpriteSheet.LoadFromFile( "./Assets/Kid/Kid.png" ))
    {
        printf( "Failed to load kid texture!\n" );
        success = false;
    }
    
    else
    {
        //Set sprite clips
        kidMove[ 0 ].x =  64;
        kidMove[ 0 ].y =   0;
        kidMove[ 0 ].w =  64;
        kidMove[ 0 ].h =  64;
        
        kidMove[ 1 ].x = 128;
        kidMove[ 1 ].y =   0;
        kidMove[ 1 ].w =  64;
        kidMove[ 1 ].h =  64;
        
        kidMove[ 2 ].x = 192;
        kidMove[ 2 ].y =   0;
        kidMove[ 2 ].w =  64;
        kidMove[ 2 ].h =  64;
        
        kidMove[ 3 ].x = 256;
        kidMove[ 3 ].y =   0;
        kidMove[ 3 ].w =  64;
        kidMove[ 3 ].h =  64;
        
        kidDeath[ 0 ].x =   0;
        kidDeath[ 0 ].y =   0;
        kidDeath[ 0 ].w =  64;
        kidDeath[ 0 ].h =  64;
    }
    
    //Load fireball texture/spritesheet
    if( !fireBallSpriteSheet.LoadFromFile("./Assets/FireBall/Fireball.png"))
    {
        //error
        printf( "Failed to load FireBall textures!\n" );
        success = false;
    }
    
    else
    {
        //Set sprite clips
        fireBallTravel[ 0 ].x =   0;
        fireBallTravel[ 0 ].y =   0;
        fireBallTravel[ 0 ].w =  64;
        fireBallTravel[ 0 ].h =  64;
        
        fireBallTravel[ 1 ].x =  64;
        fireBallTravel[ 1 ].y =   0;
        fireBallTravel[ 1 ].w =  64;
        fireBallTravel[ 1 ].h =  64;
        
        fireBallTravel[ 2 ].x = 128;
        fireBallTravel[ 2 ].y =   0;
        fireBallTravel[ 2 ].w =  64;
        fireBallTravel[ 2 ].h =  64;
        
        fireBallTravel[ 3 ].x = 192;
        fireBallTravel[ 3 ].y =   0;
        fireBallTravel[ 3 ].w =  64;
        fireBallTravel[ 3 ].h =  64;
        
        fireBallTravel[ 4 ].x = 256;
        fireBallTravel[ 4 ].y =   0;
        fireBallTravel[ 4 ].w =  64;
        fireBallTravel[ 4 ].h =  64;
        
        fireBallTravel[ 5 ].x = 320;
        fireBallTravel[ 5 ].y =   0;
        fireBallTravel[ 5 ].w =  64;
        fireBallTravel[ 5 ].h =  64;
        
        fireBallImpact[ 0 ].x = 384;
        fireBallImpact[ 0 ].y =   0;
        fireBallImpact[ 0 ].w =  64;
        fireBallImpact[ 0 ].h =  64;
        
        fireBallImpact[ 1 ].x = 448;
        fireBallImpact[ 1 ].y =   0;
        fireBallImpact[ 1 ].w =  64;
        fireBallImpact[ 1 ].h =  64;
        
        fireBallImpact[ 2 ].x = 512;
        fireBallImpact[ 2 ].y =   0;
        fireBallImpact[ 2 ].w =  64;
        fireBallImpact[ 2 ].h =  64;
        
        fireBallImpact[ 3 ].x = 576;
        fireBallImpact[ 3 ].y =   0;
        fireBallImpact[ 3 ].w =  64;
        fireBallImpact[ 3 ].h =  64;
        
        fireBallImpact[ 4 ].x = 640;
        fireBallImpact[ 4 ].y =   0;
        fireBallImpact[ 4 ].w =  64;
        fireBallImpact[ 4 ].h =  64;
        
        fireBallImpact[ 5 ].x = 704;
        fireBallImpact[ 5 ].y =   0;
        fireBallImpact[ 5 ].w =  64;
        fireBallImpact[ 5 ].h =  64;
        
        fireBallImpact[ 6 ].x = 768;
        fireBallImpact[ 6 ].y =   0;
        fireBallImpact[ 6 ].w =  64;
        fireBallImpact[ 6 ].h =  64;
        
        fireBallImpact[ 7 ].x = 832;
        fireBallImpact[ 7 ].y =   0;
        fireBallImpact[ 7 ].w =  64;
        fireBallImpact[ 7 ].h =  64;
        
        fireBallImpact[ 8 ].x = 896;
        fireBallImpact[ 8 ].y =   0;
        fireBallImpact[ 8 ].w =  64;
        fireBallImpact[ 8 ].h =  64;
    }
    
    //Load tile/floor textures
    if( !tilesSpriteSheet.LoadFromFile( "./Assets/Tiles/Tiles.png" ))
    {
        printf( "Failed to load floor textures!\n" );
        success = false;
    }
    
    if (!SetTiles(tiles))
    {
        //error
        printf ("\nFailed To Load Tile Set!");
        success = false;
    }
    
    else
    {
        //Set sprite clips
        tilesRects[ FLOOR_1 ].x =   0;
        tilesRects[ FLOOR_1 ].y =   0;
        tilesRects[ FLOOR_1 ].w =  64;
        tilesRects[ FLOOR_1 ].h =  64;
        
        tilesRects[ FLOOR_2 ].x =  64;
        tilesRects[ FLOOR_2 ].y =   0;
        tilesRects[ FLOOR_2 ].w =  64;
        tilesRects[ FLOOR_2 ].h =  64;
        
        tilesRects[ FLOOR_3 ].x = 128;
        tilesRects[ FLOOR_3 ].y =   0;
        tilesRects[ FLOOR_3 ].w =  64;
        tilesRects[ FLOOR_3 ].h =  64;
        
        tilesRects[ FLOOR_4 ].x = 192;
        tilesRects[ FLOOR_4 ].y =   0;
        tilesRects[ FLOOR_4 ].w =  64;
        tilesRects[ FLOOR_4 ].h =  64;
        
        tilesRects[ FLOOR_5 ].x = 256;
        tilesRects[ FLOOR_5 ].y =   0;
        tilesRects[ FLOOR_5 ].w =  64;
        tilesRects[ FLOOR_5 ].h =  64;
        
        tilesRects[ FLOOR_6 ].x = 320;
        tilesRects[ FLOOR_6 ].y =   0;
        tilesRects[ FLOOR_6 ].w =  64;
        tilesRects[ FLOOR_6 ].h =  64;
        
        tilesRects[ FLOOR_7 ].x = 384;
        tilesRects[ FLOOR_7 ].y =   0;
        tilesRects[ FLOOR_7 ].w =  64;
        tilesRects[ FLOOR_7 ].h =  64;
        
        tilesRects[ FLOOR_8 ].x = 448;
        tilesRects[ FLOOR_8 ].y =   0;
        tilesRects[ FLOOR_8 ].w =  64;
        tilesRects[ FLOOR_8 ].h =  64;
        
        tilesRects[ FLOOR_9 ].x = 512;
        tilesRects[ FLOOR_9 ].y =   0;
        tilesRects[ FLOOR_9 ].w =  64;
        tilesRects[ FLOOR_9 ].h =  64;
        
        tilesRects[ LAVA_MIDDLE ].x = 576;
        tilesRects[ LAVA_MIDDLE ].y =   0;
        tilesRects[ LAVA_MIDDLE ].w =  64;
        tilesRects[ LAVA_MIDDLE ].h =  64;
        
        tilesRects[ LAVA_EAST ].x = 640;
        tilesRects[ LAVA_EAST ].y =   0;
        tilesRects[ LAVA_EAST ].w =  64;
        tilesRects[ LAVA_EAST ].h =  64;
        
        tilesRects[ LAVA_NORTH ].x = 704;
        tilesRects[ LAVA_NORTH ].y =   0;
        tilesRects[ LAVA_NORTH ].w =  64;
        tilesRects[ LAVA_NORTH ].h =  64;
        
        tilesRects[ LAVA_NORTH_EAST ].x = 768;
        tilesRects[ LAVA_NORTH_EAST ].y =   0;
        tilesRects[ LAVA_NORTH_EAST ].w =  64;
        tilesRects[ LAVA_NORTH_EAST ].h =  64;
        
        tilesRects[ LAVA_NORTH_WEST ].x = 832;
        tilesRects[ LAVA_NORTH_WEST ].y =   0;
        tilesRects[ LAVA_NORTH_WEST ].w =  64;
        tilesRects[ LAVA_NORTH_WEST ].h =  64;
        
        tilesRects[ LAVA_SOUTH ].x = 896;
        tilesRects[ LAVA_SOUTH ].y =   0;
        tilesRects[ LAVA_SOUTH ].w =  64;
        tilesRects[ LAVA_SOUTH ].h =  64;
        
        tilesRects[ LAVA_SOUTH_EAST ].x = 960;
        tilesRects[ LAVA_SOUTH_EAST ].y =   0;
        tilesRects[ LAVA_SOUTH_EAST ].w =  64;
        tilesRects[ LAVA_SOUTH_EAST ].h =  64;
        
        tilesRects[ LAVA_SOUTH_WEST ].x = 1024;
        tilesRects[ LAVA_SOUTH_WEST ].y =   0;
        tilesRects[ LAVA_SOUTH_WEST ].w =  64;
        tilesRects[ LAVA_SOUTH_WEST ].h =  64;
        
        tilesRects[ LAVA_WEST ].x = 1088;
        tilesRects[ LAVA_WEST ].y =   0;
        tilesRects[ LAVA_WEST ].w =  64;
        tilesRects[ LAVA_WEST ].h =  64;
    }
    
    //Load zombie texture/spritesheets
    if( !zombieSpriteSheet.LoadFromFile( "./Assets/Zombie/Zombie.png" ) )
    {
        //error
        printf( "Failed to load zombie texture!\n" );
        success = false;
    }
    
    else
    {
        zombieMove[ 0 ].x =   0;
        zombieMove[ 0 ].y =   0;
        zombieMove[ 0 ].w =  64;
        zombieMove[ 0 ].h =  64;
        
        zombieMove[ 1 ].x =  64;
        zombieMove[ 1 ].y =   0;
        zombieMove[ 1 ].w =  64;
        zombieMove[ 1 ].h =  64;
        
        zombieMove[ 2 ].x = 128;
        zombieMove[ 2 ].y =   0;
        zombieMove[ 2 ].w =  64;
        zombieMove[ 2 ].h =  64;
        
        zombieMove[ 3 ].x = 192;
        zombieMove[ 3 ].y =   0;
        zombieMove[ 3 ].w =  64;
        zombieMove[ 3 ].h =  64;
        
        zombieDeath[ 0 ].x = 320;
        zombieDeath[ 0 ].y =   0;
        zombieDeath[ 0 ].w =  64;
        zombieDeath[ 0 ].h =  64;
    }
    
    //Open the font
    gFont = TTF_OpenFont( "Assets/INVASION2000.TTF", 24 );
    if( gFont == NULL )
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    
    return success;
}

//Unloads all Assets and Quits all Loaded Libraries
void Close( Tile* tiles[])
{
    //Deallocate tiles
    for( int i = 0; i < NUM_TILES; i++ )
    {
        if( tiles[ i ] == NULL )
        {
            delete tiles[ i ];
            tiles[ i ] = NULL;
        }
    }
    
    //Free loaded images
    kidSpriteSheet.Free();
    zombieSpriteSheet.Free();
    tilesSpriteSheet.Free();
    fireBallSpriteSheet.Free();
    kidWin.Free();
    zombieWin.Free();
    
    //Destroy window
    SDL_DestroyRenderer( windowRenderer );
    SDL_DestroyWindow( mainWindow );
    mainWindow = NULL;
    windowRenderer = NULL;
    
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}

//Given two Rectangles, Calculates whether any of their sides are intersecting

bool CheckCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;
    
    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
}

bool SetTiles (Tile* tiles[])
{
    bool tilesLoaded = true;
    int x=0, y=0;
    
    //Read from a file called level1.map
    std::ifstream map;
    map.open("./generated_map/NEW_MAP.map");
    
    // If output file stream could not be opened for reading
    if (!map)
    {
        // Print an error and exit
        printf("\nThe Map File Could Not Be Opened!\n\n");
        tilesLoaded = false;
    }
    
    else
    {
        // While there's still stuff left to read
        for(int i=0; i<NUM_TILES; i++)
        {
            //Determines what kind of tile will be made
            int tileType = -1;
            
            //Read tile from map file
            map >> tileType;
            
            //If the was a problem in reading the map
            if( map.fail() )
            {
                //Stop loading map
                printf( "Error loading map: Unexpected end of file!\n" );
                tilesLoaded = false;
                break;
            }
            
            //If the number is a valid tile number
            if( ( tileType >= 0 ) && ( tileType < NUM_TILES ) )
            {
                tiles[ i ] = new Tile( x, y, tileType );
                
                //Assigns Textures Based on Tile Type Specified in the Map File
                switch(tileType)
                {
                    case FLOOR_1:   tiles[ i ]->texture = 0;
                                    break;
                        
                    case FLOOR_2:   tiles[ i ]->texture = 1;
                                    break;
                        
                    case FLOOR_3:   tiles[ i ]->texture = 2;
                                    break;
                        
                    case FLOOR_4:   tiles[ i ]->texture = 3;
                                    break;
                        
                    case FLOOR_5:   tiles[ i ]->texture = 4;
                                    break;
                        
                    case FLOOR_6:   tiles[ i ]->texture = 5;
                                    break;
                        
                    case FLOOR_7:   tiles[ i ]->texture = 6;
                                    break;
                        
                    case FLOOR_8:   tiles[ i ]->texture = 7;
                                    break;
                    
                    case FLOOR_9:   tiles[ i ]->texture = 8;
                                    break;
                    
                    case LAVA_MIDDLE:   tiles[ i ]->texture = 9;
                                        break;

                    case LAVA_EAST:     tiles[ i ]->texture = 10;
                                        break;
                    
                    case LAVA_NORTH:    tiles[ i ]->texture = 11;
                                        break;
                    
                    case LAVA_NORTH_EAST:tiles[ i ]->texture = 12;
                                        break;
                    
                    case LAVA_NORTH_WEST:tiles[ i ]->texture = 13;
                                        break;
                    
                    case LAVA_SOUTH:    tiles[ i ]->texture = 14;
                                        break;
                    
                    case LAVA_SOUTH_EAST:tiles[ i ]->texture = 15;
                                        break;
                    
                    case LAVA_SOUTH_WEST:tiles[ i ]->texture = 16;
                                        break;
                    
                    case LAVA_WEST:      tiles[ i ]->texture = 17;
                                        break;
                }
            }
            //If tile type not recognised
            else
            {
                //Stop loading map
                printf( "Error loading map: Invalid tile type at %d!\n", i );
                tilesLoaded = false;
                break;
            }
            
            //Move to next tile spot
            x += TILE_WIDTH;
            
            //Checks to see if we've reached screen width boundary
            if( x >= SCREEN_WIDTH )
            {
                //Move back
                x = 0;
                
                //Move to the next row
                y += TILE_HEIGHT;
            }
        }
    }
    //Close the file
    map.close();
    
    //If the map was loaded fine
    return tilesLoaded;

}
    
bool TouchesWall( SDL_Rect box, Tile* tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < NUM_TILES; ++i )
    {
        //If the tile is a wall type tile
        if( ( tiles[ i ]->GetType() >= LAVA_MIDDLE ) && ( tiles[ i ]->GetType() <= LAVA_WEST ) )
        {
            //If the collision box touches the wall tile
            if( CheckCollision( box, tiles[ i ]->GetRect() ) )
            {
                return true;
            }
        }
    }
    //If no wall tiles were touched
    return false;
}
    
//Useful Function that Finds the Angle Between any two Points, given their X and Y Cartesian Coordinates
double FindAngle (int x1, int x2, int y1, int y2)
{
    double deltaX, deltaY;
    double angle;
    
    deltaX = double(x2 - x1);
    deltaY = double(y2 - y1);
    
    angle = atan2(deltaY, deltaX) * (180/PI);
    
    return angle;
}

//Checks for Collision Betwdeen Two Players, by obtaining their Collision Rectangles First
bool PlayerCollision()
{
    SDL_Rect kidRect, zombieRect;
    
    kidRect = kid.GetRect();
    zombieRect = zombie.GetRect();
    
    return CheckCollision(kidRect, zombieRect);

}

//Checks Whether to Trigger Explosion. Triggers Explosion if the Fireball Touches the Wall/Lava
bool TriggerExplosion()
{
    SDL_Rect fireBallRect;
    
    fireBallRect = fireBall.GetRect();
    
    if (TouchesWall(fireBallRect, tileSet))
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

//Checks whether the players fireball/projectile hit the zombie
bool HitZombie()
{
    SDL_Rect zombieRect, fireBallRect;
    
    zombieRect = zombie.GetRect();
    fireBallRect = fireBall.GetRect();

    return CheckCollision(fireBallRect, zombieRect);
}
