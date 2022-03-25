#pragma once
#include <string>
#include <iostream>
#include <assert.h>
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
		//int getVtrigger() const { return this->vtrigger; }
		int getEX() const { return ex; }
		int getWins() const { return wins; }
		status getState() const { return state; }
		int getAtk() const { return atk; }
		int getDef() const { return def; }
		int getSpeed() const { return speed; }
		void setHP(int hpLost) { hp = hpLost; }
		void setName(string input) { name = input; }
		void setState(status s) { state = s; }
		void setEX(int num) { ex = num; }
		void setWins(int num) { wins = num; }
		void punch(Fighter& opponent);
		void block();
		void grab(Fighter& opponent);
		virtual void skilly() { cout << "Base Skilly" << endl; }

	protected:
		string name;
		int hp;
		//int status; //neutral, block, attack, grab, stun
		//int vtrigger;
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
	private:
		ShotoSkill skill1;
		ShotoSkill skill2;
};

class Grappler : public Fighter {
	public:

	private:
		GrappleSkill skill1;
		GrappleSkill skill2;
};

class Rush : public Fighter {
	public:

	private:
		RushSkill skill1;
		RushSkill skill2;
};

#endif


