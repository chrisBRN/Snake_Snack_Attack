#pragma once

#include "level.h"
#include "snake.h"
#include "snack.h"

#include "dir_and_coordinates.h"

class game{

public:

	bool isRunning; 	
	int score;

	game() noexcept;
	
	void run_game(); 	

private:	
	
	level	lv; 
	snake	snake; 
	snack	snack; 

	//TODO replace these with an enum 
	static const unsigned int blue	{1};
	static const unsigned int green	{2};	
	static const unsigned int red	{4};
	static const unsigned int white	{15};
	
	bool isPaused;

	static void pre_titles_set_up();
	
	void pause_game(); 	
	void game_over(); 
	void player_input();
	static void speed_clamp(); 		

	//TODO move these into console functions
	void title_screen() const; 
		
	void draw_level_to_console(); 	
	void draw_score_display_to_console() const; 
	void draw_game_over_screen() const; 
	void draw_pause_screen() const;
	void draw_instructions() const;

	void cout_empty_row() const;
	void cout_filled_end_row() const ;
	void cout_hollow_mid_row(std::string str = " ", char edge = level::tileWall) const; 	
			
	void set_console_colours(const y_x &pos); 		
};