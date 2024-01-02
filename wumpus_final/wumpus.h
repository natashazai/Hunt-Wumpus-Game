#ifndef WUMPUS_H
#define WUMPUS_H 
#include "event.h"

class Wumpus : public Event {
public:

	Wumpus();
    void encounter(bool &death, int & back_bats) const override;
    void percept() const override;
    char get_debug_character() const;
	virtual int get_type() const override {
		/* unique identifier for Wumpus*/
        return 3; 
    }
};

#endif