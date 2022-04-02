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

Fighter::~Fighter() {
	cout << name << " destroyed" << endl;
}

void Fighter::punch(Fighter& opponent){
	state = status::attacking;
	int dmg = atk - opponent.getDef();
	//status opstate = opponent.getState();
	switch(opponent.getState()){
		case status::neutral:	opponent.setHP(opponent.getHP() - atk); break;
		case status::attacking:	opponent.setHP(opponent.getHP() - atk); break;
		case status::grabbing:	opponent.setHP(opponent.getHP() - atk); break;
		case status::stun:		opponent.setHP(opponent.getHP() - atk); break;
		case status::wait:		opponent.setHP(opponent.getHP() - atk); break;
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
		case status::wait:		opponent.setHP(opponent.getHP() - (atk * 2));
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

void Fighter::wait(){
	cout << name << " needs to wait for next action" << endl;
	state = status::neutral;
}
//--------------------------------------------------
Shoto::Shoto(string input) {
	name = input;
	hp = 200;
	//lifebar = "|====================|";
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
	//lifebar = "|====================|";
	ex = 0;
	wins = 0;
	atk = 10;
	def = 10;
	speed = 1;
}

Shoto::~Shoto() {
	cout << name << " destroyed" << endl;
}

void Shoto::updateLifebar() {
	double percent = (hp * 100) / maxHP;
	double length = 20 * (percent / 100);
	lifebar[0] = '|';
	for (int i = 1; i < 21; i++) {
		length > 0 ? lifebar[i] = '=' : lifebar[i] = ' ';
		length--;
	}
	lifebar[21] = '|';
	lifebar[22] = '\0';
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
		if (skill1 == 4) {
			state = status::blocking;
			if (ken.getState() == status::blocking) return;
			ken.setHP(ken.getHP() - sklList[skill1]->getDmg());
			cout << name << "blocks the attack and swiftly counters" << endl;
			return;
		}
		switch (ken.getState()) {
			case status::neutral:	ken.setHP(ken.getHP() - sklList[skill1]->getDmg()); break;
			case status::attacking:	ken.setHP(ken.getHP() - sklList[skill1]->getDmg()); break;
			case status::grabbing:	ken.setHP(ken.getHP() - sklList[skill1]->getDmg()); break;
			case status::stun:		ken.setHP(ken.getHP() - sklList[skill1]->getDmg()); break;
			case status::blocking:	ken.setHP(ken.getHP() - (sklList[skill1]->getDmg() / 2)); break;
			case status::wait:		ken.setHP(ken.getHP() - sklList[skill1]->getDmg()); break;
		}
		ex += sklList[skill1]->getExGain();
		cout << name << " uses " << sklList[skill1]->getName() << endl;
		state = status::wait;
		return;
	}
	else {
		if (skill2 == 4) {
			state = status::blocking;
			if (ken.getState() == status::blocking) return;
			ken.setHP(ken.getHP() - sklList[skill2]->getDmg());
			cout << name << "blocks the attack and swiftly counters" << endl;
			return;
		}
		switch (ken.getState()) {
			case status::neutral:	ken.setHP(ken.getHP() - sklList[skill2]->getDmg()); break;
			case status::attacking:	ken.setHP(ken.getHP() - sklList[skill2]->getDmg()); break;
			case status::grabbing:	ken.setHP(ken.getHP() - sklList[skill2]->getDmg()); break;
			case status::stun:		ken.setHP(ken.getHP() - sklList[skill2]->getDmg()); break;
			case status::blocking:	ken.setHP(ken.getHP() - (sklList[skill2]->getDmg() / 2)); break;
			case status::wait:		ken.setHP(ken.getHP() - sklList[skill2]->getDmg()); break;
		}
		ex += sklList[skill2]->getExGain();
		cout << name << " uses " << sklList[skill2]->getName() << endl;
		state = status::wait;
		return;
	}	
}
//------------------------------------------------------
Grappler::Grappler(string input){
	name = input;
	hp = maxHP;
	ex = 0;
	wins = 0;
	atk = 5;
	def = 15;
	speed = 0;
	skill1 = selectGrappleSkill();
	skill2 = selectGrappleSkill();
}

Grappler::Grappler(int num){
	if (num < 1) {
		name = "Zangief";
		skill1 = 5;
		skill2 = 9;
	}
	else {
		name = "R.Mika";
		skill1 = 6;
		skill2 = 7;
	}
	hp = maxHP;
	//lifebar = "|====================|";
	ex = 0;
	wins = 0;
	atk = 5;
	def = 15;
	speed = 0;
}

Grappler::~Grappler(){
	cout << name << " destroyed" << endl;
}

void Grappler::updateLifebar() {
	double percent = (hp * 100) / maxHP;
	double length = 20 * (percent / 100);
	lifebar[0] = '|';
	for (int i = 1; i < 21; i++) {
		length > 0 ? lifebar[i] = '=' : lifebar[i] = ' ';
		length--;
	}
	lifebar[21] = '|';
	lifebar[22] = '\0';
}

void Grappler::restoreFighter(){
	hp = maxHP;
	ex = 0;
	updateLifebar();
	state = status::neutral;
}

int Grappler::selectGrappleSkill(){
	char input = 'a';
	int count = 0;
	while (input != 'p') {
		system("cls");
		cout << "\nSelect Skill:\nPress P to confirm your choice\n" << endl;
		(count == 0) ? cout << "--> Cyclone Lariat" << endl : cout << "Cyclone Lariat" << endl;
		(count == 1) ? cout << "--> Steel Chair" << endl : cout << "Steel Chair" << endl;
		(count == 2) ? cout << "--> Dive Bomb" << endl : cout << "Dive Bomb" << endl;
		(count == 3) ? cout << "--> Pile Driver" << endl : cout << "Pile Driver" << endl;
		(count == 4) ? cout << "--> Iron Muscle" << endl : cout << "Iron Muscle" << endl;
		input = _getch();
		switch (input) {
		case 's':	count++; count %= 5; break;
		case 'w':	count--; (count < 0) ? count = 4 : count %= 5; break;
		default:	assert(!(input == 's' || input == 'w') && "select screen error");
		}
	}
	switch (count) {
	case 0: return 5;
	case 1: return 6;
	case 2: return 7;
	case 3: return 8;
	case 4: return 9;
	default: break;
	}
	return -1;
}

void Grappler::useSkill(Skill* sklList[], int slot, Fighter& ken){
	if (slot == 1) {
		if (skill1 == 9) {
			state = status::blocking;
			cout << name << "flexes their muscles. Attack increased" << endl;
			atk++;
			return;
		}
		switch (ken.getState()) {
		case status::neutral:	ken.setHP(ken.getHP() - sklList[skill1]->getDmg()); break;
		case status::attacking:	ken.setHP(ken.getHP() - sklList[skill1]->getDmg()); break;
		case status::grabbing:	ken.setHP(ken.getHP() - sklList[skill1]->getDmg()); break;
		case status::stun:		ken.setHP(ken.getHP() - sklList[skill1]->getDmg()); break;
		case status::blocking:	ken.setHP(ken.getHP() - (sklList[skill1]->getDmg() / 2)); break;
		case status::wait:		ken.setHP(ken.getHP() - sklList[skill1]->getDmg()); break;
		}
		ex += sklList[skill1]->getExGain();
		cout << name << " uses " << sklList[skill1]->getName() << endl;
		state = status::wait;
		return;
	}
	else {
		if (skill1 == 9) {
			state = status::blocking;
			cout << name << "flexes their muscles. Attack increased" << endl;
			atk++;
			return;
		}
		switch (ken.getState()) {
		case status::neutral:	ken.setHP(ken.getHP() - sklList[skill2]->getDmg()); break;
		case status::attacking:	ken.setHP(ken.getHP() - sklList[skill2]->getDmg()); break;
		case status::grabbing:	ken.setHP(ken.getHP() - sklList[skill2]->getDmg()); break;
		case status::stun:		ken.setHP(ken.getHP() - sklList[skill2]->getDmg()); break;
		case status::blocking:	ken.setHP(ken.getHP() - (sklList[skill2]->getDmg() / 2)); break;
		case status::wait:		ken.setHP(ken.getHP() - sklList[skill2]->getDmg()); break;
		}
		ex += sklList[skill2]->getExGain();
		cout << name << " uses " << sklList[skill2]->getName() << endl;
		state = status::wait;
		return;
	}
}
//---------------------------------------------------------------------------
Rush::Rush(string input){
	name = input;
	hp = maxHP;
	ex = 0;
	wins = 0;
	atk = 15;
	def = 5;
	speed = 2;
	skill1 = selectRushSkill();
	skill2 = selectRushSkill();
}

Rush::Rush(int num){
	if (num < 1) {
		name = "Cammy";
		skill1 = 10;
		skill2 = 11;
	}
	else {
		name = "Karin";
		skill1 = 13;
		skill2 = 14;
	}
	//lifebar = "|====================|";
	hp = maxHP;
	ex = 0;
	wins = 0;
	atk = 15;
	def = 5;
	speed = 2;
}

Rush::~Rush(){
	cout << name << " destroyed" << endl;
}

void Rush::updateLifebar() {
	double percent = (hp * 100) / maxHP;
	double length = 20 * (percent / 100);
	lifebar[0] = '|';
	for (int i = 1; i < 21; i++) {
		length > 0 ? lifebar[i] = '=' : lifebar[i] = ' ';
		length--;
	}
	lifebar[21] = '|';
	lifebar[22] = '\0';
}

void Rush::restoreFighter(){
	hp = maxHP;
	ex = 0;
	updateLifebar();
	state = status::neutral;
}

int Rush::selectRushSkill(){
	char input = 'a';
	int count = 0;
	while (input != 'p') {
		system("cls");
		cout << "\nSelect Skill:\nPress P to confirm your choice\n" << endl;
		(count == 0) ? cout << "--> Knee Bullet" << endl : cout << "Knee Bullet" << endl;
		(count == 1) ? cout << "--> Spiral Arrow" << endl : cout << "Spiral Arrow" << endl;
		(count == 2) ? cout << "--> Throw Kunai" << endl : cout << "Throw Kunai" << endl;
		(count == 3) ? cout << "--> Tenko" << endl : cout << "Tenko" << endl;
		(count == 4) ? cout << "--> Slide" << endl : cout << "Slide" << endl;
		input = _getch();
		switch (input) {
		case 's':	count++; count %= 5; break;
		case 'w':	count--; (count < 0) ? count = 4 : count %= 5; break;
		default:	assert(!(input == 's' || input == 'w') && "select screen error");
		}
	}
	switch (count) {
	case 0: return 10;
	case 1: return 11;
	case 2: return 12;
	case 3: return 13;
	case 4: return 14;
	default: break;
	}
	return -1;
}

void Rush::useSkill(Skill* sklList[], int slot, Fighter& ken){
	if (slot == 1) {
		if (skill1 == 14) {
			state = status::blocking;
			cout << name << "heals 20 HP" << endl;
			hp += 15;
			atk++;
			return;
		}
		switch (ken.getState()) {
		case status::neutral:	ken.setHP(ken.getHP() - sklList[skill1]->getDmg()); break;
		case status::attacking:	ken.setHP(ken.getHP() - sklList[skill1]->getDmg()); break;
		case status::grabbing:	ken.setHP(ken.getHP() - sklList[skill1]->getDmg()); break;
		case status::stun:		ken.setHP(ken.getHP() - sklList[skill1]->getDmg()); break;
		case status::blocking:	ken.setHP(ken.getHP() - (sklList[skill1]->getDmg() / 2)); break;
		case status::wait:		ken.setHP(ken.getHP() - sklList[skill1]->getDmg()); break;
		}
		ex += sklList[skill1]->getExGain();
		cout << name << " uses " << sklList[skill1]->getName() << endl;
		state = status::attacking;
		atk -= rand() % 2 + 1;
		return;
	}
	else {
		if (skill1 == 9) {
			state = status::blocking;
			cout << name << "heals 20 HP" << endl;
			hp += 15;
			atk++;
			return;
		}
		switch (ken.getState()) {
		case status::neutral:	ken.setHP(ken.getHP() - sklList[skill2]->getDmg()); break;
		case status::attacking:	ken.setHP(ken.getHP() - sklList[skill2]->getDmg()); break;
		case status::grabbing:	ken.setHP(ken.getHP() - sklList[skill2]->getDmg()); break;
		case status::stun:		ken.setHP(ken.getHP() - sklList[skill2]->getDmg()); break;
		case status::blocking:	ken.setHP(ken.getHP() - (sklList[skill2]->getDmg() / 2)); break;
		case status::wait:		ken.setHP(ken.getHP() - sklList[skill2]->getDmg()); break;
		}
		ex += sklList[skill2]->getExGain();
		cout << name << " uses " << sklList[skill2]->getName() << endl;
		state = status::attacking;
		atk -= rand() % 2 + 1;
		return;
	}
}