#include "Fighter.h"

Fighter::Fighter() {
	name = "\0";
	hp = 0;
	ex = 0;
	wins = 0;
}

Fighter::~Fighter() {}

Shoto::Shoto(string input) {
	name = input;
}

Shoto::Shoto(int def){ //default Ryu
	def < 1 ? name = "Ryu" : name = "Ken";
	hp = 200;
	ex = 0;
	wins = 0;
}

Shoto::~Shoto() {}

void Shoto::Hadouken(Fighter& op){
	op.setHP(op.getHP() - 30);
	this->ex += 1;
	std::cout << this->name << " launched a Hadouken" << endl;
	//TBD: finish function
}


