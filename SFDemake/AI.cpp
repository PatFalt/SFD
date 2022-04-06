#include "AI.h"

int AI::aggro(Fighter& ryu){
	if (ryu.getEX() == 10) return 6;
	
	return 1;
}
