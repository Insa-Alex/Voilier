#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_gpio.h"

void moteur_Config(void){
	
	// PA1 et TIM2
	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_1,LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinOutputType(GPIOA,LL_GPIO_PIN_1,LL_GPIO_OUTPUT_PUSHPULL);
	
	RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN; // Enable clock
	
	LL_TIM_EnableAllOutputs(TIM2);
	LL_TIM_SetCounterMode(TIM2,LL_TIM_COUNTERMODE_UP);
	LL_TIM_EnableARRPreload(TIM2);
	LL_TIM_EnableCounter(TIM2);
	LL_TIM_SetPrescaler(TIM2,720); //LL_TIM_SetPrescaler(TIM1,720);
	LL_TIM_SetAutoReload(TIM2,100); //LL_TIM_SetAutoReload(TIM1,100);
	
	LL_TIM_CC_EnableChannel(TIM2,LL_TIM_CHANNEL_CH2); // Enables capture/compare channel 3 by setting CC3E
	// LL_TIM_OC_ConfigOutput(TIM1,LL_TIM_CHANNEL_CH1,LL_TIM_OCPOLARITY_HIGH);
	
	LL_TIM_OC_SetMode(TIM2,LL_TIM_CHANNEL_CH2,LL_TIM_OCMODE_PWM1); // Configures Channel 1 in mode PWM1 - CCMR1 OCM1
	LL_TIM_OC_EnablePreload(TIM2,LL_TIM_CHANNEL_CH2); // Configures CCMR1 OC1PE - Output compare 1 preload enable
	LL_TIM_OC_SetCompareCH2(TIM2,0); //LL_TIM_OC_SetCompareCH1(TIM1,0);
	
}
