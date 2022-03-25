#pragma once
#ifndef SKILL_H
#define SKILL_H
#include <string>

using namespace std;

class Skill{
	public:
		Skill();
	protected:
		string name;
		//int id;
		int damage;
		int exGain;
		int cooldown;
};

class ShotoSkill : public Skill {
	public:
		ShotoSkill();
		ShotoSkill(string skillname, int dmg, int ex, int cd);
		~ShotoSkill();
};

class GrappleSkill : public Skill {
	public:
		GrappleSkill(string skillname, int dmg, int ex, int cd);
		~GrappleSkill();
};

class RushSkill : public Skill {
	public:
		RushSkill(string skillname, int dmg, int ex, int cd);
		~RushSkill();
};

#endif

//fighter hat zwei skill slots für skills, in main ein array an skills erstellen