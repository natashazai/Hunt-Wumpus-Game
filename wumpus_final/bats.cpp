#include "bats.h"
#include "event.h"

#include <iostream>

using namespace std;

/*********************************************************************
** Function: Bats()
** Description: default constructor for the class
** Parameters:no
** Pre-Conditions:no
** Post-Conditions: sets the event to char 'B'
*********************************************************************/
Bats::Bats() : Event('B') {}

/*********************************************************************
** Function:encounter()
** Description:encounter function for the class Bats
** Parameters:boolean if user is dead or alive, and reference to a 
number of bats
** Pre-Conditions:called by a function
** Post-Conditions:the function was used polymorphically
*********************************************************************/
void Bats::encounter(bool &death, int & back_bats) const {
    cout<<"You are encountering the bats"<<endl;
    back_bats = 5;
 }

/*********************************************************************
** Function:percept()
** Description:prints the percept if the user is in adjacent room to an
event
** Parameters:no
** Pre-Conditions:user is in adjacent room to the event
** Post-Conditions:the percept was printed to the screen
*********************************************************************/
void Bats::percept() const {
    cout<<endl<<endl<<"You hear wings flapping."<<endl<<endl;
    // Implement the percept function for Bats
}

/*********************************************************************
** Function:get_debug_character()
** Description:getter for the char for the specific event
** Parameters:no
** Pre-Conditions:called by a function to have access
** Post-Conditions:the char was accessed by a function
*********************************************************************/
char Bats::get_debug_character() const {
    return 'B';  // or whatever character represents Bats
}
