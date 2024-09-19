// Sound.c
// Runs on MSPM0
// Sound assets in sounds/sounds.h
// Jonathan Valvano
// 11/15/2021 
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "Sound.h"
#include "sounds/sounds.h"
#include "../inc/DAC5.h"
#include "../inc/Timer.h"


void SysTick_IntArm(uint32_t period, uint32_t priority){
  // write this
    SysTick->CTRL = 0;
    SysTick->LOAD = period - 1;
    SysTick->VAL = 0;
    SCB->SHP[1] = SCB->SHP[1] & (~0xC0000000) | priority;
    SysTick->CTRL = 0x0007;
}
// initialize a 11kHz SysTick, however no sound should be started
// initialize any global variables
// Initialize the 5 bit DAC
void Sound_Init(void){
// write this
    DAC5_Init();
    SysTick_IntArm(9090, 2);
    SysTick->CTRL = 0;

  
}

volatile uint32_t SoundNumber;
volatile const uint8_t *SoundSelect;

void SysTick_Handler(void){ // called at 11 kHz
  // output one value to DAC if a sound is active
    if(SoundNumber){
        DAC5_Out(*SoundSelect);
        SoundSelect++;
        SoundNumber--;
    }
    else{
        SysTick->CTRL = 0;
    }
}

//******* Sound_Start ************
// This function does not output to the DAC. 
// Rather, it sets a pointer and counter, and then enables the SysTick interrupt.
// It starts the sound, and the SysTick ISR does the output
// feel free to change the parameters
// Sound should play once and stop
// Input: pt is a pointer to an array of DAC outputs
//        count is the length of the array
// Output: none
// special cases: as you wish to implement
void Sound_Start(const uint8_t *pt, uint32_t count){
// write this
    SoundSelect = pt;
    SoundNumber = count;
    SysTick->CTRL = 0x07;
  
}

void Sound_Bowl(void){
    uint8_t *index;
    index = &strike1[0];
    Sound_Start(index, 6000);
}

void Sound_Win(void){
    uint8_t *index;
    index = &invaderkilled[0];
    Sound_Start(index, 3377);
  
}

