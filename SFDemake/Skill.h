#pragma once
#ifndef SKILL_H
#define SKILL_H
#include <string>
#include <iostream>
#include <conio.h>
#include <assert.h>

using namespace std;

class Skill{
	public:
		Skill();
		~Skill();
		string getName() const { return name; }
		int getDmg() const { return damage; }
		int getExGain() const { return exGain; }
		int getSkill() const { return id; }
	protected:
		string name;
		int damage;
		int exGain;
		int id;
};
//-------------------------------------------
class ShotoSkill : public Skill {
	public:	
		ShotoSkill();
		ShotoSkill(int skl);
		~ShotoSkill();
		int getCooldown() const { return cooldown; }
		//void useSkill(Fighter& ryu, Fighter& ken);
	private:
		int cooldown;
};
//--------------------------------------------
class GrappleSkill : public Skill {
	public:
		GrappleSkill();
		GrappleSkill(int skl);
		~GrappleSkill();
		int getWindup() const { return windup; }
		//void useSkill(Fighter& ryu, Fighter& ken);
	private:
		int windup;
};
//---------------------------------------------
class RushSkill : public Skill {
	public:
		RushSkill();
		RushSkill(int skl);
		~RushSkill();
		int getAtkred() const { return atkred; }
		//void useSkill(Fighter& ryu, Fighter& ken);
	private:
		int atkred;
};

#endif