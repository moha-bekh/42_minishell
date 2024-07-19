/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_atoi_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:05:29 by moha              #+#    #+#             */
/*   Updated: 2024/05/29 13:22:35 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_valid(int c, int base)
{
	char	*lbase;
	char	*Ubase;
	int		i;

	lbase = "0123456789abcdef";
	Ubase = "0123456789ABCDEF";
	i = -1;
	while (++i < base)
	{
		if (c == lbase[i] || c == Ubase[i])
			return (1);
	}
	return (0);
}

void	if_is_sign(int c, int *sign, int *i)
{
	if (c == '+')
		(*i)++;
	else if (c == '-')
	{
		*sign = -1;
		(*i)++;
	}
	return ;
}

int	m_atoi_base(const char *str, int base)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if_is_sign(str[i], &sign, &i);
	while (str[i] && is_valid(str[i], base))
	{
		res *= base;
		if (ft_isdigit(str[i]))
			res += str[i] - '0';
		else if (m_ishex_alpha(str[i]))
			res += str[i] - 'a' + 10;
		else if (m_ishexALPHA(str[i]))
			res += str[i] - 'A' + 10;
		i++;
	}
	return (res * sign);
}
