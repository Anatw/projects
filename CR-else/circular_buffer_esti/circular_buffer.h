/******************************************************************************
* File: circular_buffer.h
* Auther: Esti Binder
* Reviewed by: 
* Description: header file of operation functions on Queue
*******************************************************************************/

#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <unistd.h> /*ssize_t*/
#include <stddef.h> /*size_t*/

typedef struct circular_buffer circular_buffer_t;

/*circular buffer Create:                                                     */
/*Return: pointer to new circular buffer                                      */
/*Errors: return NULL if can't allocate memory for buffer                     */
circular_buffer_t *CBCreate(size_t capacity);

/*circular buffer Destroy:                                                    */
/*Recieve: pointer to buffer                                                  */
/*Action: free the allocated memory in buffer                                 */
void CBDestroy(circular_buffer_t *cb);

/*circular buffer Read:                                                       */
/*Recieve: pointer to buffer, buffer and count(num of chars to read from cb)  */
/*Action: move data from front of buffer to buf                               */         
ssize_t CBRead(circular_buffer_t *cb, void *buf, size_t count);

/*circular buffer Write:                                                      */
/*Recieve: pointer to buffer, buffer and count(num of chars to read from buf) */
/*Action: move data from buf to end of buffer                                 */         
ssize_t CBWrite(circular_buffer_t *cb, const void *buf, size_t count);

/*circular buffer FreeSpace:                                                  */
/*Recieve: const pointer to buffer                                            */
/*Return: free space                                                          */
size_t CBFreeSpace(const circular_buffer_t *cb);

/*circular buffer Size:                                                       */
/*Recieve: const pointer to buffer                                            */
/*Return: number of element in byffer                                         */
size_t CBSize(const circular_buffer_t *cb);

/*circular buffer Is Empty:                                                   */
/*Recieve: const pointer to buffer                                            */
/*Return: 1 if buffer is empty and 0 if buffer is not empty                   */
int CBIsEmpty(const circular_buffer_t *cb);

#endif
