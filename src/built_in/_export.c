/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:34:32 by moha              #+#    #+#             */
/*   Updated: 2024/08/07 20:43:46 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_export_print(u_padll dll)
{
	t_pev	tmp;

	if (!dll)
		return ;
	tmp = dll->e_top;
	while (tmp)
	{
		if (tmp->value && tmp->value[1] != '"')
			printf("export %s=%s\n", tmp->key, tmp->value);
		else
			printf("export %s\n", tmp->key);
		tmp = tmp->next;
	}
	return ;
}

char	*_quote_slash(char *value)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	i = -1;
	while (value[++i])
	{
		if (value[i] == '"')
		{
			tmp = ft_substr(value, 0, i);
			printf("tmp: %s\n", tmp);
			tmp2 = ft_strjoin(tmp, "\\");
			free(tmp);
			printf("tmp 2: %s\n", tmp2);
			tmp = ft_strjoin(tmp2, value + i);
			printf("tmp: %s\n", tmp);
		}
	}
	return (value);
}

int	_export(t_pdata data, char **arg)
{
	int		i;
	int		j;
	char	*value;

	if (!arg[1])
		return (_export_print(data->env.dll_senv), _SUCCESS);
	_clean_env(data, arg);
	i = 0;
	while (arg[++i])
	{
		j = _get_start_index(arg[i]);
		value = ft_substr(arg[i], j + 1, ft_strlen(arg[i]));
		value = ft_strchr_in(value, "\\\"", '"');
		data->env.dll_env = _env_push_back(data->env.dll_env, ft_substr(arg[i],
					0, j), value);
		if (!ft_strcmp(data->env.dll_env->e_bot->key, "PATH"))
		{
			ft_free_arr(data->paths[1]);
			data->paths[1] = ft_split(data->env.dll_env->e_bot->value, ':');
			_path_slash(data, 1);
		}
	}
	data->env.dll_senv = _env_clear(data->env.dll_senv);
	_set_senv(&data->env.dll_senv, data->env.dll_env);
	return (_SUCCESS);
}
