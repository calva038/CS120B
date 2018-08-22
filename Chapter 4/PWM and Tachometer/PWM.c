/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 8/14/2018 16:27:37 PST
*/

#include "rims.h"

char Hcount;
char Lcount;
unsigned char SM1_Clk;
void TimerISR() {
   SM1_Clk = 1;
}

enum SM1_States { SM1_HIGH, SM1_LOW } SM1_State;

TickFct_State_machine_1() {
   switch(SM1_State) { // Transitions
      case -1:
         Hcount = 0;
         SM1_State = SM1_HIGH;
         break;
         case SM1_HIGH: 
         if (Hcount >= 6) {
            SM1_State = SM1_LOW;
            Lcount = 0;
         }
         else if (Hcount < 6) {
            SM1_State = SM1_HIGH;
         }
         break;
      case SM1_LOW: 
         if (Lcount >= 34) {
            SM1_State = SM1_HIGH;
            Hcount = 0;
         }
         else if (Lcount < 34) {
            SM1_State = SM1_LOW;
         }
         break;
      default:
         SM1_State = SM1_HIGH;
   } // Transitions

   switch(SM1_State) { // State actions
      case SM1_HIGH:
         B=0x01;
         Hcount++;
         break;
      case SM1_LOW:
         B=0;
         Lcount++;
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int periodState_machine_1 = 25;
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