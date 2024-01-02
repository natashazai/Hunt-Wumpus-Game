#include "room.h"
#include <iostream>
#include<string>

using namespace std;

/*********************************************************************
** Function:set_event()
** Description:checks if the pointer is null and sets it to new event
object
** Parameters:pointer to an event class object
** Pre-Conditions:was called by a function
** Post-Conditions:the event was setted
*********************************************************************/
void Room::set_event(Event* new_event) {
	if (this->event != nullptr) {
		delete this->event;
	}
	this->event = new_event;
}

/*********************************************************************
** Function:get_event
** Description:getter for the event
** Parameters:no
** Pre-Conditions:no
** Post-Conditions:this event was returned
*********************************************************************/
Event* Room::get_event() const {
	return this->event;
}

/*********************************************************************
** Function:Room()
** Description:default constructor for Room class
** Parameters:no
** Pre-Conditions:no
** Post-Conditions:the hasplayer was setted to false
*********************************************************************/
Room::Room() : hasplayer(false) {}

/*********************************************************************
** Function:set_player()
** Description:sets the bool hasplayer to true
** Parameters:no
** Pre-Conditions:was called by a function
** Post-Conditions:the room has a player inside
*********************************************************************/
void Room::set_player() {
    this->hasplayer = true;
}

/*********************************************************************
** Function:set_rope()
** Description:sets the room where the user was placed with a escape rope
** Parameters:no
** Pre-Conditions:called by a function
** Post-Conditions:the room has rope inside
*********************************************************************/
void Room::set_rope() {
    this->hasrope = true;
}

/*********************************************************************
** Function:has_player()
** Description:boolean for hasplayer
** Parameters:no
** Pre-Conditions:no
** Post-Conditions:hasplayer was returned
*********************************************************************/
bool Room:: has_player() const {
   return hasplayer;
}

/*********************************************************************
** Function:has_rope()
** Description:boolean for escape rope
** Parameters:no
** Pre-Conditions:no
** Post-Conditions:hasrope was returned
*********************************************************************/
bool Room:: has_rope() const {
   return hasrope;
}

/*********************************************************************
** Function:remove_player()
** Description:sets the hasplayer flag to false
** Parameters:no
** Pre-Conditions:called by a fucntion
** Post-Conditions:the hasplayer was returned and setted to false
*********************************************************************/
void Room:: remove_player() {
    this->hasplayer = false;
}

/*********************************************************************
** Function:get_event_char()
** Description:accessing debugging characters for the events
** Parameters:no
** Pre-Conditions:called by a function
** Post-Conditions:debugging character was returned
*********************************************************************/
char Room::get_event_char() const{

    return this->event->get_debug_character();//arrow again to acces the symbol function
}

/*********************************************************************
** Function:has_event()
** Description:checks if event null and then return false 
** Parameters:no
** Pre-Conditions:was called by a function
** Post-Conditions:the boolean was returned
*********************************************************************/
bool Room::has_event() const {

    if(this->event == nullptr){
        return false;
    }else{
        return true;
    }
}

bool Room::has_event_type(int event_type) const {

    const Event* event = get_event();
    return event && event->get_type() == event_type;
}


/*********************************************************************
** Function:remove_event()
** Description:remove the event if the pointer is not null, so it
sets it to null
** Parameters:no
** Pre-Conditions:no
** Post-Conditions:the event was removed
*********************************************************************/
void Room::remove_event(){
    /*using reference to a pointer to be able to set the event to null*/
    if (event != nullptr) {
        delete event;
        /*set the event pointer to nullptr to indicate no event in the room*/
        event = nullptr;  
    }
}

/*********************************************************************
** Function:~Room()
** Description:destructor for Room class 
** Parameters:no
** Pre-Conditions:the program has reached the end
** Post-Conditions:event pointer was deleted to free the memory
*********************************************************************/
Room::~Room(){
    if(event!=nullptr)
	    delete event;
}
