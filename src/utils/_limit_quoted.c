/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _limit_quoted.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:37:33 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/26 18:37:40 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_limit_quoted(char *str)
{
	int	i;

	if (!str)
		return (false);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
	}
	return (false);
}
