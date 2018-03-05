#include "init.h"
#include "iostm8s003f3.h"

//====INIT======================================================================
void init(void)
{
//----GPIO----------------------------------------------------------------------  
  PA_DDR_DDR1 = 0; PA_CR1_C11 = 1; PA_CR2_C21 = 0; // speed in pullup noint
  PA_DDR_DDR2 = 1; PA_CR1_C11 = 1; PA_CR2_C22 = 0; // radar off out ; push pull ; 2mhz
  PA_DDR_DDR3 = 1; PA_CR1_C13 = 1; PA_CR2_C23 = 0; // 50/55 in pullup noint
  PB_DDR_DDR4 = 1; PB_CR1_C14 = 0; PB_CR2_C24 = 0; // 1 out ; OpenDrain ; 10mhz GND 1%
  PB_DDR_DDR5 = 1; PB_CR1_C15 = 0; PB_CR2_C25 = 0; // 2 out ; OpenDrain ; 10mhz GND 10%
  PC_DDR_DDR3 = 1; PC_CR1_C13 = 1; PC_CR2_C23 = 0; // 3 out ; notOpenDrain ; 10mhz GND 1f
  PC_DDR_DDR4 = 1; PC_CR1_C14 = 1; PC_CR2_C24 = 0; // out ; push pull ; 2mhz
  PC_DDR_DDR5 = 1; PC_CR1_C15 = 1; PC_CR2_C25 = 0; // out ; push pull ; 2mhz
  PC_DDR_DDR6 = 1; PC_CR1_C16 = 1; PC_CR2_C26 = 0; // out ; push pull ; 2mhz
  PC_DDR_DDR7 = 1; PC_CR1_C17 = 1; PC_CR2_C27 = 0; // out ; push pull ; 2mhz
//  PD_DDR_DDR1 = 1; PD_CR1_C11 = 1; PD_CR2_C21 = 1; // out ; push pull ; 10mhz DS данные
  PD_DDR_DDR2 = 1; PD_CR1_C12 = 1; PD_CR2_C22 = 0; // out ; push pull ; 2mhz
  PD_DDR_DDR3 = 1; PD_CR1_C13 = 1; PD_CR2_C23 = 0; // out ; push pull ; 2mhz
  PD_DDR_DDR4 = 1; PD_CR1_C14 = 1; PD_CR2_C24 = 0; // out ; push pull ; 2mhz
  PD_DDR_DDR5 = 1; PD_CR1_C15 = 1; PD_CR2_C25 = 0; // out ; push pull ; 2mhz
//  PD_DDR_DDR6 = 1; PD_CR1_C16 = 0; PD_CR2_C26 = 1; // out ; OpenDrain ; 10mhz LED of kHz  



  //----CLOCK-------------------------------------------------------------def2Mh  
//  CLK_CKDIVR_HSIDIV = 0;// 16Mhz
//  CLK_HSITRIMR = 6;
//----INTERRUPTS----------------------------------------------------------------
  asm("rim"); //Разрешаем прерывания
//----TIM1----------------------------------------------------------------------  
/*  TIM1_CR1_ARPE = 1; //buffered ARR обновление на следующей итерации
  TIM1_CR1_OPM = 0; //one puls mode off
  TIM1_CR1_URS = 0;//interrupt overflow прерывание только по переполнению разрешено
  TIM1_CR1_UDIS = 0;    // нет Прерывание
  TIM1_CCMR3_OC3M = 0x6;//  pwm1
  TIM1_CCMR3_OC3PE = 0; //предзагрузка регистра 
  TIM1_CCMR3_CC3S = 0; // настройка канала на выход
  TIM1_CCER2_CC3P = 0; //OC1 active high
  TIM1_CCER2_CC3E = 1; //включили канал
  TIM1_CCMR4_OC4M = 0x6;//  pwm1
  TIM1_CCMR4_OC4PE = 0; //предзагрузка регистра 
  TIM1_CCMR4_CC4S = 0; // настройка канала на выход
  TIM1_CCER2_CC4P = 0; //OC1 active high
  TIM1_CCER2_CC4E = 1; //включили канал
  TIM1_BKR_MOE = 1;// включили канал
 // TIM1_PSCRL = 0; TIM1_PSCRH = 0; // prescaller 1
 // TIM1_ARRH = 0; TIM1_ARRL = 0xFF;// считаем до 256
 // TIM1_CCR3H = 0; TIM1_CCR3L = 255; //половина 
  TIM1_EGR_UG = 1;
  TIM1_CR1_CEN = 1;  //start timer запускаем космонавта    */  
//----TIM2----------------------------------------------------------------------  
  TIM2_CR1_URS = 1; //interrupt only overflow
  TIM2_CR1_UDIS = 0; //update disable =0
  TIM2_IER_UIE = 1;//update interrupt enable
  TIM2_PSCR = 1; //prescaler ==2  2^1 1mhz
  TIM2_ARRH = 0x03; //1000Hz
  TIM2_ARRL = 0xE8; //
  TIM2_CR1_CEN = 1;

//----TIM4----------------------------------------------------------------------  
  
//----ADC-----------------------------------------------------------------------
  ADC_CSR_EOCIE = 0;//interrupt off
  ADC_CSR_CH = 6;   //adc chanel = 6
  ADC_CR1_SPSEL = 7;//f = Fmaster/18 = 155 и еще 14 тактов а измерение = 11КГц 
  ADC_CR1_CONT = 0; //not continuos
  ADC_CR2_ALIGN = 1;//right align
  ADC_TDRH = 0;     //off schmitt trigger
  ADC_TDRL = 0; 
  ADC_CR1_ADON = 1; //wake up ADC
  
//----UART----------------------------------------------------------------------

  
};  