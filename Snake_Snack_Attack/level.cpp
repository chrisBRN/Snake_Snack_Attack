#include "stdafx.h"
#include "level.h"
#include "snake.h"
#include "snack.h"

void level::add_map_perimeter_walls() {
	
	for (unsigned int i = 0; i < map.size(); ++i){

		map.at(0).at(i) = tileWall;				//top tileWall
		map.at(i).at(levelSize-1) = tileWall;	//right tileWall
		map.at(levelSize-1).at(i) = tileWall;	//bottom tileWall
		map.at(i).at(0) = tileWall;				//left tileWall		
	}
}

bool level::check_if_snack_is_eaten(snake const snake, snack const snack){

	bool isSnackEaten{false};

	if (snake.pos.at(0).y == snack.pos.y && 
		snake.pos.at(0).x == snack.pos.x ){

		isSnackEaten = true; 
	}

	return isSnackEaten;	
}

void level::map_update(snake &snake, snack &snack){
		
	//update snake position on level map
	for (unsigned int i = 0; i < snake.pos.size(); ++i){	
		
		switch(i){			
			case 0:	 map.at(snake.pos.at(i).y).at(snake.pos.at(i).x) = snake.head; break; 
			case 1:	 map.at(snake.pos.at(i).y).at(snake.pos.at(i).x) = snake.bodyN; break;
			case 2:	 map.at(snake.pos.at(i).y).at(snake.pos.at(i).x) = snake.bodyA; break;
			case 3:	 map.at(snake.pos.at(i).y).at(snake.pos.at(i).x) = snake.bodyK; break;
			default: map.at(snake.pos.at(i).y).at(snake.pos.at(i).x) = snake.tail; break; 	
		}					
	}

	//clear out old snake end position
	map.at(snake.oldPos.back().y).at(snake.oldPos.back().x)  = tileFloor; 	
	
	if (check_if_snack_is_eaten(snake, snack)) {

		snake.grow_snake();
		snack.update_position_randomly(*this);			
	}

	//update snack position on level map 
	map.at(snack.pos.y).at(snack.pos.x) = snack.tileSnack;	
}