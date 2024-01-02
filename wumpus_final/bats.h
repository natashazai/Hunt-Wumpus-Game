#ifndef BATS_H
#define BATS_H 
#include "event.h"

//Bats Interface
class Bats : public Event {
public:

	Bats();

    void encounter(bool &death, int & back_bats) const override;
    void percept() const override;
    char get_debug_character() const;
	virtual int get_type() const override {
		/* unique identifier for Bats*/
        return 1; 
    }

};

#endif