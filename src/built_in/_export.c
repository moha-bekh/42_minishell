/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:34:32 by moha              #+#    #+#             */
/*   Updated: 2024/08/27 16:51:38 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_varstr_conv(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
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
	char	*key;
	char	*value;
	char	*exp_value;

	key = ft_substr(arg, 0, _get_start_index(arg));
	value = ft_substr(arg, _get_start_index(arg) + 1, ft_strlen(arg));
	exp_value = ft_strdup(value);
	exp_value = _exp_value(exp_value);
	_dlst_push_back(&data->env, key, value, 0);
	_dlst_push_back(&data->export, key, exp_value, 0);
	_dlst_sort(&data->export, false);
	return (_SUCCESS);
}

int	_replace_env_value(t_pdata data, char *arg)
{
	t_pnlst	tmp;
	char	*value;
	char	*key;

	key = ft_substr(arg, 0, _get_start_index(arg));
	value = ft_substr(arg, _get_start_index(arg) + 1, ft_strlen(arg));
	tmp = data->env->d_top;
	while (tmp)
	{
		if (!ft_strcmp((char *)tmp->addr_1, key))
		{
			free(key);
			key = tmp->addr_2;
			tmp->addr_2 = value;
			free(key);
			key = NULL;
			return (1);
		}
		tmp = tmp->next;
	}
	free(value);
	return (0);
}

int	_replace_export_value(t_pdata data, char *arg)
{
	t_pnlst	tmp;
	char	*value;
	char	*key;

	key = ft_substr(arg, 0, _get_start_index(arg));
	value = ft_substr(arg, _get_start_index(arg) + 1, ft_strlen(arg));
	value = _exp_value(value);
	tmp = data->export->d_top;
	while (tmp)
	{
		if (!ft_strcmp((char *)tmp->addr_1, key))
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
	char	*tmp;

	tmp = ft_substr(value, 0, _get_start_index(value));
	if (!tmp[0] || _varstr_conv(tmp))
	{
		free(tmp);
		return (_err_print(_ERR_EXPORT_INVALID, value, true, 1));
	}
	free(tmp);
	return (_SUCCESS);
}

int	_export(t_pdata data, t_ppncmd cmd)
{
	int	i;

	if (!(*cmd)->args[1])
		return (_dlst_print_export(data->export), _SUCCESS);
	i = -1;
	while ((*cmd)->args[++i])
	{
		if (_bad_value((*cmd)->args[i]))
			continue ;
		else if (_replace_env_value(data, (*cmd)->args[i]))
		{
			_replace_export_value(data, (*cmd)->args[i]);
			continue ;
		}
		_add_value(data, (*cmd)->args[i]);
	}
	_dlst_sort(&data->export, false);
	return (_SUCCESS);
}
