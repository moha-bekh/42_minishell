/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _builtin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:16:48 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/11 18:16:52 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_save_stdfds(t_pdata data)
{
	data->shell._stdin = dup(STDIN_FILENO);
	if (data->shell._stdin < 0)
		return (_FAILURE);
	data->shell._stdout = dup(STDOUT_FILENO);
	if (data->shell._stdout < 0)
		return (_FAILURE);
	return (_SUCCESS);
}

int	_restore_stdfds(t_pdata data)
{
	if (dup2(data->shell._stdin, STDIN_FILENO) < 0)
		return (_FAILURE);
	if (dup2(data->shell._stdout, STDOUT_FILENO) < 0)
		return (_FAILURE);
	return (_SUCCESS);
}

int	_exec_builtin(t_pdata data, t_ppncmd cmd)
{
	if (!ft_strncmp((*cmd)->args[0], "cd", 2))
		return (_cd(data, (*cmd)->args));
	if (!ft_strncmp((*cmd)->args[0], "echo", 4))
		return (_echo((*cmd)->args));
	if (!ft_strncmp((*cmd)->args[0], "env", 3))
		return (_env(data, (*cmd)->args));
	if (!ft_strncmp((*cmd)->args[0], "exit", 4))
		return (_exit_(data, *cmd, (*cmd)->args));
	if (!ft_strncmp((*cmd)->args[0], "export", 6))
		return (_export(data, (*cmd)->args));
	if (!ft_strncmp((*cmd)->args[0], "pwd", 3))
		return (_pwd(data));
	if (!ft_strncmp((*cmd)->args[0], "unset", 5))
		return (_unset(data, (*cmd)->args));
	return (_FAILURE);
}

int	_exec_builtin_proc(t_pdata data, t_ppncmd cmd)
{
	if (_save_stdfds(data))
		return (_FAILURE);
	if (_exec_redirections(cmd))
	{
		data->_errno = 1;
		return (_FAILURE);
	}
	data->_errno = _exec_builtin(data, cmd);
	if (_restore_stdfds(data))
		return (_FAILURE);
	return (_SUCCESS);
}
