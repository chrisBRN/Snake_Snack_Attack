#pragma once

#include "stdafx.h"

class scr; 
class snake; 
class snack; 

class level{

public:

	level() = default;

	static const size_t			levelSize		{25}; 	 
	static const unsigned int	levelCenter		{levelSize/2}; 

	static const char			tileFloor		{'.'}; 
	static const char			tileWall		{'/'}; 

	std::vector<std::vector<char>> map{levelSize, std::vector<char>(levelSize,tileFloor)}; 		

	void map_update(snake &snake, snack &snack);
	void add_map_perimeter_walls();
	static bool check_if_snack_is_eaten(snake snake, snack snack); 
	
};



