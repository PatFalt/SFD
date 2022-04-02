#include "Game.h"

using namespace std;

Game::Game(){
	srand(time(NULL));
	for (int i = 0; i < 5; i++) {
		skills[i] = new ShotoSkill(i);
		skills[i + 5] = new GrappleSkill(i + 5);
		skills[i + 10] = new RushSkill(i + 10);
	}
	Shoto* ryu = new Shoto(0);
	Shoto* ken = new Shoto(1);
	Grappler* gief = new Grappler(0);
	Grappler* mika = new Grappler(1);
	Rush* cammy = new Rush(0);
	Rush* karin = new Rush(1);
	for (int i = 0; i < S; i++) {
		roster[i] = new Fighter();
	}
	for (int i = 0; i < 2; i++) {
		team1[i] = new Fighter();
		team2[i] = new Fighter();
	}
	roster[0] = ryu;
	roster[1] = ken;
	roster[2] = gief;
	roster[3] = mika;
	roster[4] = cammy;
	roster[5] = karin;
	int p1 = 0;
	titleScreen();
	do {
		selectMode();
		switch (mode) {
			case 0:	play(); break;//PVE
			case 1: play(); break;//PVP
			case 2: play(); break;//CVC
			case 3: play(); break;//Tag-Team
			case 4: addFighter(); break;
			case 5: printWinLoss(); break;
		}
	} while (contGame != 'q');
}

Game::~Game(){
	std::cout << "Finished" << endl;
}

void Game::titleScreen(){
	char input = 'a';
	while (input != 'p') {
		system("cls");
		std::cout << "\n\n\n";
		std::cout << "	 _____ _                 _    ______ _       _     _             ______                     _        " << endl;
		std::cout << "	/  ___| |               | |   |  ___(_)     | |   | |            |  _  \\                   | |       " << endl;
		std::cout << "	\\ `--.| |_ _ __ ___  ___| |_  | |_   _  __ _| |__ | |_ ___ _ __  | | | |___ _ __ ___   __ _| | _____ " << endl;
		std::cout << "	 `--. \\ __| '__/ _ \\/ _ \\ __| |  _| | |/ _` | '_ \\| __/ _ \\ '__| | | | / _ \\ '_ ` _ \\ / _` | |/ / _ \\" << endl;
		std::cout << "	/\\__/ / |_| | |  __/  __/ |_  | |   | | (_| | | | | ||  __/ |    | |/ /  __/ | | | | | (_| |   <  __/" << endl;
		std::cout << "	\\____/ \\__|_|  \\___|\\___|\\__| \\_|   |_|\\__, |_| |_|\\__\\___|_|    |___/ \\___|_| |_| |_|\\__,_|_|\\_\\___|" << endl;
		std::cout << "	                                        __/ |                                                        " << endl;
		std::cout << "	                                       |___/                                                         " << endl;
		std::cout << "\n\n	                                         Press P to continue" << endl;
		input = _getch();
	}
}

void Game::selectMode(){
	char input = 'a';
	int count = 0;
	while (input != 'p') {
		system("cls");
		std::cout << "\nSelect Mode:\nPress P to confirm your choice\n" << endl;
		(count == 0) ? std::cout << "--> Singleplayer" << endl : std::cout << "Singleplayer" << endl;
		(count == 1) ? std::cout << "--> Multiplayer" << endl : std::cout << "Multiplayer" << endl;
		(count == 2) ? std::cout << "--> CPU vs CPU" << endl : std::cout << "CPU vs CPU" << endl;
		(count == 3) ? std::cout << "--> Tag-Team" << endl : std::cout << "Tag-Team" << endl;
		(count == 4) ? std::cout << "--> Create Fighter" << endl : std::cout << "Create Fighter" << endl;
		(count == 5) ? std::cout << "--> Show Wins and Losses" << endl : std::cout << "Show Wins and Losses" << endl;
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
		std::cout << "\nChoose a Fighter:\nPress P to confirm your choice\n" << endl;
		for (int i = 0; i < S; i++) {
			if (roster[i]->getName() == "\0") break;
			(count == temp) ? std::cout << "-->" << " " << roster[i]->getName() << endl : std::cout << roster[i]->getName() << endl;
			temp++;
		}
		input = _getch();
		switch (input) {
			case 's':	count++; count %= temp; break;
			case 'w':	count--; (count < 0) ? count = temp-1 : count %= temp; break;
		}
	}
	std::cout << "\nYou chose " << roster[count]->getName() << endl; return count;
}

int  Game::createFighter() {
	char input = 'a';
	int count = 0;
	while (input != 'p') {
		system("cls");
		std::cout << "\nSelect Archetype:\nPress P to confirm your choice\n" << endl;
		(count == 0) ? std::cout << "--> Shoto" << endl : std::cout << "Shoto" << endl;
		(count == 1) ? std::cout << "--> Rushdown" << endl : std::cout << "Rushdown" << endl;
		(count == 2) ? std::cout << "--> Grappler" << endl : std::cout << "Grappler" << endl;
		input = _getch();
		switch (input) {
		case 's':	count++; count %= 3; break;
		case 'w':	count--; (count < 0) ? count = 2 : count %= 3; break;
		}
	}
	switch (count) {
	case 0: std::cout << "\nYou chose to create a Shoto" << endl; return 0;
	case 1: std::cout << "\nYou chose to create a Rushdown Fighter" << endl; return 1;
	case 2: std::cout << "\nYou chose to create a Grappler" << endl; return 2;
	default: break;
	}
	return 3;
}

void Game::fillTeam(){
	char input = 'a';
	int count = 0;
	int block = -1;
	int i = 0;
	char a = 'a';
	while (true) {
		int temp = 0;
		system("cls");
		std::cout << "\nChoose Team 1 member:\nPress P to confirm your choice\n" << endl;
		for (int i = 0; i < S; i++) {
			if (roster[i]->getName() == "\0") break;
			(count == temp) ? std::cout << "-->" << " " << roster[i]->getName() << endl : std::cout << roster[i]->getName() << endl;
			temp++;
		}
		std::cout << "\n\nTeam 1: " << team1[0]->getName() << " " << team1[1]->getName() << endl;
		std::cout << "\nTeam 2: " << team2[0]->getName() << " " << team2[1]->getName() << endl;
		input = _getch();
		switch (input) {
			case 's':	count++; count %= temp; break;
			case 'w':	count--; (count < 0) ? count = temp - 1 : count %= temp; break;
			case 'p':	if (count == block) {
						std::cout << "Fighter already chosen! Press any key to continue" << endl;
							input = 'a';
							a = _getch();
							break;
						}
						team1[i] = roster[count]; i++;
						block = count;
						break;
		}
		if (i == 2) break;
	}
	i = 0;
	while (true) {
		int temp = 0;
		system("cls");
		std::cout << "\nChoose Team 2 member:\nPress P to confirm your choice\n" << endl;
		for (int i = 0; i < S; i++) {
			if (roster[i]->getName() == "\0") break;
			(count == temp) ? std::cout << "-->" << " " << roster[i]->getName() << endl : std::cout << roster[i]->getName() << endl;
			temp++;
		}
		std::cout << "\n\nTeam 1: " << team1[0]->getName() << " " << team1[1]->getName() << endl;
		std::cout << "\nTeam 2: " << team2[0]->getName() << " " << team2[1]->getName() << endl;
		input = _getch();
		switch (input) {
			case 's':	count++; count %= temp; break;
			case 'w':	count--; (count < 0) ? count = temp - 1 : count %= temp; break;
			case 'p':	if (count == block) {
						std::cout << "Fighter already chosen! Press any key to continue" << endl;
						input = 'a';
						a = _getch();
						break;
						}
						team2[i] = roster[count]; i++;
						block = count;
						break;
		}
		if (i == 2) break;
	}
	system("cls");
	std::cout << "\n\nTeam 1: " << team1[0]->getName() << " " << team1[1]->getName() << endl;
	std::cout << "\nTeam 2: " << team2[0]->getName() << " " << team2[1]->getName() << endl;
	std::cout << "\nPress any key to continue: " << endl; 
	input = _getch();
	return;
}

int  Game::selectOp(int block){
	char input = 'a';
	int count = 0;
	char temp = 'a';
	do{
		int temp = 0;
		system("cls");
		std::cout << "\nChoose an Opponent:\nPress P to confirm your choice\n" << endl;
		for (int i = 0; i < S; i++) {
			if (roster[i]->getName() == "\0") break;
			(count == temp) ? std::cout << "-->" << " " << roster[i]->getName() << endl : std::cout << roster[i]->getName() << endl;
			temp++;
		}
		input = _getch();
		switch (input) {
			case 's':	count++; count %= temp; break;
			case 'w':	count--; (count < 0) ? count = temp - 1 : count %= temp; break;
		}
		if (input == 'p' && count == block) {
			std::cout << "Fighter already chosen! Press any key to continue" << endl;
			input = 'a';
			temp = _getch();
		}
	} while (input != 'p');
	std::cout << "\nYou chose " << roster[count]->getName() << endl;
	return count;
}

void  Game::fightTest() {
	int i = 0;
	Shoto ryu(0);
	assert(ryu.getHP() == 200 && "ryu instanced with wrong hp");
	std::cout << "here 1" << endl;
	Shoto ken(1);
	assert(ken.getHP() == 200 && "ryu instanced with wrong hp");
	std::cout << "here 2" << endl;
	printFightMenu(ryu, ken);
	std::cout << "here print" << endl;
	ryu.punch(ken);
	assert(ryu.getState() == status::attacking && "State not changed");
	std::cout << "here 3" << endl;
	assert(ken.getHP() == 190 && "Damage incorrectly dealt");
	std::cout << "here 4" << endl;
	printFightMenu(ryu, ken);
	ryu.block();
	assert(ryu.getState() == status::blocking && "State not changed");
	std::cout << "here 5" << endl;
	ken.punch(ryu);
	assert(ken.getState() == status::attacking && "State not changed");
	std::cout << "here 6" << endl;
	assert(ryu.getHP() == 198 && "Damage incorrectly dealt");
	std::cout << "here 7" << endl;
	printFightMenu(ryu, ken);
	ryu.grab(ken);
	assert(ryu.getState() == status::grabbing && "State not changed");
	std::cout << "here 8" << endl;
	assert(ken.getHP() == 190 && "Damage incorrectly dealt");
	std::cout << "here 9" << endl;
	ken.block();
	assert(ken.getState() == status::blocking && "State not changed");
	std::cout << "here 10" << endl;
	ryu.grab(ken);
	assert(ryu.getState() == status::grabbing && "State not changed");
	std::cout << "here 11" << endl;
	assert(ken.getHP() == 170 && "Damage incorrectly dealt");
	std::cout << "here 12" << endl;
	printFightMenu(ryu, ken);
	ken.grab(ryu);
	assert(ryu.getState() == status::grabbing && "State not changed");
	std::cout << "here 13" << endl;
	assert(ryu.getHP() == 198 && "Damage incorrectly dealt");
	std::cout << "here 14" << endl;
}

void Game::play() {
	if (mode == 3) {
		fillTeam();
		tagTeamFight();
		team1[0]->restoreFighter();
		team1[1]->restoreFighter();
		team2[0]->restoreFighter();
		team2[1]->restoreFighter();
	}
	else {
		int ryu = selectFighter();
		int ken = selectOp(ryu);
		fight(*roster[ryu], *roster[ken]);
		roster[ryu]->restoreFighter();
		roster[ken]->restoreFighter();
	}
	std::cout << "Press P to continue playing or Q to quit" << endl;
	contGame = _getch();
}

void Game::fight(Fighter& ryu, Fighter& ken) { //FEHLER HIER
	char a;
	int turn = 0;
	while (true) {
		int action = 0;
		system("cls");
		printFightMenu(ryu, ken);
		if (ryu.getHP() > 0 && ken.getHP() <= 0) {
			std::cout << "\n" << ryu.getName() << " wins!" << endl;
			ryu.setWins();
			ken.setLosses();
			break;
		}
		if (ken.getHP() > 0 && ryu.getHP() <= 0) {
			std::cout << "\n" << ken.getName() << " wins!" << endl;
			ken.setWins();
			ryu.setLosses();
			break;
		}
		if (ken.getHP() <= 0 && ryu.getHP() <= 0) {
			std::cout << "Draw!" << endl;
			break;
		}
		resolveAction(ryu, ken);
		std::cout << "\nPress any key to continue" << endl;
		a = _getch();
		turn++;
	}
}

void Game::tagTeamFight() {
	char a;
	int turn = 0;
	while (true) {
		int action = 0;
		system("cls");
		printFightMenu(*team1[0], *team2[0]);
		if ((team1[0]->getHP() > 0 && team1[1]->getHP() > 0) && (team2[0]->getHP() <= 0 || team2[1]->getHP() <= 0)) {
			std::cout << "\nTeam 1 wins!" << endl;
			team1[0]->setWins();
			team1[1]->setWins();
			team2[0]->setLosses();
			team2[1]->setLosses();
			break;
		}
		if ((team2[0]->getHP() > 0 && team2[1]->getHP() > 0) && (team1[0]->getHP() <= 0 || team1[1]->getHP() <= 0)) {
			std::cout << "\nTeam 2 wins!" << endl;
			team2[0]->setWins();
			team2[1]->setWins();
			team1[0]->setLosses();
			team1[1]->setLosses();
			break;
		}
		if ((team1[0]->getHP() <= 0 || team1[1]->getHP() <= 0) && (team2[0]->getHP() <= 0 || team2[1]->getHP() <= 0)) {
			std::cout << "Draw!" << endl;
			break;
		}
		resolveAction(*team1[0], *team2[0]);
		std::cout << "\nPress any key to continue" << endl;
		a = _getch();
		turn++;
	}
}

void Game::tagOut() {
	Fighter* temp = NULL;
	if(tag == 0){
		temp = team1[0];
		team1[0] = team1[1];
		team1[1] = temp;
		cout << team1[0]->getName() << " switched places with " << team1[1]->getName() << endl;
	}
	else {
		temp = team2[0];
		team2[0] = team2[1];
		team2[1] = temp;
		cout << team2[0]->getName() << " switched places with " << team2[1]->getName() << endl;
	}
}

void Game::resolveAction(Fighter& ryu, Fighter& ken){
	int ryuAction = 0;
	int kenAction = 0;
	switch (mode) {
		case 0:	if (ken.getState() != status::wait) { kenAction = rand() % 5 + 1; }	
				ryuAction = chooseAction(ryu);
				break; 		
		case 1: ryuAction = chooseAction(ryu);
				kenAction = chooseAction(ken);
				break;
		case 2: if (ryu.getState() != status::wait) { ryuAction = rand() % 5 + 1; }
				if (ken.getState() != status::wait) { kenAction = rand() % 5 + 1; }
				break;
		case 3: if (ken.getState() != status::wait) { kenAction = rand() % 5 + 1; }
				ryuAction = chooseAction(ryu);
				break;
	}
	cout << ryuAction << " " << kenAction << endl;
	if (mode == 3) {
		if (ryuAction == 6) { 
			tag = 0; 
			doAction(ryu, ken, ryuAction);
		}
		if (kenAction == 6) {
			tag = 1;
			doAction(ken, ryu, kenAction);
		}
	}
	if (kenAction == 2) {
		doAction(ken, ryu, kenAction);
		doAction(ryu, ken, ryuAction);
	}
	else if (ryuAction == 2) {
		doAction(ryu, ken, ryuAction);
		doAction(ken, ryu, kenAction);
	}
	else if (ryuAction == 3 && kenAction != 3) {
		doAction(ken, ryu, kenAction);
		doAction(ryu, ken, ryuAction);
	}
	else if (ryu.getSpeed() >= ken.getSpeed()) {
		if (ryuAction == 3 && kenAction == 3) {
			std::cout << ken.getName() << " escaped the grab" << endl;
		}
		else {
			doAction(ryu, ken, ryuAction);
			doAction(ken, ryu, kenAction);
		}
	} 
	else {
		if (ryuAction == 3 && kenAction == 3) {
			std::cout << ken.getName() << " escaped the grab" << endl;
		}
		doAction(ken, ryu, kenAction);
		doAction(ryu, ken, ryuAction);
	}
	if(ryu.getState() != status::wait)
		ryu.setState(status::neutral);
	if (ryu.getState() != status::wait)
		ken.setState(status::neutral);
}

void Game::doAction(Fighter& ryu, Fighter& ken, int ryuAction){
	switch (ryuAction) {
		case 0: ryu.wait(); break;
		case 1:	ryu.punch(ken); break;
		case 2:	ryu.block(); break;
		case 3:	ryu.grab(ken); break;
		case 4:	ryu.useSkill(skills, 1, ken); break;
		case 5:	ryu.useSkill(skills, 2, ken); break;
		case 6:	if (mode == 3) { tagOut(); }
				else { ryu.exAttack(ken); }
				break;
		case 7: if (mode == 3) ryu.exAttack(ken); break;
	}
}

int Game::chooseAction(Fighter& ryu) {
	int choice;
	int target;
	if (ryu.getState() == status::wait) {
		//std::cout << ryu.getName() << " needs to wait for next action" << endl;
		return 0;
	}
	std::cout << "\n\nChoose action: " << endl;
	std::cout << "1: Punch\n2: Block\n3: Grab\n4: " << skills[ryu.getSkill1()]->getName() << "\n5: " << skills[ryu.getSkill2()]->getName() << endl;
	if (mode == 3) {
		std::cout << "6: Tag-Out" << endl;
		if (ryu.getEX() == 10) std::cout << "7: EX Attack" << endl;
	}
	if (ryu.getEX() == 10) std::cout << "6: EX Attack" << endl;
	cin >> choice;
	return choice;
}

void Game::addFighter() {
	string newName;
	int size = rosterSize();
	int choice = createFighter();
	std::cout << "\nName the new Fighter: ";
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

int  Game::rosterSize() {
	int cnt = 0;
	for (int i = 0; i < S; i++) {
		if (roster[i]->getName() == "\0") break;
		cnt++;
	}
	return cnt;
}

void Game::printFightMenu(Fighter& ryu, Fighter& ken) {
	system("cls");
	std::cout << "\n";
	if (mode == 3) {
		for (int i = 0; i < 2; i++) {
			team1[i]->updateLifebar();
			team2[i]->updateLifebar();
		}
		std::cout << team1[0]->getName() << "	      " << "				"<< team2[0]->getName() << endl;
		std::cout << team1[0]->getLifebar() << "			" << team2[0]->getLifebar() << "" << endl;
		std::cout << "HP: " << team1[0]->getHP() << "					HP: " << team2[0]->getHP() << endl;
		std::cout << "EX: " << team1[0]->getEX() << "					EX: " << team2[0]->getEX() << "\n" << endl;
		std::cout << team1[1]->getName() << "	      " << "				" << team2[1]->getName() << endl;
		std::cout << team1[1]->getLifebar() << "			" << team2[1]->getLifebar() << endl;
		std::cout << "HP: " << team1[1]->getHP() << "					HP: " << team2[1]->getHP() << endl;
		std::cout << "EX: " << team1[1]->getEX() << "					EX: " << team2[1]->getEX() << endl;
	}
	else {
		ryu.updateLifebar();
		ken.updateLifebar();
		std::cout << ryu.getName() << "	Wins: " << ryu.getWins() << "				" << ken.getName() << "	  Wins: " << ken.getWins() << endl;
		std::cout << ryu.getLifebar() << "			" << ken.getLifebar() << endl;
		std::cout << "HP: " << ryu.getHP() << "					HP: " << ken.getHP() << endl;
		std::cout << "EX: " << ryu.getEX() << "					EX: " << ken.getEX() << endl;
	}
}

void Game::printWinLoss() {
	for (int i = 0; i < S; i++) {
		if (roster[i]->getName() == "\0") break;
		std::cout << roster[i]->getName() << ":  Wins: " << roster[i]->getWins() << "  |  Losses: " << roster[i]->getLosses() << endl;
	}
	std::cout << "Press any key to continue" << endl;
	char temp = _getch();
}