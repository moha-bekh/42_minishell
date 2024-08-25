/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:01:43 by moha              #+#    #+#             */
/*   Updated: 2024/08/23 19:26:57 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_str_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	_many_args(t_pdata data, char **arg)
{
	if (!_str_is_digit(arg[1]) && _str_is_digit(arg[2]))
	{
		ft_dprintf(2, "exit: %s: numeric argument required\n", arg[1]);
		_data_clear(data);
		exit(2);
	}
	ft_dprintf(2, "exit: bash: exit: too many arguments\n");
	return (_FAILURE);
}

int	_exit_arg(t_pdata data, char **arg)
{
	char	*str;

	str = NULL;
	if (is_overflow(arg[1]))
	{
		str = ft_strdup(arg[1]);
		ft_dprintf(2, "exit: %s: numeric argument required\n", str);
		free(str);
		_data_clear(data);
		exit(2);
		return (_FAILURE);
	}
	ft_dprintf(STDERR_FILENO, "exit\n");
	_data_clear(data);
	exit(ft_atoi(arg[1]) % 256);
	return (_FAILURE);
}

int	_exit_(t_pdata data, t_pcmd *cmd)
{
	int	i;

	i = 0;
	while ((*cmd)->args[i])
		i++;
	i--;
	if (!i)
	{
		ft_dprintf(STDERR_FILENO, "exit\n");
		_data_clear(data);
		exit(0);
	}
	if (i == 1)
	{
		_exit_arg(data, (*cmd)->args);
		return (_FAILURE);
	}
	else if (i > 1)
		_many_args(data, (*cmd)->args);
	return (_SUCCESS);
}
