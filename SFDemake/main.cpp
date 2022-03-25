#include <iostream>
#include <assert.h>
#include <time.h>
#include <conio.h>
#include "Fighter.h"
#include "Game.h"

using namespace std;

int main() {
	fightTest();
	titleScreen();
	//char input = 'a';
	//Fighter* ryu = new Shoto(0); //placeholder P1
	//Fighter* ken = new Shoto(1); //placeholder P2
	Fighter roster[S];
	Shoto ryu(0);
	Shoto ken(1);
	/*for (int i = 0; i < 2; i++) {
		roster[i].setName(ryu->getName());
		roster[i].setEX(ryu->getEX());
		roster[i].setWins(ryu->getWins());
		roster[i].setHP(ryu->getHP());
		ryu = ken;
	}*/
	roster[0] = ryu;
	roster[1] = ken;
	int count = 0;
	cout << roster[0].getName() << ", " << roster[1].getName() << endl;
	selectFighter(roster);
	ryu.skilly();
	/*while (input != 'p') {
		system("cls");
		cout << "\nChoose a Fighter:\nPress P to confirm your choice\n" << endl;
		(count == 0) ? cout << "-->" << " " << ryu->getName() << endl : cout << ryu->getName() << endl;
		(count == 1) ? cout << "-->" << " " << ken->getName() << endl : cout << ken->getName() << endl;
		(count == 2) ? cout << "-->" << " " << "Create new Fighter" << endl : cout << "Create new Fighter" << endl;
		input = _getch();
		switch (input) {
			case 's':	count++; count %= 3; break;
			case 'w':	count--; (count < 0) ? count = 2 : count %= 3; break;
		}
	}
	switch (count) {
		case 0: cout << "\nYou chose " << ryu->getName() << endl; break;
		case 1: cout << "\nYou chose " << ken->getName() << endl; break;
		case 2: cout << "\nYou chose to create a new Fighter" << endl; break;
		default: break;
	}*/
	//delete ryu;
	//delete[] roster;
	//delete ken; //crash
	//delete roster; crash
	//system("cls");
	return 0; 
}
