/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 8/13/2018 12:54:10 PST
*/

#include "rims.h"

/*Define user variables and functions for this state machine here.*/
unsigned char SM1_Clk;
void TimerISR() {
   SM1_Clk = 1;
}

enum SM1_States { SM1_OFF_RELEASE, SM1_ON_PRESS, SM1_ON_RELEASE, SM1_OFF_PRESS } SM1_State;

TickFct_State_machine_1() {
   switch(SM1_State) { // Transitions
      case -1:
         B=0;
         SM1_State = SM1_OFF_RELEASE;
         break;
         case SM1_OFF_RELEASE: 
         if (A0) {
            SM1_State = SM1_ON_PRESS;
         }
         else if (!A0) {
            SM1_State = SM1_OFF_RELEASE;
         }
         break;
      case SM1_ON_PRESS: 
         if (!A0) {
            SM1_State = SM1_ON_RELEASE;
         }
         else if (A0) {
            SM1_State = SM1_ON_PRESS;
         }
         break;
      case SM1_ON_RELEASE: 
         if (A0) {
            SM1_State = SM1_OFF_PRESS;
         }
         else if (!A0) {
            SM1_State = SM1_ON_RELEASE;
         }
         break;
      case SM1_OFF_PRESS: 
         if (!A0) {
            SM1_State = SM1_OFF_RELEASE;
         }
         else if (A0) {
            SM1_State = SM1_OFF_PRESS;
         }
         break;
      default:
         SM1_State = SM1_OFF_RELEASE;
   } // Transitions

   switch(SM1_State) { // State actions
      case SM1_OFF_RELEASE:
         break;
      case SM1_ON_PRESS:
         B0=1;
         break;
      case SM1_ON_RELEASE:
         break;
      case SM1_OFF_PRESS:
         B0=0;
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int periodState_machine_1 = 1000; // 1000 ms default
   TimerSet(periodState_machine_1);
   TimerOn();
   
   SM1_State = -1; // Initial state
   B = 0; // Init outputs

   while(1) {
      TickFct_State_machine_1();
      while(!SM1_Clk);
      SM1_Clk = 0;
   } // while (1)
} // Main