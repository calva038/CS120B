#include "RIMS.h"
enum States {Start, OFF_RELEASE, ON_PRESS, ON_RELEASE, OFF_PRESS} state;

void Tick(){

switch(state){ // Transitions
case Start:
B = 0;
state = OFF_RELEASE;
break;
	
case OFF_RELEASE:
if (A0){
	B = 0x01;
	state = ON_PRESS;
}
else{
	state = OFF_RELEASE;
}
break;

case ON_PRESS:
if (A0)
	state = ON_PRESS;
else{
	state = ON_RELEASE;
}
break;

case ON_RELEASE:
if (A0){
	state = OFF_PRESS;
	B = 0;
}
else{
	state = ON_RELEASE;
}
break;

case OFF_PRESS:
if (A0){
	state = OFF_PRESS;
}
else{
	state = OFF_RELEASE;
}
break;

default:
B = 0;
state = OFF_RELEASE;
break;

} // Transitions

switch(state) { //State actions
case Start:
break;	
case OFF_RELEASE:
break;
case ON_PRESS:
break;
case ON_RELEASE:
break;
case OFF_PRESS:
break;
default:
break;
} // State actions
}

void main(){
B = 0x00; //Initialize outputs
state = OFF; // Indicates initial call
while(1) { Tick();}
}
