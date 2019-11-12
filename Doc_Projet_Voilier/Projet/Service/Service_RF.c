#include "stm32f103xb.h" 
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_bus.h" // Pour l'activation des horloges
#include "stm32f1xx_ll_gpio.h"


void TIM_RF_Conf()
{	
		
	
	// Validation horloge locale
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
	
	
	LL_TIM_InitTypeDef Timer_RF;
	// chargement structure Arr, Psc, Up Count
	Timer_RF.Autoreload=449;
	Timer_RF.Prescaler=7;
	Timer_RF.ClockDivision=LL_TIM_CLOCKDIVISION_DIV1;
	Timer_RF.CounterMode=LL_TIM_COUNTERMODE_UP;
	Timer_RF.RepetitionCounter=0;
	
	LL_TIM_Init(TIM4,&Timer_RF);
	LL_TIM_EnableCounter(TIM4);
	
	//INITIALISATION CHANNEL
  LL_TIM_IC_InitTypeDef Channel_RF;
	Channel_RF.ICActiveInput =LL_TIM_ACTIVEINPUT_DIRECTTI;
	Channel_RF.ICFilter =  LL_TIM_IC_FILTER_FDIV1 ;
	Channel_RF.ICPolarity=LL_TIM_IC_POLARITY_RISING ;
	Channel_RF.ICPrescaler=LL_TIM_ICPSC_DIV8 ;
	
	LL_TIM_IC_Init (TIM4,LL_TIM_CHANNEL_CH2,&Channel_RF);
	
	
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
	LL_GPIO_SetPinMode (GPIOB,LL_GPIO_PIN_6,LL_GPIO_MODE_FLOATING);

	

	
};
void GPIO_RF_Conf()
{	
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
	
  LL_GPIO_SetPinMode (GPIOB,LL_GPIO_PIN_6,LL_GPIO_MODE_ALTERNATE );
	LL_GPIO_SetPinOutputType (GPIOB,LL_GPIO_PIN_6,LL_GPIO_OUTPUT_PUSHPULL);

};


