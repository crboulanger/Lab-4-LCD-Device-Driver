/*
 * Author: Christopher Boulanger
<<<<<<< HEAD
 * Created: 23 October 2013
 * Description: This program is a device driver for initializing SPI for an LCD.
 * It then scrolls a message on the top line and a message on the bottom line.
 * B Functionality now prompts for a message and then polls for a button push
 * After the button push, the LCD displays the corresponding message.
 * Documentation: Worked a lot with C2C Mossing. He is responsible for helping me
 * with the lab requirements and B functionality. He helped
=======
 * Created: 22 October 2013
 * Description: This program is a device driver for initializing SPI for an LCD.
 * It then scrolls a message on the top line and a message on the bottom line.
>>>>>>> ef8570c099904d0551703bcb8c44884d5af77b4f
 */

#include <msp430.h> 
#include "LCD.h"
<<<<<<< HEAD
#include "button.h"

=======
>>>>>>> ef8570c099904d0551703bcb8c44884d5af77b4f
/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;        // Stop watchdog timer

    initSPI();
    initLCD();
    clearLCD();
<<<<<<< HEAD
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
=======

    char* string1 = "ECE382 is my favorite class! ";
    char* string2 = "This is Required Functionality! ";
    scrollString(string1, string2);

>>>>>>> ef8570c099904d0551703bcb8c44884d5af77b4f
    while(1){

    }

        return 0;
}
