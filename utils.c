/* 
 * File:   utils.c
 * Author: surface
 *
 * Created on 2019年5月29日, 下午2:29
 */

int parse_position_value(int val, int* a, int* b, int* c) {
    *a = (val >> 0) & 1;
    *b = (val >> 1) & 1;
    *c = (val >> 2) & 1;
    return val;
}

