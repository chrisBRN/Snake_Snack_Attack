#pragma once

#include "stdafx.h"

class scr; 
class level; 
class snack; 

class snake{

public:

	static const char head		{'S'}; 
	static const char bodyN		{'N'};
	static const char bodyA		{'A'}; 
	static const char bodyK		{'K'}; 
	static const char tail		{'E'};
			
	y_x headPos{}; dir direction{}; int length{1}; bool alive{true};

	static const unsigned initLen {5}; 

	std::vector<y_x> pos{};
	std::vector<y_x> oldPos{};
	
	snake(); 

	void update_position(); 	
	bool check_collision();
	void grow_snake(); 
};