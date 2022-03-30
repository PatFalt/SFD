#include "Game.h"

using namespace std;

Game::Game(){
	fightTest();
	srand(time(NULL));
	for (int i = 0; i < 5; i++) {
		skills[i] = new ShotoSkill(i);
		skills[i + 5] = new GrappleSkill(i + 5);
		skills[i + 10] = new RushSkill(i + 10);
	}
	Shoto* ryu = new Shoto(0);
	Shoto* ken = new Shoto(1);
	for (int i = 0; i < S; i++) {
		roster[i] = new Fighter();
	}
	roster[0] = ryu;
	roster[1] = ken;
	int p1 = 0;
	titleScreen();
	do {
		selectMode();
		switch (mode) {
			case 0:	play(); break;//PVE
			case 1: play(); break;//PVP
			case 2: play(); break;//CVC
			case 3: p1 = selectFighter(); break;//Tag-Team
			case 4: addFighter();
				system("cls");
				break;
			case 5: printWinLoss(); break;
		}
	} while (contGame != 'q');
}

Game::~Game(){
	cout << "Finished" << endl;
}

void Game::titleScreen(){
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

void Game::selectMode(){
	char input = 'a';
	int count = 0;
	while (input != 'p') {
		system("cls");
		cout << "\nSelect Mode:\nPress P to confirm your choice\n" << endl;
		(count == 0) ? cout << "--> Singleplayer" << endl : cout << "Singleplayer" << endl;
		(count == 1) ? cout << "--> Multiplayer" << endl : cout << "Multiplayer" << endl;
		(count == 2) ? cout << "--> CPU vs CPU" << endl : cout << "CPU vs CPU" << endl;
		(count == 3) ? cout << "--> Tag-Team" << endl : cout << "Tag-Team" << endl;
		(count == 4) ? cout << "--> Create Fighter" << endl : cout << "Create Fighter" << endl;
		(count == 5) ? cout << "--> Show Wins and Losses" << endl : cout << "Show Wins and Losses" << endl;
		input = _getch();
		switch (input) {
			case 's':	count++; count %= 6; break;
			case 'w':	count--; (count < 0) ? count = 5 : count %= 6; break;
			default:	assert(!(input == 's' || input == 'w') && "select screen error");
		}
	}
	switch (count) {
		case 0: mode = 0; break;
		case 1: mode = 1; break;
		case 2: mode = 2; break;
		case 3: mode = 3; break;
		case 4: mode = 4; break;
		case 5: mode = 5; break;
		default: break;
	}
}

int Game::selectFighter(){
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

int  Game::selectOp(int block){
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

void  Game::fightTest() {
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

void Game::fight(Fighter& ryu, Fighter& ken) {
	char a;
	int turn = 0;
	while (true) {
		int action = 0;
		system("cls");
		printFightMenu(ryu, ken);
		if (ryu.getHP() > 0 && ken.getHP() <= 0) {
			cout << "\n" << ryu.getName() << " wins!" << endl;
			ryu.setWins();
			ken.setLosses();
			break;
		}
		if (ken.getHP() > 0 && ryu.getHP() <= 0) {
			cout << "\n" << ken.getName() << " wins!" << endl;
			ken.setWins();
			ryu.setLosses();
			break;
		}
		resolveAction(ryu, ken);
		cout << "\nPress any key to continue" << endl;
		a = _getch();
		turn++;
	}
}

void  Game::resolveAction(Fighter& ryu, Fighter& ken){
	int ryuAction = 0;
	int kenAction = 0;
	switch (mode) {
	case 0:		if (ken.getState() != status::wait) { kenAction = rand() % 5 + 1; }
				else{ cout << ken.getName() << " needs to wait for next action" << endl; }	
				ryuAction = chooseAction(ryu);
				break; 		
		case 1: ryuAction = chooseAction(ryu);
				kenAction = chooseAction(ken);
				break;
		case 2: if (ryu.getState() != status::wait) { ryuAction = rand() % 5 + 1; }
				 else { cout << ryu.getName() << " needs to wait for next action" << endl; }
				if (ken.getState() != status::wait) { kenAction = rand() % 5 + 1; }
				else { cout << ken.getName() << " needs to wait for next action" << endl; }
				break;
	}
	if (ryuAction == 0) {
		if(kenAction != 0)
			doAction(ken, ryu, kenAction);
	}
	else if (kenAction == 0) {
		if(ryuAction != 0)
			doAction(ryu, ken, ryuAction);
	}
	else if (kenAction == 2) {
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
	//if(ryu.getState() != status::wait)
		ryu.setState(status::neutral);
	//if(ken.getState() != status::wait)
		ken.setState(status::neutral);
}

void  Game::doAction(Fighter& ryu, Fighter& ken, int ryuAction){
	switch (ryuAction) {
		case 1:	ryu.punch(ken); break;
		case 2:	ryu.block(); break;
		case 3:	ryu.grab(ken); break;
		case 4:	ryu.useSkill(skills, 1, ken); break;
		case 5:	ryu.useSkill(skills, 2, ken); break;
		case 6:	ryu.exAttack(ken); break;
	}
}

/*void Game::useSkill(Fighter& ryu, Fighter& ken, int slot) {
	if (slot == 1) {
		switch (ken.getState()) {
			case status::neutral:	ken.setHP(ken.getHP() - skills[ryu.getSkill1()]->getDmg()); break;
			case status::attacking:	ken.setHP(ken.getHP() - skills[ryu.getSkill1()]->getDmg()); break;
			case status::grabbing:	ken.setHP(ken.getHP() - skills[ryu.getSkill1()]->getDmg()); break;
			case status::stun:		ken.setHP(ken.getHP() - skills[ryu.getSkill1()]->getDmg()); break;
			case status::blocking:	ken.setHP(ken.getHP() - (skills[ryu.getSkill1()]->getDmg() / 2)); break;
		}
		ryu.setEX(ryu.getEX() + skills[ryu.getSkill1()]->getExGain());
	}
	else {
		switch (ken.getState()) {
		case status::neutral:	ken.setHP(ken.getHP() - skills[ryu.getSkill2()]->getDmg()); break;
		case status::attacking:	ken.setHP(ken.getHP() - skills[ryu.getSkill2()]->getDmg()); break;
		case status::grabbing:	ken.setHP(ken.getHP() - skills[ryu.getSkill2()]->getDmg()); break;
		case status::stun:		ken.setHP(ken.getHP() - skills[ryu.getSkill2()]->getDmg()); break;
		case status::blocking:	ken.setHP(ken.getHP() - (skills[ryu.getSkill2()]->getDmg() / 2)); break;
		}
		ryu.setEX(ryu.getEX() + skills[ryu.getSkill2()]->getExGain());
	}
}*/

int  Game::createFighter(){
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

int  Game::rosterSize(){
	int cnt = 0;
	for (int i = 0; i < S; i++) {
		if (roster[i]->getName() == "\0") break;
		cnt++;
	}
	return cnt;
}

void Game::printFightMenu(Fighter& ryu, Fighter& ken){
	system("cls");
	cout << "\n";
	ryu.updateLifebar();
	ken.updateLifebar();
	cout << ryu.getName() << "	Wins: " << ryu.getWins() << "				" << ken.getName() << "	  Wins: " << ken.getWins() << endl;
	cout << ryu.getLifebar() << "			" << ken.getLifebar() << endl;
	cout << "HP: " << ryu.getHP() << "					HP: " << ken.getHP() << endl;
	cout << "EX: " << ryu.getEX() << "					EX: " << ken.getEX() << endl;
}

void Game::printWinLoss(){
	for (int i = 0; i < S; i++) {
		if (roster[i]->getName() == "\0") break;
		cout << roster[i]->getName() << ":  Wins: " << roster[i]->getWins() << "  |  Losses: " << roster[i]->getLosses() << endl;
	}
	cout << "Press any key to continue" << endl;
	char temp = _getch();
	 
}

void Game::play(){
	int ryu = selectFighter();
	int ken = selectOp(ryu);
	fight(*roster[ryu], *roster[ken]);
	roster[ryu]->restoreFighter();
	roster[ken]->restoreFighter();
	cout << "Press P to continue playing or Q to quit" << endl;
	contGame = _getch();
}

void Game::addFighter() {
	string newName;
	int size = rosterSize();
	int choice = createFighter();
	cout << "\nName the new Fighter: ";
	cin >> newName;
	if (choice == 0) {
		Shoto* newFighter = new Shoto(newName);
		roster[size] = newFighter;
	}
	else if (choice == 1) {
		Rush* newFighter = new Rush(newName);
		roster[size] = newFighter;
	}
	else if (choice == 2) {
		Grappler* newFighter = new Grappler(newName);
		roster[size] = newFighter;
	}
}

int Game::chooseAction(Fighter& ryu) {
	if (ryu.getState() == status::wait) {
		cout << ryu.getName() << "needs to wait for next action" << endl;
		ryu.setState(status::neutral);
		return 0;
	}
	cout << "\n\nChoose action: " << endl;
	cout << "1: Punch\n2: Block\n3: Grab\n4: " << skills[ryu.getSkill1()]->getName() << "\n5: " << skills[ryu.getSkill2()]->getName() << endl;
	if (ryu.getEX() == 10) cout << "6: EX Attack" << endl;
	int choice;
	cin >> choice;
	return choice;
}