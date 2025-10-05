#include <xc.h>


void init_timer2(void)
{   //SELECTING POST SCALAR AS 1:1
    TOUTPS3=0;
    TOUTPS2=0;
    TOUTPS1=0;
    TOUTPS0=0;
    
    /* Selecting the scale as 1:16 */
    T2CKPS0 = 1;
    T2CKPS1 = 1;
    

    /* Loading the Pre Load register with 250 */
    PR2 = 250;  //TMR2 -> 0 to 250
    
    /* The timer interrupt is enabled */
    TMR2IE = 1;
    TMR2IF = 0;
       
    /* Switching on the Timer2 *///offing it  ON WHEN REQ!!
    TMR2ON = 0;
}

