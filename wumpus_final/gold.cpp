#include "gold.h"
#include "event.h"

#include <iostream>

using namespace std;

/*********************************************************************
** Function: Gold()
** Description: default constructor for the class
** Parameters:no
** Pre-Conditions:no
** Post-Conditions: sets the event to char 'G'
*********************************************************************/
Gold::Gold() : Event('G') {}

/*********************************************************************
** Function:encounter()
** Description:encounter function for the class Gold
** Parameters:boolean if user is dead or alive, and reference to a 
number of bats
** Pre-Conditions:called by a function
** Post-Conditions:the function was used polymorphically
*********************************************************************/
void Gold::encounter(bool &death, int & back_bats) const {
        cout<<"You found a Wumpus treasure and quickly put it in your pocket, now you only need to find a way to escape."<<endl;
}

/*********************************************************************
** Function:percept()
** Description:prints the percept if the user is in adjacent room to an
event
** Parameters:no
** Pre-Conditions:user is in adjacent room to the event
** Post-Conditions:the percept was printed to the screen
*********************************************************************/
void Gold::percept() const {
    cout<<endl<<endl<<"You see a glimmer nearby."<<endl<<endl;
    // Implement the percept function for Bats
}

/*********************************************************************
** Function:get_debug_character()
** Description:getter for the char for the specific event
** Parameters:no
** Pre-Conditions:called by a function to have access
** Post-Conditions:the char was accessed by a function
*********************************************************************/
char Gold::get_debug_character() const {
    return 'G';  // or whatever character represents Bats
}
