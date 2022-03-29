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
	cout << name << " assumes a defensive stance" << endl;
}

void Fighter::grab(Fighter& opponent){
	state = status::grabbing;
	switch (opponent.getState()) {
		case status::neutral:	opponent.setHP(opponent.getHP() - (atk * 2)); 
								cout << name << " grabbed " << opponent.getName() << " and threw them over their shoulder" << endl; 
								break;
		case status::attacking:	cout << name << " got attacked while trying to grab " << opponent.getName() << endl; return;
		case status::blocking:	opponent.setHP(opponent.getHP() - (atk * 2)); 
								cout << name << " grabbed " << opponent.getName() << " and threw them over their shoulder" << endl; 
								break;
		case status::grabbing:	cout << opponent.getName() << " escaped the grab" << endl; return;
		case status::stun:		opponent.setHP(opponent.getHP() - (atk * 2)); 
								cout << name << " grabbed " << opponent.getName() << " and threw them over their shoulder" << endl; 
								break;
		default:				assert(opponent.getState() != status::neutral  && "Invalid State");
								assert(opponent.getState() != status::attacking && "Invalid State");
								assert(opponent.getState() != status::blocking && "Invalid State");
								assert(opponent.getState() != status::grabbing && "Invalid State");
								assert(opponent.getState() != status::stun && "Invalid State");
	}
}

void Fighter::useSkill(int i, Fighter& ken)
{
}

void Fighter::updateLifebar(){}

int Fighter::chooseAction(){
	cout << "\n\nChoose action: " << endl;
	cout << "1: Punch\n2: Block\n3: Grab" << endl;
	int choice = _getch();
	return 0;
}

Shoto::Shoto(string input) {
	name = input;
	hp = 200;
	lifebar = "|====================|";
	ex = 0;
	wins = 0;
	atk = 10;
	def = 10;
	speed = 1;
}

Shoto::Shoto(int num){ //default Ryu/Ken
	if (num < 1) {
		name = "Ryu";
		skill1 = new ShotoSkill("Hadoken", 30, 2, 1);
		skill2 = new ShotoSkill("Shoryuken", 40, 2, 2);
	}
	else {
		name = "Ken";
		skill1 = new ShotoSkill("Tatsumaki", 35, 2, 1);
		skill2 = new ShotoSkill("Shoryuken", 40, 2, 2);
	}
	hp = maxHP;
	lifebar = "|====================|";
	ex = 0;
	wins = 0;
	atk = 10;
	def = 10;
	speed = 1;
}

Shoto::~Shoto() {}

void Shoto::updateLifebar() {
	double percent = (hp * 100) / maxHP;
	double length = 20 * (percent / 100);
	lifebar[0] = '|';
	for (int i = 1; i < 21; i++) {
		length > 0 ? lifebar[i] = '=' : lifebar[i] = ' ';
		length--;
	}
	lifebar[22] = '|';
}

int Shoto::chooseAction(){
	cout << "\n\nChoose action: " << endl;
	cout << "1: Punch\n2: Block\n3: Grab\n4: " << skill1->getName() << "\n5: " << skill2->getName() << endl;
	int choice;
	cin >> choice;
	return choice;
}

/*void Shoto::useSkill(int i, Fighter& ken) {
	if (i == 1) {
		if(skill1->getName() == "Hadoken") { hadoken(skill1, ken); }
		if(skill1->getName() == "Shoryuken"){}
		if(skill1->getName() == "Tatsumaki"){}
		if(skill1->getName() == "Counter"){}
		if(skill1->getName() == "Shoulder Throw"){}
	}
	if (i == 2) {
		if (skill2->getName() == "Hadoken") { }
		if (skill2->getName() == "Shoryuken") {}
		if (skill2->getName() == "Tatsumaki") {}
		if (skill2->getName() == "Counter") {}
		if (skill2->getName() == "Shoulder Throw") {}
	}
}

void Shoto::hadoken(ShotoSkill& hadoken, Fighter& ken){
	if (hadoken.getCooldown() > 0) return;
}*/

Grappler::Grappler(string input){
	name = input;
	hp = 300;
	ex = 0;
	wins = 0;
	atk = 5;
	def = 15;
	speed = 0;
}

Grappler::~Grappler()
{
}

void Grappler::useSkill(int i, Fighter& ken)
{
}

Rush::Rush(string input){
	name = input;
	hp = 200;
	ex = 0;
	wins = 0;
	atk = 15;
	def = 5;
	speed = 2;
}

Rush::~Rush()
{
}

void Rush::useSkill(int i, Fighter& ken)
{
}
