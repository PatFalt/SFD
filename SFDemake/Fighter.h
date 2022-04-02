#pragma once
#include <string>
#include <iostream>
#include <assert.h>
#include <conio.h>
#include "Skill.h"
#ifndef FIGHTER_H
#define FIGHTER_H
#define chipdmg 2

using namespace std;

enum class status { neutral, attacking, blocking, grabbing, stun, wait, spdef };

class Fighter {
	public:
		Fighter();
		virtual ~Fighter();
		string getName() const { return name; }
		int getHP() const { return hp; }
		int getEX() const { return ex; }
		int getWins() const { return wins; }
		int getLosses() const { return losses; }
		status getState() const { return state; }
		int getAtk() const { return atk; }
		int getDef() const { return def; }
		int getSpeed() const { return speed; }
		string getLifebar() const { return lifebar; }
		int getSkill1() const { return skill1; }
		int getSkill2() const { return skill2; }
		int getMax() const { return maxHP; }
		void setHP(int hpLost) { hp = hpLost; }
		void setName(string input) { name = input; }
		void setState(status s) { state = s; }
		void setEX(int num) { ex = num; }
		void setWins() { wins++; }
		void setLosses() { losses++; }
		virtual void updateLifebar(){};
		void punch(Fighter& opponent);
		void block();
		void grab(Fighter& opponent);
		void exAttack(Fighter& opponent);
		void wait();
		virtual void useSkill(Skill* sklList[], int slot, Fighter& ken){};
		virtual void restoreFighter(){};
	protected:
		string name;
		int hp;
		int maxHP;
		char lifebar[23];
		status state;
		int atk;
		int def;
		int ex;
		int wins;
		int losses;
		int speed; //0 grapple, 1 shoto, 2 rush
		int skill1;
		int skill2;
};
//---------------------------------------------------------
class Shoto : public Fighter {
	public:
		Shoto(string name);
		Shoto(int num); //Default Ryu & Ken
		virtual ~Shoto();
		void updateLifebar();
		void restoreFighter();
		int selectShotoSkill();
		void useSkill(Skill* sklList[], int slot,  Fighter& ken);
	private:
		static const int maxHP = 200;
};
//----------------------------------------------------------
class Grappler : public Fighter {
	public:
		Grappler(string input);
		Grappler(int num);
		virtual ~Grappler();
		void updateLifebar();
		void restoreFighter();
		int selectGrappleSkill();
		void useSkill(Skill* sklList[], int slot, Fighter& ken);
	private:
		static const int maxHP = 300;
};
//----------------------------------------------------------
class Rush : public Fighter {
	public:
		Rush(string input);
		Rush(int num);
		virtual ~Rush();
		void updateLifebar();
		void restoreFighter();
		int selectRushSkill();
		void useSkill(Skill* sklList[], int slot, Fighter& ken);
	private:
		static const int maxHP = 100;
};

#endif