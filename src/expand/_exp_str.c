/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exp_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:41:05 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/12 16:25:37 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	_errno_proc(t_pdata data)
{
	char	*tmp;

	tmp = ft_itoa(data->_errno);
	data->exp = _env_push_back(data->exp, NULL, ft_strdup(tmp));
	free(tmp);
	free(data->tmp);
	data->tmp = NULL;
	return (_SUCCESS);
}

int	_var_env_proc(t_pdata data)
{
	char	*tmp;

	tmp = data->tmp;
	data->tmp = _get_env_value(data->env.dll_env, data->tmp);
	free(tmp);
	data->exp = _env_push_back(data->exp, NULL, ft_strdup(data->tmp));
	free(data->tmp);
	data->tmp = NULL;
	return (_SUCCESS);
}

int	_var_proc(t_pdata data, t_ptok token, int *i)
{
	char	*tmp;
	int		j;

	tmp = NULL;
	*i += 1;
	j = *i;
	while (token->value[*i] && _varchr_conv(token->value[*i]))
	{
		if (token->value[*i] == '?')
		{
			*i += 1;
			break ;
		}
		*i += 1;
	}
	data->tmp = ft_substr(token->value, j, *i - j);
	if (data->tmp[0] == '?')
		_errno_proc(data);
	else
		_var_env_proc(data);
	return (_SUCCESS);
}

int	_str_proc(t_pdata data, t_ptok token, int *i)
{
	char	*tmp;
	int		j;

	j = *i;
	while (token->value[*i + 1] && token->value[*i + 1] != '$')
		*i += 1;
	tmp = ft_substr(token->value, j, *i - j + 1);
	data->exp = _env_push_back(data->exp, NULL, ft_strdup(tmp));
	free(tmp);
	*i += 1;
	return (_SUCCESS);
}

int	_expand_string(t_pdata data, t_ptok token)
{
	char	*tmp_1;
	t_pev	tmp_2;
	int		i;

	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '$' && _varchr_conv(token->value[i + 1]))
			_var_proc(data, token, &i);
		else
			_str_proc(data, token, &i);
	}
	tmp_2 = data->exp->e_top;
	tmp_1 = ft_strdup("");
	while (tmp_2)
	{
		data->tmp = tmp_1;
		tmp_1 = ft_strjoin(tmp_1, tmp_2->value);
		free(data->tmp);
		tmp_2 = tmp_2->next;
	}
	free(token->value);
	token->value = tmp_1;
	data->exp = _env_clear(data->exp);
	return (_SUCCESS);
}
