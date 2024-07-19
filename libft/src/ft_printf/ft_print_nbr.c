/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:00:32 by mbekheir          #+#    #+#             */
/*   Updated: 2024/01/09 10:14:17 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_nbr(int nb)
{
	int	len;

	len = 0;
	if (nb == -2147483648)
	{
		ft_print_char('-');
		ft_putstr("2147483648");
		return (11);
	}
	else if (nb < 0)
	{
		nb *= -1;
		len += 1;
		ft_print_char('-');
	}
	if (nb >= 10)
		len += ft_print_nbr(nb / 10);
	len += ft_print_char((nb % 10) + '0');
	return (len);
}
