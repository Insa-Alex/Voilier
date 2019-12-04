#include "stm32f103xb.h" 
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_bus.h" // Pour l'activation des horloges
#include "stm32f1xx_ll_gpio.h"

//void (*pt_TIM2_fct)(void);

void TIM_MCC_Conf()
{	
		
	
	// Validation horloge locale
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
	
	
	LL_TIM_InitTypeDef Timer_MCC;
	// chargement structure Arr, Psc, Up Count
	Timer_MCC.Autoreload=449;
	Timer_MCC.Prescaler=7;
	Timer_MCC.ClockDivision=LL_TIM_CLOCKDIVISION_DIV1;
	Timer_MCC.CounterMode=LL_TIM_COUNTERMODE_UP;
	Timer_MCC.RepetitionCounter=0;
	
	LL_TIM_Init(TIM2,&Timer_MCC);
	LL_TIM_EnableCounter(TIM2);
	
	//INITIALISATION CHANNEL
  LL_TIM_OC_InitTypeDef Channel_MCC;
	Channel_MCC.OCMode=LL_TIM_OCMODE_PWM1;
	Channel_MCC.OCState=LL_TIM_OCSTATE_ENABLE ;
	Channel_MCC.OCNState=LL_TIM_OCSTATE_ENABLE;
	Channel_MCC.CompareValue=0x0000;
	Channel_MCC.OCPolarity=LL_TIM_OCPOLARITY_HIGH;
	Channel_MCC.OCNPolarity=LL_TIM_OCPOLARITY_HIGH;
	Channel_MCC.OCIdleState=LL_TIM_OCIDLESTATE_LOW;
	Channel_MCC.OCNIdleState=LL_TIM_OCIDLESTATE_LOW;
	
	LL_TIM_OC_Init (TIM2,LL_TIM_CHANNEL_CH2,&Channel_MCC);
	
	
	// LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);

  LL_GPIO_SetPinMode (GPIOA,LL_GPIO_PIN_1,LL_GPIO_MODE_ALTERNATE );
	LL_GPIO_SetPinOutputType (GPIOA,LL_GPIO_PIN_1,LL_GPIO_OUTPUT_PUSHPULL);
	
	
	
};
void GPIO_MCC_Conf()
{	
	LL_GPIO_SetPinMode (GPIOA,LL_GPIO_PIN_2,LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType (GPIOA,LL_GPIO_PIN_2,LL_GPIO_OUTPUT_PUSHPULL);

};

void Control_MCC ( int sens, int vitesse)
{
	if (sens ==0)
		LL_GPIO_ResetOutputPin(GPIOA,LL_GPIO_PIN_2);
	else  LL_GPIO_SetOutputPin (GPIOA,LL_GPIO_PIN_2);
	if (vitesse >30)
		LL_TIM_OC_SetCompareCH2 (TIM2,(449*vitesse)/100);
	else LL_TIM_OC_SetCompareCH2 (TIM2,0);
};
