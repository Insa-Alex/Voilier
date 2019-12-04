#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_exti.h"




void girouette_Config(void (*IT_function) (void),int Prio){
	
		
	// GPIOA
	RCC->APB2ENR = RCC->APB2ENR | RCC_APB2ENR_IOPAEN;
	
	//index en Pull Up
	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_5,LL_GPIO_MODE_INPUT);
	LL_GPIO_SetPinPull(GPIOA,LL_GPIO_PIN_5,LL_GPIO_PULL_UP);
	
	//Voie A
	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_6,LL_GPIO_MODE_FLOATING);
	
	//Voie B
	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_7,LL_GPIO_MODE_FLOATING);
	
		
	
	// TIM3
	RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;
	
	//Bit MOE est mis à 1
	LL_TIM_EnableAllOutputs(TIM3);
	
	//PSC à 1440, on compte les fronts montants et descendants des voies A et B
	LL_TIM_EnableCounter(TIM3);
	LL_TIM_SetPrescaler(TIM3,0);
	LL_TIM_SetAutoReload(TIM3,1439);

	
	LL_TIM_CC_EnableChannel(TIM3,LL_TIM_CHANNEL_CH1);
	LL_TIM_CC_EnableChannel(TIM3,LL_TIM_CHANNEL_CH2);
	
	
	//Est-ce que deux channels peuvent être actives en même temps ?
	LL_TIM_IC_SetActiveInput(TIM3,LL_TIM_CHANNEL_CH1,LL_TIM_ACTIVEINPUT_DIRECTTI);
	LL_TIM_IC_SetFilter (TIM3,LL_TIM_CHANNEL_CH1,LL_TIM_IC_FILTER_FDIV1_N2);
	LL_TIM_IC_SetActiveInput(TIM3,LL_TIM_CHANNEL_CH2,LL_TIM_ACTIVEINPUT_DIRECTTI);
	LL_TIM_IC_SetFilter (TIM3,LL_TIM_CHANNEL_CH2,LL_TIM_IC_FILTER_FDIV1_N2);
	
	//on compte sur les fronts montants ET descendants des deux entrées
	LL_TIM_SetEncoderMode(TIM3,LL_TIM_ENCODERMODE_X4_TI12);
	
	
	//Gestion des interruptions
	
	LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_5);
	LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_5);
	
	NVIC_SetPriority(EXTI9_5_IRQn,30);
	NVIC_EnableIRQ(EXTI9_5_IRQn);

	
}

short int get_pos(void){
	
	short int alpha = LL_TIM_GetCounter(TIM3);
	alpha	= alpha/4;
	//On compte jusqu'à 1440, donc on ramène à 360 en divisant par 4
		
	//décalage de la girouette de D degrés par rapport à son axe
	//D positif -> décalage dans le sens trigonométrique
	alpha+=130;
	
	//symétrie des angles par rapport à l'axe du voilier, on ramène à l'intervalle [0;180]
	if (alpha > 180){
		alpha = -alpha+360;		
	}
		
	return alpha;
}

void EXTI9_5_IRQHandler(void){
	
	LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_5);
	LL_TIM_SetCounter(TIM3,0);
	
}	



