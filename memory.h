/*
 *     memory.h
 *     Sophie Zhou (szhou13), Angela Yan (yyan08)
 *     11/19/2024
 *     CS40 HW6 
 * 
 *     Purpose: memory.h defines instructions that deal with and maniuplate
 *              memory. It defines a segement struct, which includes the 
 *              64 bit address for each segment, an integer representing the
 *              segment's id, and the size of the segment. Pointers to this 
 *              struct will be placed in the Hanson sequence (made using 
 *              make_sequence(), that "coatchecks" each segment). make_stack()
 *              creates a new Hanson stack, which we use to keep track of 
 *              unmapped indices. The functions defined in memory.h deal 
 *              with these data structures. 
 */


#ifndef MEMORY_INCLUDED
#define MEMORY_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "stack.h"
#include "seq.h"
#include "assert.h"
 

struct segment {
        int id; 
        uint32_t (*address);
        int size;
};

void initialize_zero(FILE *fp, int arrsize, Seq_T *ids);

Seq_T make_sequence();

Stack_T make_stack();

void load_memory(uint32_t ra, uint32_t rb, uint32_t rc, uint32_t *registers, 
                Seq_T *ids);

void store_memory (uint32_t ra, uint32_t rb, uint32_t rc, uint32_t *registers, 
                Seq_T *ids);

void map_segment(uint32_t rb, uint32_t rc, uint32_t *registers, 
                Stack_T *unmapped, Seq_T *ids);

uint32_t free_memory(int seg_num, Seq_T *ids, bool seg0, bool arr);

void unmap_segment (uint32_t rc, uint32_t *registers, Stack_T *unmapped, 
                   Seq_T *ids);

void load_program(uint32_t rb, uint32_t rc, uint32_t *registers, Seq_T *ids,
                  uint32_t *counter);

void free_all(Seq_T ids, Stack_T unmapped);



#endif

