#include "Fighter.h"

Fighter::Fighter() {
	name = "\0";
	hp = 0;
	ex = 0;
	state = status::neutral;
	wins = 0;
	losses = 0;
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
	cout << name << " punched " << opponent.getName() << endl;
}

void Fighter::block(){
	state = status::blocking;
	ex++;
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

void Fighter::exAttack(Fighter& opponent){
	if (ex != 10) return;
	ex = 0;
	opponent.setHP(opponent.getHP() - 45);
	opponent.setState(status::stun);
	cout << name << " dealt a devastating blow." << endl;
}

//--------------------------------------------------
Shoto::Shoto(string input) {
	name = input;
	hp = 200;
	lifebar = "|====================|";
	ex = 0;
	wins = 0;
	atk = 10;
	def = 10;
	speed = 1;
	skill1 = selectShotoSkill();
	skill2 = selectShotoSkill();
}

Shoto::Shoto(int num){ //default Ryu/Ken
	if (num < 1) {
		name = "Ryu";
		skill1 = 0;
		skill2 = 1;
	}
	else {
		name = "Ken";
		skill1 = 2;
		skill2 = 1;
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

void Shoto::restoreFighter(){
	hp = maxHP;
	ex = 0;
	updateLifebar();
	state = status::neutral;
}

int Shoto::selectShotoSkill() {
	char input = 'a';
	int count = 0;
	while (input != 'p') {
		system("cls");
		cout << "\nSelect Skill:\nPress P to confirm your choice\n" << endl;
		(count == 0) ? cout << "--> Hadoken" << endl : cout << "Hadoken" << endl;
		(count == 1) ? cout << "--> Shoryuken" << endl : cout << "Shoryuken" << endl;
		(count == 2) ? cout << "--> Tatsumaki" << endl : cout << "Tatsumaki" << endl;
		(count == 3) ? cout << "--> Axe Kick" << endl : cout << "Axe Kick" << endl;
		(count == 4) ? cout << "--> Counter" << endl : cout << "Counter" << endl;
		input = _getch();
		switch (input) {
			case 's':	count++; count %= 5; break;
			case 'w':	count--; (count < 0) ? count = 4 : count %= 5; break;
		default:	assert(!(input == 's' || input == 'w') && "select screen error");
		}
	}
	switch (count) {
		case 0: return 0;
		case 1: return 1;
		case 2: return 2;
		case 3: return 3;
		case 4: return 4;
		default: break;
	}
	return -1;
}

void Shoto::useSkill(Skill* sklList[], int slot, Fighter& ken) {
	if (slot == 1) {
		switch (ken.getState()) {
			case status::neutral:	ken.setHP(ken.getHP() - sklList[skill1]->getDmg()); break;
			case status::attacking:	ken.setHP(ken.getHP() - sklList[skill1]->getDmg()); break;
			case status::grabbing:	ken.setHP(ken.getHP() - sklList[skill1]->getDmg()); break;
			case status::stun:		ken.setHP(ken.getHP() - sklList[skill1]->getDmg()); break;
			case status::blocking:	ken.setHP(ken.getHP() - (sklList[skill1]->getDmg() / 2)); break;
		}
		ex += sklList[skill1]->getExGain();
		cout << name << " uses " << sklList[skill1]->getName() << endl;
		state = status::wait;
		return;
	}
	else {
		switch (ken.getState()) {
			case status::neutral:	ken.setHP(ken.getHP() - sklList[skill2]->getDmg()); break;
			case status::attacking:	ken.setHP(ken.getHP() - sklList[skill2]->getDmg()); break;
			case status::grabbing:	ken.setHP(ken.getHP() - sklList[skill2]->getDmg()); break;
			case status::stun:		ken.setHP(ken.getHP() - sklList[skill2]->getDmg()); break;
			case status::blocking:	ken.setHP(ken.getHP() - (sklList[skill2]->getDmg() / 2)); break;
		}
		ex += sklList[skill2]->getExGain();
		cout << name << " uses " << sklList[skill2]->getName() << endl;
		state = status::wait;
		return;
	}	
}
/*
void Shoto::hadoken(ShotoSkill& hadoken, Fighter& ken){
	if (hadoken.getCooldown() > 0) return;
}*/
//------------------------------------------------------
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

/*void Grappler::useSkill(GrappleSkill skl, Fighter& ken) {
	switch (ken.getState()) {
		case status::neutral:	ken.setHP(ken.getHP() - skl.getDmg()); break;
		case status::attacking:	ken.setHP(ken.getHP() - skl.getDmg()); break;
		case status::grabbing:	ken.setHP(ken.getHP() - skl.getDmg()); break;
		case status::stun:		ken.setHP(ken.getHP() - skl.getDmg()); break;
		case status::blocking:	ken.setHP(ken.getHP() - (skl.getDmg() / 2)); break;
	}
	ex += skl.getExGain();
}*/

void Grappler::restoreFighter(){
	hp = maxHP;
	ex = 0;
	updateLifebar();
	state = status::neutral;
}
//---------------------------------------------------------------------------
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

/*void Rush::useSkill(RushSkill skl, Fighter& ken) {
	switch (ken.getState()) {
		case status::neutral:	ken.setHP(ken.getHP() - skl.getDmg()); break;
		case status::attacking:	ken.setHP(ken.getHP() - skl.getDmg()); break;
		case status::grabbing:	ken.setHP(ken.getHP() - skl.getDmg()); break;
		case status::stun:		ken.setHP(ken.getHP() - skl.getDmg()); break;
		case status::blocking:	ken.setHP(ken.getHP() - (skl.getDmg() / 2)); break;
	}
	ex += skl.getExGain();
}*/

void Rush::restoreFighter(){
	hp = maxHP;
	ex = 0;
	updateLifebar();
	state = status::neutral;
}
