/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _here_doc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 04:26:25 by moha              #+#    #+#             */
/*   Updated: 2024/08/30 04:28:39 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_swap_fd_here_doc(t_ppncmd cmd)
{
	(*cmd)->redirs.here_fd = open((*cmd)->redirs.here_name, O_RDONLY);
	dup2((*cmd)->redirs.here_fd, STDIN_FILENO);
	close((*cmd)->redirs.here_fd);
	return (_SUCCESS);
}

int	_here_doc_writer(t_pdata data, t_ppncmd cmd, int idx)
{
	char	*line;

	(*cmd)->redirs.here_fd = open((*cmd)->redirs.here_names[idx], _O_RWCA);
	while (true)
	{
		if ((*cmd)->redirs.here_names[idx] != (*cmd)->redirs.here_name)
			unlink((*cmd)->redirs.here_names[idx]);
		line = readline("> ");
		if (!line || !ft_strcmp(line, (*cmd)->redirs.here_limit[idx]))
			break ;
		line = _xpd_xpd_str(data, line);
		ft_dprintf((*cmd)->redirs.here_fd, "%s\n", line);
		free(line);
		line = NULL;
	}
	free(line);
	close((*cmd)->redirs.here_fd);
	return (_SUCCESS);
}

int	_here_doc_proc(t_pdata data, t_ppncmd cmd)
{
	int	i;

	i = 0;
	while (i < (*cmd)->redirs.here_idx)
	{
		if (_here_doc_writer(data, cmd, i))
			return (_FAILURE);
		i++;
	}
	_swap_fd_here_doc(cmd);
	return (_SUCCESS);
}

