#include "main.h"

/**
 * get_size - Extracts and calculates the size specifier for formatting
 * @format: Formatted string containing conversion specifiers
 * @i: Current position within the format string
 *
 * Return: Size specifier for formatting, or 0 if not specified
 */
int get_size(const char *format, int *i)
{
    int curr_i = *i + 1;
    int size = 0;

    /* Check if size specifier 'l' or 'h' is present */
    if (format[curr_i] == 'l')
        size = S_LONG;
    else if (format[curr_i] == 'h')
        size = S_SHORT;

    /* Update the position pointer based on whether size specifier is found */
    if (size == 0)
        *i = curr_i - 1;
    else
        *i = curr_i;

    /* Return the calculated size specifier */
    return size;
}
