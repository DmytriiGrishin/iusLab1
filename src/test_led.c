#include "aduc812.h"
#include "led.h"
#include "max.h"


void delay ( unsigned long ms ) {
    volatile unsigned long i, j;
    for( j = 0; j < ms; j++ ) {
        for( i = 0; i < 50; i++ );
    }   
}

unsigned char left_circular_shift(unsigned char x, int n) {
    return (x << n) | (x >> (8 - n));
}
unsigned char right_circular_shift(unsigned char x, int n) {
    return (x >> n) | (x << (8 - n));
}

unsigned char invert(unsigned char c) {
    return 255 ^ c;
}

unsigned char read_dip() {
    return invert( read_max(EXT_LO));
}

void main( void ) {
    const unsigned char left_leds_init = 0xC0;
    const unsigned char right_leds_init = 0x01;
    unsigned char left_leds = left_leds_init;
    unsigned char right_leds = right_leds_init;
    unsigned char leds_var = 0;
    unsigned char dip = 0;
    while( 1 ) {
        delay(100);
        dip = read_dip();
        if (dip == 0x11) {
            leds_var = left_leds | right_leds;
            left_leds = right_circular_shift(left_leds, 1);
            right_leds = left_circular_shift(right_leds, 1);
        } else {
            left_leds = left_leds_init;
            right_leds = right_leds_init;
            leds_var = dip;
        }
        leds(leds_var);
    }
}    
