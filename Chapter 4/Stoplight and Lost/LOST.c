/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 8/13/2018 14:44:57 PST
*/

#include "rims.h"

int countdown = 12960;
unsigned char SM1_Clk;
void TimerISR() {
   SM1_Clk = 1;
}

enum SM1_States { SM1_Start, SM1_4, SM1_15, SM1_8, SM1_16, SM1_23, SM1_LOST, SM1_Time_Travel } SM1_State;

TickFct_State_machine_1() {
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_Start;
         break;
         case SM1_Start: 
         if (A == 4) {
            SM1_State = SM1_4;
         }
         else if (countdown <= 0) {
            SM1_State = SM1_Time_Travel;
         }
         else if (A != 4) {
            SM1_State = SM1_Start;
         }
         break;
      case SM1_4: 
         if (A == 8) {
            SM1_State = SM1_8;
         }
         else if (countdown <= 0) {
            SM1_State = SM1_Time_Travel;
         }
         else if (A != 8) {
            SM1_State = SM1_4;
         }
         break;
      case SM1_15: 
         if (A == 16) {
            SM1_State = SM1_16;
         }
         else if (countdown <= 0) {
            SM1_State = SM1_Time_Travel;
         }
         else if (A != 16) {
            SM1_State = SM1_15;
         }
         break;
      case SM1_8: 
         if (A == 15) {
            SM1_State = SM1_15;
         }
         else if (countdown <= 0) {
            SM1_State = SM1_Time_Travel;
         }
         else if (A != 15) {
            SM1_State = SM1_8;
         }
         break;
      case SM1_16: 
         if (A == 23) {
            SM1_State = SM1_23;
         }
         else if (countdown <= 0) {
            SM1_State = SM1_Time_Travel;
         }
         else if (A != 23) {
            SM1_State = SM1_16;
         }
         break;
      case SM1_23: 
         if (A == 42) {
            SM1_State = SM1_LOST;
         }
         else if (countdown <= 0) {
            SM1_State = SM1_Time_Travel;
         }
         else if (A != 42) {
            SM1_State = SM1_23;
         }
         break;
      case SM1_LOST: 
         break;
      case SM1_Time_Travel: 
         if (1) {
            SM1_State = SM1_Time_Travel;
         }
         break;
      default:
         SM1_State = SM1_Start;
   } // Transitions

   switch(SM1_State) { // State actions
      case SM1_Start:
         countdown--;
         break;
      case SM1_4:
         countdown--;
         break;
      case SM1_15:
         countdown--;
         break;
      case SM1_8:
         countdown--;
         break;
      case SM1_16:
         countdown--;
         break;
      case SM1_23:
         countdown--;
         break;
      case SM1_LOST:
         break;
      case SM1_Time_Travel:
         B0 = 1;
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