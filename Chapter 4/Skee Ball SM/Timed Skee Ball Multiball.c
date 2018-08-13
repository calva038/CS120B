/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 8/13/2018 12:51:0 PST
*/

#include "rims.h"

char points;
char time;
char scoreTime;
unsigned char SM1_Clk;
void TimerISR() {
   SM1_Clk = 1;
}

enum SM1_States { SM1_INIT, SM1_Game, SM1_Points, SM1_Score_On, SM1_Score_Off } SM1_State;

TickFct_State_machine_1() {
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_INIT;
         break;
         case SM1_INIT: 
         if (A0) {
            SM1_State = SM1_Game;
         }
         break;
      case SM1_Game: 
         if ( time < 30) {
            SM1_State = SM1_Points;
         }
         else if (time >= 30) {
            SM1_State = SM1_Score_On;
         }
         break;
      case SM1_Points: 
         if (1) {
            SM1_State = SM1_Game;
         }
         break;
      case SM1_Score_On: 
         if (1) {
            SM1_State = SM1_Score_Off;
         }
         break;
      case SM1_Score_Off: 
         if (scoreTime < 10) {
            SM1_State = SM1_Score_On;
         }
         else if (scoreTime >= 10) {
            SM1_State = SM1_INIT;
         }
         break;
      default:
         SM1_State = SM1_INIT;
   } // Transitions

   switch(SM1_State) { // State actions
      case SM1_INIT:
         points = 0;
         time = 0;
         scoreTime = 0;
         break;
      case SM1_Game:
         break;
      case SM1_Points:
         if (A1){
         points = points + 1;}
         if (A2){
         points = points + 2;}
         if (A3){
         points = points + 3;}
         if (A4){
         points = points + 4;}
         if (A5){
         points = points + 5;}
         if (A6){
         points = points + 10;}
         time++;
         break;
      case SM1_Score_On:
         B = points;
         scoreTime++;
         break;
      case SM1_Score_Off:
         B = 0;
         scoreTime++;
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