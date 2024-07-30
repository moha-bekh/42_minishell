/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:01:43 by moha              #+#    #+#             */
/*   Updated: 2024/07/30 17:50:21 by mbekheir         ###   ########.fr       */
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
	int	i;

	i = 0;
	if (!_str_is_digit(arg[1]) && _str_is_digit(arg[2]))
	{
		ft_putstr_fd("exit\nbash: exit: ", STDERR_FILENO);
		ft_putstr_fd(arg[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		_data_cleaner(data);
		exit(2);
	}
	else
	{
		ft_putstr_fd("exit\nbash: exit: too many arguments\n", STDERR_FILENO);
		data->_errno = 1;
	}
	return (_FAILURE);
}

int	_exit_arg(t_pdata data, char **arg)
{
	char	*str;

	str = NULL;
	if (is_overflow(arg[1]))
	{
		str = ft_strdup(arg[1]);
		ft_putstr_fd("exit\nbash: exit: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		free(str);
		_data_cleaner(data);
		exit(2);
		return (_FAILURE);
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	_data_cleaner(data);
	exit(ft_atoi(arg[1]) % 256);
	return (_FAILURE);
}

int	_exit_(t_pdata data, char **arg)
{
	int	i;

	if (!data)
		return (_EMPTY);
	i = 0;
	while (arg[i])
		i++;
	i--;
	if (!i)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		_data_cleaner(data);
		exit(0);
	}
	if (i == 1)
	{
		_exit_arg(data, arg);
		return (_FAILURE);
	}
	else if (i > 1)
		_many_args(data, arg);
	return (_SUCCESS);
}
