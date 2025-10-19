/*
 *     instructions.c
 *     Sophie Zhou (szhou13), Angela Yan (yyan08)
 *     11/19/2024
 *     CS40 HW6 
 * 
 *     Purpose: instructions.c contains implmentations and helper functions
 *              needed to implement the execute_instruction() function 
 *              defined in instructions.h. These include helper functions
 *              representing each individual instruction. instructions.c 
 *              utilizes the functions definedin word.h, and also the functions
 *              defined in memory.h to manipulate the Hanson Sequence, Hanson
 *              Stack, and struct pointers.
 */

#include <stdio.h>
#include <stdlib.h>
#include "instructions.h"
#include "Word.h"
#include "stack.h"
#include "seq.h"
#include "assert.h"


/********** instruction_0 ********
 *
 * function that given the ra, rb, rc values of an instruction and the 
 * registers, performs a conditional move:
 * if $r[C] not equal to 0, then $r[A]:=$r[B]
 *
 * Parameters:
 *      uint32_t ra:          uint32_t that represents the ra value of a
 *                            32 bit instruction
 *      uint32_t rb:          uint32_t that represents the rb value of a
 *                            32 bit instruction
 *      uint32_t rc:          uint32_t that represents the rc value of a
 *                            32 bit instruction
 *      uint32_t *registers:  a pointer to the registers (an array of 8 
 *                            uint32_t values that represent the registers 
 *                            of the UM)
 * 
 * Return: void
 *
 * Expects
 *     expects that ra, rb, and rc are valid, and that the registers array 
 *     is not null and initalized properly
 * 
 * Notes:
 *      function is only used internally, so assumes input is valid. 
 ************************/
void instruction_0(uint32_t ra, uint32_t rb, uint32_t rc, uint32_t *registers) 
{
        if (registers[rc] != 0) {
                registers[ra] = registers[rb];
        }
}

/********** instruction_1 ********
 *
 * function that given the ra, rb, rc values of an instruction,  the 
 * registers, and the segment performs a segmented load:
 * $r[A] := $m[$r[B]][$r[C]]
 *
 * Parameters:
 *      uint32_t ra:          uint32_t that represents the ra value of a
 *                            32 bit instruction
 *      uint32_t rb:          uint32_t that represents the rb value of a
 *                            32 bit instruction
 *      uint32_t rc:          uint32_t that represents the rc value of a
 *                            32 bit instruction
 *      uint32_t *registers:  a pointer to the registers (an array of 8 
 *                            uint32_t values that represent the registers 
 *                            of the UM)
 *      Seq_T *ids:           a Hanson sequence that stores struct pointers
 *                            containing the id of each segment (its index
 *                            in the sequence), the 64-bit address of the 
 *                            segment in memory, and the size of the segment.
 * 
 * Return: void
 *
 * Expects
 *     expects that ra, rb, and rc are valid, the registers array 
 *     is not null and initalized properly, and the ids Sequence is not null
 *     and is in its proper state
 * 
 * Notes:
 *      function is only used internally, so assumes input is valid. 
 *      instruction_1 uses the load_memory function defined in memory.h because
 *      it manipulates memory.
 ************************/
void instruction_1(uint32_t ra, uint32_t rb, uint32_t rc, uint32_t *registers, 
                   Seq_T *ids) 
{

        load_memory(ra, rb, rc, registers, ids);
}

/********** instruction_2 ********
 *
 * function that given the ra, rb, rc values of an instruction, the 
 * registers, and the segment , performs a segmented store:
 * $m[$r[A]][$r[B]] := $r[C]
 *
 * Parameters:
 *      uint32_t ra:          uint32_t that represents the ra value of a
 *                            32 bit instruction
 *      uint32_t rb:          uint32_t that represents the rb value of a
 *                            32 bit instruction
 *      uint32_t rc:          uint32_t that represents the rc value of a
 *                            32 bit instruction
 *      uint32_t *registers:  a pointer to the registers (an array of 8 
 *                            uint32_t values that represent the registers 
 *                            of the UM)
 *      Seq_T *ids:           a Hanson sequence that stores struct pointers
 *                            containing the id of each segment (its index
 *                            in the sequence), the 64-bit address of the 
 *                            segment in memory, and the size of the segment.
 * 
 * Return: void
 *
 * Expects
 *     expects that ra, rb, and rc are valid, the registers array 
 *     is not null and initalized properly, and the ids Sequence is not null
 *     and is in its proper state
 * 
 * Notes:
 *      function is only used internally, so assumes input is valid. 
 *      instruction_2 uses the store_memory function defined in memory.h 
 *      because it manipulates memory.
 ************************/
void instruction_2(uint32_t ra, uint32_t rb, uint32_t rc, uint32_t *registers, 
                   Seq_T *ids) 
{
        store_memory(ra, rb, rc, registers, ids);
}

/********** instruction_3 ********
 *
 * function that given the ra, rb, rc values of an instruction and the 
 * registers, performs addition:
 * $r[A] := ($r[B] + $r[C]) mod 2^32
 *
 * Parameters:
 *      uint32_t ra:          uint32_t that represents the ra value of a
 *                            32 bit instruction
 *      uint32_t rb:          uint32_t that represents the rb value of a
 *                            32 bit instruction
 *      uint32_t rc:          uint32_t that represents the rc value of a
 *                            32 bit instruction
 *      uint32_t *registers:  a pointer to the registers (an array of 8 
 *                            uint32_t values that represent the registers 
 *                            of the UM)
 * 
 * Return: void
 *
 * Expects
 *     expects that ra, rb, and rc are valid, and that the registers array 
 *     is not null and initalized properly
 * 
 * Notes:
 *      function is only used internally, so assumes input is valid. 
 ************************/
void instruction_3(uint32_t ra, uint32_t rb, uint32_t rc, uint32_t *registers) 
{
        registers[ra] = registers[rb] + registers[rc];
}

/********** instruction_4 ********
 *
 * function that given the ra, rb, rc values of an instruction and the 
 * registers, performs multiplication:
 * $r[A] := ($r[B] x $r[C]) mod 2^32
 *
 * Parameters:
 *      uint32_t ra:          uint32_t that represents the ra value of a
 *                            32 bit instruction
 *      uint32_t rb:          uint32_t that represents the rb value of a
 *                            32 bit instruction
 *      uint32_t rc:          uint32_t that represents the rc value of a
 *                            32 bit instruction
 *      uint32_t *registers:  a pointer to the registers (an array of 8 
 *                            uint32_t values that represent the registers 
 *                            of the UM)
 * 
 * Return: void
 *
 * Expects
 *     expects that ra, rb, and rc are valid, and that the registers array 
 *     is not null and initalized properly
 * 
 * Notes:
 *      function is only used internally, so assumes input is valid. 
 ************************/
void instruction_4(uint32_t ra, uint32_t rb, uint32_t rc, uint32_t *registers) 
{
       registers[ra] = (registers[rb] * registers[rc]) ;
}

/********** instruction_5 ********
 *
 * function that given the ra, rb, rc values of an instruction and the 
 * registers, performs division:
 * $r[A] := ($r[B] / $r[C]) mod 2^32
 *
 * Parameters:
 *      uint32_t ra:          uint32_t that represents the ra value of a
 *                            32 bit instruction
 *      uint32_t rb:          uint32_t that represents the rb value of a
 *                            32 bit instruction
 *      uint32_t rc:          uint32_t that represents the rc value of a
 *                            32 bit instruction
 *      uint32_t *registers:  a pointer to the registers (an array of 8 
 *                            uint32_t values that represent the registers 
 *                            of the UM)
 * 
 * Return: void
 *
 * Expects
 *     expects that ra, rb, and rc are valid, and that the registers array 
 *     is not null and initalized properly
 * 
 * Notes:
 *      function is only used internally, so assumes input is valid. 
 ************************/
void instruction_5(uint32_t ra, uint32_t rb, uint32_t rc, uint32_t *registers)
{
        registers[ra] = registers[rb] / registers[rc];
}

/********** instruction_6 ********
 *
 * function that given the ra, rb, rc values of an instruction and the 
 * registers, performs bitwise NAND:
 * $r[A] := ¬($r[B] ∧ $r[C])
 *
 * Parameters:
 *      uint32_t ra:          uint32_t that represents the ra value of a
 *                            32 bit instruction
 *      uint32_t rb:          uint32_t that represents the rb value of a
 *                            32 bit instruction
 *      uint32_t rc:          uint32_t that represents the rc value of a
 *                            32 bit instruction
 *      uint32_t *registers:  a pointer to the registers (an array of 8 
 *                            uint32_t values that represent the registers 
 *                            of the UM)
 * 
 * Return: void
 *
 * Expects
 *     expects that ra, rb, and rc are valid, and that the registers array 
 *     is not null and initalized properly
 * 
 * Notes:
 *      function is only used internally, so assumes input is valid. 
 ************************/
void instruction_6(uint32_t ra, uint32_t rb, uint32_t rc, uint32_t *registers)
{
        registers[ra] = ~(registers[rb] & registers[rc]);     
}

/********** instruction_8 ********
 *
 * function that given the rb and rc values of an instruction, the 
 * registers, and the segment , maps a segment to memory and adds it to the
 * correct spot in the Hanson Sequence ids.
 *
 * Parameters:
 *      uint32_t rb:          uint32_t that represents the rb value of a
 *                            32 bit instruction
 *      uint32_t rc:          uint32_t that represents the rc value of a
 *                            32 bit instruction
 *      uint32_t *registers:  a pointer to the registers (an array of 8 
 *                            uint32_t values that represent the registers 
 *                            of the UM)
 *      Seq_T *ids:           a pointer to the Hanson sequence that stores 
 *                            struct pointers containing the id of each segment
 *                            (its index in the sequence), the 64-bit address 
 *                            of the segment in memory, and the size of the 
 *                            segment.
 * 
 *      Stack_T *unmapped     a pointer to the Hanson stack that stores
 *                            the uint32_t pointers that represent the ids of 
 *                            the most recently unmapped segments 
 * 
 * Return: void
 *
 * Expects
 *     expects that rb, and rc are valid, the registers array 
 *     is not null and initalized properly, the ids Sequence is not null
 *     and is in its proper state, and that the unmapped Stack is not null
 *     and is in its proper state
 * 
 * Notes:
 *      function is only used internally, so assumes input is valid. 
 *      instruction_8 uses the map_sgement function defined in memory.h 
 *      because it manipulates memory.
 ************************/
void instruction_8(uint32_t rb, uint32_t rc, uint32_t *registers, 
                   Stack_T *unmapped, Seq_T *ids) 
{
      map_segment(rb,rc, registers, unmapped, ids );
}

/********** instruction_9 ********
 *
 * function that given rc value of an instruction, the 
 * registers, and the segment, unmaps a given segment in memory.
 * 
 * The segment $m[$r[C]] is unmapped. Future Map Segment instructions may 
 * reuse the identifier $r[C].
 *
 * Parameters:
 *      uint32_t rc:          uint32_t that represents the rc value of a
 *                            32 bit instruction
 *      uint32_t *registers:  a pointer to the registers (an array of 8 
 *                            uint32_t values that represent the registers 
 *                            of the UM)
 *      Seq_T *ids:           a pointer to the Hanson sequence that stores 
 *                            struct pointers containing the id of each 
 *                            segment
 *                            (its index in the sequence), the 64-bit address 
 *                            of the segment in memory, and the size of the 
 *                            segment.
 * 
 *      Stack_T *unmapped     a pointer to the Hanson stack that stores
 *                            the uint32_t pointers that represent the ids of 
 *                            the most recently unmapped segments 
 * 
 * Return: void
 *
 * Expects
 *     expects that rc is valid, the registers array 
 *     is not null and initalized properly, the ids Sequence is not null
 *     and is in its proper state, and that the unmapped Stack is not null
 *     and is in its proper state
 * 
 * Notes:
 *      function is only used internally, so assumes input is valid. 
 *      instruction_9 uses the unmap_sgement function defined in memory.h 
 *      because it manipulates memory.
 ************************/
void instruction_9(uint32_t rc, uint32_t *registers, Stack_T *unmapped, 
                   Seq_T *ids) 
{
        unmap_segment(rc, registers, unmapped, ids );
}


/********** instruction_10 ********
 *
 * function that given rc values of an instruction and the 
 * registers, writes the value in $r[C] to the I/O device immediately. 
 * Only values from 0 to 255 are allowed.
 *
 * Parameters:
 *      uint32_t rc:          uint32_t that represents the rc value of a
 *                            32 bit instruction
 *      uint32_t *registers:  a pointer to the registers (an array of 8 
 *                            uint32_t values that represent the registers 
 *                            of the UM)
 * 
 * Return: void
 *
 * Expects
 *     expects that rc is valid, and that the registers array 
 *     is not null and initalized properly. The UM is allowed to fail with an
 *     unchecked runtime error if the value is greater than 255.
 * 
 * Notes:
 *      function is only used internally, so assumes input is valid. 
 ************************/
void instruction_10(uint32_t rc, uint32_t *registers) 
{
        if (registers[rc] <= 255) {
                fprintf(stdout, "%c", registers[rc]);
        }      
}

/********** instruction_11 ********
 *
 * function that given rc values of an instruction and the 
 * registers, waits for input on the I/O device, loads $r[C] with the input 
 * (which must be a value from 0  to 255). If the end of input has been 
 * signaled, then $r[C] is loaded with a full 32-bit word in which every bit 
 * is 1.
 *
 * Parameters:
 *      uint32_t rc:          uint32_t that represents the rc value of a
 *                            32 bit instruction
 *      uint32_t *registers:  a pointer to the registers (an array of 8 
 *                            uint32_t values that represent the registers 
 *                            of the UM)
 * 
 * Return: void
 *
 * Expects
 *     expects that rc is valid, and that the registers array 
 *     is not null and initalized properly. The program expects that the 
 *     input must be a value from 0 to 255. The program also expects that
 *     input will be provided from the I/O device.
 *   
 * 
 * Notes:
 *      function is only used internally, so assumes input is valid. 
 ************************/
void instruction_11(uint32_t rc, uint32_t *registers) 
{
        int input ;
        input = getc(stdin);
        if (input == EOF) {
                registers[rc] = 0xFFFFFFFF;
        } else {
                assert(input <= 255 && input >= 0); 
                registers[rc] = (uint32_t)input;
        }         
}

/********** instruction_12 ********
 *
 * function that given the rb and rc values of an instruction, the 
 * registers, the Sequence ids, and a uint32_t counter, duplicates the segment
 * in $m[$r[B]], replaces $m[0] with the duplicate, and abandons what was 
 * previously in $m[0]. The program counter is set to point to $m[0][$r[C]]. 
 *
 * Parameters:
 *      uint32_t rb:          uint32_t that represents the rb value of a
 *                            32 bit instruction
 *      uint32_t rc:          uint32_t that represents the rc value of a
 *                            32 bit instruction
 *      uint32_t *registers:  a pointer to the registers (an array of 8 
 *                            uint32_t values that represent the registers 
 *                            of the UM)
 *      Seq_T *ids:           a pointer to the Hanson sequence that stores 
 *                            struct pointers containing the id of each segment
 *                            (its index in the sequence), the 64-bit address 
 *                            of the segment in memory, and the size of the 
 *                            segment.
 *      uint32_t *counter     a pointer to a uint32_t variable that represents
 *                            the program counter, or which index of segment 0
 *                            we are in within our execution loop
 *      
 * Return: void
 *
 * Expects
 *     expects that rb, and rc are valid, the registers array 
 *     is not null and initalized properly, the ids Sequence is not null
 *     and is in its proper state, and that counter is not null
 * 
 * Notes:
 *      function is only used internally, so assumes input is valid. 
 *      instruction_12 uses the load_program function defined in memory.h 
 *      because it manipulates memory.
 ************************/
void instruction_12(uint32_t rb, uint32_t rc, uint32_t *registers, Seq_T *ids,
                    uint32_t *counter) 
{
       load_program(rb, rc, registers, ids, counter);   
}

/********** instruction_13 ********
 *
 * function that given the ra, and val values of a load-val instruction and the
 * registers, loads val into $r[A]
 * 
 * Parameters:
 *      uint32_t ra:          uint32_t that represents the ra value of a
 *                            32 bit load-val instruction
 *      uint32_t val:         uint32_t that represents the val value of a
 *                            32 bit load-val instruction
 *      uint32_t *registers:  a pointer to the registers (an array of 8 
 *                            uint32_t values that represent the registers 
 *                            of the UM)
 * 
 * Return: void
 *
 * Expects
 *     expects that ra, and val are valid, and that the registers array 
 *     is not null and initalized properly
 * 
 * Notes:
 *      function is only used internally, so assumes input is valid. 
 ************************/
void instruction_13(uint32_t ra, uint32_t val, uint32_t *registers) 
{
        registers[ra] = val;
}


/********** execute_instruction ********
 *
 * Function that executes the instruction corresponding to a 32 bit word  
 *
 * Parameters:
 *      uint32_t opcode:      uint32_t that represents opcode of the 
 *                            instruction
 *      uint32_t word:        uint32_t word that represents the entire 
 *                            instruction
 *      uint32_t *registers:  a pointer to the registers (an array of 8 
 *                            uint32_t values that represent the registers 
 *                            of the UM)
 *      Seq_T *ids:           a pointer to the Hanson sequence that stores 
 *                            struct pointers containing the id of each segment
 *                            (its index in the sequence), the 64-bit address 
 *                            of the segment in memory, and the size of the 
 *                            segment.
 *      Stack_T *unmapped     a pointer to the Hanson stack that stores
 *                            the uint32_t pointers that represent the ids of 
 *                            the most recently unmapped segments 
 *      uint32_t *counter     a pointer to a uint32_t variable that represents
 *                            the program counter, or which index of segment 0
 *                            we are in within our execution loop
 *      
 * Return: void
 *
 * Expects
 *     expects that opcode is from 0-13, word represents a valid instruction,
 *     the ids Sequence is not null and is in its proper state, the unmapped
 *     stack is not null and is in its proper state, and that counter is 
 *     not null
 * 
 * Notes:
 *     if the opcode is not within range or the word doesn't represent a 
 *     valid instruction, the UM is allowed to fail. This function is called
 *     within our um.c.
 *    
 ************************/
void execute_instruction(uint32_t opcode, uint32_t word, uint32_t *registers, 
                        Seq_T ids, Stack_T unmapped, uint32_t *counter) 
{
        if (opcode != 12) {
                (*counter) ++; /* increments counter for each execution of the 
                                function */
        }
        uint32_t ra = 0;
        uint32_t rb = 0;
        uint32_t rc = 0;

        if (opcode == 13) { /* execute load-val instruction  */
                ra = get_lv_ra(word);
                uint32_t val = get_lv_val(word);
                instruction_13(ra, val, registers);     
        } else {
                ra = get_ra(word);
                rb = get_rb(word);
                rc = get_rc(word);

                if (opcode == 0) {
                        instruction_0(ra, rb, rc, registers);
                } if (opcode == 1) {
                        instruction_1(ra, rb, rc, registers, &ids);       
                }  if (opcode == 2) {
                        instruction_2(ra, rb, rc, registers, &ids);          
                }  if (opcode == 3) {
                        instruction_3(ra, rb, rc, registers);           
                }  if (opcode == 4) {
                        instruction_4(ra, rb, rc, registers);         
                }  if (opcode == 5) {
                        instruction_5(ra, rb, rc, registers);
                }  if (opcode == 6) {
                        instruction_6(ra, rb, rc, registers);              
                }  if (opcode == 8) {
                        instruction_8(rb, rc, registers, &unmapped, &ids);
                }  if (opcode == 9) {
                        instruction_9(rc, registers, &unmapped, &ids); 
                }  if (opcode == 10) {
                        instruction_10(rc, registers);                    
                }  if (opcode == 11) {
                        instruction_11(rc, registers);                   
                }  if (opcode == 12) {
                        instruction_12(rb, rc, registers, &ids, counter); 
                }
        }       
}