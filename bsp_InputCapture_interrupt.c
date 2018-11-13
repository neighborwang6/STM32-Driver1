/* Private variables ---------------------------------------------------------*/                  
__IO uint32_t Update_Flag_Counter = 0;
__IO uint16_t IC3ReadValue1 = 0, IC3ReadValue2 = 0;
__IO uint16_t CaptureNumber = 0;
__IO uint32_t Pulse_Width_Counter = 0;
__IO uint32_t Distance_Counter = 0;

/*  Exported variables ---------------------------------------------------------*/

int distance[10];

int FL_DistanceArry[10];
int FR_DistanceArry[10];

int LF_DistanceArry[10];
int LB_DistanceArry[10];

int RF_DistanceArry[10];
int RB_DistanceArry[10];

int BL_DistanceArry[10];
int BR_DistanceArry[10];

void TIM4_IRQHandler(void)
{
	/* Judge if there's an update event. */
	if(TIM_GetITStatus(TIM4,TIM_FLAG_Update) == SET)
  {
		TIM_ClearFlag(TIM4,TIM_FLAG_Update);
		Update_Flag_Counter += 1;
	}
	
	  /* Judge if there is a Rising edge has been */
	  else if(TIM_GetITStatus(TIM4,TIM_FLAG_CC3) == SET)
    {
		  /* Clear the flag */
		  TIM_ClearFlag(TIM4,TIM_FLAG_CC3);
		
		  if(CaptureNumber == 0) //0 : Indicate a Rising Event just happen.
      {
				/* Get the Input Capture value */
			  IC3ReadValue1 = TIM_GetCapture3(TIM4);
			  
				/* Indicate a Rising Event just happen. */
			  CaptureNumber = 1;

		    /* Clear the Overflow and the Pulse Width couter */
				Pulse_Width_Counter = 0;
		    Update_Flag_Counter = 0; 			
			
			  /* Change the TIM4-CH3 Input Capture Polarity to Falling Edge */
        TIM4 -> CCER |= (TIM_ICPolarity_Falling << 8);


		  }
		    else if(CaptureNumber == 1) 
        {
					/* Get the Input Capture value */
				  IC3ReadValue2 = TIM_GetCapture3(TIM4);
					
			  	/* Clear the Falling event,the next TIM_FLAG_CC3 is rising... */
				  CaptureNumber = 0;   
				
				  /* Change the TIM4-CH3 Input Capture Polarity to Rising Edge */
          TIM4 -> CCER &= ~(TIM_ICPolarity_Falling << 8);
			  
				  /* Capture Computation */
				  if(IC3ReadValue2 > IC3ReadValue1)
				  {
						/* Calcultate the "pulse width" number */
			  		Pulse_Width_Counter = (IC3ReadValue2 - IC3ReadValue1) + ( (0xffff) * (Update_Flag_Counter));
				
			  	}
			  	  else if(IC3ReadValue2 < IC3ReadValue1)
			  	  {
							if(Update_Flag_Counter == 0)
							{ Pulse_Width_Counter = ((0xffff - IC3ReadValue1) + IC3ReadValue2 );  }
                 else
								 { Pulse_Width_Counter = ( (0xffff - IC3ReadValue1) + IC3ReadValue2 ) + ( (0xffff) * (Update_Flag_Counter - 1) ); }
								

				    } 
				
				    /* Put the Capture in an arrar[10] */
					  distance[Distance_Counter] = Pulse_Width_Counter;
					  Distance_Counter += 1;
						
					  if(Distance_Counter > 9)
						Distance_Counter = 0;
					  
			   }

    }

}
