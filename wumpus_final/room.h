#ifndef ROOM_H
#define ROOM_H 

#include "event.h"

using namespace std;


class Room
{
private: 
    /*to use polymorphism*/
    Event* event = nullptr;
    /*boolean flag to check if there is a player inside a room or no*/
    bool hasplayer;
    bool hasrope;
	
public:
    void set_event(Event *new_event);
	Event* get_event() const;

    bool has_event_type(int) const;

    Room();

    bool has_player() const;
    bool has_rope() const;

    char get_event_char() const;

    void set_player();
    void set_rope();
    //void delete_wumpus();
    void remove_event();

    void remove_player();

     bool has_event() const;

     ~Room();


};

#endif