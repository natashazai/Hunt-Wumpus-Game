#include "game.h"
#include "gold.h"
#include "stalactites.h"
#include "bats.h"
#include "wumpus.h"

#include <iostream>

using namespace std;

/*********************************************************************
** Function: Game()
** Description: default constructor for game class
** Parameters: no
** Pre-Conditions: class bject created
** Post-Conditions: all private member variables of a class Game was
initialized
*********************************************************************/
Game::Game(){
	/*set all of the private member variables to null*/
	num_arrows = 3;
	width_input = 0;
	length_input = 0;
	row_idx_user = 0;
	col_idx_user = 0;
	row_idx = 0;
	col_idx = 0;
	wumpus_row = 0;
	wumpus_col = 0;
	gold_row =0;
	gold_col =0;
	rope_row =0;
	rope_col =0;
	vector<vector<Room>> grid;
	debug_view = true;
	win = false;
	hasgold = false;
	back_bats = 0;
	death = false;
}


bool Game::check_player_room_event(int event_type) const {
    const Room& current_room = grid.at(row_idx_user).at(col_idx_user);
    return current_room.has_event_type(event_type);
}

/*********************************************************************
** Function:set_up()
** Description: resizes the grid witht he given input from the user
and inserting the events on a random positions in 2D vector array
** Parameters: int, int
** Pre-Conditions: user input for the size of the grid
** Post-Conditions:grid was created with desired sze and all events
was inserted
*********************************************************************/
void Game::set_up(int width_input, int length_input) {
	cout<<"Enter the number of vertical rooms: ";
	cin>>this->width_input;
	cout<<"Enter the number of horizontal rooms:";
	cin>>this->length_input;
	// At this point, grid is empty
	
	this->grid.resize(this->length_input);

	// Resize each row
	for (int i = 0; i < this->length_input; i++) {
		grid.at(i).resize(this->width_input);
	}

	/*fills 2 rooms with bats*/
	this->insert_event(new Bats);
	this->insert_event(new Bats);

	/*fills 2 rooms with stalactites*/
	this->insert_event(new Stalactites);
	this->insert_event(new Stalactites);

	/*fills one room with gold*/
	this->insert_event(new Gold);

	/*fills one room with Wumpus*/
	this->insert_event(new Wumpus);

}

/*********************************************************************
** Function:place_adventurer()
** Description: plces the adventurer to the room if it doesn't have
the event inside and assignes the user position
** Parameters:no
** Pre-Conditions:called by a function
** Post-Conditions: adventurer was randonly placed, psotion was stored
*********************************************************************/
void Game::place_adventurer() {
	do {
		// Choose a random row
		row_idx_user = rand() % grid.size();
		// Choose a random column
		col_idx_user = rand() % (grid.at(0).size());
	} while (grid.at(row_idx_user).at(col_idx_user).has_event());

    /*set the player in the room*/
    grid.at(row_idx_user).at(col_idx_user).set_player();
	//grid.at(row_idx_user).at(col_idx_user).set_rope();
	//cout<<row_idx<<endl<<col_idx<<endl;
	rope_row = row_idx_user;
	rope_col = col_idx_user;
	cout<<"Rope position: "<<rope_row<<" "<<rope_col<<endl;
}

/*********************************************************************
** Function:insert_event()
** Description: inserts the event on a random position in the grid,
checking if the room already has event inside, assigns the values
** Parameters: pointer to an Event object
** Pre-Conditions:vector 2d array was created, grid
** Post-Conditions:the event was inserted to an array and values was 
assigned
*********************************************************************/
void Game::insert_event(Event* event) {
	int row_idx = 0;
	int col_idx = 0;
	do {
		// Choose a random row
		row_idx = rand() % grid.size();
		// Choose a random column
		col_idx = rand() % (grid.at(0).size());
	} while(grid.at(row_idx).at(col_idx).get_event() != nullptr || grid.at(row_idx).at(col_idx).has_player());

	// Place the event
	if(!grid.at(row_idx).at(col_idx).has_player()){
		grid.at(row_idx).at(col_idx).set_event(event);
		if (event->get_type() == 3) {
            wumpus_row = row_idx;
            wumpus_col = col_idx;
		}else if (event->get_type() == 4) {
            gold_row = row_idx;
            gold_col = col_idx;
		}
	}

}

/*********************************************************************
** Function:display_game()
** Description: displys the updated grid 
** Parameters:int, int, char 
** Pre-Conditions:grid was created and events was inserted as well as
player was setted
** Post-Conditions: the grid was printed to the screen with all changes
*********************************************************************/
void Game::display_game(int width_input, int length_input, char debug, char c) {
	if (!grid.at(row_idx_user).at(col_idx_user).has_player()) {
        place_adventurer();
    }
	cout << endl << endl;
	/*print the number of arrows to the screen*/
	cout << "Arrows remaining: " << this->num_arrows << endl;
	
	string line = "";
	for (int i = 0; i < this->length_input; ++i)
		line += "------";

	for (int i = 0; i < this->length_input; ++i)
	{
		cout << line << endl;
		for (int j = 0; j < this->width_input; ++j)
		{
			const Room& room = grid.at(i).at(j);
			if (room.has_player()) {
                cout << "*";
            } else {
                cout << " ";
            }

            //Event* event = grid.at(i).at(j).get_event();
			/*check if the user wants debug mode or no*/
			if (debug == 'T'){
				debug_view = true;
			}else if(debug == 'F'){
				debug_view = false;
			}
			/*checks if the room has event to print it to the screen*/
            if (room.has_event() == false) {
                cout << "   ||";
            } else if(room.has_event() == true){
				if (debug_view == true) {
              		cout << room.get_event_char() << " ||";
				}else if (debug_view == false){
            		cout << " " << " ||";
				}
            }
        }
	cout << endl;
	}	
	cout << line << endl;

}

/*********************************************************************
** Function:check_win()
** Description:check if the player won the game and if yes, it quits
** Parameters:no
** Pre-Conditions:called in main before printing the grid
** Post-Conditions: the game was won and quitted successfully
*********************************************************************/
bool Game::check_win() const{
	//check if game over/win
	if(win == true){
		cout<<endl<<"You won the game! Congratulations!"<<endl;
		/*exits the program if the user won the game*/
		exit(0);
	}else if(hasgold == true && row_idx_user == rope_row && col_idx_user == rope_col){
		cout<<endl<<"You won the game! Congratulations!"<<endl;
		exit(0);
	}
	return false;
}

/*********************************************************************
** Function:move_up
** Description:lets the user moves up one room
** Parameters:no
** Pre-Conditions:grid was created
** Post-Conditions:player was deleted from the previous room and setted
to the new one
*********************************************************************/
void Game::move_up() {
	if (row_idx_user > 0) {
        // Remove the player from the current room
        grid.at(row_idx_user).at(col_idx_user).remove_player();
        
        // Update the player's row position
        	row_idx_user--;

        // Set the player in the new room
        grid.at(row_idx_user).at(col_idx_user).set_player();
    }else{
		cout<<endl<<"Sorry, the input is not valid. Try again."<<endl;
	}
}

/*********************************************************************
** Function:move_down
** Description:lets the user moves down one room
** Parameters:no
** Pre-Conditions:grid was created
** Post-Conditions:player was deleted from the previous room and setted
to the new one
*********************************************************************/
void Game::move_down() {
	if (row_idx_user < this->length_input) {
        // Remove the player from the current room
        grid.at(row_idx_user).at(col_idx_user).remove_player();
        
        // Update the player's row position
        row_idx_user++;

        // Set the player in the new room
        grid.at(row_idx_user).at(col_idx_user).set_player();
    }else{
		cout<<endl<<"Sorry, the input is not valid. Try again."<<endl;
	}
}

/*********************************************************************
** Function:move_left
** Description:lets the user moves left one room
** Parameters:no
** Pre-Conditions:grid was created
** Post-Conditions:player was deleted from the previous room and setted
to the new one
*********************************************************************/
void Game::move_left() {
	if (col_idx_user > 0) {
        // Remove the player from the current room
        grid.at(row_idx_user).at(col_idx_user).remove_player();
        
        // Update the player's row position
        col_idx_user--;

        // Set the player in the new room
        grid.at(row_idx_user).at(col_idx_user).set_player();
    }else{
		cout<<endl<<"Sorry, the input is not valid. Try again."<<endl;
	}
}

/*********************************************************************
** Function:move_right
** Description:lets the user moves right one room
** Parameters:no
** Pre-Conditions:grid was created
** Post-Conditions:player was deleted from the previous room and setted
to the new one
*********************************************************************/
void Game::move_right() {
	//CHANGE 6 TO USER INPUT FOR THE SIZE OF THE GRID
	if (col_idx_user < this->width_input) {
        // Remove the player from the current room
        grid.at(row_idx_user).at(col_idx_user).remove_player();
        
        // Update the player's row position
        col_idx_user++;

        // Set the player in the new room
        grid.at(row_idx_user).at(col_idx_user).set_player();
    }else{
		cout<<endl<<"Sorry, the input is not valid. Try again."<<endl;
	}
}

/*********************************************************************
** Function:get_dir
** Description:asks the user to input the direction for an arrow
** Parameters:no
** Pre-Conditions:was called by other function
** Post-Conditions:returnchar c, so the user input
*********************************************************************/
char Game::get_dir(){
	
	char dir = ' ';
	/*takes the direction from the user*/
	while(dir!= 'w' && dir!='a' && dir!='s' && dir!='d'){
		cout << "Fire an arrow...." << endl;
		cout << "w-up" << endl;
		cout << "a-left" << endl;
		cout << "s-down" << endl;
		cout << "d-right" << endl;
		

		cout << "Enter direction: " << endl;
		cin >> dir;
		/*cleans the buffer*/
		cin.ignore(256, '\n');
		if(dir!= 'w' && dir!='a' && dir!='s' && dir!='d'){
			cout<<endl<<"Sorry, the input is mot valid. Try again."<<endl;
		}
	}

	return dir;
}

/*********************************************************************
** Function:wumpus_move
** Description:creates 3 numbers to have a 75% chance of the wumpus
going to other room if the user misses the arrow
** Parameters:no
** Pre-Conditions:the user missed the arrow
** Post-Conditions:75% chance that the wumpus will be delted from the 
room and setted to the new room
*********************************************************************/
void Game::wumpus_move(){
	cout<<"Wumpus_row: "<<wumpus_row<<endl;
	cout<<"Wumpus_col: "<<wumpus_col<<endl;
	int wumpus_move = rand()%4;
	if(wumpus_move != 0){
		grid.at(wumpus_row).at(wumpus_col).remove_event();
		this->insert_event(new Wumpus);
		/*sets the position of the wumpus to the new place*/
		int new_wumpus_row = wumpus_row;
		int new_wumpus_col = wumpus_col;
	}
	return;
}

/*********************************************************************
** Function:arrow_up()
** Description:lets the user fire an arrow in the up direction through
3 rooms at max, calls the wumpus move if the user misses an arrow, and 
calls the delte event function if the user killed the wumpus
** Parameters:no
** Pre-Conditions:user inputted f
** Post-Conditions:the arrow was fired and the wumpus is dead or it 
moved, or nothing happened, but the arrows number went down
*********************************************************************/
void Game::arrow_up(){
	int num_rooms_traveled = 0;
	for(int i =0;i<3;i++){
		/*moving the arrow one row up*/
		int arrow_row = row_idx_user - i - 1;
		int arrow_col = col_idx_user;
		cout<<arrow_row<<endl;
		cout<<arrow_col<<endl;
		if (arrow_row == wumpus_row && arrow_col == wumpus_col) {
        	cout<<"The arrow killed the Wumpus! You can be safe now!"<<endl;
			/*remove the Wumpus event, because it was killed by the player*/
        	grid.at(wumpus_row).at(wumpus_col).remove_event();
        	wumpus_row = -1;
			win = true;
			break;
		}
		num_rooms_traveled ++;
	}
	num_arrows--;
	if(wumpus_row != -1){
		if (num_rooms_traveled <= 3) {
			cout<<"Arrow traveled "<<num_rooms_traveled<<" rooms. Wumpus can wake up..."<<endl;
			/*moves the wumpus if the 75% chance was lost*/
			wumpus_move();
		}
	}
}

/*********************************************************************
** Function:arrow_down()
** Description:lets the user fire an arrow in the down direction through
3 rooms at max, calls the wumpus move if the user misses an arrow, and 
calls the delte event function if the user killed the wumpus
** Parameters:no
** Pre-Conditions:user inputted f
** Post-Conditions:the arrow was fired and the wumpus is dead or it 
moved, or nothing happened, but the arrows number went down
*********************************************************************/
void Game::arrow_down(){
	int num_rooms_traveled = 0;
	for(int i =0;i<3;i++){
		/*moving the arrow one row up*/
		int arrow_row = row_idx_user + i + 1;
		int arrow_col = col_idx_user;
		cout<<arrow_row<<endl;
		cout<<arrow_col<<endl;
		if (arrow_row == wumpus_row && arrow_col == wumpus_col) {
        	cout<<"The arrow killed the Wumpus! You can be safe now!"<<endl;
			/*remove the Wumpus event, because it was killed by the player*/
        	grid.at(wumpus_row).at(wumpus_col).remove_event();
        	wumpus_row = -1;
			win = true;
			break;
		}
		/*decreases the amount of arrows every time*/
		num_rooms_traveled ++;
	}
	num_arrows--;
	if(wumpus_row != -1){
		if (num_rooms_traveled <= 3) {
			cout<<"Arrow traveled "<<num_rooms_traveled<<" rooms. Wumpus can wake up..."<<endl;
			wumpus_move();
		}
	}
}

/*********************************************************************
** Function:arrow_left()
** Description:lets the user fire an arrow in the left direction through
3 rooms at max, calls the wumpus move if the user misses an arrow, and 
calls the delte event function if the user killed the wumpus
** Parameters:no
** Pre-Conditions:user inputted f
** Post-Conditions:the arrow was fired and the wumpus is dead or it 
moved, or nothing happened, but the arrows number went down
*********************************************************************/
void Game::arrow_left(){
	int num_rooms_traveled = 0;
	for(int i =0;i<3;i++){
		/*moving the arrow one row up*/
		int arrow_row = row_idx_user;
		int arrow_col = col_idx_user - i - 1;
		cout<<arrow_row<<endl;
		cout<<arrow_col<<endl;
		if (arrow_row == wumpus_row && arrow_col == wumpus_col) {
        	cout<<"The arrow killed the Wumpus! You can be safe now!"<<endl;
			/*remove the Wumpus event, because it was killed by the player*/
        	grid.at(wumpus_row).at(wumpus_col).remove_event();
        	wumpus_row = -1;
			win = true;
			break;
		}
		num_rooms_traveled ++;
	}
	num_arrows--;
	if(wumpus_row != -1){
		if (num_rooms_traveled <= 3) {
			/*prints the info about arrow to the screen*/
			cout<<"Arrow traveled "<<num_rooms_traveled<<" rooms. Wumpus can wake up..."<<endl;
			wumpus_move();
    	}
	}
}

/*********************************************************************
** Function:arrow_right()
** Description:lets the user fire an arrow in the right direction through
3 rooms at max, calls the wumpus move if the user misses an arrow, and 
calls the delte event function if the user killed the wumpus
** Parameters:no
** Pre-Conditions:user inputted f
** Post-Conditions:the arrow was fired and the wumpus is dead or it 
moved, or nothing happened, but the arrows number went down
*********************************************************************/
void Game::arrow_right(){
	int num_rooms_traveled = 0;
	for(int i =0;i<3;i++){
		/*moving the arrow one row up*/
		int arrow_row = row_idx_user;
		int arrow_col = col_idx_user + i + 1;
		cout<<arrow_row<<endl;
		cout<<arrow_col<<endl;
		if (arrow_row == wumpus_row && arrow_col == wumpus_col) {
        	cout<<"The arrow killed the Wumpus! You can be safe now!"<<endl;
			/*remove the Wumpus event, because it was killed by the player*/
        	grid.at(wumpus_row).at(wumpus_col).remove_event();
        	wumpus_row = -1;
			win = true;
			break;
		}
		num_rooms_traveled ++;
	}
	num_arrows--;
	if(wumpus_row != -1){
		if (num_rooms_traveled = 3) {
			cout<<"Arrow traveled "<<num_rooms_traveled<<" rooms. Wumpus can wake up..."<<endl;
			grid.at(wumpus_row).at(wumpus_col).remove_event();
			wumpus_move();
		}
	}
}

/*********************************************************************
** Function:fire_arrow()
** Description:check the input from the user and calls the proper function
** Parameters:no
** Pre-Conditions:the user chose a direction for an arrow
** Post-Conditions:the desired direction functio was called for arrow
*********************************************************************/
void Game::fire_arrow(){
	/*calls the function that stores the input from the user*/
	char dir = get_dir();
	if(dir == 'w'){
		arrow_up();
	}else if(dir =='a'){
		arrow_left();
	}else if(dir =='s'){
		arrow_down();
	}else if(dir =='d'){
		arrow_right();
	}
	return;

}

/*********************************************************************
** Function:move()
** Description:calls the proper function for the user actions
** Parameters:char c, so user input
** Pre-Conditions:user input
** Post-Conditions:the desired action was called and done
*********************************************************************/
void Game::move(char c) {
	if (c == 'f'){
		/*let the user fire an arrow*/
		Game::fire_arrow();
		return;
	}
	switch(c){
		case 'w':
			if(back_bats == 0){
				Game::move_up();
			}
			else{
				Game::move_down();
				/*number of the bats event decreases, until it reaches 5*/
				back_bats--;
			}
			break;
		case 'a':
			if(back_bats == 0){
				Game::move_left();
			}
			else{
				Game::move_right();
				back_bats--;
			}
			break;
		case 's':
			if(back_bats == 0){
				Game::move_down();
			}
			else{
				Game::move_up();
				back_bats--;
			}
			break;
		case 'd':
		/*check if the number of bats that can confuse 
		the drection is 0 and then let the user move*/
			if(back_bats == 0){
				Game::move_right();
			}
			else{
				Game::move_left();
				back_bats--;
			}
			break;
	}
}

/*********************************************************************
** Function:get_input()
** Description:takes the input from the user and does the error checking
** Parameters:no
** Pre-Conditions:was called by a function
** Post-Conditions:the user input was stored in char c
*********************************************************************/
char Game::get_input(){
	char c = ' ';
	while(c!= 'w' && c!='a' && c!='s' && c!='d' && c!='f' && c!='T' && c!='F'){
		cout << endl << endl << "Player move..." << endl << endl;
		//cout << endl << endl << "If you would like to turn on the debug mode, press 'T'/ press 'F' to turn it off. " << endl << endl;
		cout << "w-up" << endl;
		cout << "a-left" << endl;
		cout << "s-down" << endl;
		cout << "d-right" << endl;
		cout << "f-fire an arrow" << endl;

		cout << "Enter input: " << endl;
		cin >> c;
		/*cleans the buffer*/
		cin.ignore(256, '\n');
		if(c!= 'w' && c!='a' && c!='s' && c!='d' && c!='f' && c!='T' && c!='F'){
			cout<<endl<<"Sorry, the input is mot valid. Try again."<<endl;
		}
	}
	return c;
}

/*********************************************************************
** Function:percept_wumpus()
** Description:checks if the adjacent room on a grid has an event of a 
specific type, and then calls the percept function polymorphically
** Parameters:no
** Pre-Conditions: the user is in adjacent room
** Post-Conditions:percepts was called
*********************************************************************/
void Game::percept_wumpus(){
	/*creates the wumpus object;*/
	Wumpus w;
	if(row_idx_user+1 == wumpus_row && col_idx_user == wumpus_col){
		/*calls the function polymorphically*/
		w.percept();
		/*checks the position*/
	}else if(row_idx_user-1 == wumpus_row && col_idx_user == wumpus_col){
		w.percept();
	}else if(row_idx_user == wumpus_row && col_idx_user+1 == wumpus_col){
		w.percept();
	}else if(row_idx_user == wumpus_row && col_idx_user-1 == wumpus_col){
		w.percept();
	}
}

/*********************************************************************
** Function:percept_gold()
** Description:checks if the adjacent room on a grid has an event of a 
specific type, and then calls the percept function polymorphically
** Parameters:no
** Pre-Conditions: the user is in adjacent room
** Post-Conditions:percepts was called
*********************************************************************/
void Game::percept_gold(){
	Gold g;
	if(row_idx_user+1 == gold_row && col_idx_user == gold_col){
		g.percept();
	}else if(row_idx_user-1 == gold_row && col_idx_user == gold_col){
		g.percept();
	}else if(row_idx_user == gold_row && col_idx_user+1 == gold_col){
		g.percept();
	}else if(row_idx_user == gold_row && col_idx_user-1 == gold_col){
		g.percept();
	}
}

/*********************************************************************
** Function:percept_bats()
** Description:checks if the adjacent room on a grid has an event of a 
specific type, and then calls the percept function polymorphically
** Parameters:no
** Pre-Conditions: the user is in adjacent room
** Post-Conditions:percepts was called
*********************************************************************/
void Game::percept_bats(){
	Bats b;
	/*checks the position*/
	if (row_idx_user > 0 && grid[row_idx_user - 1][col_idx_user].has_event_type(1)) {
        b.percept();
    }
    if (row_idx_user < grid.size() - 1 && grid[row_idx_user + 1][col_idx_user].has_event_type(1)) {
        b.percept();
    }
	/*checks the position*/
    if (col_idx_user > 0 && grid[row_idx_user][col_idx_user - 1].has_event_type(1)) {
        b.percept();
    }
    if (col_idx_user < grid[0].size() - 1 && grid[row_idx_user][col_idx_user + 1].has_event_type(1)) {
        b.percept();
    }
}

/*********************************************************************
** Function:percept_stalactites()
** Description:checks if the adjacent room on a grid has an event of a 
specific type, and then calls the percept function polymorphically
** Parameters:no
** Pre-Conditions: the user is in adjacent room
** Post-Conditions:percepts was called
*********************************************************************/
void Game::percept_stalactites(){
	Stalactites s;
	/*checks the position*/
	if (row_idx_user > 0 && grid[row_idx_user - 1][col_idx_user].has_event_type(2)) {
        s.percept();
    }
    if (row_idx_user < grid.size() - 1 && grid[row_idx_user + 1][col_idx_user].has_event_type(2)) {
        s.percept();
    }
	/*checks the position*/
    if (col_idx_user > 0 && grid[row_idx_user][col_idx_user - 1].has_event_type(2)) {
        s.percept();
    }
    if (col_idx_user < grid[0].size() - 1 && grid[row_idx_user][col_idx_user + 1].has_event_type(2)) {
        s.percept();
    }
}

/*********************************************************************
** Function:play_game()
** Description:does the main functionalities of the game, so it calls 
all functions such as set up the grid, print the grid, check if user 
won the game, all percepts, and encounters
** Parameters:int,int,char,har, all of them are user inputs
** Pre-Conditions:user input was valid
** Post-Conditions:game was running properly and the user won or lost
*********************************************************************/
void Game::play_game(int width_input, int length_input, char debug, char c){

	Game::set_up(width_input, length_input);

	char input = ' ', arrow_input = ' ';
	
	while (Game::check_win() == false && death == false){
		//print game board
		Game::display_game(width_input, length_input, debug, c);

		percept_wumpus();
		/*if user doesn't take the gold, and the event still 
		exists, then call the percept function*/
		if(hasgold == false){
			percept_gold();
		}
		percept_stalactites();
		percept_bats();

		input = Game::get_input();
	
		/*let he user move*/
		Game::move(input);

		if (check_player_room_event(1)) {
			cout << "You are in a room with Bats!" << endl;
			Bats b;
			/*death parameter means if the user is still alive*/
			b.encounter(death, back_bats);
		} else if (check_player_room_event(2)) {
			cout << "You are in a room with Stalactites!" << endl;
			Stalactites s;
			s.encounter(death, back_bats);
		} 
		/*checks the postion of the wumpus and call encounter if it is the same as the user*/
		if(row_idx_user == wumpus_row && col_idx_user == wumpus_col){
			Wumpus w;
			w.encounter(death, back_bats);
			//death = true;
		/*checks the postion of the gold and call encounter if it is the same as the user*/
		}else if(row_idx_user == gold_row && col_idx_user == gold_col){
			if(hasgold == false){
			cout<<endl<<gold_row<<" "<<gold_col<<endl;
			Gold g;
			g.encounter(death, back_bats);
			grid.at(gold_row).at(gold_col).remove_event();
			/*sets the gols flag to true if the user entered the gold room*/
			hasgold = true;
			}
		}
		
	}
}