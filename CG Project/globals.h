//
//  globals.h
//  CG Project
//
//  Created by Varun Murthy Suravarapu on 04/05/16.
//  Copyright © 2016 Varun Murthy Suravarapu. All rights reserved.
//

#ifndef GLOBALS_H
#define GLOBALS_H

#include "constants.h"
#include <SDL2/SDL.h>
#include "texture.h"
#include <SDL2/SDL_ttf.h>
#include "fireball.h"
#include "timer.h"

//Window That is Being Rendered To
extern SDL_Window* mainWindow;

//The window renderer
extern SDL_Renderer* windowRenderer;

//Animation Data For Kid
extern Texture kidSpriteSheet;
extern SDL_Rect kidShoot[KID_SHOOT_ANIMATION_FRAMES];
extern SDL_Rect kidMove[KID_MOVE_ANIMATION_FRAMES];
extern SDL_Rect kidDeath[KID_DEATH_ANIMATION_FRAMES];

//Animation Data For Zombie
extern Texture zombieSpriteSheet;
extern SDL_Rect zombieMove[ZOMBIE_MOVE_ANIMATION_FRAMES];
extern SDL_Rect zombieDeath[ZOMBIE_DEATH_ANIMATION_FRAMES];

//Spritesheets and Data For Tiles
extern Texture tilesSpriteSheet;
extern SDL_Rect tilesRects[NUM_TILES];

//Spritesheets and Data for Fireball
extern Texture fireBallSpriteSheet;
extern SDL_Rect fireBallTravel[FIREBALL_TRAVEL_ANIMATION_FRAMES];
extern SDL_Rect fireBallImpact[FIREBALL_IMPACT_ANIMATION_FRAMES];

//Variables That Indicate Projectile Existence and Enabling of Right Click
extern bool clickEnabled;
extern bool projectileCreated;

//Global Variable Which acts as an Array for Projectiles
//New Fireball is Instantiated as and when Player Clicks
extern FireBall* fireBall;

//Indicate Current Player Health
extern int kidHealth;
extern int zombieHealth;

extern LTimer projectileTimer;

//Globally used font
extern TTF_Font *gFont;

//Rendered texture
extern Texture zombieHealthBar;
extern Texture kidHealthBar;
extern SDL_Color textColor;

extern char kidHealthMessage[20];
extern char zombieHealthMessage[20];

extern char kidHealthStatus[5];
extern char zombieHealthStatus[5];

//Splash Screens
extern Texture startScreen;
extern Texture descScreen;
extern Texture instrScreen;
extern Texture zombieWin;
extern Texture kidWin;

#endif /* globals_h */
