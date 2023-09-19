#include "main.h"

/**
 * handle_print - Handles and prints an argument based on its type
 * @fmt: Formatted string containing conversion specifiers
 * @ind: Current position within the format string
 * @list: Variable argument list containing the arguments to be printed
 * @buffer: Buffer array to handle the print
 * @flags: Active formatting flags
 * @width: Width specification for formatting
 * @precision: Precision specification for formatting
 * @size: Size specifier for formatting
 *
 * Return: Number of characters printed or -1 for unsupported format
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unknown_len = 0, printed_chars = -1;

	/* Define format types and their corresponding print functions */
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};

	/* Iterate through format types to find a match */
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
	{
		if (fmt[*ind] == fmt_types[i].fmt)
		{
			/* Call the corresponding print function */
			return fmt_types[i].fn(list, buffer, flags, width, precision, size);
		}
	}

	/* If no match is found, handle unsupported format */
	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return -1; /* End of format string, no more formats to handle */

		/* Handle unsupported format by printing '%' character */
		unknown_len += write(1, "%%", 1);

		/* Check for space character flag and adjust length accordingly */
		if (fmt[*ind - 1] == ' ')
			unknown_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return 1; /* Skip unsupported format and continue processing */
		}

		/* Print the unknown character and adjust length */
		unknown_len += write(1, &fmt[*ind], 1);

		/* Return the total length of characters printed */
		return unknown_len;
	}

	return printed_chars;
}
