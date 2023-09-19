#include "main.h"

/* Function prototype */
void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Custom printf function
 * @format: Format string containing format specifiers
 *
 * Return: Number of characters printed
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	/* Check if format is NULL */
	if (format == NULL)
		return (-1);

	/* Initialize va_list */
	va_start(list, format);

	/* Loop through the format string */
	for (i = 0; format && format[i] != '\0'; i++)
	{
		/* If character is not '%', add it to the buffer */
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];

			/* Check if buffer is full and print its contents */
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);

			/* Increment printed character count */
			printed_chars++;
		}
		else
		{
			/* Print the buffer if it contains any characters */
			print_buffer(buffer, &buff_ind);

			/* Parse format specifiers */
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);

			/* Move past '%' character in the format string */
			++i;

			/* Handle the format specifier and get the number of characters printed */
			printed = handle_print(format, &i, list, buffer, flags, width, precision, size);

			/* Check for errors in handle_print */
			if (printed == -1)
				return (-1);

			/* Increment total printed character count */
			printed_chars += printed;
		}
	}

	/* Print any remaining characters in the buffer */
	print_buffer(buffer, &buff_ind);

	/* Clean up the va_list */
	va_end(list);

	/* Return the total number of characters printed */
	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer
 * @buffer: Array of characters to be printed
 * @buff_ind: Pointer to the buffer index
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	/* Reset the buffer index */
	*buff_ind = 0;
}
