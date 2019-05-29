/*
 * File:   main.c
 * Author: surface
 *
 * Created on 2019年5月26日, 下午11:12
 */


#pragma config PWMLOCK = OFF

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "pwm.h"
#include "utils.h"

#define POS_A 0b001 // C B A
#define POS_Z 0b011
#define POS_B 0b010
#define POS_X 0b110
#define POS_C 0b100
#define POS_Y 0b101

/**
 *   Z -- B
 *  /      \
 * A        X
 *  \      /
 *   Y -- C
 *
 * AbC -> bCa -> CaB -> aBc -> BcA -> cAb -> AbC -> ...
 *
 **/


void set_pb_output(int pos);


int main(void) {
    /*
     * 10 - HIN3 / 11 - LIN3 / 12 - HIN2 / 13 - LIN2 / 14 - HIN1 / 15 - LIN1
     * HC - 8    / HB - 7    / HA - 6
     */
    
    // Config IO PORTB
    TRISB = 0x0000;
    ANSELB = 0x0000;
    set_pb_output(POS_A);
    
    // Config PWM
    // init_pwm();
    // set_pwm_output(POS_A);
    // set_pwm_duty();

    // Config IO PORTC and CN
    TRISC |= 0b0000000111000000;
    ANSELC = 0x0000;
    CNENC |= 0b0000000111000000;
    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1;
    
    // Enable global interrupt
    INTCON1bits.NSTDIS = 1;
    INTCON2bits.GIE = 1;
    
    return (EXIT_SUCCESS);
}


void __attribute__((__interrupt__,no_auto_psv)) _CNInterrupt(void) {
    int curt_pos; // { HC, HB, HA }
    int next_ctrl;

    curt_pos = (PORTC >> 6) & 0b111;

    switch(curt_pos) {
        case POS_A: next_ctrl = POS_Z; break;
        case POS_Z: next_ctrl = POS_B; break;
        case POS_B: next_ctrl = POS_X; break;
        case POS_X: next_ctrl = POS_C; break;
        case POS_C: next_ctrl = POS_Y; break;
        case POS_Y: next_ctrl = POS_A; break;
        default: next_ctrl = POS_A;
    }
    
    // Covert ctrl to PORTB output
    // 15 LIN1 / 14 HIN1 / 13 LIN2 / 12 HIN2 / 11 LIN3 / 10 HIN3
    set_pb_output(next_ctrl);
    // set_pwm_output(next_ctrl);
    
	IFS1bits.CNIF = 0;
}

void set_pb_output(int pos) {
    char port_val = 0;
    char ha, hb, hc;
    // parse_position_value(pos, &ha, &hb, &hc);
    ha = (pos >> 0) & 1;
    hb = (pos >> 1) & 1;
    hc = (pos >> 2) & 1;

    port_val = (port_val << 2) | (ha ? 0b01 : 0b10);
    port_val = (port_val << 2) | (hb ? 0b01 : 0b10);
    port_val = (port_val << 2) | (hc ? 0b01 : 0b10);
    PORTB = port_val << 10;
}


