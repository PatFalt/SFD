#pragma once
#include "Fighter.h"
#include "Skill.h"
#include "Game.h"

using namespace std;

int main() {
	srand(time(NULL));
	fightTest();
	titleScreen();
	Fighter* roster[S];
	Shoto* ryu = new Shoto(0);
	Shoto* ken = new Shoto(1);
	for (int i = 0; i < S; i++) {
		roster[i] = new Fighter();
	}
	roster[0] = ryu;
	roster[1] = ken;
	char contGame = '\0';
	while (contGame != 'q') {
		int mode = selectMode();
		if (mode == 0) {
			//PVE
			int ryu = selectFighter(roster);
			int ken = selectOp(roster, ryu);
			fight(*roster[ryu], *roster[ken]);
			cout << "Press P to continue playing or Q to quit" << endl;
			contGame = _getch();
		}
		if (mode == 1) {
			//PVP
			int choice = selectFighter(roster);
		}
		if (mode == 2) {
			//Tag-Team
			int choice = selectFighter(roster);
		}
		if (mode == 3) {
			string newName;
			int size = rosterSize(roster);
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
			system("cls");
			continue;
		}
	}
	ryu->skilly();
	delete ryu;
	delete ken;
	for (int i = S-1; i >= 0; i--) {
		delete roster[i];
	}
	return 0; 
}
