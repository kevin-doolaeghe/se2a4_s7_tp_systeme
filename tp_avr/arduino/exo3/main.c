#include <avr/io.h>			// for the input/output register
#include <avr/interrupt.h> 	
#include <util/delay.h>  	// for the _delay_ms

#define PRESCALER 1024
//#define TIME_SLOT
#define NB_TICK 6250
#define BAUDRATE	103 // UBRR value for 9600

#define SAVE_CONTEXT()  \
	asm volatile ( \
		"push	r0				\n\t" \
		"in		r0, __SREG__	\n\t" \
		"cli					\n\t" \
		"push	r0				\n\t" \
	);

#define RESTORE_CONTEXT() \
	asm volatile ( \
	);


void init_serial(void)
{
	/* ACHTUNG : we suppose UBRR value < 0xff */
	/* Not true in all case */
	uint8_t baudrate = BAUDRATE;
	/* Set baud rate */
	UBRR0H = 0;
	UBRR0L = baudrate;

	/* Enable transmitter */
	UCSR0B = (1<<TXEN0);

	/* Set frame format */
	UCSR0C = 0x06;
}


void send_serial(unsigned char c)
{
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
}


void init_task_led_red(void)
{
    DDRB |= 0x01;
    PORTB &= ~0x01;
}


void init_timer()
{
	TCCR1B |= _BV(WGM12); // CTC mode with value in OCR1A 
	TCCR1B |= _BV(CS12);  // CS12 = 1; CS11 = 0; CS10 =1 => CLK/1024 prescaler
	TCCR1B |= _BV(CS10);
	OCR1A   = NB_TICK;
	TIMSK1 |= _BV(OCIE1A);
}


void task_led_red(void)
{
    PORTB ^= 0x01;
    _delay_ms(200);
}


void scheduler()
{
}


ISR(TIMER1_COMPA_vect)
{
    send_serial('0');
}


int main(void)
{
    init_task_led_red();
    init_serial();
    init_timer();

    sei();

	while(1)
	{
        task_led_red();
	}

    cli();

	return 0;
}
