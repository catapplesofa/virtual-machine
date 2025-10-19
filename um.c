/*
 *     um.c
 *     Sophie Zhou (szhou13), Angela Yan (yyan08)
 *     11/19/2024
 *     CS40 HW6 
 * 
 *     Purpose: um.c emualtes a "Universal Machine" (UM). The executable
 *     takes a single argument (the pathnmae for a file .um) that contains
 *     machine instructions for the emulator to execute. 
 */

#include <stdio.h>
#include <stdlib.h>
#include "Word.h"
#include "instructions.h"
#include <assert.h>
#include "seq.h"
#include "stack.h"

/********** main TO DO!!!!!!! ********
 *
 * void function that checks that the given Pnm_ppm image has an even width
 * and height. If it does not, it simply updates the Pnm_ppm image passed in,
 * deleting one row/column to make it even. 
 *
 * Parameters:
 *      Pnm_ppm pixmap:         an instance of a Pnm_ppm image to be checked 
 *      Pnm_ppm new_pixmap:     updated in the function, representing the 
                                Pnm_ppm image that has even dimensions
 * Return: void
 *
 * Expects
 *      pixmap and new_pixmap is not NULL. 
 * Notes:
 *      funciton is only used internally, so assumes input is valid
 ************************/
int main (int argc, char* argv[]) {
        FILE *fp = NULL;
        long int filesize;
        
        /* invalid input */
        if (argc != 2) {
                fprintf(stderr, "usage: %s [filename]\n", argv[0]);
                exit(1);
        }

        /* open file */
        fp = fopen(argv[1], "r");
        assert(fp != NULL);
       
        /* get file size */
        fseek(fp, 0L, SEEK_END);  
        filesize = ftell(fp); 
        assert((filesize % 4) == 0); /* make sure that file is properly 
                                        formatted */
        int arrsize = filesize / 4; /* number of instructions */
        fseek(fp, 0L, SEEK_SET);
      
        /* Hanson sequence used to "coatcheck" segments in memory */
        Seq_T ids = make_sequence(); 
        /* Hanson stack used to track unmapped segments */
        Stack_T unmapped = make_stack(); 
        initialize_zero(fp, arrsize, &ids); /* initialize 0th segment */

        uint32_t registers[8] ={ 0 , 0, 0, 0, 0, 0, 0, 0}; /* initialize 
                                                            registers */
       
        uint32_t counter = 0;
        struct segment *seg = Seq_get(ids, 0);
        int length =  seg->size;
        assert(length == arrsize);
       
        /* iterate through segment 0, executing instructions */
        while (counter < (uint32_t)length) { 
                struct segment *seg = Seq_get(ids, 0);
                uint32_t word = seg->address[counter];
                uint32_t opcode = get_opcode(word);
              
                if (opcode == 7) {  /* halt instruction */   
                        break; 
                } else {
                        execute_instruction(opcode, word, registers, ids, 
                                            unmapped, &counter);  
                } 
                if (opcode == 12 ) { /* load program instruction */
                        struct segment *new_seg = Seq_get(ids, 0);
                        length = new_seg->size;
                }
        }  
        free_all(ids, unmapped);
        fclose(fp);

        return 0;
}
