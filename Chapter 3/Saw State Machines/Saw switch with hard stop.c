/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 8/13/2018 12:56:15 PST
*/

#include "rims.h"

/*Define user variables and functions for this state machine here.*/
unsigned char SM1_Clk;
void TimerISR() {
   SM1_Clk = 1;
}

enum SM1_States { SM1_OFF, SM1_ON, SM1_STOP } SM1_State;

TickFct_State_machine_1() {
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_OFF;
         break;
         case SM1_OFF: 
         if (A0 && !A1) {
            SM1_State = SM1_ON;
         }
         else if (!A0 | A1) {
            SM1_State = SM1_OFF;
         }
         break;
      case SM1_ON: 
         if (A1) {
            SM1_State = SM1_STOP;
         }
         else if (!A0 && !A1) {
            SM1_State = SM1_OFF;
         }
         else if (A0 || !A1) {
            SM1_State = SM1_ON;
         }
         break;
      case SM1_STOP: 
         if (!A0) {
            SM1_State = SM1_OFF;
         }
         else if (A0) {
            SM1_State = SM1_STOP;
         }
         break;
      default:
         SM1_State = SM1_OFF;
   } // Transitions

   switch(SM1_State) { // State actions
      case SM1_OFF:
         B=0;
         break;
      case SM1_ON:
         B=0x01;
         break;
      case SM1_STOP:
         B=0x02;
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