/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:34:32 by moha              #+#    #+#             */
/*   Updated: 2024/09/26 03:25:49 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_add_value(t_pdata data, char *arg)
{
	char	*key;
	char *value;

	key = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	if (!key)
		return (_FAILURE);
	value = ft_strchr(arg, '=');
	if (value)
	{
		if (value[1])
			value = ft_strdup(value + 1);
		else
			value = ft_strdup("");
	}
	_dlst_push_back(&data->env, key, value, 0);
	_dlst_push_back(&data->export, key, value, 0);
	_dlst_sort(&data->export, false);
	return (_SUCCESS);
}

int	_search_and_replace(t_ppadlst env, char *key, char *value)
{
	t_pnlst	tmp;

	tmp = (*env)->d_top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->addr_1, key))
		{
			free(key);
			if (tmp->addr_2)
				free(tmp->addr_2);
			tmp->addr_2 = value;
			return (_SUCCESS);
		}
		tmp = tmp->next;
	}
	return (_FAILURE);
}

int	_replace_env_value(t_ppadlst env, char *arg)
{
	char	*key;
	char	*value;

	key = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	if (!key)
		return (_FAILURE);
	value = ft_strchr(arg, '=');
	if (value)
	{
		if (value[1])
		{
			value = ft_strdup(value + 1);
			if (!value)
				return (_FAILURE);
		}
		else
		{
			value = ft_strdup("");
			if (!value)
				return (_FAILURE);
		}
	}
	if (!_search_and_replace(env, key, value))
		return (_SUCCESS);
	return (_FAILURE);
}

int	_bad_value(char *value)
{
	int	i;

	if (*value == '=')
		return (_err_print(_ERR_EXPORT_INVALID, value, true, 1));
	i = -1;
	while (value[++i] && value[i] != '=')
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
		else if (!_replace_env_value(&data->env, args[i]))
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
