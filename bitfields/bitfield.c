#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Define some bitfields
#define FLAG_A 0
#define FLAG_B 1
#define FLAG_C 2
#define FLAG_D 3
#define FLAG_E 4
// To demonstrate out-of-range bitfields won't work (note the use of uint8_t range)
#define FLAG_F 8

// Helpers
void set_bit(uint8_t* num, uint8_t bit)
{
    *num |= (1<<bit);
}

void set_bit_all(uint8_t* num)
{
    for (uint8_t i=0; i<sizeof(num); i++)
    {
        *num |= (1<<i);
    }
}

void clear_bit(uint8_t* num, uint8_t bit)
{
    *num &= ~(1<<bit);
}

void clear_bit_all(uint8_t* num)
{
    for (uint8_t i=0; i<sizeof(num); i++)
    {
        *num &= ~(1<<i);
    }
}

// Eliminate redundancy in set/clear methods
void set_and_clear_bit(uint8_t* num, uint8_t bit, bool set)
{
    bool is_set = *num & (1<<bit);
    // Prevents duplicate set/clear
    if (is_set != set)
    {
        if (set)
            *num |= (1<<bit);
        else
            *num &= ~(1<<bit);
    }
}

bool is_set_bit(uint8_t num, uint8_t bit)
{
    return num & (1<<bit);
}

void print_set_bitfields(uint8_t num)
{
    if (is_set_bit(num, FLAG_A))
        printf("FLAG_A is set\n");

    if (is_set_bit(num, FLAG_B))
        printf("FLAG_B is set\n");

    if (is_set_bit(num, FLAG_C))
        printf("FLAG_C is set\n");

    if (is_set_bit(num, FLAG_D))
        printf("FLAG_C is set\n");

    if (is_set_bit(num, FLAG_E))
        printf("FLAG_E is set\n");

    // Out-of-range bitfield, will never be set
    if (is_set_bit(num, FLAG_F))
        printf("FLAG_F is set\n");
}

int main(void)
{
    uint8_t num=0;
    printf("======== set_bit() ========\n");
    set_bit(&num, FLAG_A);
    set_bit(&num, FLAG_B);
    set_bit(&num, FLAG_C);
    set_bit(&num, FLAG_D);
    set_bit(&num, FLAG_E);

    printf("======== clear_bit() ========\n");
    clear_bit(&num, FLAG_B);
    clear_bit(&num, FLAG_D);

    print_set_bitfields(num);

    // Clear all bitfields
    clear_bit_all(&num);

    // Issue duplicate set/clear bitfields
    printf("======== set_and_clear_bit() ========\n");
    set_and_clear_bit(&num, FLAG_A, true);
    set_and_clear_bit(&num, FLAG_A, true);
    set_and_clear_bit(&num, FLAG_B, true);
    set_and_clear_bit(&num, FLAG_B, true);
    set_and_clear_bit(&num, FLAG_C, true);
    set_and_clear_bit(&num, FLAG_C, true);
    set_and_clear_bit(&num, FLAG_D, true);
    set_and_clear_bit(&num, FLAG_D, true);
    set_and_clear_bit(&num, FLAG_E, true);
    set_and_clear_bit(&num, FLAG_E, true);
    set_and_clear_bit(&num, FLAG_F, true);
    set_and_clear_bit(&num, FLAG_F, true);

    set_and_clear_bit(&num, FLAG_B, false);
    set_and_clear_bit(&num, FLAG_B, false);
    set_and_clear_bit(&num, FLAG_D, false);
    set_and_clear_bit(&num, FLAG_D, false);

    print_set_bitfields(num);

    return 0;
}
