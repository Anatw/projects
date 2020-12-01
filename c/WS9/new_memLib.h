#ifndef MEMFUNCS_H
#define MEMFUNCS_H

void *Memset(void *str, int c, size_t n);
void *Memcpy(void *dest, const void *src, size_t n);
void *Memmove(void *dest, const void *src, size_t n);

/* returns the power of 2 which is equal to word_size */
int GetPowOfTwo(int word_size);

#endif
