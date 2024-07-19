/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:45:37 by mbekheir          #+#    #+#             */
/*   Updated: 2024/01/09 10:13:59 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nb_len(unsigned int nb)
{
	int	len;

	len = 0;
	while (nb)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

char	*ft_uitoa(unsigned int nb)
{
	char	*new_nb;
	int		len;

	len = ft_nb_len(nb);
	new_nb = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_nb)
		return (0);
	new_nb[len] = '\0';
	while (nb)
	{
		new_nb[len - 1] = (nb % 10) + 48;
		nb /= 10;
		len--;
	}
	return (new_nb);
}

int	ft_print_unsigned(unsigned int nb)
{
	int		len;
	char	*new_nb;

	len = 0;
	if (!nb)
		len += ft_print_char('0');
	else
	{
		new_nb = ft_uitoa(nb);
		len += ft_print_str(new_nb);
		free(new_nb);
	}
	return (len);
}
