#include <xc.h>
#include "main.h"
extern unsigned char sec,min;
extern unsigned char pre_heat_time;
unsigned int count ;

void __interrupt() isr(void)
{
    
    
    if (TMR2IF == 1)
    {    
        if (++count == 1250) // 1sec
        {
            
            //for every one sec -- sec if sec==0 -- min
            if(sec!=0)
                sec-- ;
            else if (sec ==0 && min!=0)
            { min=0;//isnt it min--??
            sec=60;
            }
            else if(pre_heat_time !=0)
            {
                pre_heat_time--;
            }
        }
        
        TMR2IF = 0;
    }
}