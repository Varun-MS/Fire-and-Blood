//
//  gamestate.hpp
//  CG Project 2.0
//
//  Created by Varun Murthy on 1/26/17.
//  Copyright © 2017 Varun Murthy. All rights reserved.
//

#ifndef gamestate_h
#define gamestate_h

#include <stdio.h>
#include "players.h"
#include "timer.h"
#include "fireball.h"
#include "constants.h"

//We define an abstract class called "GameState", specifying a number of pure virtual functions.
//These functions are defined by the deriving class, each providing their own unique functionality, depending the state the game is in.
//This is an implementation of a Finite State Machine.
class GameState
{
    public:
        virtual void handle_events() = 0;
        virtual void logic() = 0;
        virtual void render() = 0;
        virtual ~GameState(){};
};

class StartScreen : public GameState
{
    public:
        //Loads intro resources
        StartScreen();
        //Frees intro resources
        ~StartScreen();
        
        //Main loop functions
        void handle_events();
        void logic();
        void render();
};

class DescScreen : public GameState
{
    public:
        //Loads description screen resources
        DescScreen();
        //Frees description resources
        ~DescScreen();
        
        //Main loop functions
        void handle_events();
        void logic();
        void render();
};

class InstrScreen : public GameState
{
    public:
        //Loads Instruction screen resources
        InstrScreen();
        //Frees Instruction screen resources
        ~InstrScreen();
        
        //Main loop functions
        void handle_events();
        void logic();
        void render();
};

class InGame : public GameState
{
    private:
        bool hit = false;

    public:
        //Loads required in game resources
        InGame();
        //UnLoads no longer required in game resources
        ~InGame();
        
        //Main loop functions
        void handle_events();
        void logic();
        void render();
};

class KidWins : public GameState
{
    public:
        //Loads resources required for "Kid Wins" Screen
        KidWins();
        //UnLoads no longer required resources
        ~KidWins();
        
        //Main loop functions
        void handle_events();
        void logic();
        void render();
};

class ZombieWins : public GameState
{
    public:
        //Loads resources required for "Zombie Wins" Screen
        ZombieWins();
        //UnLoads no longer required resources
        ~ZombieWins();
        
        //Main loop functions
        void handle_events();
        void logic();
        void render();
};

//State status manager
void set_next_state( int newState );

//State changer
void change_state();

#endif /* gamestate_h */
