#include "Fighter.h"

Fighter::Fighter() {
	name = "\0";
	hp = 0;
	ex = 0;
	state = status::neutral;
	wins = 0;
	atk = 0;
	def = 0;
	speed = 0;
}

Fighter::~Fighter() {}

void Fighter::punch(Fighter& opponent){
	state = status::attacking;
	int dmg = atk - opponent.getDef();
	//status opstate = opponent.getState();
	switch(opponent.getState()){
		case status::neutral:	opponent.setHP(opponent.getHP() - atk); break;
		case status::attacking:	opponent.setHP(opponent.getHP() - atk); break;
		case status::grabbing:	opponent.setHP(opponent.getHP() - atk); break;
		case status::stun:		opponent.setHP(opponent.getHP() - atk); break;
		case status::blocking:	if (dmg <= 0) {
									opponent.setHP(opponent.getHP() - chipdmg);
									break;
								}
								opponent.setHP(opponent.getHP() - dmg); break;
		default:				assert(opponent.getState() != status::neutral && "Invalid State");
								assert(opponent.getState() != status::attacking && "Invalid State");
								assert(opponent.getState() != status::blocking && "Invalid State");
								assert(opponent.getState() != status::grabbing && "Invalid State");
								assert(opponent.getState() != status::stun && "Invalid State");
	}	
	ex++;
	cout << name << " punched " << opponent.getName() << endl;
}

void Fighter::block(){
	state = status::blocking;
}

void Fighter::grab(Fighter& opponent){
	state = status::grabbing;
	switch (opponent.getState()) {
		case status::neutral:	opponent.setHP(opponent.getHP() - (atk * 2)); break;
		case status::attacking:	cout << name << " got attacked while trying to grab " << opponent.getName() << endl; return;
		case status::blocking:	opponent.setHP(opponent.getHP() - (atk * 2)); break;
		case status::grabbing:	cout << opponent.getName() << " escaped the grab" << endl; return;
		case status::stun:		opponent.setHP(opponent.getHP() - (atk * 2)); break;
		default:				assert(opponent.getState() != status::neutral  && "Invalid State");
								assert(opponent.getState() != status::attacking && "Invalid State");
								assert(opponent.getState() != status::blocking && "Invalid State");
								assert(opponent.getState() != status::grabbing && "Invalid State");
								assert(opponent.getState() != status::stun && "Invalid State");
	}
}

Shoto::Shoto(string input) {
	name = input;
}

Shoto::Shoto(int num){ //default Ryu
	num < 1 ? name = "Ryu" : name = "Ken";
	hp = 200;
	ex = 0;
	wins = 0;
	atk = 10;
	def = 10;
	speed = 1;
}

Shoto::~Shoto() {}



