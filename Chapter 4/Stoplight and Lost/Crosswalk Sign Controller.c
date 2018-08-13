/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 8/13/2018 14:21:21 PST
*/

#include "rims.h"

char count;
char count2;
char count3;
unsigned char SM1_Clk;
void TimerISR() {
   SM1_Clk = 1;
}

enum SM1_States { SM1_Wait, SM1_Release, SM1_Press, SM1_On, SM1_Flash } SM1_State;

TickFct_State_machine_1() {
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_Wait;
         break;
         case SM1_Wait: 
         if (A0) {
            SM1_State = SM1_Press;
         }
         break;
      case SM1_Release: 
         if (count < 20) {
            SM1_State = SM1_Release;
            count++;
         }
         else if (count >= 20) {
            SM1_State = SM1_On;
            B0 = 1;
            B1 = 0;
         }
         break;
      case SM1_Press: 
         if (!A0) {
            SM1_State = SM1_Release;
            B1 = 1;
         }
         break;
      case SM1_On: 
         if (count2 < 20) {
            SM1_State = SM1_On;
            count2++;
         }
         else if (count2 >= 20) {
            SM1_State = SM1_Flash;
            !B0;
         }
         break;
      case SM1_Flash: 
         if (count3 < 11) {
            SM1_State = SM1_Flash;
            
            count3++;
         }
         else if (count3 >= 11) {
            SM1_State = SM1_Wait;
            B0 = 0;
         }
         break;
      default:
         SM1_State = SM1_Wait;
   } // Transitions

   switch(SM1_State) { // State actions
      case SM1_Wait:
         count = 0;
         count2 = 0;
         count3 = 0;
         break;
      case SM1_Release:
         break;
      case SM1_Press:
         break;
      case SM1_On:
         break;
      case SM1_Flash:
         B0 = !(B0);
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int periodState_machine_1 = 500;
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