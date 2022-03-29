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

enum class status { neutral, attacking, blocking, grabbing, stun };

class Fighter {
	public:
		Fighter();
		virtual ~Fighter();
		string getName() const { return name; }
		int getHP() const { return hp; }
		int getEX() const { return ex; }
		int getWins() const { return wins; }
		status getState() const { return state; }
		int getAtk() const { return atk; }
		int getDef() const { return def; }
		int getSpeed() const { return speed; }
		string getLifebar() const { return lifebar; }

		void setHP(int hpLost) { hp = hpLost; }
		void setName(string input) { name = input; }
		void setState(status s) { state = s; }
		void setEX(int num) { ex = num; }
		void setWins(int num) { wins = num; }
		virtual void updateLifebar();
		virtual int chooseAction();

		void punch(Fighter& opponent);
		void block();
		void grab(Fighter& opponent);
		virtual void skilly() { cout << "Base Skilly" << endl; }
		virtual void useSkill(int i, Fighter& ken);
	protected:
		string name;
		int hp;
		int maxHP;
		string lifebar;
		status state;
		int atk;
		int def;
		int ex;
		int wins;
		int speed; //0 grapple, 1 shoto, 2 rush
};

class Shoto : public Fighter {
	public:
		Shoto(string name);
		Shoto(int num); //Default Ryu & Ken
		virtual ~Shoto();
		void skilly() { cout << "Shoto skilly" << endl; }
		void updateLifebar();
		int getMax() const { return maxHP; }
		int chooseAction();
		//void useSkill(int i, Fighter& ken);
		//void hadoken(ShotoSkill hadoken,  Fighter& ken);
	private:
		static const int maxHP = 200;
		ShotoSkill* skill1;
		ShotoSkill* skill2;
};

class Grappler : public Fighter {
	public:
		Grappler(string input);
		~Grappler();
		void useSkill(int i, Fighter& ken);
	private:
		static const int maxHP = 300;
		GrappleSkill* skill1;
		GrappleSkill* skill2;
};

class Rush : public Fighter {
	public:
		Rush(string input);
		~Rush();
		void useSkill(int i, Fighter& ken);
	private:
		static const int maxHP = 100;
		RushSkill* skill1;
		RushSkill* skill2;
};

#endif


