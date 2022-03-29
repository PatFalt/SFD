#pragma once
#ifndef GAME_H
#define GAME_H
#include "Fighter.h"
#include "Skill.h"
#include <assert.h>
#include <conio.h>
#include <iostream>
#include <array>
#include <time.h>
#define S 10

using namespace std;

void titleScreen();
int selectMode();
int selectFighter(Fighter* roster[]);
int selectOp(Fighter* roster[], int block);
void fightTest();
void resolveAction(Fighter& ryu, Fighter& ken, int ryuAction);
void doAction(Fighter& ryu, Fighter& ken, int ryuAction);
int createFighter();
int rosterSize(Fighter* roster[]);
void fight(Fighter& ryu, Fighter& ken);
void printFightMenu(Fighter& ryu, Fighter& ken);


#endif
