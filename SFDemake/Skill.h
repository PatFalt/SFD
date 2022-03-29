#pragma once
#ifndef SKILL_H
#define SKILL_H
#include <string>

using namespace std;

class Skill{
	public:
		Skill();
		~Skill();
		string getName() { return name; }
		int getDmg() { return damage; }
		int getExGain() { return exGain; }
	protected:
		string name;
		int damage;
		int exGain;
		
};

class ShotoSkill : public Skill {
	public:
		ShotoSkill();
		ShotoSkill(string skillname, int dmg, int ex, int cd);
		~ShotoSkill();
		int getCooldown() const { return cooldown; }
		//void useSkill(Fighter& ryu, Fighter& ken);
	private:
		int cooldown;
};

class GrappleSkill : public Skill {
	public:
		GrappleSkill();
		GrappleSkill(string skillname, int dmg, int ex, int wu);
		~GrappleSkill();
		//void useSkill(Fighter& ryu, Fighter& ken);
	private:
		int windup;
};

class RushSkill : public Skill {
	private:
		int atkred;
	public:
		RushSkill();
		~RushSkill();
		RushSkill(string skillname, int dmg, int ex, int cd);
		//void useSkill(Fighter& ryu, Fighter& ken);
};

#endif

//fighter hat zwei skill slots für skills, in main ein array an skills erstellen