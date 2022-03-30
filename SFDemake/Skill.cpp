#include "Skill.h"

Skill::Skill() {
	name = "\0";
	damage = 0;
	exGain = 0;
}

Skill::~Skill(){
	cout << name << " destructed" << endl;
}
//---------------------------------------------------
ShotoSkill::ShotoSkill() {
	cooldown = 0;
}

ShotoSkill::ShotoSkill(int skl){
	id = skl;
	cooldown = 0;
	switch (id) {
		case 0:	name = "Hadoken";
				damage = 30;
				exGain = 1;
				cooldown = 1;
				break;
		case 1:	name = "Shoryuken";
				damage = 35;
				exGain = 2;
				cooldown = 1;
				break;
		case 2:	name = "Tatsumaki";
				damage = 40;
				exGain = 1;
				cooldown = 1;
				break;
		case 3:	name = "Axe Kick";
				damage = 35;
				exGain = 2;
				cooldown = 1;
				break;
		case 4:	name = "Counter";
				damage = 20;
				exGain = 0;
				cooldown = 1;
				break;
	}
}

ShotoSkill::~ShotoSkill(){
	cout << name << " destructed" << endl;
}
//----------------------------------------------------
GrappleSkill::GrappleSkill(){
	windup = 0;
}

GrappleSkill::GrappleSkill(int skl) {
	id = skl;
	windup = 0;
	switch (id) {
		case 5:	name = "Cyclone Lariat";
				damage = 35;
				exGain = 2;
				windup = 1;
				break;
		case 6:	name = "Steel Chair";
				damage = 40;
				exGain = 1;
				windup = 1;
				break;
		case 7:	name = "Dive Bomb";
				damage = 50;
				exGain = 0;
				windup = 1;
				break;
		case 8:	name = "Pile Driver";
				damage = 45;
				exGain = 1;
				windup = 1;
				break;
		case 9:	name = "Iron Muscle";
				damage = 0;
				exGain = 0;
				windup = 1;
				break;
	}
}

GrappleSkill::~GrappleSkill(){
	cout << name << " destroyed" << endl;
}
//-----------------------------------------------------------
RushSkill::RushSkill(){
	atkred = 0;
}

RushSkill::RushSkill(int skl){
	id = skl;
	atkred = 0;
	switch (id) {
		case 10: name = "Knee Bullet";
				 damage = 30;
				 exGain = 1;
				 atkred = 1;
				 break;
		case 11: name = "Spiral Arrow";
				 damage = 40;
				 exGain = 1;
				 atkred = 1;
				 break;
		case 12: name = "Throw Kunai";
				 damage = 20;
				 exGain = 1;
				 atkred = 0;
				 break;
		case 13: name = "Tenko";
				 damage = 45;
				 exGain = 1;
				 atkred = 2;
				 break;
		case 14: name = "Slide";
				 damage = 0;
				 exGain = 0;
				 atkred = -1;
				 break;
	}
}

RushSkill::~RushSkill(){
	cout << name << " destroyed" << endl;
}
