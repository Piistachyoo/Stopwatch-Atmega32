/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* File          : application.c                                  	     */
/* Date          : Mar 26, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "application.h"

static stopwatch_states Current_state;

int main(void){
	// Initialize application
	app_vInit();

	// Wait for interrupt to happen
	while(1){
		if(Timer_Flag == 1){
			Timer_Flag = 0;
			stopwatch_seconds++;
			if(stopwatch_seconds == 60){
				stopwatch_seconds = 0;
				stopwatch_minutes++;
			}
			LCD_4bit_vSendCmd(&LCD1, CLEAR_DISPLAY);
			LCD_4bit_vSendNumber(&LCD1, stopwatch_minutes);
			LCD_4bit_vSendChar(&LCD1, ':');
			LCD_4bit_vSendNumber(&LCD1, stopwatch_seconds);
		}
	}
}

void app_vInit(void){
	/* Set stop watch initial state to idle */
	Current_state = stopwatch_idle;

	/* Set 2 push buttons on PIN D2 & D3 (INT0 and INT1) */
	PBD_vInit(&PB1);
	PBD_vInit(&PB2);

	/* Initialize buzzer GPIO pin */
	BUZZER_vInit(&buzzer1);

	/* Set interrupts on INT0 and INT1 */
	GIE_vEnableInterrupts();
	EXTI_vEnableEXTI(&EXTI1);
	EXTI_vEnableEXTI(&EXTI2);

	/* Initialize timer */
	TMR_vEnable(TMR1_CHNL);
	OCR1A_REG = timer_compare_match_value;

	/* Initialize LCD */
	LCD_4bit_vInit(&LCD1);
	LCD_CLEAR();
}

// INT0 Interrupt service routine
void __vector_1(void){
	if(Current_state == stopwatch_idle){
		BUZZER_vShortBeep(&buzzer1);
		Current_state = stopwatch_on;
		/* Start timer1 */
		TMR_vStartTimer1(PRE_1024);
	}
	else if(Current_state == stopwatch_pause){
		BUZZER_vShortBeep(&buzzer1);
		Current_state = stopwatch_on;
		/* Start timer1 */
		TMR_vStartTimer1(PRE_1024);
	}
	else{  /*Do Nothing*/  }

}

// INT1 Interrupt service routine
void __vector_2(void){
	switch(Current_state){
	case stopwatch_on:
		BUZZER_vShortBeep(&buzzer1);
		Current_state = stopwatch_pause;
		 /*Timer0 pause*/
		TMR_vDisable(TMR1_CHNL);
		break;
	case stopwatch_pause:
		BUZZER_vLongBeep(&buzzer1);
		Current_state = stopwatch_idle;
		 /*Timer0 stop*/
		TMR_vDisable(TMR1_CHNL);
		stopwatch_seconds = 0;
		stopwatch_minutes = 0;
		 /*Reset LCD Display*/
		LCD_CLEAR();
		break;
	default: break;
	}

}

// Timer 1 compare match interrupt service routine
void __vector_7(void){
	Timer_Flag = 1;
}

// Function that clears and reset LCD display
void LCD_CLEAR(void){
	LCD_4bit_vSendCmd(&LCD1, CLEAR_DISPLAY);
	LCD_4bit_vSendString(&LCD1, (u8*)"0:0");
}
