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

int selectFighter(Fighter roster[S]){
	char input = 'a';
	int count = 0;
	while (input != 'p') {
		int temp = 0;
		system("cls");
		cout << "\nChoose a Fighter:\nPress P to confirm your choice\n" << endl;
		for (int i = 0; i < S; i++) {
			if (roster[i].getName() == "\0") break;
			(count == temp) ? cout << "-->" << " " << roster[i].getName() << endl : cout << roster[i].getName() << endl;
			temp++;
		}
		(count == temp) ? cout << "-->" << " " << "Create new Fighter" << endl : cout << "Create new Fighter" << endl;
		temp++;
		input = _getch();
		switch (input) {
		case 's':	count++; count %= temp; break;
		case 'w':	count--; (count < 0) ? count = temp-1 : count %= temp; break;
		}
	}
	switch (count) {
	case 0: cout << "\nYou chose " << roster[0].getName() << endl; return 0;
	case 1: cout << "\nYou chose " << roster[1].getName() << endl; return 1;
	case 2: cout << "\nYou chose to create a new Fighter" << endl; return 2;
	default: break;
	}
}

void fightTest() {
	Shoto ryu(0);
	assert(ryu.getHP() == 200 && "ryu instanced with wrong hp");
	Shoto ken(1);
	assert(ken.getHP() == 200 && "ryu instanced with wrong hp");
	ryu.punch(ken);
	assert(ryu.getState() == status::attacking && "State not changed");
	assert(ken.getHP() == 190 && "Damage incorrectly dealt");
	ryu.block();
	assert(ryu.getState() == status::blocking && "State not changed");
	ken.punch(ryu);
	assert(ken.getState() == status::attacking && "State not changed");
	assert(ryu.getHP() == 198 && "Damage incorrectly dealt");
	ryu.grab(ken);
	assert(ryu.getState() == status::grabbing && "State not changed");
	assert(ken.getHP() == 190 && "Damage incorrectly dealt");
	ken.block();
	assert(ken.getState() == status::blocking && "State not changed");
	ryu.grab(ken);
	assert(ryu.getState() == status::grabbing && "State not changed");
	assert(ken.getHP() == 170 && "Damage incorrectly dealt");
	ken.grab(ryu);
	assert(ryu.getState() == status::grabbing && "State not changed");
	assert(ryu.getHP() == 198 && "Damage incorrectly dealt");
}
