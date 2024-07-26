/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:06:16 by moha              #+#    #+#             */
/*   Updated: 2024/07/26 18:26:11 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_set_env(u_padll *env, char **ev)
{
	int	i;
	int	j;

	if (!*ev)
		return (EXIT_SUCCESS);
	i = -1;
	while (ev[++i])
	{
		j = _get_start_index(ev[i]);
		*env = _env_push_back(*env, ft_substr(ev[i], 0, j), ft_substr(ev[i], j + 1, ft_strlen(ev[i])));
	}
	return (EXIT_SUCCESS);
}

int	_set_senv(u_padll *s_env, u_padll env)
{
	t_pev	tmp;
	char	*old_value;

	if (!env)
		return (EXIT_SUCCESS);
	tmp = env->e_top;
	while (tmp)
	{
		*s_env = _env_push_back(*s_env, ft_strdup(tmp->key), ft_strjoin("\"", tmp->value));
		old_value = (*s_env)->e_bot->value;
		(*s_env)->e_bot->value = ft_strjoin((*s_env)->e_bot->value, "\"");
		free(old_value);
		tmp = tmp->next;
	}
	*s_env = _env_sort(*s_env);
	return (EXIT_SUCCESS);
}

int	_clean_env(t_pdata data, char **arg)
{
	t_pev	tmp;
	int		i;
	int		j;

	i = -1;
	while (arg[++i])
	{
		if (strchr(arg[i], '='))
		{
			j = _get_start_index(arg[i]);
			data->tmp = ft_substr(arg[i], 0, j);
			tmp = data->env.dll_env->e_top;
			while (tmp)
			{
				if (!ft_strcmp(tmp->key, data->tmp))
				{
					data->env.dll_env = _env_pop_in(data->env.dll_env, tmp);
					break ;
				}
				tmp = tmp->next;
			}
			free(data->tmp);
		}
	}
	return (EXIT_SUCCESS);
}
