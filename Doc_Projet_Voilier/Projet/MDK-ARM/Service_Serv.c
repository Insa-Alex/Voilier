#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_gpio.h"

void Servo_conf (void){
	
	// PA8 Timer 1
	RCC -> APB2ENR |= RCC_APB2ENR_TIM1EN;
	
	LL_TIM_SetCounterMode(TIM1,LL_TIM_COUNTERMODE_UP);
	LL_TIM_EnableARRPreload(TIM1);
	LL_TIM_SetPrescaler(TIM1,1439);
	LL_TIM_SetAutoReload(TIM1,999);
	LL_TIM_OC_SetMode(TIM1,LL_TIM_CHANNEL_CH1,LL_TIM_OCMODE_PWM1);
	LL_TIM_OC_EnablePreload (TIM1,LL_TIM_CHANNEL_CH1);
	LL_TIM_OC_SetCompareCH1(TIM1,50);
	
	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_8,LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinOutputType(GPIOA,LL_GPIO_PIN_8,LL_GPIO_OUTPUT_PUSHPULL);
	
}