/*
 * LCD.c
 *
 *  Created on: Oct 22, 2013
 *      Author: Christopher Boulanger
 *      Function: Creates functions used in main.c
<<<<<<< HEAD
 *      This is B Functionality Implementation
 */
=======
 *      Fixed incompatible data types, and added additional comments
 *      This is the final program for Required Functionality
 */


>>>>>>> ef8570c099904d0551703bcb8c44884d5af77b4f
#include <msp430.h>
#include "LCD.h"

#define RS_MASK 0x40

char LCDCON = 0;

void writeCommandNibble(char commandNibble);

void writeCommandByte(char commandByte);

<<<<<<< HEAD
int getStringLength(char* string);

=======
>>>>>>> ef8570c099904d0551703bcb8c44884d5af77b4f
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
<<<<<<< HEAD
        UCB0CTL1 |= UCSWRST;//Assembly code from lab 3 helped alot with this part
=======
        UCB0CTL1 |= UCSWRST;	//Assembly code from lab 3 helped alot with this part
>>>>>>> ef8570c099904d0551703bcb8c44884d5af77b4f

        UCB0CTL0 |= UCCKPL|UCMSB|UCMST|UCSYNC;

        UCB0CTL1 |= UCSSEL1;

        UCB0STAT |= UCLISTEN;

        P1SEL |= BIT5|BIT6|BIT7;        //Clk(P1.5), SOMI(P1.6), SIMO(P1.7)
        P1SEL2 |= BIT5|BIT6|BIT7;

        P2DIR |= BIT1;                //GPIO for SS

        UCB0CTL1 &= ~UCSWRST;

}

void line1Cursor(){
<<<<<<< HEAD
	//0x02 is the command for resetting the cursor
=======
        //0x02 is the command for resetting the cursor
>>>>>>> ef8570c099904d0551703bcb8c44884d5af77b4f
        writeCommandByte(0x02);

}

void line2Cursor(){
        writeCommandByte(0x02);
        //screen is 40 bytes long, this moves it 40 times to get on the second line
        int i;
        for(i = 0; i < 40; i++){
<<<<<<< HEAD
        	//0x14 is the shift right command
=======
                //0x14 is the shift right command
>>>>>>> ef8570c099904d0551703bcb8c44884d5af77b4f
                writeCommandByte(0x14);
        }
}

<<<<<<< HEAD
void scrollString(char string1[], char string2[]){
=======
void scrollString(char* line1strg, char* line2strg){
        char* string1 = line1strg;
        char* string2 = line2strg;
>>>>>>> ef8570c099904d0551703bcb8c44884d5af77b4f

        while(1){

        line1Cursor();
        writeString(string1);

        line2Cursor();
        writeString(string2);

<<<<<<< HEAD
        string1 = rotateString(string1);
        string2 = rotateString(string2);

       //delays the next shift by 100ms
    __delay_cycles(100000);// pretty much determines the cycle speed of the string; 10000cycles is pretty fast;100000 is good; 10000000 is slow.
        }
}

char* rotateString(char string[]){
        int length = getStringLength(string);
        char last = string[0];
        int i;
        for(i = 0; i<length-1; i++){
                string[i] = string[i+1];
        }
        string[length-1] = last;

        return string;

}

void writeString(char* strg2Write){
	 //goes to 0 at the end of the pointer
=======
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
>>>>>>> ef8570c099904d0551703bcb8c44884d5af77b4f
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
<<<<<<< HEAD
    __delay_cycles(1650);
=======
    __delay_cycles(1650);//calculations in Lab Notebook
>>>>>>> ef8570c099904d0551703bcb8c44884d5af77b4f
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
<<<<<<< HEAD

int getStringLength(char* string){
        int count = 0;
        while(*string != 0){  //!= means not equal to
                count ++;
                string++;
        }
        return count;
}
=======
>>>>>>> ef8570c099904d0551703bcb8c44884d5af77b4f
