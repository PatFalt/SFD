#pragma once
#ifndef SKILL_H
#define SKILL_H
#include <string>

using namespace std;

class Skill{
	public:
		Skill();
	private:
		string name;
		int id;
		int damage;
		int exGain;
};

#endif