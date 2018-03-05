#include "iostm8s003f3.h"   // подключение заголовочного файла с объявлениями регистров. масок и битов
#include "max.h"
#include "init.h"


//__interrupt void TIM4_OVR_UIF_handler(void);

//----Var & Def ----------------------------------------------------------------
#define LA PD_ODR_ODR5//
#define LB PD_ODR_ODR4//
#define LC PD_ODR_ODR3//
#define LD PD_ODR_ODR2//
#define LE PC_ODR_ODR7//
#define LF PC_ODR_ODR6//
#define LG PC_ODR_ODR5//
#define LH PC_ODR_ODR4//
#define G1 PC_ODR_ODR3 
#define G2 PB_ODR_ODR4
#define G3 PB_ODR_ODR5
#define radar PA_ODR_ODR3
#define Speed PA_IDR_IDR1


u32 ADC=0;
u16 N=0; //число тактов для АЦП
u8 LSD[3]; //байты для отображения соотв.индикатора
u8 LSDn= 0;
u8 Digit[12]= {b11101011,b01100000,b11000111,b11100101,b01101100,b10101101,b10101111,b11100000,b11101111,b11101101,b00000100,b00010000};//0 1 2 3 4 5 6 7 8 9 - .
float ftemp=0;
u8 T100;

u8 SpeedTime =255;
u8 SpeedN = 0;

//---- funct -------------------------------------------------------------------
void Update_screen(u8 Chanel)
{ 
  G1=1; G2=1; G3=1;
  LA=1 & (LSD[Chanel]>>7);
  LB=1 & (LSD[Chanel]>>6);
  LC=1 & (LSD[Chanel]>>5);
  LD=1 & (LSD[Chanel]>>4);
  LE=1 & (LSD[Chanel]>>3);
  LF=1 & (LSD[Chanel]>>2);
  LG=1 & (LSD[Chanel]>>1);
  LH=1 & (LSD[Chanel]);
  switch (Chanel)
  {
  case 0: {G1=0; G2=1; G3=1; break;}
  case 1: {G1=1; G2=0; G3=1; break;}
  case 2: {G1=1; G2=1; G3=0; break;}
  };
    
};

void TemperatureMeasuring(void)
{
  float a,bb;
  u8 i;
  ADC = ADC>>10;
  if (ADC < 21) {a= -2.016762345 ;bb= 190.2467713;};
  if (ADC > 20)   {a= -2.016762345 ;bb= 190.2467713;};
  if (ADC > 25)   {a= -1.554305578 ;bb= 178.6853522;};
  if (ADC > 31)   {a= -1.195537695 ;bb= 167.5635478;};
  if (ADC > 39)   {a= -0.904142887 ;bb= 156.1991503;};
  if (ADC > 50)   {a= -0.667330882 ;bb= 144.35855;};
  if (ADC > 66)   {a= -0.487655046 ;bb= 132.4999449;};
  if (ADC > 87)   {a= -0.35856678  ;bb= 121.2692657;};
  if (ADC > 115)  {a= -0.265744273 ;bb= 110.5946774;};
  if (ADC > 152)  {a= -0.198418957 ;bb= 100.3612294;};
  if (ADC > 203)  {a= -0.150858848 ;bb= 90.70652727;};
  if (ADC > 269)  {a= -0.118755247 ;bb= 82.07065858;};
  if (ADC > 354)  {a= -0.098607615 ;bb= 74.93839668;};
  if (ADC > 455)  {a= -0.088271754 ;bb= 70.23558018;};
  if (ADC > 569)  {a= -0.08692755  ;bb= 69.47072806;};
  if (ADC > 684)  {a= -0.095560885 ;bb= 75.37592927;};
  if (ADC > 788)  {a= -0.11796536  ;bb= 93.03065538;};
  if (ADC > 873)  {a= -0.166019703 ;bb= 134.9820966;};
  if (ADC > 939)  {a= -0.255206771 ;bb= 218.7287538;};
  if (ADC > 974)  {a= -0.416989388 ;bb= 376.3050223;};
  if (ADC > 998)  {a= -0.782154926 ;bb= 740.7402297;};
  if (ADC > 1012) {a= -1.47682181  ;bb= 1443.743116;};
  if (ADC > 1017) {a= -3.037927826 ;bb= 3031.387934;};
  ftemp = a*ADC+bb;
  T100 = (u8) (ftemp + 100);//ftemp+100 от 0 до 256 = -100..+156
  if (T100<100) 
  {
    LSD[0] = Digit[10];//"-"
    i=(100-T100)/10;
    if (i>0) LSD[1] = Digit[i]; else {LSD[1] = Digit[10]; LSD[0]=0;};
    i=(100-T100)%10;
    LSD[2] = Digit[i];
  };
  
  if (T100>99)
  {
    i= (T100-100)/100;
    if (i>0) LSD[0] = Digit[i]; else LSD[0] = 0;
    u8 j = 100*i;
    i= (T100-100-j)/10;
    if ( (i==0) && (LSD[0]==0) ) LSD[1]=0; else LSD[1] = Digit[i];
    i = (T100-100-j)%10;
    LSD[2] = Digit[i];
  };
  N=0;  
  ADC=0;
};


//==== MAIN ====================================================================
int main( void ) // Основная программа
{
  init();
  radar = 1;// заткнись
  PA_ODR_ODR1=1;
  while(1)      // Бесконечный цикл
  {
  };    
};

//==== INTERRUPTS ==============================================================

// Вектор прерывания по обновлению или переполнению Таймера2
#pragma vector = TIM2_OVR_UIF_vector 
__interrupt void TIM2_OVR_UIF_handler(void)
{ TIM2_SR1_UIF = 0;  // очистили флаг
  //temperature
  ADC += ADC_DRL;
  ADC += ADC_DRH<<8;
  if (N==1023) TemperatureMeasuring(); else N++;
  Update_screen(LSDn);
  if (LSDn == 2) LSDn = 0; else LSDn ++;
  if ((LSD[0]==0)&&(LSDn==0)) LSDn=1;//----------------------------------------
  ADC_CR1_ADON = 1;// запуск измерения
  //speed
  if (Speed == 1) SpeedN++;
  if (SpeedN>250) SpeedN = 250;
  if ((Speed == 0)&&(SpeedN>0)) SpeedTime=SpeedN;
  if (Speed ==0) SpeedN=0;
  if (SpeedTime<14) radar = 0;
  if (SpeedTime>16) radar = 1;
  if (!radar) LSD[2]=(LSD[2] | Digit[11]);
  

} ;

//==== function ================================================================
