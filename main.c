/*
 * Author: Christopher Boulanger
 * Created: 23 October 2013
 * Description: This program is a device driver for initializing SPI for an LCD.
 * It then scrolls a message on the top line and a message on the bottom line.
 * B Functionality now prompts for a message and then polls for a button push
 * After the button push, the LCD displays the corresponding message.
 * Documentation: Worked a lot with C2C Mossing. He is responsible for helping me
 * with the lab requirements and B functionality. He helped
 */

#include <msp430.h> 
#include "LCD.h"
#include "button.h"

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;        // Stop watchdog timer

    initSPI();
    initLCD();
    clearLCD();
    configureP2PinAsButton(BIT3|BIT4|BIT5);
    char string0[] = "ECE382 is my favorite class! ";

    writeString("Message?");
    line2Cursor();
    writeString("PRESS123");

    char buttons[] = {BIT3, BIT4, BIT5};
    char pressedButton = pollP2Buttons(buttons, 3);

    if(pressedButton == BIT3){
            char string1[] = "You pressed button 1. ";
            waitForP2ButtonRelease(BIT3);
        scrollString(string0, string1);
    }
    else if(pressedButton == BIT4){
            char string2[] = "You pressed button 2. ";
            waitForP2ButtonRelease(BIT4);
        scrollString(string0, string2);
    }
    else{
            char string3 []= "You pressed button 3. ";
            waitForP2ButtonRelease(BIT5);
        scrollString(string0, string3);
    }

    //traps cpu
    while(1){

    }

        return 0;
}
