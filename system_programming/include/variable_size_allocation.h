struct vsa
{
	
	size_t capacity;
	size_t next_free;
	size_t free_space;
}; /* vsa_t */

typedef struct block_header
{
    size_t block_size;   /* Offset (in bytes) from the start of the FSA. */
    vsa_t *vsa_pool;
} block_t;

fsa_t *VSAInit(void *memory, size_t seg_size);
void *VSAAlloc(vsa_t *vsa_pool size_t block_size);
void VSAFree(void *block_ptr);
size_t VSACountFree(vsa_t *vsa_pool);
