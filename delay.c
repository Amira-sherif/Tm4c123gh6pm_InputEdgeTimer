#include "delay.h"

void delay_Milli(uint16 delay){
    NVIC_ST_RELOAD_R = delay * freq_factor_milli -1;
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R = 0x1;
    while(Get_Bit(NVIC_ST_CTRL_R,count_flag) == 0) {}
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R = 0;
}


void delay_Micro(uint32 delay){
    NVIC_ST_RELOAD_R = delay * freq_factor_micro -1;
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R = 0x1;
    while(Get_Bit(NVIC_ST_CTRL_R,count_flag) == 0) {}
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R = 0;
}
void delay_Sec(uint16 count_delay){
   // to choose the number of sec needed
    int i;
    for(i=0;i<count_delay;i++){
    delay_Milli(1000);
    }
}
