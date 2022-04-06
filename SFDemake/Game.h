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
#define S 15

using namespace std;

class Game {
	public:
		Game();
		~Game();
		void titleScreen();
		void selectMode();
		int selectFighter();
		void fillTeam();
		int selectOp(int block);
		void fightTest();
		void resolveAction(Fighter& ryu, Fighter& ken);
		void doAction(Fighter& ryu, Fighter& ken, int ryuAction);
		int chooseAction(Fighter& ryu);
		int createFighter();
		void addFighter();
		int rosterSize();
		void fight(Fighter& ryu, Fighter& ken);
		void tagTeamFight();
		void tagOut();
		void printFightMenu(Fighter& ryu, Fighter& ken);
		void printWinLoss();
		void play();
	private:
		int mode;
		int tag;
		Fighter* roster[S];
		Fighter* team1[2];
		Fighter* team2[2];
		Skill* skills[15];
		char contGame;
};

#endif