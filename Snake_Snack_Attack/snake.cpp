
#include "stdafx.h"
#include "snake.h"
#include "level.h"

snake::snake() {
	
	headPos.y	=	level::levelCenter; 
	headPos.x	=	level::levelCenter;  
	direction	=	{dir::up}; 	
	pos			=	{headPos}; 
	
	const unsigned int sizedif {initLen - pos.size()}; 
	
	for (unsigned int i = 1; i <= sizedif; ++i){	
		
		pos.push_back(headPos);		

		pos.at(i).y = level::levelCenter+i;
		pos.at(i).x	= level::levelCenter;
		
		++length; 	
	}
}

void snake::update_position(){	
	
	//updates position based on direction

	oldPos = pos;	

	switch(direction){

		case dir::up:		pos.at(0).y--; break; 
		case dir::right:	pos.at(0).x++; break; 
		case dir::down:		pos.at(0).y++; break; 
		case dir::left:		pos.at(0).x--; break;
		case dir::none: break; 
	}	

	//updates all non-head snake parts positions
	for (unsigned int i = 1; i < pos.size(); ++i){		
		pos.at(i).y = oldPos.at(i-1).y;
		pos.at(i).x = oldPos.at(i-1).x;
	}

	if (check_collision()){alive = false;}
}

bool snake::check_collision(){

	bool isColliding {false}; 

	//check for self collision
	for (unsigned int i = 1; i < pos.size(); ++i ){

		if (pos.at(0).y == pos.at(i).y && 
			pos.at(0).x == pos.at(i).x ){
			
			isColliding = true;
		}
	}

	//check for boundary collision
	if (pos.at(0).y >= level::levelSize-1 || pos.at(0).y <= 1 || 
		pos.at(0).x >= level::levelSize-1 || pos.at(0).x <= 1 ){
		
		isColliding = true; 	
	}

	return isColliding; 
}

void snake::grow_snake(){
	length++; 		
	pos.push_back(pos.back()); 	
}