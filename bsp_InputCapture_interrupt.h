/********************************************************
*    File Name    :  inputcapture
*    Copyright    :
*    Module Name  :
********************************************************/

#ifndef _BSP_INPUTCAPTURE_H_
#define _BSP_INPUTCAPTURE_H_

/********************************************************
*    Include File
********************************************************/
#include "stm32f10x.h"

/*******************************************************
*    Macro Define Section
********************************************************/
/* PB.08-TIM4CH3 */


/********************************************************
*    Prototype Declear Section    
********************************************************/

void ICx_init(void);

void IC_NVIC_Configuration(void);//Configure the nested vectored interrupt controller.
void IC_GPIO_Configuration(void);//Configure the GPIO Pins
void IC_RCC_Configuration(void);//Configurse the different system clocks. 


#endif

