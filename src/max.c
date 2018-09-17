#include "aduc812.h"


#define MAXBASE 0x8 //Ќомер страницы внешней пам€ти (xdata), куда отображаютс€
                    //регистры расширител€.

void write_max( unsigned char xdata *regnum, unsigned char val ) {
    unsigned char oldDPP = DPP;
    DPP     = MAXBASE;
    *regnum = val;
    DPP     = oldDPP;
}

unsigned char read_max( unsigned char xdata *regnum ) {
    unsigned char oldDPP=DPP;
    unsigned char val;
    DPP = MAXBASE;
    val = *regnum;
    DPP = oldDPP;
    return val;
}

