/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:54:03 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/25 23:22:53 by mbekheir         ###   ########.fr       */
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
	if (!ft_strncmp((*cmd)->args[0], "cd", 2))
		return (_cd(data, (*cmd)->args));
	if (!ft_strncmp((*cmd)->args[0], "echo", 4))
		return (_echo((*cmd)->args));
	if (!ft_strncmp((*cmd)->args[0], "env", 3))
		return (_env(data, (*cmd)->args));
	if (!ft_strncmp((*cmd)->args[0], "exit", 4))
		return (_exit_(data, (*cmd)->args));
	if (!ft_strncmp((*cmd)->args[0], "export", 6))
		return (_export(data, (*cmd)->args));
	if (!ft_strncmp((*cmd)->args[0], "pwd", 3))
		return (_pwd(data));
	if (!ft_strncmp((*cmd)->args[0], "unset", 5))
		return (_unset(data, (*cmd)->args));
	return (_SUCCESS);
}

int	_exec_builtin_proc(t_pdata data, t_ppncmd cmd)
{
	_save_stdfds(data);
	_exec_redirections(cmd);
	data->_errno = _exec_builtin(data, cmd);
	_restore_stdfds(data);
	return (_SUCCESS);
}

int	_exec_builtin_process(t_pdata data, t_ppncmd cmd)
{
	if ((*cmd)->next)
	{
		if (pipe((*cmd)->redirs.pfd) < 0)
			return (_err_print("bash: pipe failed", NULL, false, 1));
	}
	(*cmd)->pid = fork();
	if ((*cmd)->pid < 0)
		return (_err_print("bash: fork failed", NULL, false, 1));
	if (!(*cmd)->pid)
	{
		if (_exec_builtin_proc(data, cmd))
			return (_FAILURE);
	}
	return (_SUCCESS);
}
