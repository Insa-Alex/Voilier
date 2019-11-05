#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_gpio.h"

void Gir_conf (void){
	
	// GPIOA
	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_6,LL_GPIO_MODE_INPUT);
	LL_GPIO_SetPinPull(GPIOA,LL_GPIO_PIN_6,LL_GPIO_PULL_UP);
	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_7,LL_GPIO_MODE_INPUT);
	LL_GPIO_SetPinPull(GPIOA,LL_GPIO_PIN_7,LL_GPIO_PULL_UP);
	
	// TIM3
	
	
}