#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

int	print_s(char *str)
{
	int	count = 0;

	if (!str)
		str = "(null)";
	while (*str)
		count += write(1, str++, 1);
	return (count);
}

int	print_d(unsigned int num)
{
	int count = 0;
	char n;

	if (num < 0)
	{
		num *= -1;
		write(1, "-", 1);
		count++;
	}
	if (num >= 10)
		count += print_d(num / 10);
	n = "0123456789"[num % 10];
	write(1, &n, 1);
	count++;
	return (count);
}

int	print_x(unsigned int num)
{
	int	count = 0;
	char n;

	if (num >= 16)
		count += print_x(num / 16);
	n = "0123456789abcdef"[num % 16];
	write(1, &n, 1);
	count++;
	return (count);
}
int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		count = 0;

	va_start(arg, format);
	if (!format)
		return (-1);
	while (*format != '\0')
	{
		if ((*format == '%') && (*(format + 1) == 's' || *(format + 1) == 'd' || *(format + 1) == 'x'))
		{
			format++;
			if (*format == 's')
				count += print_s(va_arg(arg, char *));
			if (*format == 'd')
				count += print_d(va_arg(arg, int));
			if (*format == 'x')
				count += print_x(va_arg(arg, unsigned int));
		}
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(arg);
	return (count);
}

// #include <stdio.h>

// int main()
// {
// 	printf("Testing print_s:\n");
// 	ft_printf("Hello %s!\n", "world"); // Should print: Hello world!

// 	printf("\nTesting print_d:\n");
// 	ft_printf("The number is %d.\n", 42);

// 	printf("\nTesting print_x:\n");
// 	ft_printf("The hexadecimal number is %x.\n", 255); // Should print: The hexadecimal number is ff.

// 	printf("\nTesting null string:\n");
// 	ft_printf("This is a %s test.\n", NULL);

// 	return 0;
// }