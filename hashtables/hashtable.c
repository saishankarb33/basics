#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define NAME_MAX 256
#define TABLE_SIZE 10
#define DELETED_NODE (person_t*) (0xFFFFFFFFFFFFFULL)

typedef struct person {
    char name[NAME_MAX];
    int age;
} person_t;

person_t* hash_table[TABLE_SIZE];

unsigned int hash(char* name)
{
    int len = strnlen(name, NAME_MAX);
    unsigned int hash_val = 0;
    for (int i=0; i<len; i++)
    {
        hash_val += name[i];
        // Generate something in the range (0 - TABLE_SIZE-1)
        hash_val = (hash_val * name[i]) % TABLE_SIZE;
    }
    return hash_val;
}

void init_hash_table(void)
{
    for (int i=0; i<TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

void print_hash_table(void)
{
    printf("START\n");
    for (int i=0; i<TABLE_SIZE; i++)
    {
        if (hash_table[i] == NULL) {
            printf("\t%i\t---\n", i);
        } else if (hash_table[i] == DELETED_NODE) {
            printf("\t%i\t<deleted>\n", i);
        } else {
            printf("\t%i\t%s\n", i, hash_table[i]->name);
        }
    }
    printf("END\n");
}

bool hash_table_insert(person_t* p)
{
    if (p == NULL) return false;
    int index = hash(p->name);

    for (int i=0; i<TABLE_SIZE; i++)
    {
        // For dealing with collisions
        int try = (i+index) % TABLE_SIZE;
        if (hash_table[try] == NULL)
        {
            hash_table[try] = p;
            return true;
        }
    }
    return false;
}

person_t* hash_table_lookup(char* name)
{
    int index = hash(name);
    for (int i=0; i<TABLE_SIZE; i++)
    {
        int try = (i+index) % TABLE_SIZE;

        if (hash_table[try] == NULL) return NULL;
        // Skip deleted nodes
        if (hash_table[try] == DELETED_NODE) continue;

        if (hash_table[try] != NULL &&
            strncmp(hash_table[try]->name, name,
                sizeof(hash_table[try]->name))==0)
        {
            return hash_table[try];
        }
    }
    return NULL;
}

person_t* hash_table_delete(person_t* p)
{
    if (p == NULL) return NULL;
    int index = hash(p->name);
    for (int i=0; i<TABLE_SIZE; i++)
    {
        int try = (i+index) % TABLE_SIZE;
        // Skip deleted node
        if (hash_table[try] == DELETED_NODE) continue;

        if (hash_table[try] != NULL &&
            strncmp(hash_table[try]->name, p->name,
                sizeof(hash_table[try]->name))==0)
        {
            person_t* tmp = hash_table[try];
            hash_table[try] = DELETED_NODE;
            return tmp;
        }
    }
    return NULL;
}

int main(void)
{
    init_hash_table();
    print_hash_table();

    // Insert into hashtable
    person_t aaron = {.name="Aaron", .age=21};
    person_t jenny = {.name="Jenny", .age=24};
    person_t john = {.name="John", .age=18};
    person_t emma = {.name="Emma", .age=22};
    person_t nicole = {.name="Nicole", .age=20};
    person_t mark = {.name="Mark", .age=25};
    person_t elaine = {.name="Elaine", .age=35};
    person_t jerry = {.name="Jerry", .age=38};
    person_t george = {.name="George", .age=39};
    person_t kramer = {.name="Kramer", .age=36};

    hash_table_insert(&aaron);
    hash_table_insert(&jenny);
    hash_table_insert(&john);
    hash_table_insert(&emma);
    hash_table_insert(&nicole);
    hash_table_insert(&mark);
    hash_table_insert(&elaine);
    hash_table_insert(&jerry);
    hash_table_insert(&george);
    hash_table_insert(&kramer);

    print_hash_table();

    // Hashtable lookup
    person_t* tmp = hash_table_lookup("Jerry");
    if (tmp == NULL)
        printf("Did not find Jerry\n");
    else
        printf("Found Jerry\n");

    tmp = hash_table_lookup("Martin");
    if (tmp == NULL)
        printf("Did not find Martin\n");
    else
        printf("Found Martin\n");

    // Delete from hashtable
    hash_table_delete(&jerry);
    hash_table_delete(&george);
    hash_table_delete(&elaine);
    hash_table_delete(&kramer);
    print_hash_table();

    return 0;
}
