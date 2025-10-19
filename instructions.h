#ifndef INSTRUCTIONS_INCLUDED
#define INSTRUCTIONS_INCLUDED
#include <stdbool.h>
#include <stdint.h>
#include "stack.h"
#include "seq.h"
#include "memory.h"

void execute_instruction(uint32_t opcode, uint32_t word, uint32_t *registers,
 Seq_T ids, Stack_T unmapped, uint32_t *counter);

 #endif