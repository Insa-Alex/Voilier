#include "stm32f103xb.h" 
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_bus.h" // Pour l'activation des horloges
#include "stm32f1xx_ll_gpio.h"


void TIM_RF_Conf()
{	
		
	
	// Validation horloge locale
	
	
	
	LL_TIM_InitTypeDef Timer_RF;
  LL_TIM_IC_InitTypeDef Channel_RF;
	LL_TIM_IC_InitTypeDef Channel2_RF;
	
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);

	LL_GPIO_SetPinMode (GPIOB,LL_GPIO_PIN_6,LL_GPIO_MODE_FLOATING);
	LL_GPIO_SetPinMode (GPIOB,LL_GPIO_PIN_7,LL_GPIO_MODE_FLOATING);
	
	//INITIALISATION CHANNEL

	Channel_RF.ICActiveInput =LL_TIM_ACTIVEINPUT_DIRECTTI;
	Channel_RF.ICFilter =  LL_TIM_IC_FILTER_FDIV1 ;
	Channel_RF.ICPolarity=LL_TIM_IC_POLARITY_RISING ;
	Channel_RF.ICPrescaler=LL_TIM_ICPSC_DIV1 ;
	
	//INITIALISATION CHANNEL2

	Channel2_RF.ICActiveInput =LL_TIM_ACTIVEINPUT_INDIRECTTI ;
	Channel2_RF.ICFilter =  LL_TIM_IC_FILTER_FDIV1 ;
	Channel2_RF.ICPolarity=LL_TIM_IC_POLARITY_FALLING  ;
	Channel2_RF.ICPrescaler=LL_TIM_ICPSC_DIV1 ;
	
	// chargement structure Arr, Psc, Up Count
	Timer_RF.Autoreload=47999;
	Timer_RF.Prescaler=29;
	Timer_RF.ClockDivision=LL_TIM_CLOCKDIVISION_DIV1;
	Timer_RF.CounterMode=LL_TIM_COUNTERMODE_UP;
	Timer_RF.RepetitionCounter=0;
	
	LL_TIM_Init(TIM4,&Timer_RF);
	LL_TIM_IC_Init (TIM4,LL_TIM_CHANNEL_CH1,&Channel_RF);
		LL_TIM_IC_Init (TIM4,LL_TIM_CHANNEL_CH2,&Channel2_RF);
		
	LL_TIM_SetTriggerInput 	(TIM4,LL_TIM_TS_TI1FP1);
	LL_TIM_SetSlaveMode 	(TIM4,LL_TIM_SLAVEMODE_RESET);
	//LL_TIM_IsEnabledMasterSlaveMode 	(TIM4);
	
	 LL_TIM_CC_EnableChannel 	(TIM4, LL_TIM_CHANNEL_CH1);
	 LL_TIM_CC_EnableChannel 	(TIM4, LL_TIM_CHANNEL_CH2);
	
	LL_TIM_EnableCounter(TIM4);
	
	//LL_TIM_EnableIT_CC2(TIM4);
	

}

int lecture_rapportcycle()
{
	int periode;
	int rapport_cycle;
	
	
	periode = LL_TIM_IC_GetCaptureCH1 (TIM4);
	if (periode != 0)
	{
		rapport_cycle = (LL_TIM_IC_GetCaptureCH2(TIM4)*100/periode);
	}
	else rapport_cycle = 0;
		
	return rapport_cycle;
}

int calc_sens( int rapport_cycle)
{
	int sens;
	if (rapport_cycle > 11.2)
	{
		sens = 1;
	}	
	else sens = 0;
	return sens;
}

int calc_vitesse(int rapport_cycle, int sens)
{
	int vitesse ;
	
	if (sens ==1)
	{
		vitesse = (rapport_cycle-11.2)*40;
	}
	else vitesse = (-rapport_cycle+11.2)*40;
	 
	return vitesse;
}
