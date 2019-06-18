/* 
 * File:   pwm.c
 * Author: surface
 *
 * Created on 2019年5月29日, 下午12:39
 */

// #include <stdio.h>
// #include <stdlib.h>

#include <xc.h>
#include "utils.h"
#include "pwm.h"


void init_pwm() {
    IOCON1bits.PENH = IOCON1bits.PENL = 1;
    IOCON2bits.PENH = IOCON2bits.PENL = 1;
    IOCON3bits.PENH = IOCON3bits.PENL = 1;

    // complementary output mode
    IOCON1bits.PMOD = IOCON2bits.PMOD = IOCON3bits.PMOD = 0;
    // Period
    PWMCON1bits.ITB = PWMCON2bits.ITB = PWMCON3bits.ITB = 0;
    PTPER = 0xf100; // 0x0010 ~ 0xFFF8
    // Master duty
    PWMCON1bits.MDCS = PWMCON2bits.MDCS = PWMCON3bits.MDCS = 1;
    MDC = 0x0800; // PTPER + 0x0008; // TODO
    // Overwrite data
    IOCON1bits.OVRDAT = IOCON2bits.OVRDAT = IOCON3bits.OVRDAT = 0b01;

    PWMCON1bits.IUE = PWMCON2bits.IUE = PWMCON3bits.IUE = 1;
    PTCONbits.EIPU = 1;
    PTCON2bits.PCLKDIV = 3;
    PTCONbits.PTEN = 1;
}

/* 
 * Update PWM master duty
 * duty = 0x0008 ~ (PTPER + 0x0008)
 */
void set_pwm_duty(int duty) {
    MDC = duty; // + 0x0007;
}

void set_pwm_output(int pos) {
    int a, b, c;
    parse_position_value(pos, &a, &b, &c);
    __set_pwm_output(a, b, c);
}

void __set_pwm_output(int a, int b, int c) {
    IOCON1bits.OVRENH = IOCON1bits.OVRENL = !a;
    IOCON2bits.OVRENH = IOCON2bits.OVRENL = !b;
    IOCON3bits.OVRENH = IOCON3bits.OVRENL = !c;
}

