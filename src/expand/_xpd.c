/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _xpd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:22:33 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/21 20:13:13 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_join_strings(t_ppnlst token)
{
	t_pnlst	tmp;
	char	*old;
	char a;
	char b;

	tmp = *token;
	while (tmp && tmp->x != _PIPE && !_tok_id(tmp->x, _TYP_SEP))
	{
		if (tmp->flag)
		{
			tmp = tmp->next;
			old = tmp->addr_1;
			tmp->addr_1 = ft_strjoin(tmp->prev->addr_1, tmp->addr_1);
			free(old);
			a = tmp->prev->x;
			b = tmp->x;
			old = tmp->addr_2;
			tmp->addr_2 = ft_strjoin(&a, &b);
			free(old);
			_dlst_pop_in(&(*token)->manager, &tmp->prev);
			continue ;
		}
		tmp = tmp->next;
	}
	return (_SUCCESS);
}

int	_xpd_var(t_pdata data, t_ppnlst token)
{
	char	*tmp;

	tmp = _env_get_value(data, (*token)->addr_1);
	if (tmp)
	{
		free((*token)->addr_1);
		(*token)->addr_1 = ft_strdup(tmp);
	}
	else if (!tmp && !ft_strcmp((*token)->addr_1, "$?"))
	{
		free((*token)->addr_1);
		(*token)->addr_1 = ft_itoa(data->_errno);
	}
	return (_SUCCESS);
}

char	*_xpd_errno(t_pdata data, char *buf, int *i)
{
	char *tmp;
	int j;
	int k;

	*i += 1;
	tmp = ft_itoa(data->_errno);
	if (!tmp)
		return (buf);
	k = ft_strlen(buf);
	j = 0;
	while (tmp[j])
		buf[k++] = tmp[j++];
	free(tmp);
	return (buf);
}

char	*_xpd_get_var(char *line, int *i)
{
	char *key;
	int start;
	int len;


	len = 0;
	start = *i;
	while (line[*i] && _xpd_conv(line[*i]))
	{
		*i += 1;
		len++;
	}
	key = ft_substr(line, start, len);
	return (key);
}

char	*_xpd_env_var(t_pdata data, char *line, char *buf, int *i)
{
	char *key;
	char *value;
	int j;
	int k;

	key = _xpd_get_var(line, i);
	value = _env_get_value(data, key);
	free(key);
	if (!value)
	{
		*i += 1;
		return (buf);
	}
	k = ft_strlen(buf);
	j = 0;
	while (value[j])
		buf[k++] = value[j++];
	return (buf);
}

char	*_xpd_str(t_pdata data, char *line)
{
	char *buf;
	int i;
	int j;

	if (!line)
		return (NULL);
	buf = malloc(sizeof(char) * 4096);
	if (!buf)
		return (NULL);
	ft_memset(buf, 0, 4096);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] != '$')
		{
			i++;
			if (line[i] == '?')
				buf = _xpd_errno(data, buf, &i);
			else
				buf = _xpd_env_var(data, line, buf, &i);
			j = ft_strlen(buf);
			continue;
		}
		buf[j++] = line[i++];
	}
	free(line);
	return (buf);
}

int	_xpd_line(t_pdata data, t_ppnlst token)
{
	t_pnlst	tmp;

	tmp = *token;
	while (tmp && tmp->x != _PIPE && !_tok_id(tmp->x, _TYP_SEP))
	{
		if (tmp->x == '*' && _xpd_wildcards(data, &tmp))
			return (_FAILURE);
		else if (tmp->x == '$' && _xpd_var(data, &tmp))
			return (_FAILURE);
		if (tmp->x == '"' && _xpd_needed(tmp->addr_1))
			tmp->addr_1 = _xpd_str(data, tmp->addr_1);
		/*if (tmp->x == '"' && _xpd_needed(tmp->addr_1))*/
		/*	_xpd_str(data, &tmp);*/
		tmp = tmp->next;
	}
	_join_strings(token);
	return (_SUCCESS);
}
