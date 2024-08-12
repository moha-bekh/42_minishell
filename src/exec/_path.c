/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _path.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:19:04 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/12 16:56:35 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_is_path(char *str)
{
	if (!str)
		return (_NOT);
	if (ft_strchr(str, '/'))
		return (_IS);
	return (_NOT);
}

int	_path_slash(t_pdata data, int idx)
{
	int	i;

	if (!data || !data->paths[idx])
		return (_FAILURE);
	i = -1;
	while (data->paths[idx][++i])
	{
		data->tmp = data->paths[idx][i];
		data->paths[idx][i] = ft_strjoin(data->paths[idx][i], "/");
		free(data->tmp);
		data->tmp = NULL;
	}
	return (_SUCCESS);
}

int	_get_path(t_pdata data, t_pcmd cmd)
{
	int	i;

	if (!data || !cmd || !data->paths[0])
		return (_FAILURE);
	i = -1;
	if (data->paths[0][0])
	{
		while (data->paths[0][++i])
		{
			cmd->cmd_path = ft_strjoin(data->paths[0][i], cmd->cmd_arg[0]);
			if (!access(cmd->cmd_path, F_OK | X_OK))
				return (_SUCCESS);
			free(cmd->cmd_path);
			cmd->cmd_path = NULL;
		}
	}
	if (data->paths[1][0])
	{
		i = -1;
		while (data->paths[0][++i])
		{
			cmd->cmd_path = ft_strjoin(data->paths[1][i], cmd->cmd_arg[0]);
			if (!access(cmd->cmd_path, F_OK | X_OK))
				return (_SUCCESS);
			free(cmd->cmd_path);
			cmd->cmd_path = NULL;
		}
	}
	return (_FAILURE);
}

int	_check_access(t_pdata data, t_pcmd cmd)
{
	if (_is_path(cmd->cmd_arg[0]))
	{
		if (!access(cmd->cmd_arg[0], F_OK) && !access(cmd->cmd_arg[0], X_OK))
		{
			cmd->cmd_path = ft_strdup(cmd->cmd_arg[0]);
			return (_SUCCESS);
		}
		return (_FAILURE);
	}
	else
		_get_path(data, cmd);
	return (_SUCCESS);
}

int	_resolve_path(t_pdata data, t_pbt_op node)
{
	t_pcmd	tmp;

	if (!data || !node)
		return (_ERROR);
	tmp = node->cmd->c_top;
	while (tmp)
	{
		if (tmp->cmd_arg && _is_builtin(data, tmp->cmd_arg[0]))
		{
			tmp->built_in = true;
			tmp = tmp->next;
			continue ;
		}
		else if (tmp->cmd_arg)
			_check_access(data, tmp);
		tmp = tmp->next;
	}
	return (_SUCCESS);
}
