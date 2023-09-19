#include "main.h"

/**
 * get_width - Extracts and calculates the width specifier for formatting
 * @format: Formatted string containing conversion specifiers
 * @i: Current position within the format string
 * @list: Variable argument list for extracting width if it's a wildcard
 *
 * Return: Width specifier for formatting
 */
int get_width(const char *format, int *i, va_list list)
{
    int curr_i;
    int width = 0;

    /* Iterate through characters to find the width specifier */
    for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
    {
        if (is_digit(format[curr_i]))
        {
            width *= 10;
            width += format[curr_i] - '0';
        }
        else if (format[curr_i] == '*')
        {
            /* Handle wildcard width specifier, extract from argument list */
            curr_i++;
            width = va_arg(list, int);
            break;
        }
        else
        {
            break;
        }
    }

    /* Update the position pointer */
    *i = curr_i - 1;

    /* Return the calculated width specifier */
    return width;
}
