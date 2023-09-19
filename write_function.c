#include "main.h"

/* WRITE HANDLE */
/**
 * handle_write_char - Handles printing a character
 * @c: The character to be printed
 * @buffer: The buffer to store the result
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed
 */
int handle_write_char(char c, char buffer[], int flags, int width, int precision, int size)
{
    int i = 0;
    char padding = ' ';

    UNUSED(precision);
    UNUSED(size);

    if (flags & F_ZERO)
        padding = '0';

    buffer[i++] = c;
    buffer[i] = '\0';

    if (width > 1)
    {
        buffer[BUFF_SIZE - 1] = '\0';
        for (i = 0; i < width - 1; i++)
            buffer[BUFF_SIZE - i - 2] = padding;

        if (flags & F_MINUS)
            return (write(1, &buffer[0], 1) + write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
        else
            return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) + write(1, &buffer[0], 1));
    }

    return (write(1, &buffer[0], 1));
}

/* WRITE NUMBER */
/**
 * write_number - Handles printing a number
 * @is_negative: Indicates if the number is negative
 * @ind: Index where the number starts in the buffer
 * @buffer: The buffer to store the result
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed
 */
int write_number(int is_negative, int ind, char buffer[], int flags, int width, int precision, int size)
{
    int length = BUFF_SIZE - ind - 1;
    char padding = ' ', extra_char = 0;

    UNUSED(size);

    if ((flags & F_ZERO) && !(flags & F_MINUS))
        padding = '0';

    if (is_negative)
        extra_char = '-';
    else if (flags & F_PLUS)
        extra_char = '+';
    else if (flags & F_SPACE)
        extra_char = ' ';

    return write_num(ind, buffer, flags, width, precision, length, padding, extra_char);
}

/**
 * write_num - Writes a number using a buffer
 * @ind: Index where the number starts in the buffer
 * @buffer: The buffer to store the result
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @length: Length of the number
 * @padding: Padding character
 * @extra_char: Extra character
 *
 * Return: Number of characters printed
 */
int write_num(int ind, char buffer[], int flags, int width, int precision, int length, char padding, char extra_char)
{
    int i, padding_start = 1;

    if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
        return (0);

    if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
    {
        buffer[ind] = padding = ' ';
    }

    if (precision > 0 && precision < length)
        padding = ' ';

    while (precision > length)
    {
        buffer[--ind] = '0';
        length++;
    }

    if (width > length)
    {
        for (i = 1; i < width - length + 1; i++)
            buffer[i] = padding;

        buffer[i] = '\0';

        if (flags & F_MINUS && padding == ' ')
        {
            if (extra_char)
                buffer[--ind] = extra_char;
            return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
        }
        else if (!(flags & F_MINUS) && padding == ' ')
        {
            if (extra_char)
                buffer[--ind] = extra_char;
            return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
        }
        else if (!(flags & F_MINUS) && padding == '0')
        {
            if (extra_char)
                buffer[--padding_start] = extra_char;
            return (write(1, &buffer[padding_start], i - padding_start) + write(1, &buffer[ind], length - (1 - padding_start)));
        }
    }

    if (extra_char)
        buffer[--ind] = extra_char;
    return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Indicates if the number is negative
 * @ind: Index where the number starts in the buffer
 * @buffer: The buffer to store the result
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed
 */
int write_unsgnd(int is_negative, int ind, char buffer[], int flags, int width, int precision, int size)
{
    int length = BUFF_SIZE - ind - 1;
    char padding = ' ';

    UNUSED(is_negative);
    UNUSED(size);

    if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
        return (0);

    if (precision > 0 && precision < length)
        padding = ' ';

    if ((flags & F_ZERO) && !(flags & F_MINUS))
        padding = '0';

    while (precision > length)
    {
        buffer[--ind] = '0';
        length++;
    }

    if (width > length)
    {
        for (int i = 0; i < width - length; i++)
            buffer[i] = padding;

        buffer[i] = '\0';

        if (flags & F_MINUS)
        {
            buffer[--ind] = 'x';
            buffer[--ind] = '0';
            return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
        }
        else
        {
            buffer[--ind] = 'x';
            buffer[--ind] = '0';
            return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
        }
    }

    buffer[--ind] = 'x';
    buffer[--ind] = '0';
    return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
