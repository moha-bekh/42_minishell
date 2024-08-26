/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _path.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:19:04 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/26 12:28:09 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_is_path(char *str)
{
	if (!str)
		return (0);
	if (ft_strchr(str, '/'))
		return (1);
	return (0);
}

int	_get_path(t_pdata data, t_pcmd *cmd)
{
	char	**path;
	char	*prog;
	int		i;

	if (*data->args.env_path)
		path = data->args.env_path;
	else if (*data->args.hard_path)
		path = data->args.hard_path;
	else
		return (_FAILURE);
	prog = (*cmd)->args[0];
	i = -1;
	while (path[++i])
	{
		(*cmd)->path = ft_strjoin(path[i], prog);
		if (!access((*cmd)->path, F_OK) && !access((*cmd)->path, X_OK))
			return (_SUCCESS);
		free((*cmd)->path);
		(*cmd)->path = NULL;
	}
	return (_FAILURE);
}

int	_resolve_path(t_pdata data, t_pcmd *cmd)
{
	char	*prog;

	if (!(*cmd)->args)
		(*cmd)->path = ft_strdup("");
	else
	{
		prog = (*cmd)->args[0];
		if (_is_path(prog) && !access(prog, F_OK) && !access(prog, X_OK))
			(*cmd)->path = ft_strdup(prog);
		else if (_get_path(data, cmd))
			(*cmd)->path = ft_strdup("");
	}
	return (_SUCCESS);
}
