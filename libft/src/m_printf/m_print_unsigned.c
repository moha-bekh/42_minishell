/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_print_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 07:46:40 by moha              #+#    #+#             */
/*   Updated: 2024/05/31 10:43:07 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	m_unbr_len(unsigned int unbr)
{
	int	len;

	len = 0;
	while (unbr)
	{
		unbr /= 10;
		len++;
	}
	return (len);
}

char	*m_uitoa(unsigned int unbr)
{
	char	*uarr;
	int		len;

	len = m_unbr_len(unbr);
	uarr = malloc(sizeof(char) * (len + 1));
	if (!uarr)
		return (0);
	uarr[len] = '\0';
	while (unbr)
	{
		uarr[len - 1] = unbr % 10 + '0';
		unbr /= 10;
		len--;
	}
	return (uarr);
}

void	m_print_unsigned(int fd, unsigned int unbr, int *len)
{
	char	*uarr;

	if (!unbr)
		m_print_char(fd, '0', len);
	else
	{
		uarr = m_uitoa(unbr);
		m_print_str(fd, uarr, len);
		free(uarr);
	}
	return ;
}
