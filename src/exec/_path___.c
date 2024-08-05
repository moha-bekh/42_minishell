/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _path.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 22:00:46 by moha              #+#    #+#             */
/*   Updated: 2024/07/30 22:40:33 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_path_slash(t_pdata data, int idx)
{
	int	i;

	if (!data || !data->paths[idx])
		return (_ERROR);
	i = -1;
	while (data->paths[idx][++i])
	{
		data->tmp = data->paths[idx][i];
		data->paths[idx][i] = ft_strjoin(data->paths[idx][i], "/");
		free(data->tmp);
	}
	return (_SUCCESS);
}

int	_is_path(char *str)
{
	if (!str)
		return (_ERROR);
	if (ft_strchr(str, '/'))
		return (_IS);
	return (_NOT);
}

int	_get_path(t_pdata data, t_pcmd cmd)
{
	int	i;

	if (!data || !cmd || !data->paths[0])
		return (_ERROR);
	i = -1;
	if (data->paths[0])
	{
		while (data->paths[0][++i])
		{
			cmd->cmd_path = ft_strjoin(data->paths[0][i], cmd->cmd_a[0]);
			if (!access(cmd->cmd_path, F_OK | X_OK))
				return (_SUCCESS);
			free(cmd->cmd_path);
		}
	}
	if (data->paths[1])
	{
		i = -1;
		while (data->paths[0][++i])
		{
			cmd->cmd_path = ft_strjoin(data->paths[1][i], cmd->cmd_a[0]);
			if (!access(cmd->cmd_path, F_OK | X_OK))
				return (_SUCCESS);
			free(cmd->cmd_path);
		}
	}
	return (_ERROR);
}

int	_check_path(t_pdata data, t_pcmd cmd)
{
	if (!data || !cmd)
		return (_ERROR);
	if (!access(cmd->cmd_a[0], F_OK) && !access(cmd->cmd_a[0], X_OK))
	{
		cmd->cmd_path = ft_strdup(cmd->cmd_a[0]);
		return (_SUCCESS);
	}
	return (_ERROR);
}

int	_check_access(t_pdata data, t_pcmd cmd)
{
	if (!data || !cmd)
		return (_ERROR);
	if (_is_path(cmd->cmd_a[0]))
		_check_path(data, cmd);
	else
		_get_path(data, cmd);
	return (_SUCCESS);
}
