/*
 * LCD.h
 *
 *  Created on: Oct 22, 2013
 *      Author: Christopher Boulanger
 *      Description: API, Library to interact with the Geek Box LCD
 */

void initSPI();

void initLCD();

void clearLCD();

void moveCursorLine1();

void moveCursorLine2();

void writeChar(char asciiChar);

void writeString(char *string);

void scrollString(char* string1, char* string2);
