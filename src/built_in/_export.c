/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:34:32 by moha              #+#    #+#             */
/*   Updated: 2024/07/23 22:17:49 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_dll	*_export(t_dll *dll, char **args)
// {
// 	int		i;
// 	char	**key_value;

// 	if (!args)
// 		return (_dll_print_env(dll), NULL);
// 	printf("args exist\n");
// 	i = 0;
// 	while (args[i])
// 	{
// 		if (args[i] && ft_strchr(args[i], '='))
// 		{
// 			key_value = ft_split(args[i], '=');
// 			if (!key_value)
// 				return (NULL);
// 			dll = _dll_push_back(dll, NULL);
// 			if (key_value[0])
// 				dll->bot->key = key_value[0];
// 			if (key_value[1])
// 				dll->bot->value = key_value[1];
// 		}
// 		i++;
// 	}
// 	_dll_print_env(dll);
// 	return (dll);
// }

void	_export_print(u_padll dll)
{
	t_pev	tmp;

	tmp = dll->e_top;
	while (tmp)
	{
		printf("export %s=", tmp->key);
		printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
}

int	_get_start_index(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (i);
	}
	return (i);
}

int	_clean_env(t_pdata data, char **arg)
{
	t_pev	tmp;
	char	*key;
	int		i;
	int		j;

	i = -1;
	while (arg[++i])
	{
		if (strchr(arg[i], '='))
		{
			j = _get_start_index(arg[i]);
			key = ft_substr(arg[i], 0, j);
			tmp = data->env.dll_env->e_top;
			while (tmp)
			{
				if (!ft_strcmp(tmp->key, key))
				{
					data->env.dll_env = _env_pop_in(data->env.dll_env, tmp);
					break ;
				}
				tmp = tmp->next;
			}
			free(key);
		}
	}
	return (EXIT_SUCCESS);
}

int	_export(t_pdata data, char **arg)
{
	int		i;
	int		j;

	if (!arg)
		return (_export_print(data->env.dll_senv), EXIT_SUCCESS);
	_clean_env(data, arg);
	i = -1;
	while (arg[++i])
	{
		j = _get_start_index(arg[i]);
		data->env.dll_env = _env_push_back(data->env.dll_env, ft_substr(arg[i], 0, j), ft_substr(arg[i], j + 1, ft_strlen(arg[i])));
	}
	data->env.dll_senv = _env_clear(data->env.dll_senv);
	_set_senv(&data->env.dll_senv, data->env.dll_env);
	return (EXIT_SUCCESS);
}
