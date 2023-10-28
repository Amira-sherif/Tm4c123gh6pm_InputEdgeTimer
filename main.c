/****************************************************************************               **/
/*                                                                                           */
/* !Component       : main                                                                   */
/* !Description     : Application Entry Point                                                */
/*                                                                                           */
/* !Module          : main                                                                   */
/* !Description     : Main Module implementation                                             */
/*                                                                                           */
/* !File            : main.c                                                                 */
/*                                                                                           */
/* !Coding language : C                                                                      */
/*                                                                                           */
/* !Project         : Calculator project                                                     */
/*                                                                                           */
/*                                                                                           */
/*                                                                                           */
/*  all rights reserved                                                                      */
/*                                                                                           */
/*********************************************************************************************/
/* MODIFICATION LOG :                                                                        */
/*********************************************************************************************/
/*                                                                                           */
/* !Designed by :                                                     !Date :  Aug 26, 2023  */
/* !Coded by    :                                                     !Date :  Aug 26, 2023  */
/*                                                                                           */
/* Rev 1.0   Aug 26, 2023     Initial release                                                */
/*********************************************************************************************/

/*! Include compiler types header                                                            */

#include "DIO.h"
#include "bitwise_operations.h"
#include "delay.h"
#include "std_types.h"
#define timeWait 5
#define timeWait5 16000000*timeWait-1
#define timeWait10 16000000*2*timeWait-1
#define timeWait15 16000000*3*timeWait-1
    uint16 Timer_0A_Capture(void)
    {
        uint16 LastEdge;
        uint16 ThisEdge;
        uint16 tick;

        while((WTIMER0_RIS_R&4)==0);
        LastEdge=WTIMER0_TAR_R;
        WTIMER0_ICR_R=4;      /*GPTM Timer A Capture Mode Event Interrupt Clear*/
        while((WTIMER0_RIS_R&4)==0);
        ThisEdge=WTIMER0_TAR_R;
        tick=(LastEdge-ThisEdge)&0x00FFFFFF;
        WTIMER0_ICR_R=4;/*GPTM Timer A Capture Mode Event Interrupt Clear*/
        while((WTIMER0_RIS_R&4)==timeWait5) /*if interrupt set */
        { if(tick==timeWait5){
                 /*LED turn on Red*/
        Set_Bit(GPIO_PORTF_DATA_R,1);
        Clear_Bit(GPIO_PORTF_DATA_R,2);
        Clear_Bit(GPIO_PORTF_DATA_R,3);
        WTIMER0_ICR_R=4;/*GPTM Timer A Capture Mode Event Interrupt Clear*/

        }
        else if(tick==timeWait10)
        {   /*LED turn on Blue*/
              Set_Bit(GPIO_PORTF_DATA_R,2);
              Clear_Bit(GPIO_PORTF_DATA_R,1);
              Clear_Bit(GPIO_PORTF_DATA_R,3);
              WTIMER0_ICR_R=4;/*GPTM Timer A Capture Mode Event Interrupt Clear*/

        }
        else if(tick==timeWait15)
         {   /*LED turn on Green*/
                Clear_Bit(GPIO_PORTF_DATA_R,2);
                Clear_Bit(GPIO_PORTF_DATA_R,1);
                Set_Bit(GPIO_PORTF_DATA_R,3);
                WTIMER0_ICR_R=4;/*GPTM Timer A Capture Mode Event Interrupt Clear*/

         }
     }
    }

int main(void)
{
    SYSCTL_RCGCWTIMER_R|=1;
    DIO_Init(PORTB_ID);
    DIO_Init(PORTF_ID);

    DIO_configurePin(PORTB_ID,6, INPUT_PIN, DISABLE,ENABLE);

    GPIO_PORTB_AFSEL_R=0x40;
    DIO_configurePin(PORTF_ID,4, OUTPUT_PIN, DISABLE,ENABLE);
    Clear_Bit( WTIMER0_CTL_R,0);/*Disable Timer0*/
    WTIMER0_CFG_R=4;
    WTIMER0_TAMR_R=0x17;         /*mode capture ,Edge Time ,count Dir up */
    WTIMER0_CTL_R &=~0x0C;       /*Rising edge */
    Set_Bit( WTIMER0_CTL_R,0);    /*Enable Timer0*/

    WTIMER0_TAILR_R=16000000*timeWait-1;  /*wait 5 sec*/




	return 0;
}
