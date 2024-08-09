/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _expand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:41:05 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/09 17:22:34 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_varchr_conv(char c)
{
	if (!ft_isalnum(c) && c != '_')
		return (_FAILURE);
	return (_SUCCESS);
}

int	_var_process(t_pdata data, t_ptok token, int *i)
{
	char	*tmp;
	int		j;

	*i += 1;
	j = *i;
	while (token->value[*i] && _varchr_conv(token->value[*i]))
		*i += 1;
	tmp = ft_substr(token->value, j, *i - j);
	data->tmp = _get_env_value(data->env.dll_env, tmp);
	free(tmp);
	data->exp = _env_push_back(data->exp, NULL, ft_strdup(data->tmp));
	free(data->tmp);
	return (_SUCCESS);
}

int	_str_process(t_pdata data, t_ptok token, int *i)
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
			_var_process(data, token, &i);
		else
			_str_process(data, token, &i);
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

int	_expand(t_pdata data)
{
	t_ptok	tmp;
	char	*value;

	if (!data || !data->tok)
		return (_FAILURE);
	tmp = data->tok->t_top;
	while (tmp)
	{
		if (tmp->type == '$' && tmp->next)
		{
			// if (tmp->next->value[0] == '?')
			// {
			// 	data->tmp = tmp->value;
			// 	tmp->value = ft_strjoin(tmp->value, tmp->next->value);
			// 	free(data->tmp);
			// 	data->tmp = NULL;
			// 	data->tok = _tok_pop_in(data->tok, tmp->next);
			// }
			// else
				tmp = tmp->next;
				data->tok = _tok_pop_in(data->tok, tmp->prev);
				value = _get_env_value(data->env.dll_env, tmp->value);
				free(tmp->value);
				tmp->value = value;
		}
		if (tmp->type == '"' && tmp->value[0])
			_expand_string(data, tmp);
		tmp = tmp->next;
	}
	return (_SUCCESS);
}
