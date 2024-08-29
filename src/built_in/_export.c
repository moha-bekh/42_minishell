/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:34:32 by moha              #+#    #+#             */
/*   Updated: 2024/08/29 05:04:27 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_varstr_conv(char *str, int idx)
{
	int	i;

	i = 0;
	while (str[i] && i < idx)
	{
		if (!ft_isalpha(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	_add_value(t_pdata data, char *arg)
{
	int	idx;

	if (!arg)
		return (_SUCCESS);
	idx = _sep(arg);
	if (!idx)
	{
		_dlst_push_back(&data->env, ft_strdup(arg), NULL, 0);
		_dlst_push_back(&data->export, ft_strdup(arg), NULL, 0);
	}
	else
	{
		_dlst_push_back(&data->env, ft_substr(arg, 0, idx), ft_strdup(arg + (idx
					+ 1)), 0);
		_dlst_push_back(&data->export, ft_substr(arg, 0, idx), ft_strdup(arg
				+ (idx + 1)), 0);
	}
	_dlst_sort(&data->export, false);
	return (_SUCCESS);
}

int	_replace_env_value(t_pdata data, char *arg)
{
	char	*key;
	int		idx;
	t_pnlst	tmp;

	if (!arg || !data->env)
		return (0);
	idx = _sep(arg);
	key = ft_substr(arg, 0, idx);
	tmp = data->env->d_top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->addr_1, key))
		{
			free(key);
			free(tmp->addr_2);
			tmp->addr_2 = ft_strdup(arg + (idx + 1));
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	_replace_export_value(t_pdata data, char *arg)
{
	t_pnlst	tmp;
	char	*value;
	char	*key;

	key = ft_substr(arg, 0, _sep(arg));
	value = ft_substr(arg, _sep(arg) + 1, ft_strlen(arg));
	tmp = data->export->d_top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->addr_1, key))
		{
			free(key);
			key = tmp->addr_2;
			tmp->addr_2 = value;
			free(key);
			tmp = NULL;
			return (1);
		}
		tmp = tmp->next;
	}
	free(value);
	return (0);
}

int	_bad_value(char *value)
{
	int	idx;

	idx = _sep(value);
	if (!value[0] || _varstr_conv(value, idx))
		return (_err_print(_ERR_EXPORT_INVALID, value, true, 1));
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
		else if (_replace_env_value(data, args[i]))
		{
			_replace_export_value(data, args[i]);
			continue ;
		}
		else if (args[i])
			_add_value(data, args[i]);
	}
	_dlst_sort(&data->export, false);
	return (_SUCCESS);
}
