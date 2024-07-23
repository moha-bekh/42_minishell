/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _set_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:06:16 by moha              #+#    #+#             */
/*   Updated: 2024/07/23 22:16:43 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_set_env(u_padll *dll_env, char **ev)
{
	int	i;
	int	j;

	if (!*ev)
		return (EXIT_SUCCESS);
	i = -1;
	while (ev[++i])
	{
		j = _get_start_index(ev[i]);
		*dll_env = _env_push_back(*dll_env, ft_substr(ev[i], 0, j), ft_substr(ev[i], j + 1, ft_strlen(ev[i])));
	}
	return (EXIT_SUCCESS);
}

int	_set_senv(u_padll *dll_senv, u_padll dll_env)
{
	t_pev	tmp;

	if (!dll_env)
		return (EXIT_SUCCESS);
	tmp = dll_env->e_top;
	while (tmp)
	{
		*dll_senv = _env_push_back(*dll_senv, ft_strdup(tmp->key), ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	*dll_senv = _env_sort(*dll_senv);
	return (EXIT_SUCCESS);
}
