/*
PROJECT NAME: FLASHER
CUSTOMER: AMPERE - KINETIC FLASHER
TESTED WITH: KINETIC LAMP
DATE UPDATED: 28/08/2026
VALIDATED ON VEHICLE 
OPERATING VOLTAGE: 14V
OPERATING VOLTAGE RANGE : 11V - 18V
*/

#define MAIN_C

// Files includes
#include "adcx.h"

#include "delay.h"

#include "led.h" 


float Voltage;
float InputVoltage;

float Value_adc = 0;

u16 delayTime = 350;

void LOAD_OUTPUT_ENABLE(void);
int ReadAndStoreADCValue(void);
int getDelayFromFormula(int voltage, int adcValue);
u8 ADC_buff = 0;
u8 ADC_buff1 = 0;

void getDelayValue(void);
volatile bool check_flag = false;
volatile u8 i = 0;

s32 main(void) {

   DELAY_Init();

   ADC1BasicConfigWithParameter();
   ADC1PinConfigWithParameter();
   ADC1ChannelConfigWithParameter();
   OUTPUT_Init();
   INPUT_Init();
   Buzzer_low();
   ADC1SingleChannelInit();

   delayTime = 350;
   while (1) {

      LOAD_OUTPUT_ENABLE();
   }

}

void LOAD_OUTPUT_ENABLE(void) {
   Enable_High();
   Select_Low();

   if (Value_adc < 10) {

      LEFT_OUTPUT_HIGH();
      ReadAndStoreADCValue();
      check_flag = true;
   } else {

//      if (check_flag == true) {
//         check_flag = false;
//         delayTime = 350;
//         LEFT_OUTPUT_HIGH();
//         Buzzer_high();
//         DELAY_Ms(delayTime); // delayTime
//         Buzzer_low();
//         LEFT_OUTPUT_LOW();
//         DELAY_Ms(delayTime);

//      }

      if (delayTime == 350) {
				ADC_buff1 = 0;
//				 LEFT_OUTPUT_HIGH();
//         Buzzer_high();
//         DELAY_Ms(50);
//         ADC_buff = ReadAndStoreADCValue();
//         ADC_buff1 = ADC_buff + ADC_buff1;
//         DELAY_Ms(30);
//         ADC_buff = ReadAndStoreADCValue();
//         ADC_buff1 = ADC_buff + ADC_buff1;
//         DELAY_Ms(60);
//         ADC_buff = ReadAndStoreADCValue();
//         ADC_buff1 = ADC_buff + ADC_buff1;
//         Buzzer_low();
//         LEFT_OUTPUT_LOW();
//         DELAY_Ms(200);
       
         LEFT_OUTPUT_HIGH();
         Buzzer_high();
         DELAY_Ms(80);
         ADC_buff = ReadAndStoreADCValue();
         ADC_buff1 = ADC_buff + ADC_buff1;
         DELAY_Ms(130);
         ADC_buff = ReadAndStoreADCValue();
         ADC_buff1 = ADC_buff + ADC_buff1;
         DELAY_Ms(80);
         ADC_buff = ReadAndStoreADCValue();
         ADC_buff1 = ADC_buff + ADC_buff1;
         Buzzer_low();
         LEFT_OUTPUT_LOW();
         DELAY_Ms(350);

         if (ADC_buff1 < 2 && ADC_buff1 > 0) {
            ADC_buff1 = 0;
            delayTime = 165;
         }
      }
      if (delayTime == 165) {
         ADC_buff1 = 0;
				
				///////////////////
//				LEFT_OUTPUT_HIGH();
//         Buzzer_high();
//         DELAY_Ms(80);
//         ADC_buff = ReadAndStoreADCValue();
//         ADC_buff1 = ADC_buff + ADC_buff1;
//         DELAY_Ms(130);
//         ADC_buff = ReadAndStoreADCValue();
//         ADC_buff1 = ADC_buff + ADC_buff1;
//         DELAY_Ms(80);
//         ADC_buff = ReadAndStoreADCValue();
//         ADC_buff1 = ADC_buff + ADC_buff1;
//         Buzzer_low();
//         LEFT_OUTPUT_LOW();
//         DELAY_Ms(350);

				////////////////////////
         LEFT_OUTPUT_HIGH();
         Buzzer_high();
         DELAY_Ms(50);
         ADC_buff = ReadAndStoreADCValue();
         ADC_buff1 = ADC_buff + ADC_buff1;
         DELAY_Ms(30);
         ADC_buff = ReadAndStoreADCValue();
         ADC_buff1 = ADC_buff + ADC_buff1;
         DELAY_Ms(60);
         ADC_buff = ReadAndStoreADCValue();
         ADC_buff1 = ADC_buff + ADC_buff1;
         Buzzer_low();
         LEFT_OUTPUT_LOW();
         DELAY_Ms(200);

         if (ADC_buff1 > 2) {
            delayTime = 350;
            ADC_buff1 = 0;
         }
      }
   }
}

int ReadAndStoreADCValue(void) {

   ADC_ANY_CH_Config(ADC1, 0, ADC_Channel_5);
   DELAY_Ms(10);
   InputVoltage = GetAdcAverage1(ADC1, 5);
   Voltage = (((float) InputVoltage) / 4095) * 5; //use 5V as VDD
   ADC_ANY_CH_Config(ADC1, 0, ADC_Channel_7);
   DELAY_Ms(10); 
   Value_adc = GetAdcAverage1(ADC1, 5);
   delayTime = getDelayFromFormula(InputVoltage, Value_adc);
	
   if (Value_adc == 0) {
      delayTime = 350;
   }

   if (delayTime == 350) {
      return 1;
   }

   if (delayTime == 165 && Value_adc != 0) {
      return 0;
   }

}

int getDelayFromFormula(int voltage, int adcValue) {

   //		 float factor = (float)(voltage - 1650) / 2445; // Normalize voltage range (4080 - 1860) 
   //    int threshold = 870 + (factor * (2510 - 870)); // Linearly interpolate
   //    return (Value_adc >= threshold) ? 350 : 165;
	
//	float factor = (float)(voltage - 1980) / 1720; // Normalize voltage range (4080 - 1860) 
//   int threshold = 45 + (factor * (3900 - 45)); // Linearly interpolate
//    return (Value_adc >= threshold) ? 350 : 165;
	
	 
		if(adcValue <= 90)
		{
		return 165;
		}
//		else
//		{
//			return 350;
//		}
	 
	else{
//	
///////10 to 16v
   float factor = (float)(voltage - 2200) / 1500; // Normalize voltage range (4080 - 1860) 
   int threshold = 445 + (factor * (3900 - 445)); // Linearly interpolate
    return (Value_adc >= threshold) ? 350 : 165;
	}
}