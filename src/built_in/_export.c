/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:34:32 by moha              #+#    #+#             */
/*   Updated: 2024/08/08 14:53:49 by mbekheir         ###   ########.fr       */
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

int	_varstr_conv(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (_FAILURE);
		i++;
	}
	return (_SUCCESS);
}

char	*_exp_value(char *value)
{
	char	*tmp;

	if (!value)
		return (NULL);
	value = ft_strchr_in(value, "\\\"", '"');
	tmp = value;
	value = ft_strjoin("\"", value);
	free(tmp);
	tmp = value;
	value = ft_strjoin(value, "\"");
	free(tmp);
	return (value);
}

int	_add_value(t_pdata data, char *arg)
{
	char	*value;
	char	*exp_value;
	char	*tmp;

	tmp = ft_substr(arg, 0, _get_start_index(arg));
	value = ft_substr(arg, _get_start_index(arg) + 1, ft_strlen(arg));
	exp_value = ft_strdup(value);
	exp_value = _exp_value(exp_value);
	data->env.dll_env = _env_push_back(data->env.dll_env, tmp, value);
	data->env.dll_senv = _env_push_back(data->env.dll_senv, tmp, exp_value);
	data->env.dll_senv = _env_sort(data->env.dll_senv);
	return (_SUCCESS);
}

int	_replace_env_value(t_pdata data, char *arg)
{
	t_pev	tmp;
	char	*value;

	data->tmp = ft_substr(arg, 0, _get_start_index(arg));
	value = ft_substr(arg, _get_start_index(arg) + 1, ft_strlen(arg));
	tmp = data->env.dll_env->e_top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, data->tmp))
		{
			free(data->tmp);
			data->tmp = tmp->value;
			tmp->value = value;
			free(data->tmp);
			data->tmp = NULL;
			return (_IS);
		}
		tmp = tmp->next;
	}
	free(value);
	free(data->tmp);
	data->tmp = NULL;
	return (_NOT);
}

int	_replace_senv_value(t_pdata data, char *arg)
{
	t_pev	tmp;
	char	*value;

	data->tmp = ft_substr(arg, 0, _get_start_index(arg));
	value = ft_substr(arg, _get_start_index(arg) + 1, ft_strlen(arg));
	value = _exp_value(value);
	tmp = data->env.dll_senv->e_top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, data->tmp))
		{
			free(data->tmp);
			data->tmp = tmp->value;
			tmp->value = value;
			free(data->tmp);
			data->tmp = NULL;
			return (_IS);
		}
		tmp = tmp->next;
	}
	free(value);
	free(data->tmp);
	data->tmp = NULL;
	return (_NOT);
}

int	_bad_value(char *value)
{
	char	*tmp;

	tmp = ft_substr(value, 0, _get_start_index(value));
	if (!tmp[0] || _varstr_conv(tmp))
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(value, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(tmp);
		return (_FAILURE);
	}
	free(tmp);
	return (_SUCCESS);
}

int	_export(t_pdata data, char **arg)
{
	int	i;

	if (!arg[1])
		return (_export_print(data->env.dll_senv), _SUCCESS);
	i = 0;
	while (arg[++i])
	{
		if (_bad_value(arg[i]))
			continue ;
		else if (_replace_env_value(data, arg[i]))
		{
			_replace_senv_value(data, arg[i]);
			continue ;
		}
		_add_value(data, arg[i]);
	}
	data->env.dll_senv = _env_sort(data->env.dll_senv);
	return (_SUCCESS);
}
