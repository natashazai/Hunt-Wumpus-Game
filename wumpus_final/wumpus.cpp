#include "wumpus.h"
#include <iostream>
#include "event.h"

using namespace std;

/*********************************************************************
** Function: Wumpus()
** Description: default constructor for the class
** Parameters:no
** Pre-Conditions:no
** Post-Conditions: sets the event to char 'W'
*********************************************************************/
Wumpus::Wumpus() : Event('W') {}

/*********************************************************************
** Function:encounter()
** Description:encounter function for the class Wumpus
** Parameters:boolean if user is dead or alive, and reference to a 
number of bats
** Pre-Conditions:called by a function
** Post-Conditions:the function was used polymorphically
*********************************************************************/
void Wumpus::encounter(bool &death, int & back_bats) const {
        cout<<"You have entered the room… it looks dark… Your blood run cold in your veins… You think it was a wrong choice. You see the Wumpus… GAME OVER."<<endl;
        death = true;
    }

/*********************************************************************
** Function:percept()
** Description:prints the percept if the user is in adjacent room to an
event
** Parameters:no
** Pre-Conditions:user is in adjacent room to the event
** Post-Conditions:the percept was printed to the screen
*********************************************************************/
void Wumpus::percept() const {
    cout<<endl<<endl<<"You smell a terrible stench."<<endl<<endl;;
    // Implement the percept function for Bats
}

/*********************************************************************
** Function:get_debug_character()
** Description:getter for the char for the specific event
** Parameters:no
** Pre-Conditions:called by a function to have access
** Post-Conditions:the char was accessed by a function
*********************************************************************/
char Wumpus::get_debug_character() const {
    return 'W';  // or whatever character represents Bats
}
