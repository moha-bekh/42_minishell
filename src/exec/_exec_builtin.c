/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:54:03 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/29 19:26:29 by moha             ###   ########.fr       */
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

int	_exec_builtin_proc(t_pdata data, t_ppncmd cmd)
{
	if ((*cmd)->next)
		pipe((*cmd)->redirs.pfd);
	_save_stdfds(data);
	_exec_redirections(data, cmd);
	data->_errno = _exec_builtin(data, cmd);
	_restore_stdfds(data);
	if ((*cmd)->prev)
	{
		close((*cmd)->prev->redirs.pfd[0]);
		close((*cmd)->prev->redirs.pfd[1]);
	}
	return (_SUCCESS);
}
