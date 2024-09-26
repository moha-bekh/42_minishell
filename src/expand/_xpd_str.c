/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _xpd_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:47:09 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/26 14:04:23 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*_xpd_errno(t_pdata data, char *buf, int *i)
{
	char	*tmp;
	int		j;
	int		k;

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
	char	*key;
	int		start;
	int		len;

	len = 0;
	start = *i;
	while (line[*i] && _xpd_conv(line[*i]))
	{
		*i += 1;
		len++;
	}
	key = ft_substr(line, start, len);
	if (!key)
		return (NULL);
	return (key);
}

char	*_xpd_env_var(t_pdata data, char *line, char *buf, int *i)
{
	char	*key;
	char	*value;
	int		j;
	int		k;

	key = _xpd_get_var(line, i);
	value = _get_env_value(data, key);
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
	char	*buf;
	int		i;
	int		j;

	if (!line || _alloc((void **)&buf, sizeof(char) * 4096))
		return (NULL);
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
			continue ;
		}
		buf[j++] = line[i++];
	}
	free(line);
	return (buf);
}
