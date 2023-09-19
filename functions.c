#include "main.h"

/**
 * is_printable - Checks if a character is printable
 * @c: The character to be checked
 *
 * Return: 1 if the character is printable, 0 otherwise
 */
int is_printable(char c)
{
    if (c >= 32 && c < 127)
        return (1);

    return (0);
}

/**
 * append_hexa_code - Appends ASCII in hexadecimal format to a buffer
 * @ascii_code: The ASCII code to be appended
 * @buffer: The buffer array to store the result
 * @i: The index in the buffer to start appending
 *
 * Return: Always returns 3
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
    char map_to[] = "0123456789ABCDEF";

    /* Hexadecimal format is always 2 digits long */
    if (ascii_code < 0)
        ascii_code *= -1;

    buffer[i++] = '\\';
    buffer[i++] = 'x';

    buffer[i++] = map_to[ascii_code / 16];
    buffer[i] = map_to[ascii_code % 16];

    return (3);
}

/**
 * is_digit - Checks if a character is a digit
 * @c: The character to be checked
 *
 * Return: 1 if the character is a digit, 0 otherwise
 */
int is_digit(char c)
{
    if (c >= '0' && c <= '9')
        return (1);

    return (0);
}

/**
 * convert_size_number - Casts a number to the specified size
 * @num: The number to be casted
 * @size: The size indicating the type to be casted
 *
 * Return: The casted value of num
 */
long int convert_size_number(long int num, int size)
{
    if (size == S_LONG)
        return (num);
    else if (size == S_SHORT)
        return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - Casts an unsigned number to the specified size
 * @num: The unsigned number to be casted
 * @size: The size indicating the type to be casted
 *
 * Return: The casted value of num
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
    if (size == S_LONG)
        return (num);
    else if (size == S_SHORT)
        return ((unsigned short)num);

    return ((unsigned int)num);
}

