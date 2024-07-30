/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:01:43 by moha              #+#    #+#             */
/*   Updated: 2024/07/30 12:59:19 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_exit_arg(t_pdata data, char *arg)
{
	char	*str;

	str = NULL;
	if (is_overflow(arg))
	{
		str = ft_strdup(arg);
		ft_putstr_fd("exit\nbash: exit: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		free(str);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		_data_cleaner(data);
		exit(2);
		return (_FAILURE);
	}
	_data_cleaner(data);
	exit(ft_atoi(arg));
	return (_FAILURE);
}

int	_exit_(t_pdata data, char **arg)
{
	int	i;

	if (!data || !arg)
		return (_EMPTY);
	i = -1;
	while (arg[i])
		i++;
	if (i == 2)
	{
		_exit_arg(data, arg[1]);
		return (_FAILURE);
	}
	else if (i > 2)
	{
		ft_putstr_fd("exit\nbash: exit: too many arguments\n", STDERR_FILENO);
		_data_cleaner(data);
		data->_errno = 1;
		return (_FAILURE);
	}
	_data_cleaner(data);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(ft_atoi(arg[1]));
	return (_SUCCESS);
}
