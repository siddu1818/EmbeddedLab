// Lab9Main.c
// Runs on MSPM0G3507
// Lab 9 ECE319K
// Your name
// Last Modified: 12/31/2023

#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "../inc/ADC1.h"
#include "../inc/DAC5.h"
#include "SmallFont.h"
#include "LED.h"
#include "Switch.h"
#include "Sound.h"
#include "images/images.h"
// ****note to ECE319K students****
// the data sheet says the ADC does not work when clock is 80 MHz
// however, the ADC seems to work on my boards at 80 MHz
// I suggest you try 80MHz, but if it doesn't work, switch to 40MHz
void PLL_Init(void){ // set phase lock loop (PLL)
  // Clock_Init40MHz(); // run this line for 40MHz
  Clock_Init80MHz(0);   // run this line for 80MHz
}
uint32_t player = 1;
uint32_t M=1;
uint32_t Random32(void){
  M = 1664525*M+1013904223;
  return M;
}
uint32_t Random(uint32_t n){
  return (Random32()>>16)%n;
}
uint32_t spot;
uint32_t spot2;
int32_t data;
// games  engine runs at 30Hz
int32_t x = 0;
    int32_t y = 0;

    uint32_t wait = 1;

    uint32_t score1 = 0;
    uint32_t score2 = 0;

    int32_t arrowend;

    uint32_t gameType;

    uint32_t randHoleX;
    uint32_t randHoleY;
    uint32_t randObstacle;

    uint32_t golfBallYOne = 144;
    uint32_t golfBallYTwo = 126;

    uint32_t repeat = 1;
    uint32_t golfDone = 0;

    uint32_t z = 0;

void makeGolfBackGround(void){

    ST7735_DrawBitmap(0, 160, grass, 16, 20);
    ST7735_DrawBitmap(16, 160, grass, 16, 20);
    ST7735_DrawBitmap(32, 160, grass, 16, 20);
    ST7735_DrawBitmap(48, 160, grass, 16, 20);
    ST7735_DrawBitmap(64, 160, grass, 16, 20);
    ST7735_DrawBitmap(80, 160, grass, 16, 20);
    ST7735_DrawBitmap(96, 160, grass, 16, 20);
    ST7735_DrawBitmap(112, 160, grass, 16, 20);
    ST7735_DrawBitmap(128, 160, grass, 16, 20);

    // Next row, y = 160 - 20 = 140
    ST7735_DrawBitmap(0, 140, grass, 16, 20);
    ST7735_DrawBitmap(16, 140, grass, 16, 20);
    ST7735_DrawBitmap(32, 140, grass, 16, 20);
    ST7735_DrawBitmap(48, 140, grass, 16, 20);
    ST7735_DrawBitmap(64, 140, grass, 16, 20);
    ST7735_DrawBitmap(80, 140, grass, 16, 20);
    ST7735_DrawBitmap(96, 140, grass, 16, 20);
    ST7735_DrawBitmap(112, 140, grass, 16, 20);
    ST7735_DrawBitmap(128, 140, grass, 16, 20);

    // Continue subtracting 20 from y for each new row
    // y = 140 - 20 = 120
    ST7735_DrawBitmap(0, 120, grass, 16, 20);
    ST7735_DrawBitmap(16, 120, grass, 16, 20);
    ST7735_DrawBitmap(32, 120, grass, 16, 20);
    ST7735_DrawBitmap(48, 120, grass, 16, 20);
    ST7735_DrawBitmap(64, 120, grass, 16, 20);
    ST7735_DrawBitmap(80, 120, grass, 16, 20);
    ST7735_DrawBitmap(96, 120, grass, 16, 20);
    ST7735_DrawBitmap(112, 120, grass, 16, 20);
    ST7735_DrawBitmap(128, 120, grass, 16, 20);

    // y = 120 - 20 = 100
    ST7735_DrawBitmap(0, 100, grass, 16, 20);
    ST7735_DrawBitmap(16, 100, grass, 16, 20);
    ST7735_DrawBitmap(32, 100, grass, 16, 20);
    ST7735_DrawBitmap(48, 100, grass, 16, 20);
    ST7735_DrawBitmap(64, 100, grass, 16, 20);
    ST7735_DrawBitmap(80, 100, grass, 16, 20);
    ST7735_DrawBitmap(96, 100, grass, 16, 20);
    ST7735_DrawBitmap(112, 100, grass, 16, 20);
    ST7735_DrawBitmap(128, 100, grass, 16, 20);

    // y = 100 - 20 = 80
    ST7735_DrawBitmap(0, 80, grass, 16, 20);
    ST7735_DrawBitmap(16, 80, grass, 16, 20);
    ST7735_DrawBitmap(32, 80, grass, 16, 20);
    ST7735_DrawBitmap(48, 80, grass, 16, 20);
    ST7735_DrawBitmap(64, 80, grass, 16, 20);
    ST7735_DrawBitmap(80, 80, grass, 16, 20);
    ST7735_DrawBitmap(96, 80, grass, 16, 20);
    ST7735_DrawBitmap(112, 80, grass, 16, 20);
    ST7735_DrawBitmap(128, 80, grass, 16, 20);

    // y = 80 - 20 = 60
    ST7735_DrawBitmap(0, 60, grass, 16, 20);
    ST7735_DrawBitmap(16, 60, grass, 16, 20);
    ST7735_DrawBitmap(32, 60, grass, 16, 20);
    ST7735_DrawBitmap(48, 60, grass, 16, 20);
    ST7735_DrawBitmap(64, 60, grass, 16, 20);
    ST7735_DrawBitmap(80, 60, grass, 16, 20);
    ST7735_DrawBitmap(96, 60, grass, 16, 20);
    ST7735_DrawBitmap(112, 60, grass, 16, 20);
    ST7735_DrawBitmap(128, 60, grass, 16, 20);

    // y = 60 - 20 = 40
    ST7735_DrawBitmap(0, 40, grass, 16, 20);
    ST7735_DrawBitmap(16, 40, grass, 16, 20);
    ST7735_DrawBitmap(32, 40, grass, 16, 20);
    ST7735_DrawBitmap(48, 40, grass, 16, 20);
    ST7735_DrawBitmap(64, 40, grass, 16, 20);
    ST7735_DrawBitmap(80, 40, grass, 16, 20);
    ST7735_DrawBitmap(96, 40, grass, 16, 20);
    ST7735_DrawBitmap(112, 40, grass, 16, 20);
    ST7735_DrawBitmap(128, 40, grass, 16, 20);

    // y = 40 - 20 = 20
    ST7735_DrawBitmap(0, 20, grass, 16, 20);
    ST7735_DrawBitmap(16, 20, grass, 16, 20);
    ST7735_DrawBitmap(32, 20, grass, 16, 20);
    ST7735_DrawBitmap(48, 20, grass, 16, 20);
    ST7735_DrawBitmap(64, 20, grass, 16, 20);
    ST7735_DrawBitmap(80, 20, grass, 16, 20);
    ST7735_DrawBitmap(96, 20, grass, 16, 20);
    ST7735_DrawBitmap(112, 20, grass, 16, 20);
    ST7735_DrawBitmap(128, 20, grass, 16, 20);

    ST7735_DrawBitmap(spot-5, spot2, golf, 10, 10);
    ST7735_DrawBitmap(randHoleX, randHoleY, hole, 15, 15);
    ST7735_DrawBitmap(randObstacle, 85, obstacle, 55, 15);

}

void makeArrowBackGround(void){
    ST7735_FillScreen(ST7735_BLACK);
    ST7735_DrawBitmap(spot-5, 155, bow, 20, 8);
    ST7735_DrawBitmap(15, 18, target, 98, 18);
}

void makeBackGround(void) {
    ST7735_FillScreen(ST7735_BLACK);
        ST7735_DrawBitmap(15, 159, background, 98, 160);
        ST7735_DrawBitmap(38, 20, pin, 5, 18);
        ST7735_DrawBitmap(50, 20, pin, 5, 18);
        ST7735_DrawBitmap(62, 20, pin, 5, 18);
        ST7735_DrawBitmap(74, 20, pin, 5, 18);
        ST7735_DrawBitmap(86, 20, pin, 5, 18);

        ST7735_DrawBitmap(44, 29, pin, 5, 18);
        ST7735_DrawBitmap(56, 29, pin, 5, 18);
        ST7735_DrawBitmap(68, 29, pin, 5, 18);
        ST7735_DrawBitmap(80, 29, pin, 5, 18);

        ST7735_DrawBitmap(50, 38, pin, 5, 18);
        ST7735_DrawBitmap(62, 38, pin, 5, 18);
        ST7735_DrawBitmap(74, 38, pin, 5, 18);

        ST7735_DrawBitmap(56, 47, pin, 5, 18);
        ST7735_DrawBitmap(68, 47, pin, 5, 18);

        ST7735_DrawBitmap(62, 56, pin, 5, 18);


        //ST7735_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
        ST7735_DrawBitmap(spot-5, 155, bball, 10, 10);
}

void pinfall15(void) {
    ST7735_FillScreen(ST7735_BLACK);

            ST7735_DrawBitmap(15, 159, background, 98, 160);
            ST7735_DrawBitmap(x, y, bball, 10, 10);
            ST7735_DrawBitmap(38, 20, pin30, 9, 18);
            ST7735_DrawBitmap(50, 20, pin30, 9, 18);
            ST7735_DrawBitmap(62, 20, pin30, 9, 18);
            ST7735_DrawBitmap(74, 20, pin30, 9, 18);
            ST7735_DrawBitmap(86, 20, pin30, 9, 18);

            ST7735_DrawBitmap(44, 29, pin30, 9, 18);
            ST7735_DrawBitmap(56, 29, pin30, 9, 18);
            ST7735_DrawBitmap(68, 29, pin30, 9, 18);
            ST7735_DrawBitmap(80, 29, pin30, 9, 18);

            ST7735_DrawBitmap(50, 38, pin30, 9, 18);
            ST7735_DrawBitmap(62, 38, pin30, 9, 18);
            ST7735_DrawBitmap(74, 38, pin30, 9, 18);

            ST7735_DrawBitmap(56, 47, pin30, 9, 18);
            ST7735_DrawBitmap(68, 47, pin30, 9, 18);

            ST7735_DrawBitmap(62, 56, pin30, 9, 18);

            Clock_Delay1ms(400);

            ST7735_DrawBitmap(15, 159, background, 98, 160);
                        ST7735_DrawBitmap(x, y, bball, 10, 10);
                        ST7735_DrawBitmap(38, 20, pin60, 13, 18);
                        ST7735_DrawBitmap(50, 20, pin60, 13, 18);
                        ST7735_DrawBitmap(62, 20, pin60, 13, 18);
                        ST7735_DrawBitmap(74, 20, pin60, 13, 18);
                        ST7735_DrawBitmap(86, 20, pin60, 13, 18);

                        ST7735_DrawBitmap(44, 29, pin60, 13, 18);
                        ST7735_DrawBitmap(56, 29, pin60, 13, 18);
                        ST7735_DrawBitmap(68, 29, pin60, 13, 18);
                        ST7735_DrawBitmap(80, 29, pin60, 13, 18);

                        ST7735_DrawBitmap(50, 38, pin60, 13, 18);
                        ST7735_DrawBitmap(62, 38, pin60, 13, 18);
                        ST7735_DrawBitmap(74, 38, pin60, 13, 18);

                        ST7735_DrawBitmap(56, 47, pin60, 13, 18);
                        ST7735_DrawBitmap(68, 47, pin60, 13, 18);

                        ST7735_DrawBitmap(62, 56, pin60, 13, 18);

                        Clock_Delay1ms(400);

                                    ST7735_DrawBitmap(15, 159, background, 98, 160);
                                                ST7735_DrawBitmap(x, y, bball, 10, 10);
                                                ST7735_DrawBitmap(38, 20, pin90, 18, 8);
                                                ST7735_DrawBitmap(50, 20, pin90, 18, 8);
                                                ST7735_DrawBitmap(62, 20, pin90, 18, 8);
                                                ST7735_DrawBitmap(74, 20, pin90, 18, 8);
                                                ST7735_DrawBitmap(86, 20, pin90, 18, 8);

                                                ST7735_DrawBitmap(44, 29, pin90, 18, 8);
                                                ST7735_DrawBitmap(56, 29, pin90, 18, 8);
                                                ST7735_DrawBitmap(68, 29, pin90, 18, 8);
                                                ST7735_DrawBitmap(80, 29, pin90, 18, 8);

                                                ST7735_DrawBitmap(50, 38, pin90, 18, 8);
                                                ST7735_DrawBitmap(62, 38, pin90, 18, 8);
                                                ST7735_DrawBitmap(74, 38, pin90, 18, 8);

                                                ST7735_DrawBitmap(56, 47, pin90, 18, 8);
                                                ST7735_DrawBitmap(68, 47, pin90, 18, 8);

                                                ST7735_DrawBitmap(62, 56, pin90, 18, 8);
            //ST7735_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)

}

void pinfall12(void) {
    ST7735_FillScreen(ST7735_BLACK);

                ST7735_DrawBitmap(15, 159, background, 98, 160);
                ST7735_DrawBitmap(x, y, bball, 10, 10);
                ST7735_DrawBitmap(38, 20, pin, 5, 18);
                        ST7735_DrawBitmap(50, 20, pin, 5, 18);
                        ST7735_DrawBitmap(62, 20, pin, 5, 18);
                ST7735_DrawBitmap(74, 20, pin30, 9, 18);
                ST7735_DrawBitmap(86, 20, pin30, 9, 18);

                ST7735_DrawBitmap(44, 29, pin30, 9, 18);
                ST7735_DrawBitmap(56, 29, pin30, 9, 18);
                ST7735_DrawBitmap(68, 29, pin30, 9, 18);
                ST7735_DrawBitmap(80, 29, pin30, 9, 18);

                ST7735_DrawBitmap(50, 38, pin30, 9, 18);
                ST7735_DrawBitmap(62, 38, pin30, 9, 18);
                ST7735_DrawBitmap(74, 38, pin30, 9, 18);

                ST7735_DrawBitmap(56, 47, pin30, 9, 18);
                ST7735_DrawBitmap(68, 47, pin30, 9, 18);

                ST7735_DrawBitmap(62, 56, pin30, 9, 18);

                Clock_Delay1ms(400);

                ST7735_DrawBitmap(15, 159, background, 98, 160);
                ST7735_DrawBitmap(x, y, bball, 10, 10);
                ST7735_DrawBitmap(38, 20, pin, 5, 18);
                        ST7735_DrawBitmap(50, 20, pin, 5, 18);
                        ST7735_DrawBitmap(62, 20, pin, 5, 18);
                ST7735_DrawBitmap(74, 20, pin60, 13, 18);
                ST7735_DrawBitmap(86, 20, pin60, 13, 18);

                ST7735_DrawBitmap(44, 29, pin60, 13, 18);
                ST7735_DrawBitmap(56, 29, pin60, 13, 18);
                ST7735_DrawBitmap(68, 29, pin60, 13, 18);
                ST7735_DrawBitmap(80, 29, pin60, 13, 18);

                ST7735_DrawBitmap(50, 38, pin60, 13, 18);
                ST7735_DrawBitmap(62, 38, pin60, 13, 18);
                ST7735_DrawBitmap(74, 38, pin60, 13, 18);

                ST7735_DrawBitmap(56, 47, pin60, 13, 18);
                ST7735_DrawBitmap(68, 47, pin60, 13, 18);

                ST7735_DrawBitmap(62, 56, pin60, 13, 18);

                Clock_Delay1ms(400);

                ST7735_DrawBitmap(15, 159, background, 98, 160);
                ST7735_DrawBitmap(x, y, bball, 10, 10);
                ST7735_DrawBitmap(38, 20, pin, 5, 18);
                        ST7735_DrawBitmap(50, 20, pin, 5, 18);
                        ST7735_DrawBitmap(62, 20, pin, 5, 18);
                ST7735_DrawBitmap(74, 20, pin90, 18, 8);
                ST7735_DrawBitmap(86, 20, pin90, 18, 8);

                ST7735_DrawBitmap(44, 29, pin90, 18, 8);
                ST7735_DrawBitmap(56, 29, pin90, 18, 8);
                ST7735_DrawBitmap(68, 29, pin90, 18, 8);
                ST7735_DrawBitmap(80, 29, pin90, 18, 8);

                ST7735_DrawBitmap(50, 38, pin90, 18, 8);
                ST7735_DrawBitmap(62, 38, pin90, 18, 8);
                ST7735_DrawBitmap(74, 38, pin90, 18, 8);

                ST7735_DrawBitmap(56, 47, pin90, 18, 8);
                ST7735_DrawBitmap(68, 47, pin90, 18, 8);

                ST7735_DrawBitmap(62, 56, pin90, 18, 8);
}

void pinfall9(void) {
    ST7735_FillScreen(ST7735_BLACK);

                ST7735_DrawBitmap(15, 159, background, 98, 160);
                ST7735_DrawBitmap(x, y, bball, 10, 10);
                ST7735_DrawBitmap(38, 20, pin, 5, 18);
                        ST7735_DrawBitmap(50, 20, pin, 5, 18);
                        ST7735_DrawBitmap(62, 20, pin, 5, 18);
                        ST7735_DrawBitmap(74, 20, pin, 5, 18);
                        ST7735_DrawBitmap(86, 20, pin, 5, 18);

                ST7735_DrawBitmap(44, 29, pin30, 9, 18);
                ST7735_DrawBitmap(56, 29, pin30, 9, 18);
                ST7735_DrawBitmap(68, 29, pin30, 9, 18);
                ST7735_DrawBitmap(80, 29, pin30, 9, 18);

                ST7735_DrawBitmap(50, 38, pin30, 9, 18);
                ST7735_DrawBitmap(62, 38, pin30, 9, 18);
                ST7735_DrawBitmap(74, 38, pin30, 9, 18);

                ST7735_DrawBitmap(56, 47, pin30, 9, 18);
                ST7735_DrawBitmap(68, 47, pin30, 9, 18);

                ST7735_DrawBitmap(62, 56, pin, 5, 18);

                Clock_Delay1ms(400);

                ST7735_DrawBitmap(15, 159, background, 98, 160);
                ST7735_DrawBitmap(x, y, bball, 10, 10);
                ST7735_DrawBitmap(38, 20, pin, 5, 18);
                        ST7735_DrawBitmap(50, 20, pin, 5, 18);
                        ST7735_DrawBitmap(62, 20, pin, 5, 18);
                        ST7735_DrawBitmap(74, 20, pin, 5, 18);
                        ST7735_DrawBitmap(86, 20, pin, 5, 18);

                ST7735_DrawBitmap(44, 29, pin60, 13, 18);
                ST7735_DrawBitmap(56, 29, pin60, 13, 18);
                ST7735_DrawBitmap(68, 29, pin60, 13, 18);
                ST7735_DrawBitmap(80, 29, pin60, 13, 18);

                ST7735_DrawBitmap(50, 38, pin60, 13, 18);
                ST7735_DrawBitmap(62, 38, pin60, 13, 18);
                ST7735_DrawBitmap(74, 38, pin60, 13, 18);

                ST7735_DrawBitmap(56, 47, pin60, 13, 18);
                ST7735_DrawBitmap(68, 47, pin60, 13, 18);

                ST7735_DrawBitmap(62, 56, pin, 5, 18);

                Clock_Delay1ms(400);

                ST7735_DrawBitmap(15, 159, background, 98, 160);
                ST7735_DrawBitmap(x, y, bball, 10, 10);
                ST7735_DrawBitmap(38, 20, pin, 5, 18);
                        ST7735_DrawBitmap(50, 20, pin, 5, 18);
                        ST7735_DrawBitmap(62, 20, pin, 5, 18);
                        ST7735_DrawBitmap(74, 20, pin, 5, 18);
                        ST7735_DrawBitmap(86, 20, pin, 5, 18);

                ST7735_DrawBitmap(44, 29, pin90, 18, 8);
                ST7735_DrawBitmap(56, 29, pin90, 18, 8);
                ST7735_DrawBitmap(68, 29, pin90, 18, 8);
                ST7735_DrawBitmap(80, 29, pin90, 18, 8);

                ST7735_DrawBitmap(50, 38, pin90, 18, 8);
                ST7735_DrawBitmap(62, 38, pin90, 18, 8);
                ST7735_DrawBitmap(74, 38, pin90, 18, 8);

                ST7735_DrawBitmap(56, 47, pin90, 18, 8);
                ST7735_DrawBitmap(68, 47, pin90, 18, 8);

                ST7735_DrawBitmap(62, 56, pin, 5, 18);
}

void pinfall3(void) {
    if(x <= 64){
        ST7735_FillScreen(ST7735_BLACK);
        ST7735_DrawBitmap(15, 159, background, 98, 160);
        ST7735_DrawBitmap(x, y, bball, 10, 10);
        ST7735_DrawBitmap(38, 20, pin30, 9, 18);
        ST7735_DrawBitmap(50, 20, pin30, 9, 18);
        ST7735_DrawBitmap(62, 20, pin, 5, 18);
        ST7735_DrawBitmap(74, 20, pin, 5, 18);
        ST7735_DrawBitmap(86, 20, pin, 5, 18);

        ST7735_DrawBitmap(44, 29, pin30, 9, 18);
        ST7735_DrawBitmap(56, 29, pin, 5, 18);
        ST7735_DrawBitmap(68, 29, pin, 5, 18);
        ST7735_DrawBitmap(80, 29, pin, 5, 18);

        ST7735_DrawBitmap(50, 38, pin, 5, 18);
        ST7735_DrawBitmap(62, 38, pin, 5, 18);
        ST7735_DrawBitmap(74, 38, pin, 5, 18);

        ST7735_DrawBitmap(56, 47, pin, 5, 18);
        ST7735_DrawBitmap(68, 47, pin, 5, 18);

        ST7735_DrawBitmap(62, 56, pin, 5, 18);

        Clock_Delay1ms(400);


        ST7735_DrawBitmap(15, 159, background, 98, 160);
        ST7735_DrawBitmap(x, y, bball, 10, 10);
        ST7735_DrawBitmap(38, 20, pin60, 13, 18);
        ST7735_DrawBitmap(38, 20, pin60, 13, 18);
        ST7735_DrawBitmap(50, 20, pin, 5, 18);
        ST7735_DrawBitmap(62, 20, pin, 5, 18);
        ST7735_DrawBitmap(74, 20, pin, 5, 18);
        ST7735_DrawBitmap(86, 20, pin, 5, 18);

        ST7735_DrawBitmap(44, 29, pin60, 13, 18);
        ST7735_DrawBitmap(56, 29, pin, 5, 18);
        ST7735_DrawBitmap(68, 29, pin, 5, 18);
        ST7735_DrawBitmap(80, 29, pin, 5, 18);

        ST7735_DrawBitmap(50, 38, pin, 5, 18);
        ST7735_DrawBitmap(62, 38, pin, 5, 18);
        ST7735_DrawBitmap(74, 38, pin, 5, 18);

        ST7735_DrawBitmap(56, 47, pin, 5, 18);
        ST7735_DrawBitmap(68, 47, pin, 5, 18);

        ST7735_DrawBitmap(62, 56, pin, 5, 18);

        Clock_Delay1ms(400);


        ST7735_DrawBitmap(15, 159, background, 98, 160);
        ST7735_DrawBitmap(x, y, bball, 10, 10);
        ST7735_DrawBitmap(38, 20, pin90, 18, 8);
        ST7735_DrawBitmap(50, 20, pin90, 18, 8);
        ST7735_DrawBitmap(62, 20, pin, 5, 18);
        ST7735_DrawBitmap(74, 20, pin, 5, 18);
        ST7735_DrawBitmap(86, 20, pin, 5, 18);

        ST7735_DrawBitmap(44, 29, pin90, 18, 8);
        ST7735_DrawBitmap(56, 29, pin, 5, 18);
        ST7735_DrawBitmap(68, 29, pin, 5, 18);
        ST7735_DrawBitmap(80, 29, pin, 5, 18);

        ST7735_DrawBitmap(50, 38, pin, 5, 18);
        ST7735_DrawBitmap(62, 38, pin, 5, 18);
        ST7735_DrawBitmap(74, 38, pin, 5, 18);

        ST7735_DrawBitmap(56, 47, pin, 5, 18);
        ST7735_DrawBitmap(68, 47, pin, 5, 18);

        ST7735_DrawBitmap(62, 56, pin, 5, 18);


    }
    else{
        ST7735_FillScreen(ST7735_BLACK);
        ST7735_DrawBitmap(15, 159, background, 98, 160);
        ST7735_DrawBitmap(x, y, bball, 10, 10);
        ST7735_DrawBitmap(38, 20, pin, 5, 18);
        ST7735_DrawBitmap(50, 20, pin, 5, 18);
        ST7735_DrawBitmap(62, 20, pin, 5, 18);
        ST7735_DrawBitmap(74, 20, pin30, 9, 18);
        ST7735_DrawBitmap(86, 20, pin30, 9, 18);

        ST7735_DrawBitmap(44, 29, pin, 5, 18);
        ST7735_DrawBitmap(56, 29, pin, 5, 18);
        ST7735_DrawBitmap(68, 29, pin, 5, 18);
        ST7735_DrawBitmap(80, 29, pin30, 9, 18);

        ST7735_DrawBitmap(50, 38, pin, 5, 18);
        ST7735_DrawBitmap(62, 38, pin, 5, 18);
        ST7735_DrawBitmap(74, 38, pin, 5, 18);

        ST7735_DrawBitmap(56, 47, pin, 5, 18);
        ST7735_DrawBitmap(68, 47, pin, 5, 18);

        ST7735_DrawBitmap(62, 56, pin, 5, 18);

        Clock_Delay1ms(400);


        ST7735_DrawBitmap(15, 159, background, 98, 160);
        ST7735_DrawBitmap(x, y, bball, 10, 10);
        ST7735_DrawBitmap(38, 20, pin, 5, 18);
        ST7735_DrawBitmap(50, 20, pin, 5, 18);
        ST7735_DrawBitmap(62, 20, pin, 5, 18);
        ST7735_DrawBitmap(74, 20, pin60, 13, 18);
        ST7735_DrawBitmap(86, 20, pin60, 13, 18);

        ST7735_DrawBitmap(44, 29, pin, 5, 18);
        ST7735_DrawBitmap(56, 29, pin, 5, 18);
        ST7735_DrawBitmap(68, 29, pin, 5, 18);
        ST7735_DrawBitmap(80, 29, pin60, 13, 18);

        ST7735_DrawBitmap(50, 38, pin, 5, 18);
        ST7735_DrawBitmap(62, 38, pin, 5, 18);
        ST7735_DrawBitmap(74, 38, pin, 5, 18);

        ST7735_DrawBitmap(56, 47, pin, 5, 18);
        ST7735_DrawBitmap(68, 47, pin, 5, 18);

        ST7735_DrawBitmap(62, 56, pin, 5, 18);

        Clock_Delay1ms(400);


        ST7735_DrawBitmap(15, 159, background, 98, 160);
        ST7735_DrawBitmap(x, y, bball, 10, 10);
        ST7735_DrawBitmap(38, 20, pin, 5, 18);
        ST7735_DrawBitmap(50, 20, pin, 5, 18);
        ST7735_DrawBitmap(62, 20, pin, 5, 18);
        ST7735_DrawBitmap(74, 20, pin90, 18, 8);
        ST7735_DrawBitmap(86, 20, pin90, 18, 8);

        ST7735_DrawBitmap(44, 29, pin, 5, 18);
        ST7735_DrawBitmap(56, 29, pin, 5, 18);
        ST7735_DrawBitmap(68, 29, pin, 5, 18);
        ST7735_DrawBitmap(80, 29, pin90, 18, 8);

        ST7735_DrawBitmap(50, 38, pin, 5, 18);
        ST7735_DrawBitmap(62, 38, pin, 5, 18);
        ST7735_DrawBitmap(74, 38, pin, 5, 18);

        ST7735_DrawBitmap(56, 47, pin, 5, 18);
        ST7735_DrawBitmap(68, 47, pin, 5, 18);

        ST7735_DrawBitmap(62, 56, pin, 5, 18);
    }
}

void pinfall1(void) {
    if(x <= 64){
        ST7735_FillScreen(ST7735_BLACK);
        ST7735_DrawBitmap(15, 159, background, 98, 160);
        ST7735_DrawBitmap(x, y, bball, 10, 10);
        ST7735_DrawBitmap(38, 20, pin30, 9, 18);
        ST7735_DrawBitmap(50, 20, pin, 5, 18);
        ST7735_DrawBitmap(62, 20, pin, 5, 18);
        ST7735_DrawBitmap(74, 20, pin, 5, 18);
        ST7735_DrawBitmap(86, 20, pin, 5, 18);

        ST7735_DrawBitmap(44, 29, pin, 5, 18);
        ST7735_DrawBitmap(56, 29, pin, 5, 18);
        ST7735_DrawBitmap(68, 29, pin, 5, 18);
        ST7735_DrawBitmap(80, 29, pin, 5, 18);

        ST7735_DrawBitmap(50, 38, pin, 5, 18);
        ST7735_DrawBitmap(62, 38, pin, 5, 18);
        ST7735_DrawBitmap(74, 38, pin, 5, 18);

        ST7735_DrawBitmap(56, 47, pin, 5, 18);
        ST7735_DrawBitmap(68, 47, pin, 5, 18);

        ST7735_DrawBitmap(62, 56, pin, 5, 18);

        Clock_Delay1ms(400);


        ST7735_DrawBitmap(15, 159, background, 98, 160);
        ST7735_DrawBitmap(x, y, bball, 10, 10);
        ST7735_DrawBitmap(38, 20, pin60, 13, 18);
        ST7735_DrawBitmap(38, 20, pin, 5, 18);
        ST7735_DrawBitmap(50, 20, pin, 5, 18);
        ST7735_DrawBitmap(62, 20, pin, 5, 18);
        ST7735_DrawBitmap(74, 20, pin, 5, 18);
        ST7735_DrawBitmap(86, 20, pin, 5, 18);

        ST7735_DrawBitmap(44, 29, pin, 5, 18);
        ST7735_DrawBitmap(56, 29, pin, 5, 18);
        ST7735_DrawBitmap(68, 29, pin, 5, 18);
        ST7735_DrawBitmap(80, 29, pin, 5, 18);

        ST7735_DrawBitmap(50, 38, pin, 5, 18);
        ST7735_DrawBitmap(62, 38, pin, 5, 18);
        ST7735_DrawBitmap(74, 38, pin, 5, 18);

        ST7735_DrawBitmap(56, 47, pin, 5, 18);
        ST7735_DrawBitmap(68, 47, pin, 5, 18);

        ST7735_DrawBitmap(62, 56, pin, 5, 18);

        Clock_Delay1ms(400);


        ST7735_DrawBitmap(15, 159, background, 98, 160);
        ST7735_DrawBitmap(x, y, bball, 10, 10);
        ST7735_DrawBitmap(15, 159, background, 98, 160);
        ST7735_DrawBitmap(38, 20, pin90, 18, 8);
        ST7735_DrawBitmap(50, 20, pin, 5, 18);
        ST7735_DrawBitmap(62, 20, pin, 5, 18);
        ST7735_DrawBitmap(74, 20, pin, 5, 18);
        ST7735_DrawBitmap(86, 20, pin, 5, 18);

        ST7735_DrawBitmap(44, 29, pin, 5, 18);
        ST7735_DrawBitmap(56, 29, pin, 5, 18);
        ST7735_DrawBitmap(68, 29, pin, 5, 18);
        ST7735_DrawBitmap(80, 29, pin, 5, 18);

        ST7735_DrawBitmap(50, 38, pin, 5, 18);
        ST7735_DrawBitmap(62, 38, pin, 5, 18);
        ST7735_DrawBitmap(74, 38, pin, 5, 18);

        ST7735_DrawBitmap(56, 47, pin, 5, 18);
        ST7735_DrawBitmap(68, 47, pin, 5, 18);

        ST7735_DrawBitmap(62, 56, pin, 5, 18);


    }
    else{
        ST7735_FillScreen(ST7735_BLACK);
        ST7735_DrawBitmap(15, 159, background, 98, 160);
        ST7735_DrawBitmap(x, y, bball, 10, 10);
        ST7735_DrawBitmap(38, 20, pin, 5, 18);
        ST7735_DrawBitmap(50, 20, pin, 5, 18);
        ST7735_DrawBitmap(62, 20, pin, 5, 18);
        ST7735_DrawBitmap(74, 20, pin, 5, 18);
        ST7735_DrawBitmap(86, 20, pin30, 9, 18);

        ST7735_DrawBitmap(44, 29, pin, 5, 18);
        ST7735_DrawBitmap(56, 29, pin, 5, 18);
        ST7735_DrawBitmap(68, 29, pin, 5, 18);
        ST7735_DrawBitmap(80, 29, pin, 5, 18);

        ST7735_DrawBitmap(50, 38, pin, 5, 18);
        ST7735_DrawBitmap(62, 38, pin, 5, 18);
        ST7735_DrawBitmap(74, 38, pin, 5, 18);

        ST7735_DrawBitmap(56, 47, pin, 5, 18);
        ST7735_DrawBitmap(68, 47, pin, 5, 18);

        ST7735_DrawBitmap(62, 56, pin, 5, 18);

        Clock_Delay1ms(400);


        ST7735_DrawBitmap(15, 159, background, 98, 160);
        ST7735_DrawBitmap(x, y, bball, 10, 10);
        ST7735_DrawBitmap(38, 20, pin, 5, 18);
        ST7735_DrawBitmap(50, 20, pin, 5, 18);
        ST7735_DrawBitmap(62, 20, pin, 5, 18);
        ST7735_DrawBitmap(74, 20, pin, 5, 18);
        ST7735_DrawBitmap(86, 20, pin60, 13, 18);

        ST7735_DrawBitmap(44, 29, pin, 5, 18);
        ST7735_DrawBitmap(56, 29, pin, 5, 18);
        ST7735_DrawBitmap(68, 29, pin, 5, 18);
        ST7735_DrawBitmap(80, 29, pin, 5, 18);

        ST7735_DrawBitmap(50, 38, pin, 5, 18);
        ST7735_DrawBitmap(62, 38, pin, 5, 18);
        ST7735_DrawBitmap(74, 38, pin, 5, 18);

        ST7735_DrawBitmap(56, 47, pin, 5, 18);
        ST7735_DrawBitmap(68, 47, pin, 5, 18);

        ST7735_DrawBitmap(62, 56, pin, 5, 18);

        Clock_Delay1ms(400);


        ST7735_DrawBitmap(15, 159, background, 98, 160);
        ST7735_DrawBitmap(x, y, bball, 10, 10);
        ST7735_DrawBitmap(38, 20, pin, 5, 18);
        ST7735_DrawBitmap(50, 20, pin, 5, 18);
        ST7735_DrawBitmap(62, 20, pin, 5, 18);
        ST7735_DrawBitmap(74, 20, pin, 5, 18);
        ST7735_DrawBitmap(86, 20, pin90, 18, 8);

        ST7735_DrawBitmap(44, 29, pin, 5, 18);
        ST7735_DrawBitmap(56, 29, pin, 5, 18);
        ST7735_DrawBitmap(68, 29, pin, 5, 18);
        ST7735_DrawBitmap(80, 29, pin, 5, 18);

        ST7735_DrawBitmap(50, 38, pin, 5, 18);
        ST7735_DrawBitmap(62, 38, pin, 5, 18);
        ST7735_DrawBitmap(74, 38, pin, 5, 18);

        ST7735_DrawBitmap(56, 47, pin, 5, 18);
        ST7735_DrawBitmap(68, 47, pin, 5, 18);

        ST7735_DrawBitmap(62, 56, pin, 5, 18);
    }
}


uint32_t checkPins(uint32_t x2, uint32_t y2, uint32_t x1, uint32_t y1){
    uint32_t squareDistance = ((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2));

    // Define the minimum threshold value for collision detection
    uint32_t minThreshold = 10; // Minimum threshold value set to 14 pixels

    // Compare the square distance to the square of the minimum threshold value to check for collision
    if (squareDistance <= (minThreshold * minThreshold)) {
        // Collision detected between the bowling ball and the bowling pin
        // Handle collision logic here
        return 1;
    }

    return 0;
}
uint32_t dontPrint = 0;

void moveGolf(int32_t dx, int32_t dy){
    x = spot - 5;
    y = spot2;
    uint32_t countY = 0;
    while(countY <= 30){
        if(x >= 118){
            dx *= -1;

        }
        else if(x <= 0){
            dx *= -1;
        }
        else if(y <= 10){
            dy *= -1;
        }
        else if(y >= 160){
            dy *= -1;
        }
        // ST7735_DrawBitmap(randObstacle, 85, obstacle, 55, 15); 70, 72    85, 83
        else if(x >= (randObstacle) && x <= (randObstacle + 55) && ((y >=69 && y <= 75) || (y <=97 && y >= 91))){
            dy *= -1;
        }
        /*else if((x <= (randObstacle) || x >= (randObstacle + 55)) && (y >= 85 && y <= 100)) {
            dx *= -1;
        }*/
        else if(checkPins(randHoleX, randHoleY, x, y)){
            repeat = 1;
            golfDone++;
            if(player == 1){
              player = 2;
            }
            else if(player == 2){
                  player = 1;
              }
            break;
        }

        ST7735_DrawBitmap(x, y, golfcoverr, 10, 10);
        x += dx;
        y -= dy;
        ST7735_DrawBitmap(x, y, golf, 10, 10);
        Clock_Delay1ms(120);
        countY++;
        spot = x;
        spot2 = y;
    }
}

void moveArrow(int32_t dx, int32_t dy){
    x = spot - 5;
    y = 155;

    while(1){
        if(y <= 21){
            if(((x >= 15) && (x < 26)) || ((x >= 103) && (x < 114))){
                if(player == 1){
                        score1 += 1;
                    }
                else if(player == 2){
                        score2 += 1;
                    }
                ST7735_SetCursor(0, 1);
                ST7735_OutString("+1");
                Clock_Delay1ms(2000);
                break;
            }
            else if(((x >= 26) && (x < 37)) || ((x >= 92) && (x < 103))){
                if(player == 1){
                        score1 += 3;
                    }
                else if(player == 2){
                        score2 += 3;
                    }
                ST7735_SetCursor(0, 1);
                ST7735_OutString("+3");
                Clock_Delay1ms(2000);
                break;
            }
            else if(((x >= 37) && (x < 48)) || ((x >= 81) && (x < 92))){
                if(player == 1){
                        score1 += 9;
                    }
                else if(player == 2){
                        score2 += 9;
                    }
                ST7735_SetCursor(0, 1);
                ST7735_OutString("+9");
                Clock_Delay1ms(2000);
                break;
            }
            else if(((x >= 48) && (x < 59)) || ((x >= 70) && (x < 81))){
                if(player == 1){
                        score1 += 12;
                    }
                else if(player == 2){
                        score2 += 12;
                    }
                ST7735_SetCursor(0, 1);
                ST7735_OutString("+12");
                Clock_Delay1ms(2000);
                break;
            }
            else if(((x >= 59) && (x < 70))){
                if(player == 1){
                        score1 += 15;
                    }
                else if(player == 2){
                        score2 += 15;
                    }
                ST7735_SetCursor(0, 1);
                ST7735_OutString("+15");
                Clock_Delay1ms(2000);
                break;
            }
            else{
                ST7735_SetCursor(0, 1);
                ST7735_OutString("+0");
                Clock_Delay1ms(2000);
                break;
            }
        }
        if(dontPrint >= 2) {
            ST7735_DrawBitmap(x, y, coverArrow, 6, 15);
        }
        x += dx;
        y -= dy;
        if(dontPrint >= 2) {
            ST7735_DrawBitmap(x, y, arrow, 6, 15);
        }
        dontPrint++;
        Clock_Delay1ms(120);
    }
}


void moveBowlingBall(int32_t dx, int32_t dy){
    x = spot - 5;
    y = 155;

    uint32_t pinsKnocked = 0;
    while(1){
        if(x <= 15 || x >= 113 || y <= 15){
            pinsKnocked = 0;
            ST7735_SetCursor(0, 1);
            ST7735_OutString("+0");
            Clock_Delay1ms(2000);
            break;
        }
        else if(checkPins(62, 56, x, y)){
            __enable_irq();
            Sound_Bowl();
            Clock_Delay1ms(1000);
            __disable_irq();
            pinfall15();
            ST7735_SetCursor(0, 1);
            ST7735_OutString("+15");
            if(player == 1){
                    score1 += 15;
                }
            else if(player == 2){
                    score2 += 15;
                }
            Clock_Delay1ms(2000);
            break;
        }
        else if(checkPins(56, 47, x, y) || checkPins(68, 47, x, y)){
            __enable_irq();
                        Sound_Bowl();
                        Clock_Delay1ms(1000);
                        __disable_irq();
            pinfall12();
            ST7735_SetCursor(0, 1);
            ST7735_OutString("+12");
            if(player == 1){
                    score1 += 12;
                }
                else if(player == 2){
                        score2 += 12;
                    }
            Clock_Delay1ms(2000);
            break;
        }
        else if(checkPins(50, 38, x, y) || checkPins(62, 38, x, y) || checkPins(74, 38, x, y)){
            __enable_irq();
                        Sound_Bowl();
                        Clock_Delay1ms(1000);
                        __disable_irq();
            pinfall9();
            ST7735_SetCursor(0, 1);
                        ST7735_OutString("+9");
                        if(player == 1){
                                score1 += 9;
                            }
                            else if(player == 2){
                                    score2 += 9;
                                }
                        Clock_Delay1ms(2000);
            break;
        }
        else if(checkPins(44, 29, x, y) || checkPins(56, 29, x, y) || checkPins(68, 29, x, y) || checkPins(80, 29, x, y)){
            __enable_irq();
                        Sound_Bowl();
                        Clock_Delay1ms(1000);
                        __disable_irq();
            pinfall3();
            ST7735_SetCursor(0, 1);
                        ST7735_OutString("+3");
                        if(player == 1){
                                score1 += 3;
                            }
                            else if(player == 2){
                                    score2 += 3;
                                }
                        Clock_Delay1ms(2000);
            break;
       }
        else if(checkPins(38, 20, x, y) || checkPins(50, 20, x, y) || checkPins(62, 20, x, y) || checkPins(74, 20, x, y) || checkPins(86, 20, x, y)){
            __enable_irq();
                        Sound_Bowl();
                        Clock_Delay1ms(1000);
                        __disable_irq();
            pinfall1();
            ST7735_SetCursor(0, 1);
            ST7735_OutString("+1");
            Clock_Delay1ms(2000);
            if(player == 1){
                    score1 += 1;
                }
                else if(player == 2){
                        score2 += 1;
                    }
            break;
       }

        ST7735_DrawBitmap(x, y, ballleftover, 10, 10);
        x += dx;
        y -= dy;
        ST7735_DrawBitmap(x, y, bball, 10, 10);
        Clock_Delay1ms(120);
    }

}





uint32_t thisOne = 0;


void TIMG12_IRQHandler(void){uint32_t pos,msg;
  if((TIMG12->CPU_INT.IIDX) == 1){ // this will acknowledge
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    data = ADCin();

    //arrowend = Convert(data);
    arrowend = 15 + (data * 98) / 4095;

    /*if(data < 20) {
        arrowend = ADCin() << 1;
    } else {
        arrowend = ((ADCin() >> 2) + 80);
    }*/

    //ST7735_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
    if(gameType == 1 || gameType == 2){
        ST7735_Line(spot, 144, arrowend, 126, 0xFF);
    }
    if(gameType == 3){
        ST7735_Line(spot, spot2 - 10, arrowend, spot2 - 20, 0xFF);
    }
    ST7735_FillScreen(ST7735_BLACK);
    if(gameType == 1){
        ST7735_DrawBitmap(spot-5, 155, bball, 10, 10);
    }
    else if(gameType == 2){
        ST7735_DrawBitmap(spot-5, 155, bow, 20, 8);
    }



    if((Switch_In() & (1<<31)) != 0) {
        __disable_irq();
        ST7735_DrawBitmap(28, 117, scoreboard, 80, 46);
        ST7735_SetCursor(8, 9);
        printf("%1u", score1);
        ST7735_SetCursor(14, 9);
        printf("%1u", score2);
        Clock_Delay1ms(2000);
        __enable_irq();
    }

    if((Switch_In() & (1<<28)) != 0) {

        if(gameType == 1){
            makeBackGround();
                      ST7735_Line(spot, 144, arrowend, 126, 0xFF);
                      __disable_irq();
                      int32_t changeInX = arrowend - spot;
                      int32_t changeInY = 144 - 126;
                      //moveBowlingBall(changeInX, changeInY);
                      /*ST7735_SetCursor(0, 0);
                                printf("d=%1u.%.3u cm ", changeInX);
                                ST7735_SetCursor(0, 1);
                                printf("d=%1u.%.3u cm ", changeInY);*/
                      // Find the maximum absolute value between changeInX and changeInY
                                int32_t maxAbsValue;

                                if (changeInX < 0) {
                                    changeInX = -changeInX;
                                    thisOne = 1;
                                }
                                if (changeInY < 0) {
                                    changeInY = -changeInY;
                                }

                                if (changeInX > changeInY) {
                                    maxAbsValue = changeInX;
                                } else {
                                    maxAbsValue = changeInY;
                                }


                                if (maxAbsValue > 9) {
                                    uint32_t scalingFactor = (maxAbsValue + 8) / 9;
                                    changeInX /= scalingFactor;
                                    changeInY /= scalingFactor;
                                }
                                if(thisOne == 1) {
                                    changeInX = changeInX*-1;
                                }
                                thisOne = 0;

                      LED_On(17);
                      moveBowlingBall(changeInX, changeInY);
                      LED_Off(17);
                      wait = 0;
                      if(player == 1){
                              ST7735_SetCursor(0, 0);
                              ST7735_OutString("P1");
                              player = 2;
                          }
                          else if(player == 2){
                                  ST7735_SetCursor(0, 0);
                                  ST7735_OutString("P2");
                                  player = 1;
                              }
        }

        else if(gameType == 2){
            makeArrowBackGround();
                      ST7735_Line(spot, 144, arrowend, 126, 0xFF);
                      __disable_irq();
                      int32_t changeInX = arrowend - spot;
                      int32_t changeInY = 144 - 126;
                      //moveBowlingBall(changeInX, changeInY);
                      /*ST7735_SetCursor(0, 0);
                                printf("d=%1u.%.3u cm ", changeInX);
                                ST7735_SetCursor(0, 1);
                                printf("d=%1u.%.3u cm ", changeInY);*/
                      int32_t maxAbsValue;

                                                      if (changeInX < 0) {
                                                          changeInX = -changeInX;
                                                          thisOne = 1;
                                                      }
                                                      if (changeInY < 0) {
                                                          changeInY = -changeInY;
                                                      }

                                                      if (changeInX > changeInY) {
                                                          maxAbsValue = changeInX;
                                                      } else {
                                                          maxAbsValue = changeInY;
                                                      }


                                                      if (maxAbsValue > 9) {
                                                          uint32_t scalingFactor = (maxAbsValue + 8) / 9;
                                                          changeInX /= scalingFactor;
                                                          changeInY /= scalingFactor;
                                                      }
                                                      if(thisOne == 1) {
                                                          changeInX = changeInX*-1;
                                                      }
                                                      thisOne = 0;

                      LED_On(17);
                      __enable_irq();
                            Sound_Win();
                            Clock_Delay1ms(1000);
                            __disable_irq();
                      moveArrow(changeInX, changeInY);
                      LED_Off(17);
                      dontPrint = 0;
                      wait = 0;
                      if(player == 1){
                              ST7735_SetCursor(0, 0);
                              ST7735_OutString("P1");
                              player = 2;
                          }
                          else if(player == 2){
                                  ST7735_SetCursor(0, 0);
                                  ST7735_OutString("P2");
                                  player = 1;
                              }
        } else if(gameType == 3) {
              makeGolfBackGround();
              ST7735_Line(spot, golfBallYOne, arrowend,golfBallYTwo, 0xFF);
              __disable_irq();
              int32_t changeInX = arrowend - spot;
              int32_t changeInY = golfBallYOne - golfBallYTwo;
              //moveBowlingBall(changeInX, changeInY);
              /*ST7735_SetCursor(0, 0);
                        printf("d=%1u.%.3u cm ", changeInX);
                        ST7735_SetCursor(0, 1);
                        printf("d=%1u.%.3u cm ", changeInY);*/
              int32_t maxAbsValue;

                                              if (changeInX < 0) {
                                                  changeInX = -changeInX;
                                                  thisOne = 1;
                                              }
                                              if (changeInY < 0) {
                                                  changeInY = -changeInY;
                                              }

                                              if (changeInX > changeInY) {
                                                  maxAbsValue = changeInX;
                                              } else {
                                                  maxAbsValue = changeInY;
                                              }


                                              if (maxAbsValue > 9) {
                                                  uint32_t scalingFactor = (maxAbsValue + 8) / 9;
                                                  changeInX /= scalingFactor;
                                                  changeInY /= scalingFactor;
                                              }
                                              if(thisOne == 1) {
                                                  changeInX = changeInX*-1;
                                              }
                                              thisOne = 0;
                        if(player == 1){
                                  ST7735_SetCursor(0, 0);
                                  ST7735_OutString("P1");
                              }
                      else if(player == 2){
                                  ST7735_SetCursor(0, 0);
                                  ST7735_OutString("P2");
                      }

              LED_On(17);
              if(player == 1){
                score1++;
              }
              else if(player == 2){
                    score2++;
                }
              moveGolf(changeInX, changeInY);
              LED_Off(17);
              dontPrint = 0;
              wait = 0;

         }

      }
// game engine goes here
    // 1) sample slide pot
    // 2) read input switches
    // 3) move sprites
    // 4) start sounds
    // 5) set semaphore
    // NO LCD OUTPUT IN INTERRUPT SERVICE ROUTINES
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
  }
}
uint8_t TExaS_LaunchPadLogicPB27PB26(void){
  return (0x80|((GPIOB->DOUT31_0>>26)&0x03));
}

typedef enum {English, Spanish, Portuguese, French} Language_t;
Language_t myLanguage=English;
typedef enum {HELLO, GOODBYE, LANGUAGE} phrase_t;
const char Hello_English[] ="Hello";
const char Hello_Spanish[] ="\xADHola!";
const char Hello_Portuguese[] = "Ol\xA0";
const char Hello_French[] ="All\x83";
const char Goodbye_English[]="Goodbye";
const char Goodbye_Spanish[]="Adi\xA2s";
const char Goodbye_Portuguese[] = "Tchau";
const char Goodbye_French[] = "Au revoir";
const char Language_English[]="English";
const char Language_Spanish[]="Espa\xA4ol";
const char Language_Portuguese[]="Portugu\x88s";
const char Language_French[]="Fran\x87" "ais";
const char *Phrases[3][4]={
  {Hello_English,Hello_Spanish,Hello_Portuguese,Hello_French},
  {Goodbye_English,Goodbye_Spanish,Goodbye_Portuguese,Goodbye_French},
  {Language_English,Language_Spanish,Language_Portuguese,Language_French}
};


// use main1 to observe special characters
int main1(void){ // main1
    char l;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
  ST7735_FillScreen(0x0000);            // set screen to black
  for(phrase_t myPhrase=HELLO; myPhrase<= GOODBYE; myPhrase++){
    for(Language_t myL=English; myL<= French; myL++){
         ST7735_OutString((char *)Phrases[LANGUAGE][myL]);
      ST7735_OutChar(' ');
         ST7735_OutString((char *)Phrases[myPhrase][myL]);
      ST7735_OutChar(13);
    }
  }
  Clock_Delay1ms(3000);
  ST7735_FillScreen(0x0000);       // set screen to black
  l = 128;
  while(1){
    Clock_Delay1ms(2000);
    for(int j=0; j < 3; j++){
      for(int i=0;i<16;i++){
        ST7735_SetCursor(7*j+0,i);
        ST7735_OutUDec(l);
        ST7735_OutChar(' ');
        ST7735_OutChar(' ');
        ST7735_SetCursor(7*j+4,i);
        ST7735_OutChar(l);
        l++;
      }
    }
  }
}

// use main2 to observe graphics
int main2(void){ // main2
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
  ST7735_InitR(INITR_GREENTAB);



  //ST7735_FillScreen(ST7735_WHITE);
  //ST7735_DrawBitmap(15, 159, backgroundd, 98, 160); // player ship bottom
  //printf("d=%1u.%.3u cm ", 1000, 1000);
  while(1){
    }

    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  /*ST7735_FillScreen(ST7735_BLACK);
  ST7735_DrawBitmap(22, 159, bball, 10,10); // player ship bottom
  ST7735_DrawBitmap(53, 151, Bunker0, 18,5);
  ST7735_DrawBitmap(42, 159, PlayerShip1, 18,8); // player ship bottom
  ST7735_DrawBitmap(62, 159, PlayerShip2, 18,8); // player ship bottom
  ST7735_DrawBitmap(82, 159, PlayerShip3, 18,8); // player ship bottom
  ST7735_DrawBitmap(0, 9, SmallEnemy10pointA, 16,10);
  ST7735_DrawBitmap(20,9, SmallEnemy10pointB, 16,10);
  ST7735_DrawBitmap(40, 9, SmallEnemy20pointA, 16,10);
  ST7735_DrawBitmap(60, 9, SmallEnemy20pointB, 16,10);
  ST7735_DrawBitmap(80, 9, SmallEnemy30pointA, 16,10);

  for(uint32_t t=500;t>0;t=t-5){
    SmallFont_OutVertical(t,104,6); // top left
    Clock_Delay1ms(50);              // delay 50 msec
  }
  ST7735_FillScreen(0x0000);   // set screen to black
  ST7735_SetCursor(1, 1);
  ST7735_OutString("GAME OVER");
  ST7735_SetCursor(1, 2);
  ST7735_OutString("Nice try,");
  ST7735_SetCursor(1, 3);
  ST7735_OutString("Earthling!");
  ST7735_SetCursor(2, 4);
  ST7735_OutUDec(1234);
  while(1){
  }*/
}

// use main3 to test switches and LEDs
int main3(void){ // main3
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  while(1){
      uint32_t test = 0;
      while(test == 0){
          test = Switch_In();
      }

      LED_On(17);
      LED_On(19);
      LED_On(20);

      LED_Off(17);
      LED_Off(19);
      LED_Off(20);
  }
}
// use main4 to test sound outputs
int main4(void){ uint32_t last=0,now;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(ADC0,6,0); // ADC1 channel 6 is PB20, TExaS scope
  __enable_irq();
  while(1){
    now = Switch_In(); // one of your buttons
    if((last == 0)&&(now == 1)){
      Sound_Shoot(); // call one of your sounds
    }
    if((last == 0)&&(now == 2)){
      Sound_Killed(); // call one of your sounds
    }
    if((last == 0)&&(now == 4)){
      Sound_Explosion(); // call one of your sounds
    }
    if((last == 0)&&(now == 8)){
      Sound_Fastinvader1(); // call one of your sounds
    }
    // modify this to test all your sounds
  }
}
// ALL ST7735 OUTPUT MUST OCCUR IN MAIN











int main(void){ // final main
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  ST7735_FillScreen(ST7735_WHITE);
  ADCinit();     //PB18 = ADC1 channel 5, slidepot
  Switch_Init(); // initialize switches
  LED_Init();    // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(0,0,&TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
    // initialize interrupts on TimerG12 at 30 Hz

  // initialize all data structures
  __enable_irq();
  ST7735_DrawBitmap(38, 30, Wii, 50, 21);
    ST7735_SetCursor(3, 5);
    ST7735_OutString("Choose Language");
    ST7735_SetCursor(7, 8);
    ST7735_OutString("Espa\xA4ol");
    ST7735_SetCursor(3, 9);
    ST7735_OutString("(bot\xA2n de Arriba)");
    ST7735_SetCursor(7, 12);
    ST7735_OutString("English");
    ST7735_SetCursor(4, 13);
    ST7735_OutString("(Down Button)");
    uint32_t theSwitch = 0;
    uint32_t language = 0; //spanish = 1, english = 0
    while(1) {
        theSwitch = Switch_In();
        if((theSwitch & ((1<<28) + (1<<31))) != 0) {
            break;
        }
    }
    if((theSwitch & (1<<28)) != 0) {
        language = 1;
    }
    if((theSwitch & (1<<31)) != 0) {
        language = 0;
    }


    Clock_Delay1ms(1000);
    ST7735_DrawBitmap(0, 160, loadingscreen, 128, 160);
    if(language == 0) {
        ST7735_SetCursor(3, 11);
            ST7735_OutString("Up");
            ST7735_SetCursor(6, 11);
            ST7735_OutString("Down");
            ST7735_SetCursor(12, 11);
            ST7735_OutString("R/L");
    } else {
        ST7735_SetCursor(0, 11);
            ST7735_OutString("Arriba");
            ST7735_SetCursor(6, 11);
            ST7735_OutString("Abajo");
            ST7735_SetCursor(12, 11);
            ST7735_OutString("Derecho");
    }
    //ST7735_OutString("Bowling(Up)");
    //ST7735_OutString("Shooting(Right/Left)");

    theSwitch = 0;
    while(1){
        theSwitch = Switch_In();
        if(theSwitch != 0){
            break;
        }
    }
    if((theSwitch & (1<<28)) != 0) {
        gameType = 1;
    }
    else if((theSwitch & (1<<31)) != 0) {
        gameType = 3;
    }
    else{
        gameType = 2;
    }



    if(gameType == 1){
        for(int i = 0; i < 6; i++) {
        spot = Random(98) + 15;
        makeBackGround();

        if(player == 1){
            ST7735_SetCursor(0, 0);
            ST7735_OutString("P1");
        }
        else if(player == 2){
                ST7735_SetCursor(0, 0);
                ST7735_OutString("P2");
            }

        ST7735_SetCursor(0, 7);
        ST7735_OutString("                         ");
        ST7735_SetCursor(0, 7);
        //ST7735_OutString(" Player " + );
        if(language == 0) {
            ST7735_OutString(" Prepare to aim in: ");
            ST7735_SetCursor(0, 8);
            ST7735_OutString("                         ");
            ST7735_SetCursor(8, 8);
            ST7735_OutString("5");
            Clock_Delay1ms(1000);
            ST7735_SetCursor(9, 8);
            ST7735_OutString("4");
            Clock_Delay1ms(1000);
            ST7735_SetCursor(10, 8);
            ST7735_OutString("3");
            Clock_Delay1ms(1000);
            ST7735_SetCursor(11, 8);
            ST7735_OutString("2");
            Clock_Delay1ms(1000);
            ST7735_SetCursor(12, 8);
            ST7735_OutString("1");
            Clock_Delay1ms(1000);
        } else {
            ST7735_OutString(" Prep\xA0rate para apuntar en: ");
            ST7735_SetCursor(0, 8);
            ST7735_OutString("                         ");
            ST7735_SetCursor(8, 8);
            ST7735_OutString("5");
            Clock_Delay1ms(1000);
            ST7735_SetCursor(9, 8);
            ST7735_OutString("4");
            Clock_Delay1ms(1000);
            ST7735_SetCursor(10, 8);
            ST7735_OutString("3");
            Clock_Delay1ms(1000);
            ST7735_SetCursor(11, 8);
            ST7735_OutString("2");
            Clock_Delay1ms(1000);
            ST7735_SetCursor(12, 8);
            ST7735_OutString("1");
            Clock_Delay1ms(1000);
        }



        __disable_irq();
        TimerG12_IntArm(80000000/30,2);
        __enable_irq();

        while(wait) {

        }
        wait = 1;
        Clock_Delay1ms(2000);
    }

        Clock_Delay1ms(2000);
        ST7735_FillScreen(ST7735_BLACK);
        __enable_irq();
                           Sound_Bowl();
                           Clock_Delay1ms(1000);
                           __disable_irq();
        if(language == 0) {
            ST7735_SetCursor(5, 0);
                    ST7735_OutString("Game Over");

                    ST7735_SetCursor(1, 2);
                    ST7735_OutString("Player 1 Score is:");
                    ST7735_SetCursor(1, 3);
                    printf("%1u", score1);

                    ST7735_SetCursor(1, 5);
                    ST7735_OutString("Player 2 Score is:");
                    ST7735_SetCursor(1, 6);
                    printf("%1u", score2);

                    ST7735_SetCursor(1, 8);
                    ST7735_OutString("The winner is.......");
                    ST7735_SetCursor(6, 9);
                    if(score1 == score2){
                        ST7735_OutString("Tie");
                    }
                    else if(score1 > score2){
                        ST7735_OutString("Player 1");
                    }
                    else{
                        ST7735_OutString("Player 2");
                    }
        } else {
            ST7735_SetCursor(5, 0);
                    ST7735_OutString("Juego Terminado");

                    ST7735_SetCursor(1, 2);
                    ST7735_OutString("Jugador una");
                    ST7735_SetCursor(1, 3);
                    ST7735_OutString("Puntuaci\xA2n es:");
                    ST7735_SetCursor(1, 4);
                    printf("%1u", score1);

                    ST7735_SetCursor(1, 6);
                    ST7735_OutString("Jugador dos");
                    ST7735_SetCursor(1, 7);
                    ST7735_OutString("Puntuaci\xA2n es:");
                    ST7735_SetCursor(1, 8);
                    printf("%1u", score2);

                    ST7735_SetCursor(1, 10);
                    ST7735_OutString("La ganadora es.......");
                    ST7735_SetCursor(6, 11);
                    if(score1 == score2){
                        ST7735_OutString("Atar");
                    }
                    else if(score1 > score2){
                        ST7735_OutString("Jugador Uno");
                    }
                    else{
                        ST7735_OutString("Jugador os");
                    }
        }

    }


    if(gameType == 2){
        for(int i = 0; i < 6; i++) {
        spot = Random(98) + 15;
        makeArrowBackGround();

        if(player == 1){
            ST7735_SetCursor(0, 0);
            ST7735_OutString("P1");
        }
        else if(player == 2){
                ST7735_SetCursor(0, 0);
                ST7735_OutString("P2");
            }

        if(language == 0) {
                    ST7735_OutString(" Prepare to aim in: ");
                    ST7735_SetCursor(0, 8);
                    ST7735_OutString("                         ");
                    ST7735_SetCursor(8, 8);
                    ST7735_OutString("5");
                    Clock_Delay1ms(1000);
                    ST7735_SetCursor(9, 8);
                    ST7735_OutString("4");
                    Clock_Delay1ms(1000);
                    ST7735_SetCursor(10, 8);
                    ST7735_OutString("3");
                    Clock_Delay1ms(1000);
                    ST7735_SetCursor(11, 8);
                    ST7735_OutString("2");
                    Clock_Delay1ms(1000);
                    ST7735_SetCursor(12, 8);
                    ST7735_OutString("1");
                    Clock_Delay1ms(1000);
                } else {
                    ST7735_OutString(" Prep\xA0rate para apuntar en: ");
                    ST7735_SetCursor(0, 8);
                    ST7735_OutString("                         ");
                    ST7735_SetCursor(8, 8);
                    ST7735_OutString("5");
                    Clock_Delay1ms(1000);
                    ST7735_SetCursor(9, 8);
                    ST7735_OutString("4");
                    Clock_Delay1ms(1000);
                    ST7735_SetCursor(10, 8);
                    ST7735_OutString("3");
                    Clock_Delay1ms(1000);
                    ST7735_SetCursor(11, 8);
                    ST7735_OutString("2");
                    Clock_Delay1ms(1000);
                    ST7735_SetCursor(12, 8);
                    ST7735_OutString("1");
                    Clock_Delay1ms(1000);
                }


        __disable_irq();
        TimerG12_IntArm(80000000/30,2);
        __enable_irq();

        while(wait) {

        }
        wait = 1;
        Clock_Delay1ms(2000);
    }

        Clock_Delay1ms(2000);
        ST7735_FillScreen(ST7735_BLACK);

        if(language == 0) {
                    ST7735_SetCursor(5, 0);
                            ST7735_OutString("Game Over");

                            ST7735_SetCursor(1, 2);
                            ST7735_OutString("Player 1 Score is:");
                            ST7735_SetCursor(1, 3);
                            printf("%1u", score1);

                            ST7735_SetCursor(1, 5);
                            ST7735_OutString("Player 2 Score is:");
                            ST7735_SetCursor(1, 6);
                            printf("%1u", score2);

                            ST7735_SetCursor(1, 8);
                            ST7735_OutString("The winner is.......");
                            ST7735_SetCursor(6, 9);
                            if(score1 == score2){
                                ST7735_OutString("Tie");
                            }
                            else if(score1 > score2){
                                ST7735_OutString("Player 1");
                            }
                            else{
                                ST7735_OutString("Player 2");
                            }
                } else {
                    ST7735_SetCursor(5, 0);
                            ST7735_OutString("Juego Terminado");

                            ST7735_SetCursor(1, 2);
                            ST7735_OutString("Jugador una");
                            ST7735_SetCursor(1, 3);
                            ST7735_OutString("Puntuaci\xA2n es:");
                            ST7735_SetCursor(1, 4);
                            printf("%1u", score1);

                            ST7735_SetCursor(1, 6);
                            ST7735_OutString("Jugador dos");
                            ST7735_SetCursor(1, 7);
                            ST7735_OutString("Puntuaci\xA2n es:");
                            ST7735_SetCursor(1, 8);
                            printf("%1u", score2);

                            ST7735_SetCursor(1, 10);
                            ST7735_OutString("La ganadora es.......");
                            ST7735_SetCursor(6, 11);
                            if(score1 == score2){
                                ST7735_OutString("Atar");
                            }
                            else if(score1 > score2){
                                ST7735_OutString("Jugador Uno");
                            }
                            else{
                                ST7735_OutString("Jugador os");
                            }
                }


    }


    if(gameType == 3){
        while(1) {
        if(repeat){
            spot = Random(98) + 15;
            spot2 = 155;
            randHoleX = Random(113);
            randHoleY = 15 + Random(55);
            randObstacle = Random(68);
            repeat = 0;
        }
        makeGolfBackGround();

        if(player == 1){
            ST7735_SetCursor(0, 0);
            ST7735_OutString("P1");
        }
        else if(player == 2){
                ST7735_SetCursor(0, 0);
                ST7735_OutString("P2");
            }

        if(language == 0) {
                            ST7735_OutString(" Prepare to aim in: ");
                            ST7735_SetCursor(0, 8);
                            ST7735_OutString("                         ");
                            ST7735_SetCursor(8, 8);
                            ST7735_OutString("5");
                            Clock_Delay1ms(1000);
                            ST7735_SetCursor(9, 8);
                            ST7735_OutString("4");
                            Clock_Delay1ms(1000);
                            ST7735_SetCursor(10, 8);
                            ST7735_OutString("3");
                            Clock_Delay1ms(1000);
                            ST7735_SetCursor(11, 8);
                            ST7735_OutString("2");
                            Clock_Delay1ms(1000);
                            ST7735_SetCursor(12, 8);
                            ST7735_OutString("1");
                            Clock_Delay1ms(1000);
                        } else {
                            ST7735_OutString(" Prep\xA0rate para apuntar en: ");
                            ST7735_SetCursor(0, 8);
                            ST7735_OutString("                         ");
                            ST7735_SetCursor(8, 8);
                            ST7735_OutString("5");
                            Clock_Delay1ms(1000);
                            ST7735_SetCursor(9, 8);
                            ST7735_OutString("4");
                            Clock_Delay1ms(1000);
                            ST7735_SetCursor(10, 8);
                            ST7735_OutString("3");
                            Clock_Delay1ms(1000);
                            ST7735_SetCursor(11, 8);
                            ST7735_OutString("2");
                            Clock_Delay1ms(1000);
                            ST7735_SetCursor(12, 8);
                            ST7735_OutString("1");
                            Clock_Delay1ms(1000);
                        }


        __disable_irq();
        TimerG12_IntArm(80000000/30,2);
        __enable_irq();

        while(wait) {

        }
        if(golfDone == 2){
            break;
        }
        wait = 1;
        Clock_Delay1ms(2000);
    }

        Clock_Delay1ms(2000);
        ST7735_FillScreen(ST7735_BLACK);

        if(language == 0) {
                    ST7735_SetCursor(5, 0);
                            ST7735_OutString("Game Over");

                            ST7735_SetCursor(1, 2);
                            ST7735_OutString("Player 1 Score is:");
                            ST7735_SetCursor(1, 3);
                            printf("%1u", score1);

                            ST7735_SetCursor(1, 5);
                            ST7735_OutString("Player 2 Score is:");
                            ST7735_SetCursor(1, 6);
                            printf("%1u", score2);

                            ST7735_SetCursor(1, 8);
                            ST7735_OutString("The winner is.......");
                            ST7735_SetCursor(6, 9);
                            if(score1 == score2){
                                ST7735_OutString("Tie");
                            }
                            else if(score1 > score2){
                                ST7735_OutString("Player 1");
                            }
                            else{
                                ST7735_OutString("Player 2");
                            }
                } else {
                    ST7735_SetCursor(5, 0);
                            ST7735_OutString("Juego Terminado");

                            ST7735_SetCursor(1, 2);
                            ST7735_OutString("Jugador una");
                            ST7735_SetCursor(1, 3);
                            ST7735_OutString("Puntuaci\xA2n es:");
                            ST7735_SetCursor(1, 4);
                            printf("%1u", score1);

                            ST7735_SetCursor(1, 6);
                            ST7735_OutString("Jugador dos");
                            ST7735_SetCursor(1, 7);
                            ST7735_OutString("Puntuaci\xA2n es:");
                            ST7735_SetCursor(1, 8);
                            printf("%1u", score2);

                            ST7735_SetCursor(1, 10);
                            ST7735_OutString("La ganadora es.......");
                            ST7735_SetCursor(6, 11);
                            if(score1 == score2){
                                ST7735_OutString("Atar");
                            }
                            else if(score1 > score2){
                                ST7735_OutString("Jugador Uno");
                            }
                            else{
                                ST7735_OutString("Jugador os");
                            }
                }

    }








}
