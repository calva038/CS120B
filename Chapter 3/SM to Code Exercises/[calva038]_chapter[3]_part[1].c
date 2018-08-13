#include "RIMS.h"
enum States {Start, OFF, ON} state;

void Tick(){

switch(state){ // Transitions
case Start:
state = OFF;
break;

case OFF:
if (A0)
	state = ON;
else
	state = OFF;
break;

case ON:
if (A0)
	state = ON;
else
	state = OFF;
break;

default:
break;

} // Transitions

switch(state) { //State actions
case Start:
break;	
	
case OFF:
B=0;
break;

case ON:
B = 0x01;
break;

default:
break;
} // State actions
}

void main(){
B = 0x00; //Initialize outputs
state = Start; // Indicates initial call
while(1) { Tick();}
}
