/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 13:50:09 by mbekheir          #+#    #+#             */
/*   Updated: 2024/01/09 10:13:23 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format(va_list args, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_print_char(va_arg(args, int));
	else if (format == 's')
		len += ft_print_str(va_arg(args, char *));
	else if (format == 'd' || format == 'i')
		len += ft_print_nbr(va_arg(args, int));
	else if (format == 'p')
		len += ft_print_ptr(va_arg(args, unsigned long long));
	else if (format == 'u')
		len += ft_print_unsigned(va_arg(args, unsigned int));
	else if (format == 'x')
		len += ft_print_hex(va_arg(args, unsigned int), format);
	else if (format == 'X')
		len += ft_print_hex(va_arg(args, unsigned int), format);
	else if (format == '%')
		len += ft_print_char('%');
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;
	int		i;

	len = 0;
	i = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += ft_format(args, str[i + 1]);
			i++;
		}
		else
			len += ft_print_char(str[i]);
		i++;
	}
	va_end(args);
	return (len);
}

/* int	main(void)
{
	ft_printf("allo la terre!");
	printf("\n");

	ft_printf("%c", 'c');
	printf("\n");

	ft_printf("%s", "hello world!");
	printf("\n");

	ft_printf("%d", 10);
	printf("\n");

	ft_printf("%%");
	printf("\n");

	char *ptr = "hey!";
	int len1 = printf("%p\n", ptr);
	int len2 = ft_printf("%p\n", ptr);
	printf("%d\n%d\n", len1, len2);

	unsigned int nb = 100;
	int len3 = ft_printf("%u\n", nb);
	int len4 = printf("%u\n", nb);
	printf("%d\n%d\n", len3, len4);

	unsigned int hex = 0;
	int len5 = ft_printf("%X\n", hex);
	int len6 = printf("%X\n", hex);
	printf("%d\n%d\n", len5, len6);

	return (0);
}
 */