#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE -1

/* Doubly LL node representation.
---------------------------------------------               -----------------------------------------------
|               |              |             |/            \ |              |             |               |
|     prev      |     data     |     next    |-------------- |     prev     |     data    |     next      |
|               |              |             |\            / |              |             |               |
---------------------------------------------               -----------------------------------------------
*/

typedef struct node
{
    int val;
    struct node* next;
    struct node* prev;
} node_t;

// Helpers
static void doubly_print_elements(node_t* head)
{
    node_t* curr = head;
    while (curr != NULL)
    {
        if (curr->next != NULL)
            printf("%d<->", curr->val);
        else
            printf("%d\n", curr->val);
        curr = curr->next;
    }
}

static int doubly_append(node_t* head, int val)
{
    node_t* curr = head;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = (node_t*) malloc(sizeof(node_t));
    if (curr->next == NULL)
        return -1;
    curr->next->val = val;
    curr->next->next = NULL;
    curr->next->prev = curr;
    return 0;
}

static int doubly_prepend(node_t** head, int val)
{
    node_t* curr = (node_t*) malloc(sizeof(node_t));
    if (curr == NULL)
        return -1;
    curr->val = val;
    curr->next = *head;
    curr->prev = NULL;
    *head = curr;
    return 0;
}

static int doubly_remove_head(node_t** head)
{
    if (*head == NULL)
        return -1;
    node_t* curr = (*head)->next;
    curr->prev = NULL;
    free(*head);
    *head = curr;
    return 0;
}

static int doubly_remove_tail(node_t* head)
{
    if (head == NULL)
        return -1;
    if (head->next == NULL)
    {
        free(head);
        return 0;
    }
    node_t* curr = head;
    while (curr->next->next != NULL)
    {
        curr = curr->next;
    }
    free(curr->next);
    curr->next = NULL;
    return 0;
}

static int doubly_remove_by_index(node_t* head, int idx)
{
    if (head == NULL)
        return -1;
    if (head->next == NULL)
    {
        free(head);
        return 0;
    }
    node_t* curr = head;
    for (int i=0; i<idx-2; i++)
    {
        curr = curr->next;
    }
    node_t* temp = curr->next;
    curr->next = temp->next;
    curr->next->prev = temp->prev;
    free(temp);
    return 0;
}

static int doubly_add_by_index(node_t* head, int idx, int val)
{
    if (head == NULL)
        return -1;

    node_t* curr = head;
    for (int i=0; i<idx-2; i++)
        curr = curr->next;
    node_t* temp = (node_t*) malloc(sizeof(node_t));
    if (temp == NULL)
        return -1;
    // 5<->10<->12<->15<->20
    temp->val = val;
    temp->next = curr->next;
    temp->prev = curr;
    curr->next = temp;
    return 0;
}

int main(void)
{
    /*
    * Assign 10 to head of LL
    * NULL<->10<->NULL
    */
    node_t* head = NULL;
    head = (node_t*) malloc(sizeof(node_t));
    if (head == NULL)
        return 1;
    head->val = 10;
    head->next = NULL;
    head->prev = NULL;
    doubly_print_elements(head);

    /*
    * Append 20 manually to LL
    * NULL<->10<->20<->NULL
    */
    head->next = (node_t*) malloc(sizeof(node_t));
    if (head->next == NULL)
        return FAILURE;
    head->next->val = 20;
    head->next->next = NULL;
    head->next->prev = head;
    doubly_print_elements(head);

    /*
    * Append 30 to LL
    * NULL<->10<->20<->30<->NULL
    */
    int rval = doubly_append(head, 30);
    if (rval < 0)
        return FAILURE;
    doubly_print_elements(head);
    
    /*
    * Prepend 5 to LL
    * NULL<->5<->10<->20<->30<->NULL
    */
    rval = doubly_prepend(&head, 5);
    if (rval < 0)
        return FAILURE;
    doubly_print_elements(head);

    /*
    * Remove 5 (head) from LL
    * NULL<->10<->20<->30<->NULL
    */
    rval = doubly_remove_head(&head);
    if (rval < 0)
        return FAILURE;
    doubly_print_elements(head);

    /*
    * Remove 30 (tail) from LL
    * NULL<->10<->20<->NULL
    */
    rval = doubly_remove_tail(head);
    if (rval < 0)
        return FAILURE;
    doubly_print_elements(head);

    /*
    * Append 30, 40 and 50 to LL
    * NULL<->10<->20<->30<->40<->50<->NULL
    */
    rval = doubly_append(head, 30);
    if (rval < 0)
        return FAILURE;
    doubly_print_elements(head);

    rval = doubly_append(head, 40);
    if (rval < 0)
        return FAILURE;
    doubly_print_elements(head);

    rval = doubly_append(head, 50);
    if (rval < 0)
        return FAILURE;
    doubly_print_elements(head);

    /*
    * Remove 3rd element (30) from LL
    * NULL<->10<->20<->40<->50<->NULL
    */
    rval = doubly_remove_by_index(head, 3);
    if (rval < 0)
        return FAILURE;
    doubly_print_elements(head);

    /*
    * Add 30 as 3rd element to LL
    * NULL<->10<->20<->30<->40<->50<->NULL
    */
    rval = doubly_add_by_index(head, 3, 30);
    if (rval < 0)
        return FAILURE;
    doubly_print_elements(head);

    return SUCCESS;
}