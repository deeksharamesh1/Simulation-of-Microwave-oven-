/* 
 * File:   main.h
 * Author: DEEKSHA RAMESH
 *
 * Created on 23 February, 2025, 5:03 PM
 */

#ifndef MAIN_H
#define	MAIN_H
#define POWER_ON_SCREEN  0x01
#define MENU_SCREEN  0x02
#define MICRO_MODE  0x11
#define GRILL_MODE  0x12
#define CONVECTION_MODE  0x13
#define START_MODE  0x14
#define LED1                RD0 //SUS MY ADD FOR TIME BEING ERRORS
#define RESET_MODE  0xFF
#define RESET_NOTHING 0x00

#define FAN_DDR TRISC2
#define FAN RC2
#define DISPLAY_TIME  0xDD

#define BUZZER_DDR TRISC1
#define BUZZER RC1
// for start pause stop
#define START 0xAA
#define PAUSE 0xBB
#define STOP  0xCC
#endif	/* MAIN_H */

