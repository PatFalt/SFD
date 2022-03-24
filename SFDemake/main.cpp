#include <iostream>
#include <assert.h>
#include <time.h>
#include <conio.h>
#include "Fighter.h"

using namespace std;

int main() {
	char input = 'a';
	while(input != 'p') {
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
	input = 'a';
	Fighter* ryu = new Shoto("Ryu"); //placeholder P1
	Fighter* ken = new Shoto("Ken"); //placeholder P2
	int count = 0;
	while(input != 'p') {
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
	}
	delete ryu;
	delete ken;
	//system("cls");
	return 0; 
}
