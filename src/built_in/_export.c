/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:34:32 by moha              #+#    #+#             */
/*   Updated: 2024/09/25 23:21:31 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_add_value(t_pdata data, char *arg)
{
	char	*key;
	int		idx;

	idx = _sep(arg);
	if (!idx)
		key = ft_strdup(arg);
	else
	{
		key = ft_substr(arg, 0, idx);
		if (!key)
			return (_FAILURE);
	}
	if (!ft_strcmp(key, data->env->d_bot->addr_1))
	{
		free(key);
		return (_SUCCESS);
	}
	if (!idx)
	{
		_dlst_push_back(&data->env, key, NULL, 0);
		_dlst_push_back(&data->export, key, NULL, 0);
	}
	else
	{
		_dlst_push_back(&data->env, key, ft_strdup(arg + (idx + 1)), 0);
		_dlst_push_back(&data->export, key, ft_strdup(arg + (idx + 1)), 0);
	}
	_dlst_sort(&data->export, false);
	return (_SUCCESS);
}

int	_replace_env_value(t_ppadlst env, char *arg)
{
	char	*key;
	char	*value;
	t_pnlst	tmp;
	int		idx;

	idx = _sep(arg);
	key = ft_substr(arg, 0, idx);
	if (!key)
		return (_FAILURE);
	value = ft_strdup(arg + (idx + 1));
	if (!value)
	{
		free(key);
		return (_FAILURE);
	}
	tmp = (*env)->d_top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->addr_1, key))
		{
			free(key);
			if (tmp->addr_2)
				free(tmp->addr_2);
			tmp->addr_2 = value;
			return (1);
		}
		tmp = tmp->next;
	}
	free(key);
	free(value);
	return (0);
}

int	_bad_value(char *value)
{
	int	sep;
	int	i;

	if (*value == '=')
		return (_err_print(_ERR_EXPORT_INVALID, value, true, 1));
	sep = _sep(value);
	i = -1;
	while (value[++i] && i < sep)
	{
		if (!ft_isalpha(value[i]) && value[i] != '_')
			return (_err_print(_ERR_EXPORT_INVALID, value, true, 1));
	}
	return (_SUCCESS);
}

int	_export(t_pdata data, char **args)
{
	int	i;

	if (!args[1])
		return (_dlst_print_export(data->export), _SUCCESS);
	i = 0;
	while (args[++i])
	{
		if (_bad_value(args[i]))
			continue ;
		else if (_replace_env_value(&data->env, args[i]))
		{
			_replace_env_value(&data->export, args[i]);
			continue ;
		}
		else if (args[i])
			_add_value(data, args[i]);
	}
	_dlst_sort(&data->export, false);
	return (_SUCCESS);
}
