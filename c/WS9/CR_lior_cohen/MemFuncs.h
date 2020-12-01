/****************************************************************************
* File Name: MemFuncs.h														*
* Writer: Lior Cohen														*
* Date: 23/02/2020														    *
* Purpose: The header file for the MemFuncs.c								*
* Code Reviwer: Anat Wax													*
*****************************************************************************/
#ifndef MEMFUNCS_H
#define MEMFUNCS_H

/* Sets data in a block of memory */
void *Memset(void *str, int c, size_t n);

/* Copies data from a source to a destination */
void *Memcpy(void *dest, const void *src, size_t n);

/* Moves data from a source to detination */
void *Memmove(void *dest, const void *src, size_t n);

/* returns the power of 2 which is equal to word_size */
int GetPowOfTwo(int word_size);

#endif
