#include "stalactites.h"

#include <iostream>

using namespace std;

//Stalactites Implementation
/*********************************************************************
** Function: Stalactites()
** Description: default constructor for the class
** Parameters:no
** Pre-Conditions:no
** Post-Conditions: sets the event to char 'S'
*********************************************************************/
Stalactites::Stalactites() : Event('S') {}

/*********************************************************************
** Function:encounter()
** Description:encounter function for the class Stalactites
** Parameters:boolean if user is dead or alive, and reference to a 
number of bats
** Pre-Conditions:called by a function
** Post-Conditions:the function was used polymorphically
*********************************************************************/
void Stalactites::encounter(bool &death, int & back_bats) const {
    int check_stal= rand()%2;
    if(check_stal == 0){
        cout<<"It is not your luckiest day today...You were killed by the fallen stalactite..."<<endl;
        cout<<"GAME OVER"<<endl;
        death = true;
    }else if(check_stal == 1){
        cout<<"You entered a room and fortunatelly stalactites didn't fall on you. Congratulations!"<<endl;
    }
}

/*********************************************************************
** Function:percept()
** Description:prints the percept if the user is in adjacent room to an
event
** Parameters:no
** Pre-Conditions:user is in adjacent room to the event
** Post-Conditions:the percept was printed to the screen
*********************************************************************/
void Stalactites::percept() const {
    cout<<endl<<endl<<"You hear water dripping."<<endl<<endl;
    // Implement the percept function for Stalactites
}

/*********************************************************************
** Function:get_debug_character()
** Description:getter for the char for the specific event
** Parameters:no
** Pre-Conditions:called by a function to have access
** Post-Conditions:the char was accessed by a function
*********************************************************************/
char Stalactites::get_debug_character() const {
    return 'S';  // or whatever character represents Stalactites
}
