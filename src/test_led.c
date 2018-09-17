#include "aduc812.h"
#include "led.h"
#include "max.h"


void delay ( unsigned long ms ) {
    volatile unsigned long i, j;
    for( j = 0; j < ms; j++ ) {
        for( i = 0; i < 50; i++ );
    }   
}

unsigned char binary_from_string(char* s) {
  unsigned char result = 0;
  signed char i;
  for (i = 0; i < 8; ++i)
      result |= (s[i] == '1') << (7 - i);
  return result; 
}

unsigned char left_circular_shift(unsigned char x, int n) {
  return (x << n) | (x >> (8 - n));
}
unsigned char right_circular_shift(unsigned char x, int n) {
  return (x >> n) | (x << (8 - n));
}
unsigned char read_dip() {
    return read_max(EXT_LO);
}

void main( void ) {
    unsigned char left_leds = binary_from_string("11000000");
    unsigned char right_leds = binary_from_string("00000001");
    unsigned char leds_var = 0;
    unsigned char dip = 0;
    while( 1 ) {
        delay(20);
        dip = read_dip();
        if (dip == 0x11) {
            leds_var = left_leds | right_leds;
            left_leds = right_circular_shift(left_leds, 1);
            right_leds = left_circular_shift(right_leds, 1);
        } else {
            left_leds = binary_from_string("11000000");
            right_leds = binary_from_string("00000001");
            leds_var = dip;
        }
        leds(leds_var);
    }
}    
