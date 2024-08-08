/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _echo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:01:54 by moha              #+#    #+#             */
/*   Updated: 2024/08/08 16:14:40 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_echo(t_pdata data, char **arg)
{
	int		i;
	bool	new_line;

	i = 0;
	new_line = true;
	if (arg[1][0] == '-' && arg[1][1] == 'n' && !arg[1][2])
	{
		new_line = false;
		i++;
	}
	while (arg[++i])
	{
		if (arg[i + 1])
			printf("%s ", arg[i]);
		else
			printf("%s", arg[i]);
	}
	if (new_line)
		printf("\n");
	data->_errno = 0;
	return (_SUCCESS);
}
