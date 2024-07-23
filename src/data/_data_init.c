/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _data_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 23:44:34 by moha              #+#    #+#             */
/*   Updated: 2024/07/23 17:52:07 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_data_init_args(t_pdata data, int ac, char **av, char **ev)
{
	if (!data)
		return (EXIT_FAILURE);
	ft_memset(data, 0, sizeof(t_data));
	data->ac = ac;
	data->av = av;
	data->input = NULL;
	ft_memset(&data->env, 0, sizeof(t_env));
	data->env.dll_env = NULL;
	data->env.env = ev;
	data->env.min_ev = NULL;
	data->tok = NULL;
	data->scop = NULL;
	data->tree = NULL;
	return (EXIT_SUCCESS);
}

int	_data_min_env(t_pdata data)
{
	if (_alloc((void *)&data->env.min_ev, sizeof(char *) * 3)
		|| !data->env.min_ev)
		return (EXIT_FAILURE);
	data->env.min_ev[0] = getcwd(NULL, 0);
	data->env.min_ev[1] = ft_strdup("PATH=" _PATH);
	data->env.min_ev[2] = NULL;
	return (EXIT_SUCCESS);
}

int	_data_dll_env(u_padll *dll_env, char **ev)
{
	int	i;
	int	j;

	if (!*ev)
		return (EXIT_SUCCESS);
	i = -1;
	while (ev[++i])
	{
		j = 0;
		while (ev[i][j] != '=')
			j++;
		*dll_env = _env_push_back(*dll_env, ft_substr(ev[i], 0, j),
				ft_substr(ev[i], j + 1, ft_strlen(ev[i])));
	}
	return (EXIT_SUCCESS);
}

int	_data_init(t_pdata data, int ac, char **av, char **ev)
{
	if (!data || _data_init_args(data, ac, av, ev))
		return (EXIT_FAILURE);
	if (_data_min_env(data))
		return (EXIT_FAILURE);
	if (_data_dll_env(&data->env.dll_env, ev) && _data_dll_env(&data->env.dll_sort_env, ev))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
