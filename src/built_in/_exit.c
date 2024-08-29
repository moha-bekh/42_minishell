/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:01:43 by moha              #+#    #+#             */
/*   Updated: 2024/08/29 05:02:54 by moha             ###   ########.fr       */
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

int	_many_args(char **args)
{
	if (!_str_is_digit(args[1]) && _str_is_digit(args[2]))
		exit(_err_print(_ERR_EXIT_NUM, args[1], true, 2));
	return (_err_print(_ERR_EXIT_MANY, NULL, false, 2));
}

int	_exit_arg(t_pdata data, char **args)
{
	char	*str;

	str = NULL;
	if (is_overflow(args[1]))
	{
		str = ft_strdup(args[1]);
		ft_dprintf(2, _ERR_EXIT_NUM, str);
		free(str);
		_data_clear(data);
		exit(2);
	}
	ft_dprintf(STDERR_FILENO, "exit\n");
	_data_clear(data);
	exit(ft_atoi(args[1]) % 256);
}

int	_exit_(t_pdata data, char **args)
{
	int	i;

	i = 0;
	while (args[i])
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
		_exit_arg(data, args);
		return (_FAILURE);
	}
	else if (i > 1)
		_many_args(args);
	return (_SUCCESS);
}
