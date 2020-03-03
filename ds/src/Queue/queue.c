typedef struct queue_node
{
	void *data;
	struct sll_node *next;
}node_t;

struct queue
{
	node_t *front;
	node_t *rear;
};
