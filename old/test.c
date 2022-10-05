#include <stdio.h>
#include <math.h>

#define FREQ 32000
#define BLANK(t) {for (int i = 0; i<FREQ/1000*t; i++){putchar(0);}}
#define DO(o,t) {for (int i = 0; i<FREQ*t; i++){putchar(9999 * (i % (int)(FREQ/16.351/pow(2,o)) > FREQ/16.351/pow(2,o+1)));}}
#define RE(o,t) {for (int i = 0; i<FREQ*t; i++){putchar(9999 * (i % (int)(FREQ/18.354/pow(2,o)) > FREQ/18.354/pow(2,o+1)));}}
#define MI(o,t) {for (int i = 0; i<FREQ*t; i++){putchar(9999 * (i % (int)(FREQ/20.601/pow(2,o)) > FREQ/20.601/pow(2,o+1)));}}
#define FA(o,t) {for (int i = 0; i<FREQ*t; i++){putchar(9999 * (i % (int)(FREQ/23.124/pow(2,o)) > FREQ/23.124/pow(2,o+1)));}}
#define SOLd(o,t) {for (int i = 0; i<FREQ*t; i++){putchar(9999 * (i % (int)(FREQ/25.956/pow(2,o)) > FREQ/25.956/pow(2,o+1)));}}

int main(void)
{
	
	MI(3,1)BLANK(0.1)MI(3,1)SOLd(3,1)FA(3,1)MI(3,1)SOLd(3,1)BLANK(0.1)SOLd(3,1)
	//for (int i = 0; i<FREQ; i++)
//	/	putchar(9999 * (i % (FREQ/LA5) > FREQ/(LA5*2)));
	return 0;
}
