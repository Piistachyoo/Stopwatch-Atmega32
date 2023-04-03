/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* File          : application.h                                  	     */
/* Date          : Mar 26, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "../HAL/HAL_layer.h"

#include "../MCAL/ATMEGA32/TMR/TMR_interface.h"
#include "../MCAL/ATMEGA32/GIE/GIE_interface.h"
#include "../MCAL/ATMEGA32/EXTI/EXTI_interface.h"



PB_cfg PB1 = {.PortName = PORTD, .PinNum = PIN2, .PBmode = MODE_PULLUP};
PB_cfg PB2 = {.PortName = PORTD, .PinNum = PIN3, .PBmode = MODE_PULLUP};
EXTI_cfg EXTI1 = {.INTx = INT0, .INTx_MODE = MODE_RISING_EDGE};
EXTI_cfg EXTI2 = {.INTx = INT1, .INTx_MODE = MODE_FALLING_EDGE};
buzzer_cfg buzzer1 = {.buzzer_port = PORTB, .buzzer_pin = PIN7};
LCD_4bit_cfg LCD1 = {
		.LCD_PORT = PORTC,
		.LCD_RS_PIN = PIN0,
		.LCD_RW_PIN = PIN1,
		.LCD_EN_PIN = PIN2
};


static u8 stopwatch_seconds=0;
static u8 stopwatch_minutes=0;
static u8 Timer_Flag = 0;

#define timer_compare_match_value	7813u

void app_vInit(void);
void __vector_1(void) __attribute__ ((signal));
void __vector_2(void) __attribute__ ((signal));
void __vector_7(void) __attribute__ ((signal));
void LCD_CLEAR(void);

typedef enum{
	stopwatch_idle,
	stopwatch_on,
	stopwatch_pause
}stopwatch_states;
