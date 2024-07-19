/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_printfd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 07:47:39 by moha              #+#    #+#             */
/*   Updated: 2024/05/31 10:42:55 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	m_print_char(int fd, char c, int *len)
{
	write(fd, &c, 1);
	(*len)++;
	return ;
}

void	m_print_str(int fd, char *str, int *len)
{
	int	i;

	i = -1;
	if (!str)
		ft_putstr("(null)");
	while (str[++i])
	{
		write(fd, &str[i], 1);
		(*len)++;
	}
	return ;
}

void	m_print_nbr(int fd, int nbr, int *len)
{
	if (nbr == -2147483648)
	{
		write(fd, "-2147483648", 11);
		(*len) += 11;
	}
	if (nbr < 0)
	{
		nbr *= -1;
		write(fd, "-", 1);
		(*len)++;
	}
	if (nbr >= 10)
	{
		m_print_nbr(fd, nbr / 10, len);
		m_print_nbr(fd, nbr % 10, len);
	}
	if (nbr >= 0 && nbr <= 9)
	{
		nbr += '0';
		write(fd, &nbr, 1);
		(*len)++;
	}
	return ;
}

void	m_format(va_list args, int fd, const char format, int *len)
{
	if (format == '%')
	{
		write(fd, "%", 1);
		(*len)++;
	}
	else if (format == 'c')
		m_print_char(fd, va_arg(args, int), len);
	else if (format == 's')
		m_print_str(fd, va_arg(args, char *), len);
	else if (format == 'd')
		m_print_nbr(fd, va_arg(args, int), len);
	else if (format == 'u')
		m_print_unsigned(fd, va_arg(args, unsigned int), len);
	else if (format == 'x')
		m_print_hex(fd, va_arg(args, unsigned int), 'x', len);
	else if (format == 'X')
		m_print_hex(fd, va_arg(args, unsigned int), 'X', len);
	else if (format == 'p')
		m_print_ptr(fd, va_arg(args, unsigned long long), len);
	return ;
}

int	m_printfd(int fd, const char *format, ...)
{
	va_list	args;
	int		len;
	int		i;

	va_start(args, format);
	len = 0;
	i = -1;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			m_format(args, fd, format[i + 1], &len);
			i++;
		}
		else
		{
			write(fd, &format[i], 1);
			len++;
		}
	}
	va_end(args);
	return (len);
}
