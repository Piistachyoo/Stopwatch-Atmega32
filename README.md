# Stopwatch-Atmega32
## Project Description
Project was consisted of a microcontroller (AVR Atmega32) connected to 2 pushbuttons on PD2 and PD3 for external interrupts, an LCD to show timer counts and a buzzer for user feedback.

#### The stopwatch is designed as a state machine with 3 states:

 1. stopwatch_idle
 2. stopwatch_on
 3. stopwatch_pause

If the program is in **stopwatch_idle** state, you can only press on **PB1**, the program's state changes to **stopwatch_on** state and starts counting, and you will hear a **short beep** to confirm that state change is done.

If the program is in **stopwatch_on** state,  you can only press on **PB2**, the program's state changes to **stopwatch_pause** and the timer is stopped on display, and you will hear a **short beep** to confirm that state change is done.

When you reach **stopwatch_pause** state, you will have 2 options,

Pressing on **PB1** will change the program's state back to **stopwatch_on**, and the system will continue counting from where you stopped, and you will hear a **short beep** to confirm that state change is done.

Pressing on **PB2** will change the program's state to **stopwatch_idle**, and resets the stopwatch to it's original state, and you will hear a **long beep** to confirm that state change is done.



## Configurations and Connections

 **All Configurations are available for change in /Application/application.h**

PB1 is connected to external interrupt on PD2 and activates on rising edge to ensure timing starts when i release the button.
PB2 is connected to external interrupt and activates on falling edge to ensure timing stops right when i click on the button.
LCD is connected to port C and working in 4-bit mode, and is used to display counted time.
Buzzer is connected to PB7 and is used to confirm state changes.

## Files

 - **Application:** Contains program main
 - **HAL:** Hardware architecture layer: contains software related to any on-board hardware element
 - **MCAL:** Microcontroller architecture layer: contains software related to any peripheral inside the microcontroller
 - **Services:** Contains my data types and some bit math operations