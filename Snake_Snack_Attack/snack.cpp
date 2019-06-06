

#include "stdafx.h"
#include "snack.h"
#include <random>

void snack::update_position_randomly(level &lvl){	

	while (true){

		pos.y = r_between(0,lvl.map.size()-1);
		pos.x = r_between(0,lvl.map.size()-1); 		

		if (lvl.map.at(pos.y).at(pos.x) == level::tileFloor){
			break;
		}
	}		
}

unsigned int snack::r_between(const unsigned int min, const unsigned int max){
	
	std::random_device randomSeed;
	std::mt19937 generator(randomSeed());

	std::uniform_int_distribution<unsigned int> const distribution(min, max); 
	return distribution(generator);
}
