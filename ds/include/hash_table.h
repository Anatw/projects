/*******************************************************************************
the hash table is an array of dll_t variables.

                              Written by Anat Wax
						                 23-25 of April, 2020
							               Reviewer: Esti Binder
*******************************************************************************/
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

/* Hash Table type */
typedef struct hash_table hash_t;

#include <stddef.h> /* size_t */

/* 
* Hash Table Create: Create managing struct
* Receive: hash_func
*               * Receive: data - data to hash.
*               * Return: size_t with the index to insert into. the key should be given uniformly between 0 and the size of the table.
*          cmp_func - function to be used in need of comparison - such as in "find" function - to check wether the data in the table equal the desired data by the user.
*               * Receive: data1, data2 - data to compare.
*               * Return: 1 if data1 is bigger than data2.
*                         0 if they equal.
*                         -1 if data2 is smaller than data1.
*          table_size - size of table requested.
* Return: pointer to a new hash_t struct.			  
* Errors: return NULL if error occurred.
* Time Complexity: O(n) 
*/
hash_t *HashCreate(int (*cmp_func)(const void *data1, const void *data2),
                   size_t (*hash_func)(const void *data),
                   size_t table_size);

/* 
* Hash Table Destroy: Destroyes hash table.
* Receive: table - a hash table to destroy.	  
* Time Complexity: O(n) 
*/
void HashDestroy(hash_t *table);

/* 
* Hash Table Insert: Insert new element to hash table.
* Receive: table - a hash table to insert into.
*          data - pointer to data to insert.
* Return: 0 if succeed, any other number if not.
* Time Complexity: O(1) 
*/
int HashInsert(hash_t *table, void *data);

/* 
* Hash Table Remove: search for a specific element in the hase table and removes
*                    it from table.
* Receive: table - a hash table to remove from.
*          data - pointer to data to search and remove corresponding element.
* Time Complexity: best & avarage case: O(1) worst case: O(n)
*/
void HashRemove(hash_t *table, const void *data);

/* 
* Hash Table Find: Find element in hash table.
* Receive: table - a hash table to search in.
*          data - pointer to data to search for corresponding element.
* Return: - pointer to the element found.
          - NULL if no element found.
          - If there was a problem with DLLPushFront - return the data in the
            last valid node of the current dll.
* Time Complexity: best & avarage case: O(1) worst case: O(n)
*/
void *HashFind(const hash_t *table, const void *data);

/* 
* Hash Table Is Empty: Check if a hash table is empty.
* Receive: table - a hash table to check.
* Return: 1 if empty, 0 if not.
* Time Complexity: O(1)
*/
int HashIsEmpty(const hash_t *table);

/* 
* Hash Table For Each: Commit operation on each table element.
* Receive: table - a hash table to work on.
*          op_func -
*                   * Receive: data - to commit operation on.
*                              param - parameter for the function to work with.
*                   * Return: 0 to continue actions, any other number if not.
*          param - parameter for op_func to work with.
* Return: 0 if operation committed successfully on all elements in the table;
*         any other value: value returned from op_func.
* Time Complexity: O(n)
*/
int HashForEach(hash_t *table,
                int (*op_func)(void *data, void *param),
                const void *param);

/* 
* Hash Table Size: Get table size.
* Receive: table - a hash table to get its size.
* Return: size_t with table size.
* Time Complexity: O(table_size) (given by user...)
*/
size_t HashSize(const hash_t *table);

/* 
* Hash Table Load Factor: Get table load factor.
* Receive: table - a hash table to get its load factor.
* Return: table's load factor (# of elements / # of buckets).
* Time Complexity: O(n)
*/
double HashLoad(hash_t *table);

/* 
* Hash Table Standard Deviation: Get table's standard deviation.
* Receive: table - a hash table to get its standard deviation.
* Return: table's standard deviation.
* Time Complexity: O(n)
*/
double HashSD(hash_t *table);

#endif /* HASH_TABLE_H */
