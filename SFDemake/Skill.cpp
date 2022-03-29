#include "Skill.h"

Skill::Skill(){
	name = "\0";
	damage = 0;
	exGain = 0;
}

Skill::~Skill()
{
}

ShotoSkill::ShotoSkill(){
	cooldown = 0;
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

GrappleSkill::GrappleSkill(){
	windup = 0;
}

GrappleSkill::GrappleSkill(string skillname, int dmg, int ex, int wu) {
	name = skillname;
	damage = dmg;
	exGain = ex;
	windup = wu;
}

GrappleSkill::~GrappleSkill()
{
}

RushSkill::RushSkill(){
}

RushSkill::RushSkill(string skillname, int dmg, int ex, int cd) {
	name = skillname;
	damage = dmg;
	exGain = ex;
}

RushSkill::~RushSkill()
{
}
