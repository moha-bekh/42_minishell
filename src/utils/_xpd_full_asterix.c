/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _xpd_full_asterix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:55:35 by oek               #+#    #+#             */
/*   Updated: 2024/10/21 14:03:55 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_xpd_full_asterix(char *str)
{
	int	i;

	if (!str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
		{
			if (!str[i - 1] && str[i + 1] == ' ')
				return (true);
			if (str[i - 1] == ' ' && !str[i + 1])
				return (true);
			if (str[i - 1] == ' ' && str[i + 1] == ' ')
				return (true);
		}
		i++;
	}
	return (false);
}
