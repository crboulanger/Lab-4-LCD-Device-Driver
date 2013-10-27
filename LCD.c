/*
 * LCD.c
 *
 *  Created on: Oct 22, 2013
 *      Author: Christopher Boulanger
 *      Function: Creates functions used in main.c
 *      Fixed incompatible data types, and added additional comments
 *      This is the final program for Required Functionality
 */


#include <msp430.h>
#include "LCD.h"

#define RS_MASK 0x40

char LCDCON = 0;

void writeCommandNibble(char commandNibble);

void writeCommandByte(char commandByte);

void writeDataByte(char dataByte);

void LCD_write_8(char byteToSend);

void LCD_write_4(char byteToSend);

void SPI_send(char byteToSend);

void set_SS_lo();

void set_SS_hi();



void clearLCD(){
        writeCommandByte(1);
}

void initSPI(){
        UCB0CTL1 |= UCSWRST;	//Assembly code from lab 3 helped alot with this part

        UCB0CTL0 |= UCCKPL|UCMSB|UCMST|UCSYNC;

        UCB0CTL1 |= UCSSEL1;

        UCB0STAT |= UCLISTEN;

        P1SEL |= BIT5|BIT6|BIT7;        //Clk(P1.5), SOMI(P1.6), SIMO(P1.7)
        P1SEL2 |= BIT5|BIT6|BIT7;

        P2DIR |= BIT1;                //GPIO for SS

        UCB0CTL1 &= ~UCSWRST;

}

void line1Cursor(){
        //0x02 is the command for resetting the cursor
        writeCommandByte(0x02);

}

void line2Cursor(){
        writeCommandByte(0x02);
        //screen is 40 bytes long, this moves it 40 times to get on the second line
        int i;
        for(i = 0; i < 40; i++){
                //0x14 is the shift right command
                writeCommandByte(0x14);
        }
}

void scrollString(char* line1strg, char* line2strg){
        char* string1 = line1strg;
        char* string2 = line2strg;

        while(1){

        line1Cursor();
        writeString(string1);

        line2Cursor();
        writeString(string2);

        string1++;
        //when the program sees 0 at the end of the string it resets the string
        if(*string1 == 0){
                string1 = line1strg;
                }

        string2++; //advance the pointer++
                if(*string2 == 0){
                string2 = line2strg;
        }
                //delays the next shift by 102ms// calculations in Lab notebook
    __delay_cycles(100000);// pretty much determines the cycle speed of the string; 10000cycles is pretty fast;100000 is good; 10000000 is slow.
        }
}

void writeString(char* strg2Write){
        //goes to 0 at the end of the pointer
        while(*strg2Write != 0){
                writeChar(*strg2Write);
                strg2Write++;
        }
}

void writeChar(char char2Write){
        writeDataByte(char2Write);
}

void set_SS_lo(){
        P2OUT &= ~BIT1;
}

void set_SS_hi(){
        P2OUT |= BIT1;
}

void initLCD()
{
        set_SS_hi();

    writeCommandNibble(0x03);

    writeCommandNibble(0x03);

    writeCommandNibble(0x03);

    writeCommandNibble(0x02);

    writeCommandByte(0x28);

    writeCommandByte(0x0C);

    writeCommandByte(0x01);

    writeCommandByte(0x06);

    writeCommandByte(0x01);

    writeCommandByte(0x02);

    SPI_send(0);
    __delay_cycles(41);
}

void writeCommandNibble(char commandNibble)
{
    LCDCON &= ~RS_MASK;
    LCD_write_4(commandNibble);
    __delay_cycles(1650);//calculations in Lab Notebook
}

void writeCommandByte(char commandByte)
{
    LCDCON &= ~RS_MASK;
    LCD_write_8(commandByte);
    __delay_cycles(1650);
}

void writeDataByte(char dataByte)
{
    LCDCON |= RS_MASK;
    LCD_write_8(dataByte);
    __delay_cycles(41);
}

void LCD_write_8(char byteToSend)
{
    unsigned char sendByte = byteToSend;

    sendByte &= 0xF0;

    sendByte = sendByte >> 4;               // rotate to the right 4 times

    LCD_write_4(sendByte);

    sendByte = byteToSend;

    sendByte &= 0x0F;

    LCD_write_4(sendByte);
}

void LCD_write_4(char byteToSend)
{
    unsigned char sendByte = byteToSend;

    sendByte &= 0x0F;

    sendByte |= LCDCON;

    sendByte &= 0x7F;

    SPI_send(sendByte);

    __delay_cycles(42);

    sendByte |= 0x80;

    SPI_send(sendByte);

    __delay_cycles(42);

    sendByte &= 0x7F;

    SPI_send(sendByte);

    __delay_cycles(42);
}

void SPI_send(char byteToSend)
{
    char readByte;

    set_SS_lo();

    UCB0TXBUF = byteToSend;

    while(!(UCB0RXIFG & IFG2))
    {
        // wait until you've received a byte
    }

    readByte = UCB0RXBUF;

    set_SS_hi();
}
