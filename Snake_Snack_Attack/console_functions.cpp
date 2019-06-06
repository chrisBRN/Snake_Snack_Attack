#include "stdafx.h"
#include "console_functions.h"

void set_title_bar() noexcept {
	SetConsoleTitle(TEXT("Snake Snack Attack"));
}

void set_console_window_size() noexcept {

	//included to prevent console opening in a "too small" state causing banding issues
	//takes no account of user specific default console behavior i.e. font size 
	//whilst this is not a complete fix it should prevent the majority of problems

	const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	SMALL_RECT rect;
	rect.Top = 0;
	rect.Left = 0;
	rect.Bottom = 40;
	rect.Right = 40;	

	SetConsoleWindowInfo(handle, 1, &rect);	
}

void hide_console_input() noexcept {

	const HANDLE	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	//hide cursor	
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &info);

	//hide input
	const HANDLE handleStdIn = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(handleStdIn, &mode);
	SetConsoleMode(handleStdIn, mode & ~ENABLE_ECHO_INPUT);
	SetConsoleMode(handleStdIn, mode);
}

void clear_console(){

	// below code is an edit of code found here: https://stackoverflow.com/a/34843392 	

	// Flood-fill the console with spaces to clear it
	const CONSOLE_SCREEN_BUFFER_INFO csbi {};
	std::cout.flush();

	const HANDLE	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	const DWORD length = csbi.dwSize.X * csbi.dwSize.Y; 	
	DWORD written {};
	FillConsoleOutputCharacter(hOut, TEXT(' '), length, {0,0}, &written);

	//reset cursor position
	set_cursor_position(0,0); 
}

void set_cursor_position(const short int y, const short int x) noexcept {	
	
	const HANDLE	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//col major
	SetConsoleCursorPosition(hOut, {x,y}); 
} 

void set_colour(const int colour) noexcept { 	
	const HANDLE	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, colour); 
}