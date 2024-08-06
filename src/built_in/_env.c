/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:01:58 by moha              #+#    #+#             */
/*   Updated: 2024/08/06 07:10:08 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_env(t_pdata data, char **arg)
{
	t_pev	tmp;

	if (!data || !data->env.dll_env)
		return (_FAILURE);
	if (arg[1])
	{
		ft_putstr_fd("env: ", STDERR_FILENO);
		ft_putstr_fd(arg[1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		data->_errno = 127;
		return (_FAILURE);
	}
	tmp = data->env.dll_env->e_top;
	while (tmp)
	{
		if (tmp->value && tmp->value[0])
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (_SUCCESS);
}
