#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct node
{
    int val;
    struct node* next;
} node_t;

typedef struct stack
{
    node_t* head;
} stack_t;

// Helpers

static void init_stack(stack_t** s)
{
    (*s)->head = NULL;
}

static int stack_push(stack_t* s, int val)
{
    node_t* newnode = (node_t*) malloc(sizeof(node_t));
    if (newnode == NULL)
        return -1;
    newnode->val = val;
    newnode->next = s->head;
    s->head = newnode;
    return 0;
}

static int stack_pop(stack_t* s)
{
    if (s->head == NULL) return -1;

    node_t* tmp = s->head;
    s->head = s->head->next;
    free(tmp);
    return 0;
}

static void stack_print_elements(stack_t* s)
{
    node_t* curr = s->head;
    while (curr != NULL)
    {
        if (curr->next != NULL)
            printf("%d->", curr->val);
        else
            printf("%d\n", curr->val);
        curr = curr->next;
    }
}

int main(void)
{
    stack_t *s;
    init_stack(&s);
    /*
    * Create a stack with some elements (aka, "push")
    * 10->20->30
    */
    int rval = stack_push(s, 10);
    if (rval < 0)
        return FAILURE;
    rval = stack_push(s, 20);
    if (rval < 0)
        return FAILURE;
    rval = stack_push(s, 30);
    if (rval < 0)
        return FAILURE;
    stack_print_elements(s);

    /*
    * Remove elements from stack (aka, "pop")
    */
    rval = stack_pop(s);
    // Expected output: 10->20
    stack_print_elements(s);

    // Expected output: 10
    rval = stack_pop(s);
    stack_print_elements(s);

    return SUCCESS;
}
