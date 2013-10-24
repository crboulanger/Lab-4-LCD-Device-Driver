#include <msp430.h> 

#define RS_MASK 0x40

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	void initSPI();

	void initLCD();

	void clearLCD();

		for (init i=0, i>0, i++){
	
			void moveCursorLine1(writeChar,writeString,scrollString);

			void moveCursorLine2(writeChar,writeString,scrollString);

			return message;
		}
	return 0;
}

