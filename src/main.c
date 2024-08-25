/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 06:00:00 by moha              #+#    #+#             */
/*   Updated: 2024/08/25 21:55:32 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_wait_pids(t_pdata data, u_padllst cmd_line, t_pcmd limit)
{
	t_pcmd	tmp;

	(void)limit;
	tmp = cmd_line->c_top;
	while (tmp)
	{
		waitpid(tmp->pid, &data->_errno, 0);
		if (WIFEXITED(data->_errno))
		{
			data->_errno = WEXITSTATUS(data->_errno);
			// printf("pid: %d\terrno: %d\n", tmp->pid, data->_errno);
		}
		// else
		// printf("pid: %d\texit abnormaly\n", tmp->pid);
		// if (tmp == limit)
		// 	break ;
		tmp = tmp->next;
	}
}

// int	_expand_vars(t_pdata data, t_pcmd *cmd)
// {
// 	t_pnlst	tmp;

// 	tmp = (*cmd)->token;
// 	while (tmp)
// 	{
// 		if (tmp->x == '$' && tmp->next)
// 		{
// 			tmp = tmp->next;
// 			_dllst_pop_in(&(*cmd)->token->manager, &tmp->prev);
// 		}
// 	}
// }

int	_exec_failed(t_pdata data, t_pcmd *cmd)
{
	ft_dprintf(2, "bash: %s: command not found\n", (*cmd)->args[0]);
	_data_structs_clear(data);
	_data_clear(data);
	exit(127);
	return (_FAILURE);
}

int	_set_redir_in(t_pcmd *cmd)
{
	(*cmd)->redirs.fd[0] = open((*cmd)->redirs.in_name, O_RDONLY);
	if ((*cmd)->redirs.fd[0] < 0)
		return (_EXT_OPEN);
	if (dup2((*cmd)->redirs.fd[0], STDIN_FILENO) < 0)
		return (perror("dup2: "), _EXT_DUP2);
	close((*cmd)->redirs.fd[0]);
	return (_SUCCESS);
}

int	_set_redir_out(t_pcmd *cmd)
{
	if ((*cmd)->redirs.out_trunc)
		(*cmd)->redirs.fd[1] = open((*cmd)->redirs.out_name,
				O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		(*cmd)->redirs.fd[1] = open((*cmd)->redirs.out_name,
				O_RDWR | O_CREAT | O_APPEND, 0644);
	if (dup2((*cmd)->redirs.fd[1], STDOUT_FILENO) < 0)
		return (perror("dup2: "), _EXT_DUP2);
	close((*cmd)->redirs.fd[1]);
	return (_SUCCESS);
}

int	_read_from_pipe(t_pcmd *cmd)
{
	close((*cmd)->prev->redirs.pfd[1]);
	if (dup2((*cmd)->prev->redirs.pfd[0], STDIN_FILENO) < 0)
		return (perror("dup2: "), _EXT_DUP2);
	close((*cmd)->prev->redirs.pfd[0]);
	return (_SUCCESS);
}

int	_write_to_pipe(t_pcmd *cmd)
{
	close((*cmd)->redirs.pfd[0]);
	if (dup2((*cmd)->redirs.pfd[1], STDOUT_FILENO) < 0)
		return (perror("dup2: "), _EXT_DUP2);
	close((*cmd)->redirs.pfd[1]);
	return (_SUCCESS);
}

int	_exec_child_proc(t_pdata data, t_pcmd *cmd)
{
	data->s_sig.sa_handler = child_hndl;
	if ((*cmd)->prev)
		_read_from_pipe(cmd);
	if ((*cmd)->next)
		_write_to_pipe(cmd);
	if ((*cmd)->redirs.in_name)
		_set_redir_in(cmd);
	if ((*cmd)->redirs.out_name)
		_set_redir_out(cmd);
	execve((*cmd)->path, (*cmd)->args, data->args.env);
	_exec_failed(data, cmd);
	return (_FAILURE);
}

int	_exec_parent_proc(t_pcmd *cmd)
{
	if ((*cmd)->prev)
	{
		close((*cmd)->prev->redirs.pfd[1]);
		close((*cmd)->prev->redirs.pfd[0]);
	}
	return (_SUCCESS);
}

int	_exec_proc(t_pdata data, t_pcmd *cmd)
{
	if ((*cmd)->next)
		if (pipe((*cmd)->redirs.pfd))
			return (perror("pipe: "), _EXT_PIPE);
	(*cmd)->pid = fork();
	if ((*cmd)->pid < 0)
		return (perror("fork: "), _EXT_FORK);
	if (!(*cmd)->pid)
	{
		if (_exec_child_proc(data, cmd))
			return (_FAILURE);
	}
	else
		_exec_parent_proc(cmd);
	return (_SUCCESS);
}

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

int	_exec_builtin(t_pdata data, t_pcmd *cmd)
{
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

int	_exec_cmd_line(t_pdata data, t_pbtree *node)
{
	t_pcmd	tmp;

	(void)data;
	_pars_pipe_lines(node);
	tmp = (*node)->cmd_line->c_top;
	while (tmp && !data->_errno)
	{
		_pars_args_line(&tmp);
		if (_is_builtin(data, tmp->args))
			data->_errno = _exec_builtin(data, &tmp);
		else
		{
			_resolve_path(data, &tmp);
			// _expand_vars(data, &tmp);
			_exec_proc(data, &tmp);
		}
		tmp = tmp->next;
	}
	_wait_pids(data, (*node)->cmd_line, tmp);
	return (_SUCCESS);
}

int	_exec(t_pdata data, t_pbtree *node)
{
	if (!*node)
		return (_SUCCESS);
	if ((*node)->left)
		_exec(data, &(*node)->left);
	else if ((*node)->token->x == '(')
	{
		_cmd_push_back(&(*node)->cmd_line, (*node)->token);
		(*node)->cmd_line->c_top->pid = fork();
		if ((*node)->cmd_line->c_top->pid < 0)
			return (perror("fork: "), _EXT_FORK);
		if (!(*node)->cmd_line->c_top->pid)
			_exec(data, &(*node)->right);
		else
			waitpid((*node)->cmd_line->c_top->pid, &data->_errno, 0);
		return (_SUCCESS);
	}
	else if ((*node)->token->x != _AND && (*node)->token->x != _OR)
		_exec_cmd_line(data, node);
	else
	{
		if ((*node)->token->x == _AND && data->_errno != 0)
			return (_SUCCESS);
		else if ((*node)->token->x == _OR && data->_errno == 0)
			return (_SUCCESS);
	}
	if ((*node)->right)
		_exec(data, &(*node)->right);
	return (_SUCCESS);
}

int	main(int ac, char **av, char **ev)
{
	static t_data	data;

	if (_data_init(&data, ac, av, ev) || _set_signals(&data))
		return (_data_clear(&data), _FAILURE);
	while (1)
	{
		data.prompt = readline(">$ ");
		if ((!data.prompt || !data.prompt[0]) && !_data_structs_clear(&data))
			continue ;
		add_history(data.prompt);
		if (_token_list(&data) && !_data_structs_clear(&data))
			continue ;
		data.tree = _tree_builder(&data);
		if (_exec(&data, &data.tree) && !_data_structs_clear(&data))
			continue ;
		_data_structs_clear(&data);
	}
	return (_data_clear(&data), _SUCCESS);
}
