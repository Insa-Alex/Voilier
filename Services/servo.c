#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_gpio.h"
#include "math.h"

void servo_Config(void){
	
	// PA8 et TIM1
	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_8,LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinOutputType(GPIOA,LL_GPIO_PIN_8,LL_GPIO_OUTPUT_PUSHPULL);
	
	RCC -> APB2ENR |= RCC_APB2ENR_TIM1EN; // Enable clock
	
	LL_TIM_EnableAllOutputs(TIM1);
	LL_TIM_SetCounterMode(TIM1,LL_TIM_COUNTERMODE_UP);
	LL_TIM_EnableARRPreload(TIM1);
	LL_TIM_EnableCounter(TIM1);
	LL_TIM_SetPrescaler(TIM1,1439); 
	LL_TIM_SetAutoReload(TIM1,999); 
	
	LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH1); // Enables capture/compare channel 3 by setting CC3E
	// LL_TIM_OC_ConfigOutput(TIM1,LL_TIM_CHANNEL_CH1,LL_TIM_OCPOLARITY_HIGH);
	
	LL_TIM_OC_SetMode(TIM1,LL_TIM_CHANNEL_CH1,LL_TIM_OCMODE_PWM1); // Configures Channel 1 in mode PWM1 - CCMR1 OCM1
	LL_TIM_OC_EnablePreload(TIM1,LL_TIM_CHANNEL_CH1); // Configures CCMR1 OC1PE - Output compare 1 preload enable
	LL_TIM_OC_SetCompareCH1(TIM1,0); 
	
}


short int Cmd_Law(short int alpha){
	short int theta;
	
	if ((alpha < 45) || (alpha > 315)){
		theta=0;
	} else if (alpha == 180){
		theta = 60;
	} else {
		theta = (int)((4./9)*alpha - 20);
	}
	return theta;
}

void TourneVoile(short int theta){
//générer un signal sous forme d'une PWM de période 20ms et de duty cycle entre 1 et 2 ms.

	//1ms = 0 et 2 ms = 90
	// Plutôt 0.5 ms => 0 et 1 ms => 90, valeurs expérimentales

	
	LL_TIM_OC_SetCompareCH1(TIM1,(int)(theta*(-5./9)+100));
	

}

