/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:54:03 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/12 20:54:35 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_is_builtin(t_pdata data, char *str)
{
	int	i;

	if (!data || !str)
		return (_ERROR);
	i = -1;
	while (++i < 7)
	{
		if (!ft_strcmp(data->built_in[i], str))
			return (_IS);
	}
	return (_NOT);
}

int	_exec_builtin(t_pdata data, t_pcmd cmd)
{
	if (!data || !cmd)
		return (_ERROR);
	if (!ft_strcmp(cmd->cmd_arg[0], "pwd"))
		return (_pwd());
	else if (!ft_strcmp(cmd->cmd_arg[0], "echo"))
		return (_echo(data, cmd->cmd_arg));
	// else if (!ft_strcmp(cmd->cmd_arg[0], "cd"))
	// 	_cd(data, cmd);
	else if (!ft_strcmp(cmd->cmd_arg[0], "export"))
		return (_export(data, cmd->cmd_arg));
	else if (!ft_strcmp(cmd->cmd_arg[0], "unset"))
		return (_unset(data, cmd->cmd_arg));
	else if (!ft_strcmp(cmd->cmd_arg[0], "env"))
		return (_env(data, cmd->cmd_arg));
	else if (!ft_strcmp(cmd->cmd_arg[0], "exit"))
		return (_exit_(data, cmd->cmd_arg));
	return (_SUCCESS);
}
