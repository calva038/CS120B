/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 8/15/2018 14:25:50 PST
*/

#include "rims.h"

unsigned char temperatureDesired = 0;
unsigned char temperatureCurrent = 0;
unsigned char duty = 0;
unsigned short timer = 0;
unsigned char L = 10;
unsigned char H = 10;
unsigned char restart = 0;
unsigned char SM1_Clk;
void TimerISR() {
   SM1_Clk = 1;
}

enum SM1_States { SM1_OFF, SM1_ON, SM1_CHECK } SM1_State;

TickFct_State_machine_1() {
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_OFF;
         break;
         case SM1_OFF: 
         if ((duty >= L) && timer < 300) {
            SM1_State = SM1_ON;
            duty = 0;
         }
         else if ((duty < L) && timer < 300) {
            SM1_State = SM1_OFF;
         }
         else if (timer >= 300) {
            SM1_State = SM1_CHECK;
            duty = 0;
         }
         break;
      case SM1_ON: 
         if ((duty < H) && timer < 300) {
            SM1_State = SM1_ON;
         }
         else if ((duty >= H) && timer < 300) {
            SM1_State = SM1_OFF;
            duty = 0;
         }
         else if (timer >= 300) {
            SM1_State = SM1_CHECK;
            duty = 0;
         }
         break;
      case SM1_CHECK: 
         if ((duty < 5)) {
            SM1_State = SM1_CHECK;
         }
         else if (restart == 1) {
            SM1_State = SM1_OFF;
            restart = 0;
         }
         break;
      default:
         SM1_State = SM1_OFF;
   } // Transitions

   switch(SM1_State) { // State actions
      case SM1_OFF:
         duty++;
         timer++;
         B = 0;
         break;
      case SM1_ON:
         duty++;
         timer++;
         B = 0x01;
         break;
      case SM1_CHECK:
         if (duty < 5){
         duty++;
         }
         else{
         temperatureDesired = (A3 + A2 + A1 + A0);
         temperatureCurrent = ((A7 + A6 + A5 + A4) >> 4);
         if (temperatureDesired == temperatureCurrent){
         }
         else if (temperatureDesired < temperatureCurrent){
         if (H < 20){
         H++;
         L--;
         }
         }
         else if (temperatureDesired > temperatureCurrent){
         if (L > 6){
         L++;
         H--;
         }
         }
         restart = 1;
         }
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int periodState_machine_1 = 50;
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