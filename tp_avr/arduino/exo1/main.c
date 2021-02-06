#include <avr/io.h>			// for the input/output register
#include <util/delay.h>  	// for the _delay_ms
#include <stdint.h>

void init_led(void)
{
    DDRB |= 0x03;
    PORTB = 0x00;
}

void set_led(int8_t status) {
    PORTB = status;
}

int main(void)
{
    init_led();

	while(1)
	{
        set_led(0x01);
        _delay_ms(200);
        set_led(0x02);
        _delay_ms(300);
	}

	return 0;
}
