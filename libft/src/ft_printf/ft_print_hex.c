/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:08:32 by mbekheir          #+#    #+#             */
/*   Updated: 2024/01/09 10:14:23 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hex_len(unsigned int nb)
{
	int	len;

	len = 0;
	while (nb)
	{
		len++;
		nb /= 16;
	}
	return (len);
}

void	ft_put_hex(unsigned int nb, const char format)
{
	if (nb >= 16)
	{
		ft_put_hex(nb / 16, format);
		ft_put_hex(nb % 16, format);
	}
	else
	{
		if (nb <= 9)
			ft_putchar(nb + '0');
		else
		{
			if (format == 'x')
				ft_putchar((nb - 10) + 'a');
			if (format == 'X')
				ft_putchar((nb - 10) + 'A');
		}
	}
}

int	ft_print_hex(unsigned int nb, const char format)
{
	if (!nb)
		return (ft_print_char('0'));
	else
		ft_put_hex(nb, format);
	return (ft_hex_len(nb));
}
