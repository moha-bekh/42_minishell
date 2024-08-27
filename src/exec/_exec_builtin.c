/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:54:03 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/27 16:09:23 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_is_builtin(t_pdata data, char **args)
{
	t_pnlst	tmp;

	if (!args || !args[0])
		return (0);
	tmp = data->builtins->d_top;
	while (tmp)
	{
		if (!ft_strcmp((char *)tmp->addr_1, args[0]))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	_exec_builtin(t_pdata data, t_ppncmd cmd)
{
	if ((*cmd)->prev)
		_read_from_pipe(cmd);
	if ((*cmd)->next)
		_write_to_pipe(cmd);
	if ((*cmd)->redirs.in_name)
		_set_redir_in(cmd);
	if ((*cmd)->redirs.out_name)
		_set_redir_out(cmd);
	// if (!ft_strncmp(args, "cd", 3))
	// 	return (_cd(data));
	if (!ft_strncmp((*cmd)->args[0], "echo", 4))
		return (_echo(data, cmd));
	if (!ft_strncmp((*cmd)->args[0], "env", 3))
		return (_env(data, cmd));
	if (!ft_strncmp((*cmd)->args[0], "export", 6))
		return (_export(data, cmd));
	if (!ft_strncmp((*cmd)->args[0], "pwd", 3))
		return (_pwd());
	if (!ft_strncmp((*cmd)->args[0], "unset", 5))
		return (_unset(data, cmd));
	return (_SUCCESS);
}

int	_exec_builtin_proc(t_pdata data, t_ppncmd cmd)
{
	int	dup_stdin;
	int	dup_stdout;

	data->_errno = _exec_builtin(data, cmd);
	if ((*cmd)->redirs.in_name || (*cmd)->redirs.here_name)
	{
		dup_stdin = dup(data->args._stdin);
		data->_errno = dup2(dup_stdin, STDIN_FILENO);
		if (data->_errno < 0)
			return (perror("dup2: "), _EXT_DUP2);
	}
	if ((*cmd)->redirs.out_name)
	{
		dup_stdout = dup(data->args._stdout);
		data->_errno = dup2(dup_stdout, STDOUT_FILENO);
		if (data->_errno < 0)
			return (perror("dup2: "), _EXT_DUP2);
	}
	return (_SUCCESS);
}
