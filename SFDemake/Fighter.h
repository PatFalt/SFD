#pragma once
#include <string>
#include <iostream>
#ifndef FIGHTER_H
#define FIGHTER_H

using namespace std;

class Fighter {

	public:
		Fighter();
		virtual ~Fighter();
		string getName() const { return this->name; }
		int getHP() const { return this->hp; }
		//int getVtrigger() const { return this->vtrigger; }
		int getEX() const { return this->ex; }
		int getWins() const { return this->wins; }
		void setHP(int hpLost) { this->hp -= hpLost; }
		virtual void skilly() { cout << "Parent Class Skill" << endl; }

	protected:
		string name;
		int hp;
		int status; //neutral, block, attack
		//int vtrigger;
		int ex;
		int wins;
};

class Shoto : public Fighter {
	public:
		Shoto(string name);
		Shoto(int def);
		virtual ~Shoto();
	private:
		void Hadouken(Fighter& op);
		void skilly() { cout << "Shoto Class Skill" << endl; }

};

class Grappler : public Fighter {
	private:

};

class Rush : public Fighter {
	private:

};

#endif


