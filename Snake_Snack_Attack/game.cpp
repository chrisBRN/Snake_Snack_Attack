#include "stdafx.h"
#include "game.h"
#include "console_functions.h"

game::game() noexcept {
	score = 0;
	isRunning = true;
	isPaused = false;
}

void game::run_game() {	
			
	pre_titles_set_up(); 
	title_screen(); 	

	lv.add_map_perimeter_walls();
	snack.update_position_randomly(lv);
	
	while (snake.alive) {				

		player_input();			
		lv.map_update(snake, snack);

		draw_level_to_console(); 
		draw_score_display_to_console(); 	
		draw_instructions(); 

		score = snake.length - snake.initLen;

		speed_clamp();
		std::cout.flush();
	}	
	game_over(); 		
}

void game::pre_titles_set_up(){

	// console specific setup
	set_title_bar();
	set_console_window_size(); 	
	hide_console_input(); 
	clear_console(); 		
}

void game::title_screen() const {	

	set_colour(white);

	while (true){			

		set_cursor_position(0,0); 		

		cout_filled_end_row(); 
		for (int i = 1; i < 10; ++i){cout_hollow_mid_row();} 
		cout_hollow_mid_row("SNAKE"); 
		cout_hollow_mid_row(); 
		cout_hollow_mid_row("SNACK"); 
		cout_hollow_mid_row(); 
		cout_hollow_mid_row("A");
		cout_hollow_mid_row("T");
		cout_hollow_mid_row("T");
		cout_hollow_mid_row("A");
		cout_hollow_mid_row("C");
		cout_hollow_mid_row("K");
		for (int i = 1; i < 5; ++i){cout_hollow_mid_row();} 
		cout_filled_end_row(); 
		cout_empty_row(); 	
		cout_hollow_mid_row("PRESS ENTER TO PLAY", ' '); 	
		
		if (GetAsyncKeyState(VK_RETURN)) {
			clear_console(); 
			break;
		}		
	}	
}

void game::game_over(){		

	while (true){			

		draw_game_over_screen(); 

		// destroys this game object and creates a new ones via main.cpp
		if (GetAsyncKeyState(VK_RETURN)) {break;}		
		// exits the program via main.cpp
		if (GetAsyncKeyState(VK_ESCAPE)) {isRunning = false; break;}		
	}		
	clear_console(); 
}

void game::pause_game(){		

	while(isPaused){	

		draw_pause_screen(); 			
		speed_clamp(); 		
		if (GetAsyncKeyState(VK_SPACE)){isPaused = false;}
	}
}

void game::speed_clamp(){	

	//controls the snake speed by pausing the core loop briefly
	const int speed {(1000/13)}; 
	std::this_thread::sleep_for(std::chrono::milliseconds(speed));	
}

void game::player_input() {	

	//takes player input via wasd or arrow keys and converts into direction changes		

	bool up{false}, right{false}, down{false}, left{false};

	if (GetAsyncKeyState(VK_UP)	  || GetAsyncKeyState('W'))	{up = true;}
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))	{down = true;}
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))	{left = true;}
	if (GetAsyncKeyState(VK_RIGHT)|| GetAsyncKeyState('D'))	{right = true;}	

	//prevents 'double backing' i,e. direct opposite movement killing player via collision 	
	switch(snake.direction){	
		case dir::up:		down	= false; break; 
		case dir::down: 	up		= false; break; 
		case dir::left:		right	= false; break; 
		case dir::right:	left	= false; break;  
		case dir::none:		break; 		
	}

	if (up)		{snake.direction = dir::up;}
	if (down)	{snake.direction = dir::down;}
	if (left)	{snake.direction = dir::left;}
	if (right)	{snake.direction = dir::right;}

	snake.update_position(); 

	if (GetAsyncKeyState(VK_ESCAPE)	){snake.alive = false;}
	if (GetAsyncKeyState(VK_SPACE)	){isPaused = true;}

	if (isPaused){pause_game();} 
}

void game::draw_level_to_console(){
	
	//loops up to level size printing level map to screen
	for (unsigned int row = 0; row < lv.map.size(); ++row){
		for (unsigned int col = 0; col < lv.map.size(); ++col){		

			const y_x coord {row,col}; 

			set_cursor_position(row,col); 
			set_console_colours(coord); 
			std::cout << lv.map.at(row).at(col); 			
		}
		std::cout << std::endl;
	}		
}

void game::draw_score_display_to_console() const{
	
	//allows for different length strings when score changes from 9 to 10 or 99 to 100
	std::string evenOffset {""}; 

	if (std::to_string(score).length() % 2 == 0){evenOffset = " ";}

	const std::string scoreString	{"SCORE @ : " + std::to_string(score) + evenOffset}; 

	cout_empty_row(); 		
	cout_filled_end_row(); 	
	cout_hollow_mid_row(); 		
	cout_hollow_mid_row(scoreString); 
	cout_hollow_mid_row();  
	cout_filled_end_row(); 
}

void game::draw_game_over_screen() const {

	set_colour(red);

	set_cursor_position(0,0); 

	cout_filled_end_row(); 
	for (unsigned int i = 1; i < lv.map.size()/3-1; ++i){cout_hollow_mid_row();} 
	cout_hollow_mid_row("GAME OVER"); 
	cout_hollow_mid_row(); 
	cout_hollow_mid_row(); 
	cout_hollow_mid_row("PRESS ENTER"); 
	cout_hollow_mid_row(); 
	cout_hollow_mid_row("TO PLAY AGAIN"); 
	cout_hollow_mid_row(); 
	cout_hollow_mid_row(); 
	cout_hollow_mid_row("OR ESCAPE"); 
	cout_hollow_mid_row(); 
	cout_hollow_mid_row("TO QUIT"); 		
	for (unsigned int i = 1; i < lv.map.size()/3-1; ++i){cout_hollow_mid_row();} 
	cout_filled_end_row(); 

	draw_score_display_to_console(); 

	for (unsigned int i = 1; i <= 6; ++i){cout_empty_row();}	

	std::cout.flush();
}

void game::draw_pause_screen() const {

	set_cursor_position(0,0); 

	set_colour(white);

	cout_filled_end_row(); 
	for (unsigned int i = 1; i < lv.map.size()/2-2; ++i){cout_hollow_mid_row();} 
	cout_hollow_mid_row("GAME PAUSED"); 
	cout_hollow_mid_row(); 
	cout_hollow_mid_row("PRESS SPACE"); 
	cout_hollow_mid_row(); 
	cout_hollow_mid_row("TO RESUME"); 
	for (unsigned int i = 1; i < lv.map.size()/2-2; ++i){cout_hollow_mid_row();} 
	cout_filled_end_row(); 

	draw_score_display_to_console(); 

	for (unsigned int i = 1; i <= 6; ++i){cout_empty_row();}

	std::cout.flush();
}

void game::draw_instructions() const {
	
	std::cout << std::endl; 
	cout_hollow_mid_row("ARROW KEYS TO MOVE", ' '); 
	std::cout << std::endl; 
	cout_hollow_mid_row("SPACE TO PAUSE", ' '); 
	std::cout << std::endl; 
	cout_hollow_mid_row("ESCAPE TO QUIT", ' '); 
}

void game::set_console_colours(const y_x &pos){

	if (lv.map.at(pos.y).at(pos.x) == snake.head)				{set_colour(green);}
	else if (lv.map.at(pos.y).at(pos.x) == snake.bodyN)		{set_colour(green);}
	else if (lv.map.at(pos.y).at(pos.x) == snake.bodyA)		{set_colour(green);}
	else if (lv.map.at(pos.y).at(pos.x) == snake.bodyK)		{set_colour(green);}
	else if (lv.map.at(pos.y).at(pos.x) == snake.tail)			{set_colour(green);}
	else if (lv.map.at(pos.y).at(pos.x) == level::tileFloor)		{set_colour(blue);}
	else														{set_colour(white);}												
}

void game::cout_empty_row() const {

	for (unsigned int i = 0; i < lv.map.size(); ++i){
		std::cout << " "; 	
	}
	std::cout << std::endl;
}

void game::cout_filled_end_row() const{

	for (unsigned int i = 0; i < lv.map.size(); ++i){
		std::cout << level::tileWall;
	}
	std::cout << std::endl;
}

void game::cout_hollow_mid_row(std::string str, const char edge) const{	

	const unsigned int cen {(1 + (lv.map.size() - 1)/2)}; 

	const unsigned int offset {(2 + (str.length() - 1)/2)}; 

	std::cout << edge;
	for (unsigned int i = 1; i <= cen - offset; ++i){std::cout << " "; }
	std::cout << str; //if blank " "
	for (unsigned int i = 1; i <= cen - offset; ++i){std::cout << " "; }
	std::cout << edge;

	std::cout << std::endl; 
}