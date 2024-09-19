/*
 * Switch.c
 *
 *  Created on: Nov 5, 2023
 *      Author:
 */
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
// LaunchPad.h defines all the indices into the PINCM table
void Switch_Init(void){
    IOMUX->SECCFG.PINCM[PA28INDEX] = 0x00040081;
    IOMUX->SECCFG.PINCM[PA24INDEX] = 0x00040081;
    IOMUX->SECCFG.PINCM[PA31INDEX] = 0x00040081;
    IOMUX->SECCFG.PINCM[PA12INDEX] = 0x00040081;

    GPIOA->DOE31_0 |= ((1 << 28) + (1 << 24) + (1 << 31) + (1 << 12));
}
// return current state of switches
uint32_t Switch_In(void){
    uint32_t test2 = GPIOA->DIN31_0;
    return test2;
}
