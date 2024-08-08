/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:34:32 by moha              #+#    #+#             */
/*   Updated: 2024/08/08 10:47:08 by moha             ###   ########.fr       */
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

int	_var_conv(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (_NOT);
		i++;
	}
	return (_IS);
}

int	_replace_value(t_pdata data, char **arg)
{
	t_pev	tmp;
	int		i;

	i = -1;
	while (arg[++i])
	{
		if (!_var_conv(arg[i]))
		{
			ft_putstr_fd("bash: export: `", 2);
			ft_putstr_fd(arg[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else
		{
			data->tmp = ft_substr(arg[i], 0, _get_start_index(arg[i]));
			tmp = data->env.dll_env->e_top;
			while (tmp)
			{
				if (!ft_strcmp(tmp->key, data->tmp))
				{
					free(data->tmp);
					data->tmp = tmp->value;
					tmp->value = ft_substr(arg[i], _get_start_index(arg[i]) + 1,
							ft_strlen(arg[i]));
					free(data->tmp);
					data->tmp = NULL;
					break ;
				}
				tmp = tmp->next;
			}
			free(data->tmp);
			data->tmp = NULL;
		}
	}
	return (_SUCCESS);
}

int	_export(t_pdata data, char **arg)
{
	if (!arg[1])
		return (_export_print(data->env.dll_senv), _SUCCESS);
	_replace_value(data, arg);
	data->env.dll_senv = _env_clear(data->env.dll_senv);
	_set_senv(&data->env.dll_senv, data->env.dll_env);
	return (_SUCCESS);
}
