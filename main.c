    /*
 * File:   main.c
 * Author: DEEKSHA RAMESH
 *
 * Created on 23 February, 2025, 4:14 PM
 */



#include <xc.h>
#include "clcd.h"
#include "main.h"
#include "microoven.h"
#include "matrix_keypad.h"
#include "timers.h"



#pragma config WDTE= OFF

unsigned char operational_flag=POWER_ON_SCREEN ;
unsigned char reset_flag=RESET_NOTHING;
extern unsigned char min,sec;

void init_config(void)
{/*configure clcd*/
    init_clcd(); 
    init_matrix_keypad();
    //config fan
    FAN_DDR=0;
    FAN=0;
    //configure timer
    init_timer2();
    PEIE=1;
    GIE=1;
    //config buzzer
    BUZZER_DDR=0;//trisc1 as output
    BUZZER=0;
}

void main(void) {
    unsigned char key;unsigned char start_mode=0;
    init_config();
    while(1)
    {   key=read_matrix_keypad(STATE);//edge trigger,0-9 * # or ALL_RELEASED
        //if condition: to select mode based on key press only that too in menu screen
        if(operational_flag==MENU_SCREEN)
        {
            /*key=read_matrix_keypad(STATE);//edge trigger*/
            if(key==1)
            {   clear_screen();
                operational_flag=MICRO_MODE;
                clcd_print("Power=900W",LINE2(0));
                __delay_ms(2000);
                clear_screen();
                reset_flag=RESET_MODE;
                start_mode=0;
            }
            else if(key==2)
            {   
                clear_screen();
                operational_flag=GRILL_MODE;
                reset_flag=RESET_MODE;
                start_mode=0;
            }
            else if(key==3)
            {   clear_screen();
                operational_flag= CONVECTION_MODE;
                reset_flag=RESET_MODE;
                start_mode=0;
                
            }
            else if(key==4)
            {    clear_screen();
                operational_flag= START_MODE;
                start_mode=1;
                reset_flag=RESET_MODE;
                
                
            }
        }
        if(operational_flag==DISPLAY_TIME)
        {
            if(key==4)
            { 
               //operational_flag=START; 
                if(start_mode)//increment sec by 30
                {
                    sec=sec+30;
                    if(sec>59)
                    {min++;sec=sec-60;}
                        
                }
            }
            else if(key==5)
            {
                operational_flag=PAUSE;
            }
            else if(key==6)
            {
                operational_flag=STOP;
            }
            
            
        }
        else if(operational_flag== PAUSE)
        {   //resume oven
            if(key==4)
            {
                FAN=1;
                TMR2ON=1;
                operational_flag=DISPLAY_TIME;
            }
        }

        //cooking mode based on keypress over
        switch(operational_flag)
        { 
            case POWER_ON_SCREEN:
                            //display power on screen 
                            power_on_screen();
                            operational_flag=MENU_SCREEN;
                            clear_screen();//to clear clcd
                            break;
            case MENU_SCREEN:
                            //display menus
                            display_menu_screen();
                            break;
                
            case MICRO_MODE:
                            //read key and set time based on that.
                            set_time(key,reset_flag);
                            //turn on microwave and display the time.
                            break;
            case DISPLAY_TIME:
                            time_display();
                            break;
            case PAUSE:
                            //stop oven and the timer
                            FAN=0;
                            TMR2ON=0;
                            break;
            case STOP:
                            FAN=0;
                            TMR2ON=0;
                            clear_screen();
                            //go back to menu 
                            operational_flag=MENU_SCREEN;
                            break;
                        
                
            case GRILL_MODE:
                            //read key and set time based on that.
                            set_time(key,reset_flag);//it goes to display time automatically
                            break;
                
            case CONVECTION_MODE:
                            set_temp(key,reset_flag);
                            break;
                
            case START_MODE:
                            //30 sec as cooking time
                            heat_food();
                            break;
            
        }
        reset_flag=RESET_NOTHING;
    }
}
