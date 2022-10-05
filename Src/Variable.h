#ifndef VARIABLE_H_INCLUDED
#define VARIABLE_H_INCLUDED
#define alienRows 8 //So dong quai
#define alienColumns 6 //So cot quai 
class Position {
	public:
		int x, y;
		Position(){
			x=-20;
			y=-20;
		}
};

class Action{
	public:
		virtual void move()=0;
};
extern int n;
extern int die;
#endif
