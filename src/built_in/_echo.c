/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _echo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alblanc <alblanc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 02:56:34 by alblanc           #+#    #+#             */
/*   Updated: 2024/10/23 16:03:27 by alblanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_check_nl_flag(char *arg)
{
	int	i;

	if (!arg)
		return (false);
	if (arg[0] != '-')
		return (false);
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
	i = 1;
	if (args[i])
	{
		if (_check_nl_flag(args[i]))
		{
			i++;
			new_line = false;
			while (_check_nl_flag(args[i]))
				i++;
		}
		while (args && args[i])
		{
			ft_dprintf(1, "%s", args[i]);
			if (args[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (new_line)
		write(1, "\n", 1);
	return (_SUCCESS);
}
