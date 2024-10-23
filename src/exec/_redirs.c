/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _redirs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 06:39:42 by moha              #+#    #+#             */
/*   Updated: 2024/10/23 02:42:35 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_xpd_here_doc(t_pdata data, t_ppncmd cmd)
{
	int		fd[2];
	char	*new_hd;
	char	*tmp;

	fd[0] = open((*cmd)->redirs.in_name, O_RDONLY);
	tmp = _get_rname();
	new_hd = ft_strjoin("/tmp/", tmp);
	free(tmp);
	fd[1] = open(new_hd, O_RDWR | O_CREAT | O_APPEND, 0644);
	while (1)
	{
		tmp = get_next_line(fd[0]);
		if (!tmp)
			break ;
		printf("tmp: %s\n", tmp);
		tmp = _xpd_str(data, tmp, true);
		ft_dprintf(fd[1], "%s\n", tmp);
		free(tmp);
		tmp = NULL;
	}
	close(fd[0]);
	close(fd[1]);
	(*cmd)->redirs.in_name = new_hd;
	return (_SUCCESS);
}

int	_swap_fd_redir_in(t_ppncmd cmd)
{
	if ((*cmd)->redirs.in_name[0] == '$')
		return (_err_print(_ERR_AMBIGOUS, (*cmd)->redirs.in_name, true, 1));
	if (access((*cmd)->redirs.in_name, F_OK))
		return (_err_print(_ERR_NO_FILE, (*cmd)->redirs.in_name, true, 1));
	else if (access((*cmd)->redirs.in_name, R_OK))
		return (_err_print(_ERR_PERM, (*cmd)->redirs.in_name, true, 1));
	if ((*cmd)->redirs.is_here_doc && (*cmd)->redirs.xpd_hd)
		_xpd_here_doc(_get_data(), cmd);
	else
	{
		(*cmd)->redirs.fd[0] = open((*cmd)->redirs.in_name, O_RDONLY);
		if ((*cmd)->redirs.fd[0] < 0)
			return (perror("open"), _FAILURE);
		if (dup2((*cmd)->redirs.fd[0], STDIN_FILENO) < 0)
			return (perror("dup2"), _FAILURE);
		close((*cmd)->redirs.fd[0]);
	}
	return (_SUCCESS);
}

int	_swap_fd_redir_out(t_ppncmd cmd)
{
	if ((*cmd)->redirs.out_name[0] == '$')
		return (_err_print(_ERR_AMBIGOUS, (*cmd)->redirs.out_name, true, 1));
	if (access((*cmd)->redirs.out_name, W_OK))
		return (_err_print(_ERR_PERM, (*cmd)->redirs.out_name, true, 1));
	if ((*cmd)->redirs.out_trunc)
		(*cmd)->redirs.fd[1] = open((*cmd)->redirs.out_name,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		(*cmd)->redirs.fd[1] = open((*cmd)->redirs.out_name,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if ((*cmd)->redirs.fd[1] < 0)
		return (perror("open"), _FAILURE);
	if (dup2((*cmd)->redirs.fd[1], STDOUT_FILENO) < 0)
		return (perror("dup2"), _FAILURE);
	close((*cmd)->redirs.fd[1]);
	return (_SUCCESS);
}

int	_read_from_pipe(t_ppncmd cmd)
{
	close((*cmd)->prev->redirs.pfd[1]);
	(*cmd)->prev->redirs.pfd[1] = -1;
	if (dup2((*cmd)->prev->redirs.pfd[0], STDIN_FILENO) < 0)
		return (perror("dup2"), _FAILURE);
	close((*cmd)->prev->redirs.pfd[0]);
	(*cmd)->prev->redirs.pfd[0] = -1;
	return (_SUCCESS);
}

int	_write_to_pipe(t_ppncmd cmd)
{
	close((*cmd)->redirs.pfd[0]);
	(*cmd)->redirs.pfd[0] = -1;
	if (dup2((*cmd)->redirs.pfd[1], STDOUT_FILENO) < 0)
		return (perror("dup2"), _FAILURE);
	close((*cmd)->redirs.pfd[1]);
	(*cmd)->redirs.pfd[1] = -1;
	return (_SUCCESS);
}

int	_exec_redirections(t_ppncmd cmd)
{
	if ((*cmd)->redirs.out_name && _swap_fd_redir_out(cmd))
		return (_FAILURE);
	if ((*cmd)->redirs.in_name && _swap_fd_redir_in(cmd))
		return (_FAILURE);
	if ((*cmd)->prev && !(*cmd)->redirs.in_name && _read_from_pipe(cmd))
		return (_FAILURE);
	if ((*cmd)->next && !(*cmd)->redirs.out_name && _write_to_pipe(cmd))
		return (_FAILURE);
	if ((*cmd)->prev && (*cmd)->redirs.in_name)
	{
		if ((*cmd)->prev->redirs.pfd[0] > 0)
			close((*cmd)->prev->redirs.pfd[0]);
		if ((*cmd)->prev->redirs.pfd[1] > 0)
			close((*cmd)->prev->redirs.pfd[1]);
	}
	if ((*cmd)->next && (*cmd)->redirs.out_name)
	{
		if ((*cmd)->redirs.pfd[0] > 0)
			close((*cmd)->redirs.pfd[0]);
		if ((*cmd)->redirs.pfd[1] > 0)
			close((*cmd)->redirs.pfd[1]);
	}
	return (_SUCCESS);
}
