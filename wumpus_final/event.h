#ifndef EVENT_H
#define EVENT_H 

using namespace std;

//Event Interface
//Note: this must be an abstract class!

class Event
{

private:
    char debug_character;
	

public:

	Event(char debug_character);

	virtual char get_debug_character() const =0;

	virtual int get_type() const =0;

    virtual void encounter(bool &death, int & back_bats) const =0;
    virtual void percept() const =0;
	
	//virtual ~Event();
};
#endif