/*
 *     word.h
 *     Sophie Zhou (szhou13), Angela Yan (yyan08)
 *     11/19/2024
 *     CS40 HW6 
 * 
 *     Purpose: word.h defines functions that extracts the opcode, register 
 *              values (and value in the case of load val). 
 */

#include <stdbool.h>
#include <stdint.h>

int get_opcode(uint32_t word);
int get_ra(uint32_t word);
int get_rb(uint32_t word);
int get_rc(uint32_t word);
int get_lv_ra(uint32_t word); 
int get_lv_val(uint32_t word);