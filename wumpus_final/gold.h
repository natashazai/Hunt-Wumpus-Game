#ifndef GOLD_H
#define GOLD_H 
#include "event.h"

class Gold : public Event {
public:
	
	Gold();
    void encounter(bool &death, int & back_bats) const override;
    void percept() const override;
    char get_debug_character() const;
	virtual int get_type() const override {
		/* unique identifier for Gold*/
        return 4; 
    }


};

#endif