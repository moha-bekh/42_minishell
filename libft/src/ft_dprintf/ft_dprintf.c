/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:03:32 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/31 15:53:35 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbrbase_buf(t_ft_pdprintf d, int nb, int base, bool upper)
{
	if (!nb)
		ft_putchar_buf(d, '0');
	else if (nb < 0)
	{
		ft_putchar_buf(d, '-');
		ft_putnbrbase_buf(d, -nb, base, upper);
	}
	else
	{
		if (nb >= base)
			ft_putnbrbase_buf(d, (nb / base), base, upper);
		if ((nb % base) < 10)
			ft_putchar_buf(d, (nb % base) + '0');
		else
		{
			if (upper)
				ft_putchar_buf(d, (nb % base) - 10 + 'A');
			else
				ft_putchar_buf(d, (nb % base) - 10 + 'a');
		}
	}
}

void	ft_putptr_rec(t_ft_pdprintf d, unsigned long long ptr)
{
	if (ptr >= 16)
		ft_putptr_rec(d, (ptr / 16));
	if ((ptr % 16) < 10)
		ft_putchar_buf(d, (ptr % 16) + '0');
	else
		ft_putchar_buf(d, (ptr % 16) - 10 + 'a');
}

void	ft_putptr_buf(t_ft_pdprintf d, unsigned long long ptr)
{
	if (!ptr)
		ft_putstr_buf(d, "(nil)");
	else
	{
		ft_putstr_buf(d, "0x");
		ft_putptr_rec(d, ptr);
	}
}

void	ft_putformat(t_ft_pdprintf d)
{
	d->i++;
	if (d->format[d->i] == '%')
		ft_putchar_buf(d, '%');
	else if (d->format[d->i] == 'c')
		ft_putchar_buf(d, va_arg(d->args, int));
	else if (d->format[d->i] == 's')
		ft_putstr_buf(d, va_arg(d->args, char *));
	else if (d->format[d->i] == 'd')
		ft_putnbrbase_buf(d, va_arg(d->args, int), 10, false);
	else if (d->format[d->i] == 'x')
		ft_putnbrbase_buf(d, va_arg(d->args, unsigned int), 16, false);
	else if (d->format[d->i] == 'X')
		ft_putnbrbase_buf(d, va_arg(d->args, unsigned int), 16, true);
	else if (d->format[d->i] == 'p')
		ft_putptr_buf(d, va_arg(d->args, unsigned long long));
	return ;
}

int	ft_dprintf(int fd, const char *format, ...)
{
	t_fd_dprintf	d;

	d = (t_fd_dprintf){0};
	d.fd = fd;
	d.format = format;
	va_start(d.args, format);
	while (d.format[d.i])
	{
		if (d.format[d.i] == '%')
			ft_putformat(&d);
		else
			ft_putchar_buf(&d, d.format[d.i]);
		d.i++;
	}
	write(d.fd, d.buf, d.j);
	va_end(d.args);
	return (d.len);
}
