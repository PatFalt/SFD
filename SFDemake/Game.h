#pragma once
#ifndef GAME_H
#define GAME_H
#include "Fighter.h"
#include "Skill.h"
#include <assert.h>
#include <conio.h>
#include <iostream>
#include <array>
#define S 10

using namespace std;

void titleScreen();
int selectFighter(Fighter roster[S]);
void fightTest();
void fight();


#endif
