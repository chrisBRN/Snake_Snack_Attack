//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                    
//	SNAKE SNACK ATTACK
//
//	A WINDOWS SNAKE GAME WRITTEN IN C++ BY ChrisBRN 
//
//////////////////////////////////////////////////////////////////////////////////////////////

//	Exciting feature list;
//	
//	* a simple snake game
//	* score display
//	* title, game over and pause screens
//	* wasd & arrow key control
//	* 3 colours! 

//The below list represents changes that could be made to further improve the game 

//TODO 1.a.		snack::r_between() generates a new random seed on every call - rewrite
//TODO 1.b.		game::speed_clamp() does not take system differences into account - rewrite				

//TODO 2.a.		Remove the need for windows specific headers/libraries i.e make code portable

//TODO 3.a.		Implement a graphics library (i.e. SFML)
//				* reduces/removes most or all console specific code 
//				* resolve issues caused by used of pseudo graphics (fonts) i.e. height/width//				
//TODO 3.b.		Move all 'draw' functions out of game class into dedicated class/file

//TODO 4.a.		Include a 'win state'
//TODO 4.b.		Add music & FX
//TODO 4.c.		Add high score mechanism (saved between games)

#include "stdafx.h"
#include "game.h"

int main(){

	while (true){

		game game; 	

		game.run_game(); 	
		
		if (game.isRunning == false){break;}
	}	

	return 0;
}