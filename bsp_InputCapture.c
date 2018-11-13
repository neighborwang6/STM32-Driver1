/********************************************************
*    Include File Section
********************************************************/
#include "bsp_inputcapture.h"
/********************************************************
*    Global variable
********************************************************/
TIM_ICInitTypeDef TIM_ICInitStructure;
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;


/********************************************************
*    Prototype Define Section
********************************************************/

/* PB.08-TIM4CH3 */
void ICx_init(void)
{
  IC_RCC_Configuration();//Configurse the different system clocks.
  IC_GPIO_Configuration();//Configure the GPIO Pins	
  IC_NVIC_Configuration();//Configure the nested vectored interrupt controller.
  
  /* Time Base unit Gonfiguration */
  TIM_TimeBaseInitStructure.TIM_Prescaler  = 143;//Sampling @??MHz = APB1_Clk@72MHz/(TIM_Prescaler - 1)
	TIM_TimeBaseInitStructure.TIM_Period     = 0xfffe;
  
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);//TIM_TimeBaseInitStruct.TIM_RepetitionCounter
	
	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);//Enables the TIMx peripheral Preload register on CCR3
	
  /* ICx Config : Channel3 of TIM4 Configuration in pwm mode */
  TIM_ICInitStructure.TIM_Channel     = TIM_Channel_3;
  TIM_ICInitStructure.TIM_ICPolarity  = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter    = 0x3;   //0011: fSAMPLING=fCK_INT, N=8


  TIM_ICInit(TIM4,&TIM_ICInitStructure);

  /* TIM Enable Counter */
  TIM_Cmd(TIM4,ENABLE);
  /* Enable the CC3 Interrupt Request */
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);	
  TIM_ITConfig(TIM4,TIM_IT_CC3,ENABLE);	


}

/**
*  Configurse the different system clocks. 
*/
void IC_RCC_Configuration(void)
{
   /* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

   /* GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

}

/**
*  Configure the GPIO Pins
*/
void IC_GPIO_Configuration(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;

   /* TIM4 channel 3 pin (PB.08) configuration */
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 
    GPIO_Init(GPIOB, &GPIO_InitStructure);
 }

 
/**
*  Configure the nested vectored interrupt controller.
*/
void IC_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable the TIM3 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  
	NVIC_Init(&NVIC_InitStructure);
}

