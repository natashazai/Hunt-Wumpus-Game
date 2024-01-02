#ifndef STALACTITES_H
#define STALACTITES_H 
#include "event.h"

class Stalactites : public Event {
public:

	Stalactites();
    void encounter(bool &death, int & back_bats) const override;
    void percept() const override;
    char get_debug_character() const;
	virtual int get_type() const override {
        return 2;
    }
};

#endif
