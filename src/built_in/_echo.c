/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _echo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:01:54 by moha              #+#    #+#             */
/*   Updated: 2024/09/30 16:30:15 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_check_nl_flag(char *arg)
{
	int	i;

	i = 0;
	while (arg[++i])
	{
		if (arg[i] != 'n')
			return (false);
	}
	return (true);
}

int	_echo(char **args)
{
	int		i;
	bool	new_line;

	new_line = true;
	if (!args[1])
		return (printf("\n"), _SUCCESS);
	if (args[1][0] == '-' && args[1][1] == 'n' && _check_nl_flag(args[1]))
	{
		new_line = false;
		i = 1;
	}
	else
		i = 0;
	while (args && args[++i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
	}
	if (new_line)
		printf("\n");
	return (_SUCCESS);
}
