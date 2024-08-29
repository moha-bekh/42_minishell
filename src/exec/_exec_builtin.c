/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:54:03 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/29 06:24:19 by moha             ###   ########.fr       */
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
		if (!ft_strcmp(tmp->addr_1, args[0]))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	_exec_builtin(t_pdata data, t_ppncmd cmd)
{
	if ((*cmd)->prev && _read_from_pipe(cmd))
		return (_FAILURE);
	if ((*cmd)->next && _write_to_pipe(cmd))
		return (_FAILURE);
	// if ((*cmd)->redirs.in_name && _set_redir_in(cmd))
	// 	return (_FAILURE);
	// if ((*cmd)->redirs.out_name && _set_redir_out(cmd))
	// 	return (_FAILURE);
	if (!ft_strncmp((*cmd)->args[0], "cd", 2))
		return (_cd(data, (*cmd)->args));
	if (!ft_strncmp((*cmd)->args[0], "echo", 4))
		return (_echo(data, (*cmd)->args));
	if (!ft_strncmp((*cmd)->args[0], "env", 3))
		return (_env(data, (*cmd)->args));
	if (!ft_strncmp((*cmd)->args[0], "exit", 4))
		return (_exit_(data, (*cmd)->args));
	if (!ft_strncmp((*cmd)->args[0], "export", 6))
		return (_export(data, (*cmd)->args));
	if (!ft_strncmp((*cmd)->args[0], "pwd", 3))
		return (_pwd());
	if (!ft_strncmp((*cmd)->args[0], "unset", 5))
		return (_unset(data, (*cmd)->args));
	return (_SUCCESS);
}

int	_exec_builtin_redir_in(t_pdata data, t_ppncmd cmd)
{
	data->args._stdin = dup(STDIN_FILENO);
	if (data->args._stdin < 0)
		return (_err_print("bash: dup failed", NULL, false, 1));
	(*cmd)->redirs.fd[0] = open((*cmd)->redirs.in_name, O_RDONLY);
	if ((*cmd)->redirs.fd[0] < 0)
		return (_err_print("bash: open", NULL, false, 0));
	if (dup2((*cmd)->redirs.fd[0], STDIN_FILENO) < 0)
		return (_err_print("bash: dup2 failed", NULL, false, 1));
	if (close((*cmd)->redirs.fd[0]))
		return (_err_print("bash: close", NULL, false, 0));
	return (_SUCCESS);
}

int	_exec_builtin_redir_out(t_pdata data, t_ppncmd cmd)
{
	data->args._stdout = dup(STDOUT_FILENO);
	if (data->args._stdout < 0)
		return (_err_print("bash: dup failed", NULL, false, 1));
	if ((*cmd)->redirs.out_trunc)
		(*cmd)->redirs.fd[1] = open((*cmd)->redirs.out_name, _O_RWCT);
	else
		(*cmd)->redirs.fd[1] = open((*cmd)->redirs.out_name, _O_RWCA);
	if ((*cmd)->redirs.fd[1] < 0)
		return (_err_print(_ERR_IS_DIR, (*cmd)->redirs.out_name, true, 1));
	if (dup2((*cmd)->redirs.fd[1], STDOUT_FILENO) < 0)
		return (_err_print("bash: dup2 failed", NULL, false, 1));
	if (close((*cmd)->redirs.fd[1]) < 0)
		return (_err_print("bash: close failed", NULL, false, 1));
	return (_SUCCESS);
}

int	_restore_stdfds(t_pdata data)
{
	if (dup2(data->args._stdin, STDIN_FILENO) < 0)
		return (_err_print("bash: dup2 failed", NULL, false, 1));
	if (dup2(data->args._stdout, STDOUT_FILENO) < 0)
		return (_err_print("bash: dup2 failed", NULL, false, 1));
	return (_SUCCESS);
}

int	_exec_builtin_proc(t_pdata data, t_ppncmd cmd)
{
	if ((*cmd)->redirs.in_name && !(*cmd)->redirs.here_fd
		&& _exec_builtin_redir_in(data, cmd))
		return (_FAILURE);
	else if ((*cmd)->redirs.here_name && (*cmd)->redirs.here_fd)
	{
		data->args._stdin = dup(STDIN_FILENO);
		if (data->args._stdin < 0)
			return (_err_print("bash: dup failed", NULL, false, 1));
		(*cmd)->redirs.here_fd = open((*cmd)->redirs.here_name, _O_RWCT);
		if ((*cmd)->redirs.here_fd < 0)
			return (_err_print("bash: open", NULL, false, 0));
		if (dup2((*cmd)->redirs.here_fd, STDIN_FILENO) < 0)
			return (_err_print("bash: dup2 failed", NULL, false, 1));
		if (close((*cmd)->redirs.here_fd))
			return (_err_print("bash: close", NULL, false, 0));
	}
	if ((*cmd)->redirs.out_name && _exec_builtin_redir_out(data, cmd))
		return (_FAILURE);
	data->_errno = _exec_builtin(data, cmd);
	if (_restore_stdfds(data))
		return (_FAILURE);
	return (_SUCCESS);
}
