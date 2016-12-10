//
//  globals.cpp
//  CG Project
//
//  Created by Varun Murthy Suravarapu on 04/05/16.
//  Copyright © 2016 Varun Murthy Suravarapu. All rights reserved.
//

#include <SDL2/SDL.h>
#include "texture.h"
#include "constants.h"
#include <SDL2/SDL_ttf.h>
#include "fireball.h"
#include "timer.h"
#include "globals.h"

//Window That is Being Rendered To
SDL_Window* mainWindow = NULL;

//The window renderer
SDL_Renderer* windowRenderer = NULL;

//Animation Data For Kid
Texture kidSpriteSheet;
SDL_Rect kidShoot[KID_SHOOT_ANIMATION_FRAMES];
SDL_Rect kidMove[KID_MOVE_ANIMATION_FRAMES];
SDL_Rect kidDeath[KID_DEATH_ANIMATION_FRAMES];

//Animation Data For Zombie
Texture zombieSpriteSheet;
SDL_Rect zombieMove[ZOMBIE_MOVE_ANIMATION_FRAMES];
SDL_Rect zombieDeath[ZOMBIE_DEATH_ANIMATION_FRAMES];

//Spritesheets and Data For Tiles
Texture tilesSpriteSheet;
SDL_Rect tilesRects[NUM_TILES];

//Spritesheets and Data for Fireball
Texture fireBallSpriteSheet;
SDL_Rect fireBallTravel[FIREBALL_TRAVEL_ANIMATION_FRAMES];
SDL_Rect fireBallImpact[FIREBALL_IMPACT_ANIMATION_FRAMES];

bool clickEnabled = true;
bool projectileCreated = false;

FireBall* fireBall = NULL;
int kidHealth = 4000;
int zombieHealth = 4000;

LTimer projectileTimer;

//Globally used font
TTF_Font *gFont = NULL;

//Rendered texture
Texture zombieHealthBar;
Texture kidHealthBar;
SDL_Color textColor = {255, 255, 255};

char kidHealthMessage[20] = "Kid Health: ";
char zombieHealthMessage[20] = "Zombie Health: ";

char kidHealthStatus[5] = "4000";
char zombieHealthStatus[5] = "4000";

//Splash Screens
Texture startScreen;
Texture descScreen;
Texture instrScreen;
Texture zombieWin;
Texture kidWin;

