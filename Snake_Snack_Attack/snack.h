#pragma once

#include "level.h"

class scr; 
class snake; 
class level; 

class snack{

public:

	y_x pos {}; 		

	static const char tileSnack {'@'}; 	

	snack() = default;

	void update_position_randomly(level &lvl); 	

	static unsigned int r_between(unsigned int min, unsigned int max); 
		
};