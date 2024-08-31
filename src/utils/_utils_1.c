/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:35:57 by moha              #+#    #+#             */
/*   Updated: 2024/08/31 16:43:39 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_sep(char *str)
{
	int	i;

	if (!*str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	_path_slash(t_pdata data)
{
	char	**path;
	char	*tmp;
	int		i;

	if (data->args.env_path)
		path = data->args.env_path;
	else
		path = data->args.hard_path;
	i = -1;
	while (path[++i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free(tmp);
		tmp = NULL;
	}
	return (_SUCCESS);
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

int	_count_args(t_pnlst token)
{
	t_pnlst	tmp;
	int		i;

	if (!token)
		return (0);
	tmp = token;
	i = 0;
	while (tmp && tmp->x != _PIPE && !_tok_id(tmp->x, _TYP_SEP))
	{
		if (tmp && _tok_id(tmp->x, _TYP_REDIRS))
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
