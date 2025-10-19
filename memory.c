/*
 *     memory.c
 *     Sophie Zhou (szhou13), Angela Yan (yyan08)
 *     11/19/2024
 *     CS40 HW6 
 * 
 *     Purpose: memory.c contains implementation of the memory class. These
 *     functions are used by um.c and instructions.c to make changes to 
 *     memory. 
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "bitpack.h"
#include "stack.h"
#include "seq.h"
#include "assert.h"
#include "memory.h"

/********** initialize_zero ********
 *
 * Function initializes the 0th segment with the instructions provided in the
 * input um file. The new segment is stored in the Sequence ids.
 * 
 * Parameters:
 *      FILE *fp:             file pointer that represents the input file
 *                            holding all the instructions
 *      int arrsize:          integer representing the size of segment 0,
 *                            or how many instructions the input file holds
 *      Seq_T *ids:           a pointer to the Hanson sequence that stores 
 *                            struct pointers containing the id of each segment 
 *                            (its index in the sequence), the 64-bit address 
 *                            of the segment in memory, and the size of the 
 *                            segment.
 *     
 * Return: void
 *
 * Expects
 *     expects that the file pointer is not null and is a valid .um file,
 *     the arrsize is correct corresponding to the input file, and that 
 *     the Sequence is not null.
 * 
 * Notes:
 *     if the opcode is not within range or the word doesn't represent a 
 *     valid instruction, the UM is allowed to fail. This function is called
 *     within our um.c.
 *    
 ************************/
void initialize_zero(FILE *fp, int arrsize, Seq_T *ids) 
{

        /* make new segment */
        uint32_t(*address) = malloc(arrsize * sizeof(uint32_t)); 
        assert(address!= NULL);
        
        /* make instance of struct */
        struct segment *new_segment = malloc(sizeof(struct segment)); 
        assert(new_segment != NULL);
        new_segment->address = address; 
        new_segment->id = 0; 
        new_segment->size = arrsize;
        Seq_addhi(*ids, new_segment); /* add to sequence */

        /* initialize segment with instructions inside input file */
        for (int i = 0; i < arrsize; i++ ) {         
                char ch;
                uint32_t word = 0;
                for (int i = 0; i < 4; i ++) {
                        ch = getc(fp);
                        word = Bitpack_newu(word, 8, 24 - 8*i, (uint8_t)ch);
                }
                address[i] = word;  
        }
}

/********** make_sequence ********
 *
 * Function that creates a new Hanson Sequence
 *     
 * Return: the new instance of a Hanson Sequence
 ************************/
Seq_T make_sequence() 
{
        Seq_T ids = Seq_new(10); /* make sequence */
        assert(ids != NULL);
        return ids;
}

/********** make_stack ********
 *
 * Function that creates a new Hanson Stack
 *     
 * Return: the new instance of a Hanson Stack
 ************************/
Stack_T make_stack() 
{
        Stack_T unmapped = Stack_new(); /* make stack */
        assert(unmapped != NULL);
        return unmapped;
}

/********** load_memory ********
 *
 * function that performs a segmented load:
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
 *      this function is used in instructions.c to implement the instruction_1
 *      helper function, called inside execute_instruction
 ************************/
void load_memory(uint32_t ra, uint32_t rb, uint32_t rc, uint32_t *registers, 
                Seq_T *ids) 
{
        struct segment *info = Seq_get(*ids, registers[rb]);
        uint32_t *array = info->address;
        int index = registers[rc];
        registers[ra] = array[index];
}

/********** store_memory ********
 *
 * function performs a segmented store:
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
 *      this function is used in instructions.c to implement the instruction_2
 *      helper function, called inside execute_instruction
 ************************/
void store_memory (uint32_t ra, uint32_t rb, uint32_t rc, uint32_t *registers, 
                   Seq_T *ids) 
{
        struct segment *array = Seq_get(*ids, registers[ra]);
        array->address[registers[rb]] = registers[rc];
}

/********** map_segment ********
 *
 * function that maps a segment to memory and adds it to the
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
 *      this function is used in instructions.c to implement the instruction_8
 *      helper function, called inside execute_instruction
 ************************/
void map_segment(uint32_t rb, uint32_t rc, uint32_t *registers, 
                Stack_T *unmapped, Seq_T *ids) 
{

        /* creates new segment */
        uint32_t *address = malloc(registers[rc] * (sizeof (uint32_t))); 
        assert(address!= NULL);
        for (uint32_t i = 0; i < registers[rc]; i++) {
                address[i]  = (uint32_t)0; /* initializes all indices to 0 */
        }
        
        /* if there are no indices to be reused */
        if (Stack_empty(*unmapped)){ 
                struct segment *new_segment = malloc(sizeof(struct segment)); 
                new_segment->address = address; 
                new_segment -> size = registers[rc];
                new_segment->id = Seq_length(*ids);
                
                Seq_addhi(*ids, new_segment); /* add to back of sequence */
                registers[rb] = new_segment->id; 
        
        /* else, add to last unmapped index in the sequence */  
        } else { 
                uint32_t index = (uint32_t)(uintptr_t)Stack_pop(*unmapped); 
                struct segment *old_segment = Seq_get(*ids, index);
                old_segment->id = index;
                old_segment-> address = address;
                old_segment->size = registers[rc];
                registers[rb] = index;       
        }
}

/********** free_memory ********
 *
 * function that frees memory stored in the index Sequence. 
 *
 * Parameters:
 *      int seg_num:          integer representing the id of the segment we 
 *                            want to free
 *      Seq_T *ids:           a pointer to the Hanson sequence that stores 
 *                            struct pointers containing the id of each segment 
 *                            (its index in the sequence), the 64-bit address 
 *                            of the segment in memory, and the size of the 
 *                            segment.
 *      bool seg0:            boolean representing if we want to free the 
 *                            struct pointer
 *      bool arr:             boolean representing if we want to free the 
 *                            array address
 *                     
 * Return: void
 *
 * Expects
 *     expects that seg_num is within range of the Sequence, and that sequence
 *     is not null.
 ************************/
uint32_t free_memory(int seg_num, Seq_T *ids, bool seg0, bool arr) 
{
        assert(ids != NULL);
        uint32_t index = 0;
        
        struct segment *old_segment = Seq_get(*ids, seg_num);
        if (old_segment != NULL) { 
                index = old_segment -> id; 
                uint32_t *array = old_segment->address; 
                if (arr) {
                        free(array);         
                }
                if (seg0) { 
                        free (old_segment);
                }
        }
        return index;  /* return id of segment we just freed */
}


/********** unmap_segment ********
 *
 * function that given rc value of an instruction, the 
 * registers, and the segment, unmaps a given segment in memory.
 *
 * Parameters:
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
 *      this function is used in instructions.c to implement the instruction_9
 *      helper function, called inside execute_instruction
 ************************/
void unmap_segment (uint32_t rc, uint32_t *registers, Stack_T *unmapped, 
                    Seq_T *ids) 
{
        int seg_num = registers[rc];
        uint32_t index = free_memory(seg_num, ids, false, true);
        Stack_push(*unmapped, (void*)(uintptr_t)index);
}

/********** load_program ********
 *
 * function that duplicates the segment in $m[$r[B]], replaces $m[0] with the 
 * duplicate, and abandons what was previously in $m[0]. The program counter is 
 * set to point to $m[0][$r[C]]. 
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
 *      this function is used in instructions.c to implement the instruction_12
 *      helper function, called inside execute_instruction
 ************************/
void load_program(uint32_t rb, uint32_t rc, uint32_t *registers, Seq_T *ids, 
                uint32_t *counter) 
{
        *counter = registers[rc]; 
        if (registers[rb] == 0) {
                return;
        } 

        uint32_t i = free_memory(0, ids, true, true); /* free segment 0 */
        (void) i;

        /* make a copy of segment m[rb]*/
        struct segment* old = Seq_get(*ids, registers[rb]); 
        int arrsize = old -> size;
        uint32_t *address = malloc(arrsize * (sizeof (uint32_t))); 
        assert(address!= NULL);
        
        for (int i = 0; i < arrsize; i++) { /* copy every element over */
                address[i]  = old->address [i];
        }

        /* make instance of struct */
        struct segment *new_segment = malloc(sizeof(struct segment)); 
        //printf("size of segment is %lu\n", sizeof(struct segment));
        new_segment->address = address;
        new_segment->id = 0;
        new_segment->size = arrsize;
        
        registers[rb] = 0;
        Seq_put(*ids, 0, new_segment);  /* put new segment into Sequence */ 
}

/********** free_all ********
 *
 * function that frees all heap-allocated memory at the end of program 
 * execution
 *
 * Parameters:
 *      Seq_T ids:            a Hanson sequence that stores 
 *                            struct pointers containing the id of each segment 
 *                            (its index in the sequence), the 64-bit address 
 *                            of the segment in memory, and the size of the 
 *                            segment.
 *     Stack_T *unmapped      a Hanson stack that stores
 *                            the uint32_t pointers that represent the ids of 
 *                            the most recently unmapped segments 
 *                     
 * Return: void
 *
 * Expects
 *     expects that ids is not null, and unmapped is not null
 ************************/
void free_all(Seq_T ids, Stack_T unmapped) {
        
        /* identifies all of the indices in the sequence that are not storing
        memory addresses */
        while (!Stack_empty(unmapped)) {
                uint32_t index = (uint32_t)(uintptr_t)Stack_pop(unmapped); 
                struct segment *empty = (void*)(uintptr_t)Seq_get(ids, index);
                empty->size = -10;
        }

        if (Seq_length(ids) != 0) {
                
                for (int i = 0; i < Seq_length(ids); i++) {   
                        struct segment *old_segment = Seq_get(ids, i); 

                        /* if index stores memory address, free both struct 
                        pointer and address */
                        if (old_segment->size != -10) {    
                             free_memory(i, &ids, true, true);

                        /* if index doesn't memory address, just free 
                        struct pointer */
                        } else {
                                free_memory(i, &ids, true, false);
                        }     
                }
        }
        Seq_free(&ids);
        Stack_free(&unmapped);  
}

    
      

 



       