#ifndef NEW_MEMLIB_H
#define NEW_MEMLIB_H

void *Memset(void *str, int c, size_t n);
void *Memcpy(void *dest, const void *src, size_t n);
void *Memmove(void *dest, const void *src, size_t n);

#endif /* NEW_MEMLIB_H */
