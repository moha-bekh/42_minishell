/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _xpd_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:11:19 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/23 12:08:22 by mbekheir         ###   ########.fr       */
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
		tmp = _xpd_str(data, tmp, true);
		ft_dprintf(fd[1], "%s\n", tmp);
		free(tmp);
		tmp = NULL;
	}
	close(fd[0]);
	unlink((*cmd)->redirs.in_name);
	close(fd[1]);
	(*cmd)->redirs.in_name = new_hd;
	return (_SUCCESS);
}
