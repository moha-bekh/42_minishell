/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _xpd_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:41:05 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/01 02:08:17 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_xpd_var_proc(t_pdata data, t_ppnlst token, int *i)
{
	char	*str;
	char	*tmp;
	int		j;

	str = (*token)->addr_1;
	j = ++(*i);
	while (str[*i] && _xpd_conv(str[*i]))
	{
		if (str[*i] == '?')
		{
			*i += 1;
			break ;
		}
		*i += 1;
	}
	tmp = ft_substr(str, j, *i - j);
	if (tmp[0] == '?')
		_xpd_errno(data);
	else
		_xpd_var_env(data, tmp);
	free(tmp);
	return (_SUCCESS);
}

int	_xpd_str_proc(t_pdata data, t_ppnlst token, int *i)
{
	char	*str;
	char	*tmp;
	int		j;

	str = (*token)->addr_1;
	j = *i;
	while (str[*i + 1] && str[*i + 1] != '$')
		*i += 1;
	tmp = ft_substr(str, j, *i - j + 1);
	_dlst_push_back(&data->xpd, ft_strdup(tmp), NULL, 0);
	free(tmp);
	*i += 1;
	return (_SUCCESS);
}

int	_xpd_join(t_pdata data, t_ppnlst token)
{
	t_pnlst	inc;
	char	*tmp;
	char	*pmt;

	inc = data->xpd->d_top;
	tmp = ft_strdup("");
	while (inc)
	{
		pmt = tmp;
		tmp = ft_strjoin(tmp, inc->addr_1);
		free(pmt);
		inc = inc->next;
	}
	free((*token)->addr_1);
	(*token)->addr_1 = tmp;
	_dlst_clear(&data->xpd);
	data->xpd = NULL;
	return (_SUCCESS);
}

int	_xpd_str(t_pdata data, t_ppnlst token)
{
	char	*str;
	int		i;

	str = (*token)->addr_1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && _xpd_conv(str[i + 1]))
			_xpd_var_proc(data, token, &i);
		else
			_xpd_str_proc(data, token, &i);
	}
	_xpd_join(data, token);
	return (_SUCCESS);
}
