/* 
 * File:   utils.h
 * Author: surface
 *
 * Created on 2019年5月29日, 下午2:58
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif


void set_pwm_output(int pos);
void __set_pwm_output(int a, int b, int c);
void set_pwm_duty(int duty);
void init_pwm();


#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

