#ifndef GAME_H
#define GAME_H 

#include <vector>
#include <iostream> 
#include "room.h"

using namespace std;

//Game interface 
class Game
{
private:
	

	int length_input; 			//length of the board
	int width_input;  			//width of the board
	int num_arrows; 		//keep track of number of errors remaining
	bool debug_view;		//debug mode or not
	vector<vector<Room>> grid;
	Room room;
	int row_idx_user;
	int col_idx_user;
	int row_idx;
	int col_idx;
	int wumpus_row;
	int wumpus_col;
	bool win;
	int gold_row;
	int gold_col;
	bool hasgold;
	int rope_row;
	int rope_col;
	int back_bats;
	bool death;


public:

	
	Game();
	
	bool check_player_room_event(int event_type) const;

	void set_up(int, int);
	void insert_event(Event* event);

	void place_adventurer();


	void display_game(int, int, char, char);

	bool check_win() const;

	char get_dir();
	void wumpus_move();
	void fire_arrow();

	void move_up();
	void move_down();
	void move_left();
	void move_right();
	void move(char);

	char get_input();

	void play_game(int, int, char, char);

	void arrow_up();
	void arrow_down();
	void arrow_left();
	void arrow_right();
	void percept_wumpus();
	void percept_gold();
	void percept_bats();
	void percept_stalactites();

};
#endif