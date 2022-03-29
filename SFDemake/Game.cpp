#include "Game.h"

using namespace std;

void titleScreen(){
	char input = 'a';
	while (input != 'p') {
		system("cls");
		cout << "\n";
		cout << "	 _____ _                 _    ______ _       _     _             ______                     _        " << endl;
		cout << "	/  ___| |               | |   |  ___(_)     | |   | |            |  _  \\                   | |       " << endl;
		cout << "	\\ `--.| |_ _ __ ___  ___| |_  | |_   _  __ _| |__ | |_ ___ _ __  | | | |___ _ __ ___   __ _| | _____ " << endl;
		cout << "	 `--. \\ __| '__/ _ \\/ _ \\ __| |  _| | |/ _` | '_ \\| __/ _ \\ '__| | | | / _ \\ '_ ` _ \\ / _` | |/ / _ \\" << endl;
		cout << "	/\\__/ / |_| | |  __/  __/ |_  | |   | | (_| | | | | ||  __/ |    | |/ /  __/ | | | | | (_| |   <  __/" << endl;
		cout << "	\\____/ \\__|_|  \\___|\\___|\\__| \\_|   |_|\\__, |_| |_|\\__\\___|_|    |___/ \\___|_| |_| |_|\\__,_|_|\\_\\___|" << endl;
		cout << "	                                        __/ |                                                        " << endl;
		cout << "	                                       |___/                                                         " << endl;
		cout << "\n\n	                                         Press P to continue" << endl;
		input = _getch();
	}
}

int selectMode(){
	char input = 'a';
	int count = 0;
	while (input != 'p') {
		system("cls");
		cout << "\nSelect Mode:\nPress P to confirm your choice\n" << endl;
		(count == 0) ? cout << "--> Singleplayer" << endl : cout << "Singleplayer" << endl;
		(count == 1) ? cout << "--> Multiplayer" << endl : cout << "Multiplayer" << endl;
		(count == 2) ? cout << "--> Tag-Team" << endl : cout << "Tag-Team" << endl;
		(count == 3) ? cout << "--> Create Fighter" << endl : cout << "Create Fighter" << endl;
		input = _getch();
		switch (input) {
			case 's':	count++; count %= 4; break;
			case 'w':	count--; (count < 0) ? count = 3 : count %= 4; break;
			default:	assert(!(input == 's' || input == 'w') && "select screen error");
		}
	}
	switch (count) {
		case 0: cout << "\nYou chose to fight against the computer" << endl; return 0;
		case 1: cout << "\nYou chose to fight against another player" << endl; return 1;
		case 2: cout << "\nYou chose Tag-Team Battle" << endl; return 2;
		case 3: cout << "\nYou chose to create a new Fighter" << endl; return 3;
		default: break;
	}
	return 4;
}

int selectFighter(Fighter* roster[]){
	char input = 'a';
	int count = 0;
	while (input != 'p') {
		int temp = 0;
		system("cls");
		cout << "\nChoose a Fighter:\nPress P to confirm your choice\n" << endl;
		for (int i = 0; i < S; i++) {
			if (roster[i]->getName() == "\0") break;
			(count == temp) ? cout << "-->" << " " << roster[i]->getName() << endl : cout << roster[i]->getName() << endl;
			temp++;
		}
		input = _getch();
		switch (input) {
		case 's':	count++; count %= temp; break;
		case 'w':	count--; (count < 0) ? count = temp-1 : count %= temp; break;
		}
	}
	cout << "\nYou chose " << roster[count]->getName() << endl; return count;
}

int selectOp(Fighter* roster[], int block){
	char input = 'a';
	int count = 0;
	char temp = 'a';
	do{
		int temp = 0;
		system("cls");
		cout << "\nChoose an Opponent:\nPress P to confirm your choice\n" << endl;
		for (int i = 0; i < S; i++) {
			if (roster[i]->getName() == "\0") break;
			(count == temp) ? cout << "-->" << " " << roster[i]->getName() << endl : cout << roster[i]->getName() << endl;
			temp++;
		}
		input = _getch();
		switch (input) {
			case 's':	count++; count %= temp; break;
			case 'w':	count--; (count < 0) ? count = temp - 1 : count %= temp; break;
		}
		if (input == 'p' && count == block) {
			cout << "Fighter already chosen! Press any key to continue" << endl;
			input = 'a';
			temp = _getch();
		}
	} while (input != 'p');
	cout << "\nYou chose " << roster[count]->getName() << endl; 
	return count;
}

void fightTest() {
	int i = 0;
	Shoto ryu(0);
	assert(ryu.getHP() == 200 && "ryu instanced with wrong hp");
	cout << "here 1" << endl;
	Shoto ken(1);
	assert(ken.getHP() == 200 && "ryu instanced with wrong hp");
	cout << "here 2" << endl;
	printFightMenu(ryu, ken);
	cout << "here print" << endl;
	ryu.punch(ken);
	assert(ryu.getState() == status::attacking && "State not changed");
	cout << "here 3" << endl;
	assert(ken.getHP() == 190 && "Damage incorrectly dealt");
	cout << "here 4" << endl;
	printFightMenu(ryu, ken);
	ryu.block();
	assert(ryu.getState() == status::blocking && "State not changed");
	cout << "here 5" << endl;
	ken.punch(ryu);
	assert(ken.getState() == status::attacking && "State not changed");
	cout << "here 6" << endl;
	assert(ryu.getHP() == 198 && "Damage incorrectly dealt");
	cout << "here 7" << endl;
	printFightMenu(ryu, ken);
	ryu.grab(ken);
	assert(ryu.getState() == status::grabbing && "State not changed");
	cout << "here 8" << endl;
	assert(ken.getHP() == 190 && "Damage incorrectly dealt");
	cout << "here 9" << endl;
	ken.block();
	assert(ken.getState() == status::blocking && "State not changed");
	cout << "here 10" << endl;
	ryu.grab(ken);
	assert(ryu.getState() == status::grabbing && "State not changed");
	cout << "here 11" << endl;
	assert(ken.getHP() == 170 && "Damage incorrectly dealt");
	cout << "here 12" << endl;
	printFightMenu(ryu, ken);
	ken.grab(ryu);
	assert(ryu.getState() == status::grabbing && "State not changed");
	cout << "here 13" << endl;
	assert(ryu.getHP() == 198 && "Damage incorrectly dealt");
	cout << "here 14" << endl;
}

void resolveAction(Fighter& ryu, Fighter& ken, int ryuAction){
	//int kenAction = rand() % 5 + 1;
	int kenAction = rand() % 3 + 1; //for testing only
	if (kenAction == 2) {
		doAction(ken, ryu, kenAction);
		doAction(ryu, ken, ryuAction);
	}
	else if (ryuAction == 3 && kenAction != 3) {
		doAction(ken, ryu, kenAction);
		doAction(ryu, ken, ryuAction);
	}
	else if (ryu.getSpeed() >= ken.getSpeed()) {
		if (ryuAction == 3 && kenAction == 3) {
			cout << ken.getName() << " escaped the grab" << endl; 
		}
		else {
			doAction(ryu, ken, ryuAction);
			doAction(ken, ryu, kenAction);
		}
	}
	ryu.setState(status::neutral);
	ken.setState(status::neutral);
}

void doAction(Fighter& ryu, Fighter& ken, int ryuAction){
	switch (ryuAction) {
		case 1:		ryu.punch(ken); break;
		case 2:		ryu.block(); break;
		case 3:		ryu.grab(ken); break;
			//case skill1, skill2 tbd
	}
}


int createFighter(){
	char input = 'a';
	int count = 0;
	while (input != 'p') {
		system("cls");
		cout << "\nSelect Archetype:\nPress P to confirm your choice\n" << endl;
		(count == 0) ? cout << "--> Shoto" << endl : cout << "Shoto" << endl;
		(count == 1) ? cout << "--> Rushdown" << endl : cout << "Rushdown" << endl;
		(count == 2) ? cout << "--> Grappler" << endl : cout << "Grappler" << endl;
		input = _getch();
		switch (input) {
			case 's':	count++; count %= 3; break;
			case 'w':	count--; (count < 0) ? count = 2 : count %= 3; break;
		}
	}
	switch (count) {
		case 0: cout << "\nYou chose to create a Shoto" << endl; return 0;
		case 1: cout << "\nYou chose to create a Rushdown Fighter" << endl; return 1;
		case 2: cout << "\nYou chose to create a Grappler" << endl; return 2;
		default: break;
	}
	return 3;
}

int rosterSize(Fighter* roster[]){
	int cnt = 0;
	for (int i = 0; i < S; i++) {
		if (roster[i]->getName() == "\0") break;
		cnt++;
	}
	return cnt;
}

void fight(Fighter& ryu, Fighter& ken) {
	char a;
	while (true) {
		int action = 0;
		system("cls");
		printFightMenu(ryu, ken);
		if (ryu.getHP() > 0 && ken.getHP() <= 0) {
			cout << "\n" << ryu.getName() << " wins!" << endl;
			break;
		}
		if (ken.getHP() > 0 && ryu.getHP() <= 0) {
			cout << "\n" << ken.getName() << " wins!" << endl;
			break;
		}
		resolveAction(ryu, ken, ryu.chooseAction());
		cout << "\nPress any key to continue" << endl;
		a = _getch();
	}
}



void printFightMenu(Fighter& ryu, Fighter& ken){
	system("cls");
	cout << "\n";
	ryu.updateLifebar();
	ken.updateLifebar();
	cout << ryu.getName() << "	Wins: " << ryu.getWins() << "				" << ken.getName() << "	  Wins: " << ken.getWins() << endl;
	cout << ryu.getLifebar() << "			" << ken.getLifebar() << endl;
	cout << "HP: " << ryu.getHP() << "					HP: " << ken.getHP() << endl;
}
