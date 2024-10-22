/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _xpd_full_asterix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:55:35 by oek               #+#    #+#             */
/*   Updated: 2024/10/22 11:44:56 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_is_full(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '*')
			return (false);
	}
	return (true);
}

int	_xpd_full_asterix(char *str)
{
	char	**arr;
	int		i;

	arr = ft_split(str, ' ');
	if (!arr)
		return (false);
	i = -1;
	while (arr[++i])
	{
		if (_is_full(arr[i]))
		{
			ft_free_arr(arr);
			return (true);
		}
	}
	ft_free_arr(arr);
	return (false);
}
