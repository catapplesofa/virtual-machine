/*
 *     word.c
 *     Sophie Zhou (szhou13), Angela Yan (yyan08)
 *     11/19/2024
 *     CS40 HW6 
 * 
 *     Purpose: word.c contains implementations of the fucntions defined in 
 *     word.h. It uses  Bitpack_getu() to extract values from certain positions 
 *     of the 32-bit instruction. These include the opcode, the registers,
 *     and values (in the case of the load val instruction). Word.c utilizes
 *     the functions defined in bitpack.h
 */

#include <stdio.h>
#include <stdlib.h>
#include "bitpack.h"
#include "Word.h"

/********** get_opcode ********
 *
 * function that given a 32 bit word instruction, returns the opcode 
 * (represented by the first 4, most significant bits of the 32 bit word)
 *
 * Parameters:
 *      uint32_t word:          a 32 bit word that represents a given 
 *                              instruction

 * Return: an integer representing the opcode of the instruction
 *
 * Expects
 *     that the 32 bit word is valid.
 * 
 * Notes:
 *      function is only used internally, so assumes input is valid. This
 *      function also utilizes Bitpack_getu defined in bitpack.h
 ************************/
int get_opcode(uint32_t word) {
        int code = Bitpack_getu(word, 4, 28);
        return code;
}

/********** get_ra ********
 *
 * function that given a 32 bit word instruction, returns the ra value 
 * (represented by 3 bits, at lsb = 6 in the word)
 *
 * Parameters:
 *      uint32_t word:          a 32 bit word that represents a given 
 *                              instruction

 * Return: an integer representing the ra value stored in the instruction
 *
 * Expects
 *     that the 32 bit word is valid.
 * 
 * Notes:
 *      function is only used internally, so assumes input is valid. This
 *      function also utilizes Bitpack_getu defined in bitpack.h
 ************************/
int get_ra(uint32_t word) {
        int ra = Bitpack_getu(word, 3, 6);
        return ra;
}

/********** get_rb ********
 *
 * function that given a 32 bit word instruction, returns the rb value 
 * (represented by 3 bits, at lsb = 3 in the word)
 *
 * Parameters:
 *      uint32_t word:          a 32 bit word that represents a given 
 *                              instruction

 * Return: an integer representing the rb value stored in the instruction
 *
 * Expects
 *     that the 32 bit word is valid.
 * 
 * Notes:
 *      function is only used internally, so assumes input is valid. This
 *      function also utilizes Bitpack_getu defined in bitpack.h
 ************************/
int get_rb(uint32_t word) {
        int rb = Bitpack_getu(word, 3, 3);
        return rb;
}

/********** get_rc ********
 *
 * function that given a 32 bit word instruction, returns the rc value 
 * (represented by 3 bits, at lsb = 0 in the word)
 *
 * Parameters:
 *      uint32_t word:          a 32 bit word that represents a given 
 *                              instruction

 * Return: an integer representing the rc value stored in the instruction
 *
 * Expects
 *     that the 32 bit word is valid.
 * 
 * Notes:
 *      function is only used internally, so assumes input is valid. This
 *      function also utilizes Bitpack_getu defined in bitpack.h
 ************************/
int get_rc(uint32_t word) {
        int rc = Bitpack_getu(word, 3, 0);
        return rc;
}

/********** get_lv_ra ********
 *
 * function that given a 32 bit word load-value instruction, returns the ra 
 * value (represented by 3 bits, at lsb = 25 in the word)
 *
 * Parameters:
 *      uint32_t word:          a 32 bit word that represents a given 
 *                              load-value instruction 
 *                       
 * Return: an integer representing the ra value stored in the load-value 
 *         instruction
 *
 * Expects
 *     that the 32 bit word is valid and that the word represents a load-value
 *     instruction
 * 
 * Notes:
 *      function is only used internally, so assumes input is valid. This
 *      function also utilizes Bitpack_getu defined in bitpack.h
 ************************/
int get_lv_ra(uint32_t word) {
        int ra = Bitpack_getu(word, 3, 25);
        return ra;
}

/********** get_lv_val ********
 *
 * function that given a 32 bit word load-value instruction, returns the value 
 * (represented by 25 bits, at lsb = 0 in the word)
 *
 * Parameters:
 *      uint32_t word:          a 32 bit word that represents a given 
 *                              load-value instruction 
 *                       
 * Return: an integer representing the value stored in the load-value 
 *         instruction
 *
 * Expects
 *     that the 32 bit word is valid and that the word represents a load-value
 *     instruction
 * 
 * Notes:
 *      function is only used internally, so assumes input is valid. This
 *      function also utilizes Bitpack_getu defined in bitpack.h
 ************************/
int get_lv_val(uint32_t word) {
        int val = Bitpack_getu(word, 25, 0);
        return val;
}