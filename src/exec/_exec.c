/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:20:38 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/08 18:44:53 by mbekheir         ###   ########.fr       */
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
		return (_exit_(data, (*cmd)->args));
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
		return (_FAILURE);
	data->_errno = _exec_builtin(data, cmd);
	if (_restore_stdfds(data))
		return (_FAILURE);
	return (_SUCCESS);
}

// void	_tmp_hndl(int sig)
// {
// 	(void)sig;
// 	if (sig == SIGINT)
// 		printf("sigint\n");
// 	if (sig == SIGQUIT)
// 		printf("sigquit\n");
// }

int	_exec_process(t_pdata data, t_pncmd cmd)
{
	char	**env;

	if (_xpd_line(data, &cmd->token))
		return (_FAILURE);
	if (_pars_args_line(data, &cmd, &cmd->token, true))
		return (_FAILURE);
	// if (ft_strchr(cmd->args[0], '/'))
	// {
	// 	if (access(cmd->args[0], X_OK) < 0)
	// 	{
	// 		data->_errno = 126;
	// 		return (_err_print(_ERR_NOT_FOUND, cmd->args[0], true, 127));
	// 	}
	// }
	if (!cmd->next && !cmd->prev && _is_builtin(data, cmd->args))
	{
		if (_exec_builtin_proc(data, &cmd))
			return (_FAILURE);
	}
	else
	{
		if (cmd->next)
		{
			if (pipe(cmd->redirs.pfd) < 0)
				return (_err_print("bash: pipe failed", NULL, false, 1));
		}
		cmd->pid = fork();
		if (cmd->pid < 0)
			return (_err_print("bash: fork failed", NULL, false, 1));
		if (!cmd->pid)
		{
			data->shell.s_sigint.sa_handler = SIG_DFL;
			sigaction(SIGINT, &data->shell.s_sigint, NULL);
			data->shell.s_sigquit.sa_handler = SIG_DFL;
			sigaction(SIGQUIT, &data->shell.s_sigquit, NULL);
			if (_exec_redirections(&cmd))
			{
				_data_clear(data);
				exit(1);
			}
			if (!cmd->args)
				return (_SUCCESS);
			if (_is_builtin(data, cmd->args))
			{
				data->_errno = _exec_builtin(data, &cmd);
				_data_clear(data);
				exit(data->_errno);
			}
			else
			{
				if (_resolve_path(data, &cmd))
					return (_FAILURE);
				env = _ltoa(data->env);
				// execve(cmd->path, cmd->args, env);
				execve(cmd->path, cmd->args, data->args.env);
				if (cmd->args)
					_err_print(_ERR_NOT_FOUND, cmd->args[0], true, 127);
				ft_free_arr(env);
				_data_clear(data);
				exit(127);
			}
		}
		else
		{
			if (cmd->prev)
			{
				close(cmd->prev->redirs.pfd[1]);
				close(cmd->prev->redirs.pfd[0]);
			}
		}
	}
	return (_SUCCESS);
}

int	_exec_loop(t_pdata data, t_ppbtree node)
{
	t_pncmd	cmd;

	if (_pars_pipe_lines(node))
		return (_FAILURE);
	cmd = (*node)->cmd_line->c_top;
	while (cmd)
	{
		if (_exec_process(data, cmd))
			return (_FAILURE);
		cmd = cmd->next;
	}
	cmd = (*node)->cmd_line->c_top;
	if (!cmd->next && _is_builtin(data, cmd->args))
		return (_SUCCESS);
	while (cmd)
	{
		data->shell.s_sigint.sa_handler = SIG_IGN;
		sigaction(SIGINT, &data->shell.s_sigint, NULL);
		data->shell.s_sigquit.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &data->shell.s_sigquit, NULL);
		if (cmd->pid)
			waitpid(cmd->pid, &data->_errno, 0);
		if (WIFEXITED(data->_errno))
			data->_errno = WEXITSTATUS(data->_errno);
		else if (WIFSIGNALED(data->_errno))
			data->_errno = WTERMSIG(data->_errno) + 128;
		// if (tcsetattr(STDIN_FILENO, TCSANOW, &data->shell.new_term) == -1)
		// 	return (_FAILURE);
		if (data->_errno == 130)
			write(1, "\n", 1);
		if (data->_errno == 131)
			write(1, "Quit (core dumped)\n", 19);
		data->shell.s_sigint.sa_handler = _hndl_sigint;
		sigaction(SIGINT, &data->shell.s_sigint, NULL);
		data->shell.s_sigquit.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &data->shell.s_sigquit, NULL);
		cmd = cmd->next;
	}
	return (_SUCCESS);
}

int	_exec_subshell(t_pdata data, t_ppbtree node)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (_err_print("bash: fork failed", NULL, false, 1));
	if (!pid)
	{
		if (_exec(data, node))
			return (_FAILURE);
		_data_clear(data);
		exit(data->_errno);
	}
	else
	{
		waitpid(pid, &data->_errno, 0);
		if (WIFEXITED(data->_errno))
			data->_errno = WEXITSTATUS(data->_errno);
		else if (WIFSIGNALED(data->_errno))
			data->_errno = WTERMSIG(data->_errno) + 128;
	}
	return (_SUCCESS);
}

int	_exec(t_pdata data, t_ppbtree node)
{
	char	type;

	if (!*node)
		return (_SUCCESS);
	type = (*node)->token->x;
	if ((*node)->left)
		_exec(data, &(*node)->left);
	if ((type == _AND && data->_errno) || (type == _OR && !data->_errno))
		return (_SUCCESS);
	if (type == '(')
	{
		if (_exec_subshell(data, &(*node)->right))
			return (_FAILURE);
		return (_SUCCESS);
	}
	if (type != _AND && type != _OR && _exec_loop(data, node))
		return (_FAILURE);
	if ((*node)->right)
		_exec(data, &(*node)->right);
	return (_SUCCESS);
}
