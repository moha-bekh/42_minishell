/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _hd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:16:30 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/12 00:34:12 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_hd_open_fd(t_pdata data, t_pnlst token, int *fd)
{
	*fd = open(token->addr_1, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (*fd < 0)
	{
		_data_clear(data);
		exit(1);
	}
}

void	_hd_fill_loop(t_pdata data, t_pnlst token, char *line)
{
	int	fd;

	_hd_open_fd(data, token, &fd);
	while (true && data->_errno != 130)
	{
		line = readline("> ");
		if (!line && data->_errno != 130)
		{
			ft_dprintf(2, _ERR_HERE_EOF, token->next->addr_1);
			close(fd);
			_data_clear(data);
			exit(0);
		}
		if (!ft_strcmp(line, token->next->addr_1))
			break ;
		if (line && !_tok_id(token->next->x, _QUOTES))
			line = _xpd_str(data, line);
		if (line)
			ft_dprintf(fd, "%s\n", line);
		free(line);
		line = NULL;
	}
	close(fd);
}

int	_hd_parent_proc(t_pdata data, t_pnlst token, pid_t *pid)
{
	token = token->next;
	data->shell.s_sigint.sa_handler = SIG_IGN;
	sigaction(SIGINT, &data->shell.s_sigint, NULL);
	waitpid(*pid, &data->_errno, 0);
	if (WIFEXITED(data->_errno))
		data->_errno = WEXITSTATUS(data->_errno);
	else if (WIFSIGNALED(data->_errno))
		data->_errno = WTERMSIG(data->_errno) + 128;
	data->shell.s_sigint.sa_handler = _hndl_sigint;
	sigaction(SIGINT, &data->shell.s_sigint, NULL);
	if (data->_errno == 130)
		return (_FAILURE);
	return (_SUCCESS);
}

int	_hd_fill(t_pdata data, t_pnlst token)
{
	pid_t	pid;
	char	*line;

	line = NULL;
	pid = fork();
	if (pid < 0)
		return (_FAILURE);
	if (pid == 0)
	{
		data->shell.s_sigint.sa_handler = _hndl_hd_sigint;
		sigaction(SIGINT, &data->shell.s_sigint, NULL);
		_hd_fill_loop(data, token, line);
		free(line);
		if (data->_errno == 130)
			_data_clear_exit(data, 130);
		_data_clear_exit(data, 0);
	}
	else if (pid != 0 && _hd_parent_proc(data, token, &pid))
		return (_FAILURE);
	return (_SUCCESS);
}

int	_here_doc_filler(t_pdata data)
{
	t_pnlst	tmp;

	tmp = data->tokens->d_top;
	while (tmp)
	{
		if (tmp->x == _HERE_DOC)
		{
			if (_hd_fill(data, tmp))
				return (_FAILURE);
		}
		tmp = tmp->next;
	}
	return (_SUCCESS);
}
