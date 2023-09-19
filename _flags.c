#include "main.h"

/**
 * get_flags - Extracts and calculates active flags from a format string
 * @format: Formatted string containing conversion specifiers
 * @i: Current position within the format string
 *
 * Return: Flags representing active formatting options
 */
int get_flags(const char *format, int *i)
{
    /* Define characters representing formatting flags */
    const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};

    /* Define corresponding flag values */
    const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

    int j, curr_i;
    int flags = 0;

    /* Loop through the format string starting from the current position */
    for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
    {
        /* Check if the current character is one of the flag characters */
        for (j = 0; FLAGS_CH[j] != '\0'; j++)
        {
            if (format[curr_i] == FLAGS_CH[j])
            {
                /* Set the corresponding flag bit */
                flags |= FLAGS_ARR[j];
                break;
            }
        }

        /* If the character doesn't match any flags, exit the loop */
        if (FLAGS_CH[j] == '\0')
            break;
    }

    /* Update the position pointer to the end of the extracted flags */
    *i = curr_i - 1;

    /* Return the calculated flags */
    return flags;
}
