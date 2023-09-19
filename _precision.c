#include "main.h"

/**
 * get_precision - Extracts and calculates the precision for printing
 * @format: Formatted string containing conversion specifiers
 * @i: Current position within the format string
 * @list: Variable argument list (va_list)
 *
 * Return: Precision value for formatting, or -1 if not specified
 */
int get_precision(const char *format, int *i, va_list list)
{
    int curr_i = *i + 1;
    int precision = -1;

    /* Check if precision is specified with a dot (.) */
    if (format[curr_i] != '.')
        return precision;

    precision = 0;

    /* Loop through characters in format to extract precision */
    for (curr_i += 1; format[curr_i] != '\0'; curr_i++)
    {
        /* If the character is a digit, update the precision value */
        if (is_digit(format[curr_i]))
        {
            precision *= 10;
            precision += format[curr_i] - '0';
        }
        /* If the character is an asterisk (*), retrieve precision from argument list */
        else if (format[curr_i] == '*')
        {
            curr_i++;
            precision = va_arg(list, int);
            break;
        }
        /* Exit the loop if the character is not a digit or asterisk */
        else
            break;
    }

    /* Update the position pointer to the end of the extracted precision */
    *i = curr_i - 1;

    /* Return the calculated precision value */
    return precision;
}
