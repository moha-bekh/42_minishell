/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:35:57 by moha              #+#    #+#             */
/*   Updated: 2024/08/09 16:53:33 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_get_start_index(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (i);
	}
	return (i);
}

char	*_get_env_value(u_padll env, char *key)
{
	t_pev	tmp;

	if (!env || !key)
		return (ft_strdup(""));
	tmp = env->e_top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

int	_count_arg(t_ptok token)
{
	t_ptok	tmp;
	int		i;

	if (!token)
		return (_FAILURE);
	tmp = token;
	i = 0;
	while (tmp && tmp->type != _PIPE && !_tok_is(_TYP_SEP, tmp->type))
	{
		if (tmp && _tok_is(_TYP_REDIRS, tmp->type))
		{
			tmp = tmp->next;
			if (tmp)
				tmp = tmp->next;
			continue ;
		}
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	*get_random_name(void)
{
	int				fd;
	unsigned char	*buf;
	int				i;

	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (_alloc((void **)&buf, 11))
		return (NULL);
	read(fd, buf, 10);
	close(fd);
	i = -1;
	while (buf[++i])
		buf[i] = (buf[i] % 26) + 97;
	return ((char *)buf);
}

int	is_overflow(char *str)
{
	if (str[0] == '-' && (ft_strlen(str) <= 20))
	{
		if (ft_strncmp(str, "-9223372036854775808", 20) > 0)
			return (1);
	}
	else if (ft_strlen(str) <= 19)
	{
		if (ft_strncmp(str, "9223372036854775807", 19) > 0)
			return (1);
	}
	return (0);
}
