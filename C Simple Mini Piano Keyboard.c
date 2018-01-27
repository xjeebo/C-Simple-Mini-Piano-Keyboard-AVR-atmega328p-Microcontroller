// ---------------------------------------------------------------------------
// CpE 301
// March 6, 2017
// S. Harris
// DA6_UARTexample_withInterrupts.c
// ---------------------------------------------------------------------------
//
// This code displays the character typed by the user on the serial terminal.
//
// ---------------------------------------------------------------------------

#include <avr/io.h>
#define F_CPU 8000000	// Clock Speed
#define C4 1911
#define D4 1703
#define E4 1517
#define F4 1432
#define G4 1276
#define A4 1136
#define B4 1012
#define C5 476.783
#define D5 850.31
#define E5 757.438
#define F5 714.86
#define G5 636.763
#define A5 567.182
#define B5 505.191
#include <util/delay.h>
#include <avr/interrupt.h>

#define BAUD  9600

void settings8();
void initUART();

int main( void )
{
	settings8();
	OCR1B = 255;
	initUART();
	while (1);									// Wait for interrupt
	

	return 0;
}

void settings8(){
	TCCR1A |= _BV(COM1B1);  //Clear OC1A/OC1B on compare match
	TCCR1B |= _BV(WGM13) |  _BV(CS11);	//mode 8, PWM, Phase and Frequency Correct (TOP value is ICR1)
	DDRB = 0xFF; // make Port B an output
}


void initUART() {
	unsigned int baudrate;

	// Set baud rate:  UBRR = [F_CPU/(16*BAUD)] -1
	baudrate = ((F_CPU/16)/BAUD) - 1;
	UBRR0H = (unsigned char) (baudrate >> 8);
	UBRR0L = (unsigned char) baudrate;

	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);		// Enable receiver and transmitter
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);		// Set data frame: 8 data bits, 1 stop bit, no parity
	UCSR0B |= (1 << RXCIE0);						// Enable receiver interrupt
	sei();										// Enable global interrupts
}

// UART receiver interrupt handler
ISR (USART_RX_vect)
{
	
	unsigned char receivedChar;
	receivedChar = UDR0;							// Read data from the RX buffer

	 if(receivedChar== 'a'){
		ICR1 = C4; 
	}
	else if(receivedChar == 's'){
		ICR1 = D4; 
	}
	else if(receivedChar == 'd'){
		ICR1 = E4; 
	}
	else if(receivedChar == 'f'){
		ICR1 = F4; 
	}	
	else if(receivedChar == 'g'){
		ICR1 = G4;
	}
	else if(receivedChar == 'h'){
		ICR1 = A5; 
	}	
	else if(receivedChar == 'j'){
		ICR1 = B5;
	}
	else if(receivedChar == 'k'){
		ICR1 = C5;
	}
	_delay_ms(100);
	ICR1 = 0;

	UDR0 = receivedChar;							// Write the data to the TX buffer
}