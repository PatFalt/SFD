#include "Skill.h"

Skill::Skill(){
	name = "\0";
	damage = 0;
	exGain = 0;
	cooldown = 0;
}

ShotoSkill::ShotoSkill(){

}

ShotoSkill::ShotoSkill(string skillname, int dmg, int ex, int cd) {
	name = skillname;
	damage = dmg;
	exGain = ex;
	cooldown = cd;
}

ShotoSkill::~ShotoSkill()
{
}

GrappleSkill::GrappleSkill(string skillname, int dmg, int ex, int cd) {
	name = skillname;
	damage = dmg;
	exGain = ex;
	cooldown = cd;
}

GrappleSkill::~GrappleSkill()
{
}

RushSkill::RushSkill(string skillname, int dmg, int ex, int cd) {
	name = skillname;
	damage = dmg;
	exGain = ex;
	cooldown = cd;
}

RushSkill::~RushSkill()
{
}
