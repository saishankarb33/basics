#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct node
{
    int val;
    struct node* next;
} node_t;

// Queues are FIFO, unless of course you believe in anarchy...
typedef struct queue
{
    node_t* head;
    node_t* tail;
} queue_t;

// Helpers
static void init_queue(queue_t** q)
{
    (*q)->head = NULL;
    (*q)->tail = NULL;
}

static int enqueue(queue_t* q, int val)
{
    node_t* newnode = (node_t*) malloc(sizeof(node_t));
    if (newnode == NULL)
        return -1;
    newnode->val = val;
    newnode->next = NULL;

    if (q->head == NULL)
        q->head = newnode;

    if (q->tail != NULL)
    {
        q->tail->next = newnode;
    }        
    q->tail = newnode;

    return 0;
}

static int dequeue(queue_t* q)
{
    if (q->head == NULL) return -1;

    node_t* tmp = q->head;
    q->head = q->head->next;
    // If queue is empty
    if (q->head == NULL)
        q->tail == NULL;
    free(tmp);
    return 0;
}

static void queue_print_elements(queue_t* q)
{
    node_t* tmp = q->head;
    while (tmp != NULL)
    {
        if (tmp->next != NULL)
            printf("%d->", tmp->val);
        else
            printf("%d\n", tmp->val);
        tmp = tmp->next;
    }
}

int main(void)
{
    queue_t* q;
    /*
    * Create a queue with some elements (aka, "enqueue")
    * 10->20->30->NULL
    */
    init_queue(&q);
    int rval = enqueue(q, 10);
    if (rval < 0)
        return FAILURE;
    rval = enqueue(q, 20);
    if (rval < 0)
        return FAILURE;
    rval = enqueue(q, 30);
    if (rval < 0)
        return FAILURE;
    queue_print_elements(q);

    /*
    * Dequeue
    * 20->30->NULL
    */
    rval = dequeue(q);
    queue_print_elements(q);

    return SUCCESS;
}
