/*
 * Author: Christopher Boulanger
 * Created: 22 October 2013
 * Description: This program is a device driver for initializing SPI for an LCD.
 * It then scrolls a message on the top line and a message on the bottom line.
 */

#include <msp430.h> 
#include "LCD.h"
/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;        // Stop watchdog timer

    initSPI();
    initLCD();
    clearLCD();

    char* string1 = "ECE382 is my favorite class! ";
    char* string2 = "This is Required Functionality ";
    scrollString(string1, string2);

    while(1){

    }

        return 0;
}
