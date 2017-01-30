//
//  constants.h
//  CG Project
//
//  Created by Varun Murthy Suravarapu on 04/05/16.
//  Copyright © 2016 Varun Murthy Suravarapu. All rights reserved.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H

//Defined PI here for some use in some Trigonometric Functions in the Game
#define PI 3.1415

//Screen Window Resolution, Decided based on Our Tiling System
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 730;

//Tile Constants
const int NUM_TILES = 100;
const int TILE_WIDTH = 64;
const int TILE_HEIGHT = 64;
enum tiletype
{
    FLOOR_1,
    FLOOR_2,
    FLOOR_3,
    FLOOR_4,
    FLOOR_5,
    FLOOR_6,
    FLOOR_7,
    FLOOR_8,
    FLOOR_9,
    LAVA_MIDDLE,
    LAVA_EAST,
    LAVA_NORTH,
    LAVA_NORTH_EAST,
    LAVA_NORTH_WEST,
    LAVA_SOUTH,
    LAVA_SOUTH_EAST,
    LAVA_SOUTH_WEST,
    LAVA_WEST
};

//Player States
enum playerstates
{
    DEAD,
    IN_PLAY,
    SHOOTING,
    HURT
};

//Game States
enum gamestates
{
    STATE_NULL,
    START_SCREEN,
    DESCRIPTION_SCREEN,
    INSTRUCTION_SCREEN,
    IN_GAME,
    ZOMBIE_WIN,
    KID_WIN,
    STATE_EXIT,
};

//Projectile States
enum projectilestates
{
    TRAVEL,
    IMPACT,
    INVISIBLE,
};

//Zombie Properties
const int ZOMBIE_WIDTH = 64;
const int ZOMBIE_HEIGHT = 64;
const int ZOMBIE_VEL = 5;
const int ZOMBIE_DEATH_ANIMATION_FRAMES = 1;
const int ZOMBIE_MOVE_ANIMATION_FRAMES = 4;

//Kid Properties
const int KID_WIDTH = 64;
const int KID_HEIGHT = 64;
const int KID_VEL = 5;
const int KID_DEATH_ANIMATION_FRAMES = 1;
const int KID_MOVE_ANIMATION_FRAMES = 4;
const int KID_SHOOT_ANIMATION_FRAMES = 2;

//Fireball Properties
const int FIREBALL_WIDTH = 64;
const int FIREBALL_HEIGHT = 64;
const int FIREBALL_VEL = 14;
const int FIREBALL_TRAVEL_ANIMATION_FRAMES = 6;
const int FIREBALL_IMPACT_ANIMATION_FRAMES = 9;

#endif /* constants_h */
