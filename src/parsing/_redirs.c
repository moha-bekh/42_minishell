/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _redirs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:02:48 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/26 17:06:29 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_pars_redir_in(t_ppncmd cmd, t_pnlst token)
{
	if ((*cmd)->redirs.in_access)
		return (_err_print(_ERR_ENV_NO_FILE, token->addr_1, true, 1), _SUCCESS);
	else if (!(*cmd)->redirs.in_access && !access(token->addr_1, F_OK | R_OK))
	{
		(*cmd)->redirs.in_name = (char *)token->addr_1;
		return (_SUCCESS);
	}
	(*cmd)->redirs.in_name = (char *)token->addr_1;
	(*cmd)->redirs.in_access = true;
	(*cmd)->redirs.here_fd = 0;
	return (_SUCCESS);
}

int	_pars_redir_outt(t_ppncmd cmd, t_pnlst token, bool inside)
{
	(*cmd)->redirs.fd[1] = open(token->addr_1, _O_RWCT);
	if ((*cmd)->redirs.fd[1] < 0)
		return (_err_print(_ERR_IS_DIR, token->addr_1, true, 1));
	if (inside || (!inside && !(*cmd)->redirs.out_inside))
	{
		if (inside)
			(*cmd)->redirs.out_inside = true;
		(*cmd)->redirs.out_name = (char *)token->addr_1;
		(*cmd)->redirs.out_trunc = true;
	}
	if (close((*cmd)->redirs.fd[1]))
		return (_err_print("close", NULL, true, 1));
	return (_SUCCESS);
}

int	_pars_redir_outa(t_ppncmd cmd, t_pnlst token, bool inside)
{
	(*cmd)->redirs.fd[1] = open(token->addr_1, _O_RWCA);
	if ((*cmd)->redirs.fd[1] < 0)
		return (_err_print(_ERR_IS_DIR, token->addr_1, true, 1));
	if (inside || (!inside && !(*cmd)->redirs.out_inside))
	{
		if (inside)
			(*cmd)->redirs.out_inside = true;
		(*cmd)->redirs.out_name = (char *)token->addr_1;
		(*cmd)->redirs.out_trunc = false;
	}
	if (close((*cmd)->redirs.fd[1]))
		return (_err_print("close", NULL, true, 1));
	return (_SUCCESS);
}

int	_limit_quoted(char *str)
{
	int	i;

	if (!str)
		return (false);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
	}
	return (false);
}

int	_pars_heredoc(t_pdata data, t_ppncmd cmd, t_pnlst token, bool inside)
{
	char	*path_name;
	char	*name;
	char	*line;
	int		idx;

	if (!(*cmd)->redirs.here_name)
	{
		if (_alloc((void **)&(*cmd)->redirs.here_names, sizeof(char *) * 17)
			|| _alloc((void **)&(*cmd)->redirs.here_limit, sizeof(char *) * 17))
			return (_FAILURE);
	}
	name = _get_rname();
	path_name = ft_strjoin("/tmp/", name);
	free(name);
	(*cmd)->redirs.here_names[(*cmd)->redirs.here_idx] = path_name;
	(*cmd)->redirs.here_limit[(*cmd)->redirs.here_idx] = (char *)token->addr_1;
	{
		idx = (*cmd)->redirs.here_idx;
		(*cmd)->redirs.here_fd = open(path_name, _O_RWCA);
		while (true)
		{
			line = readline("> ");
			if (!ft_strcmp(line, (*cmd)->redirs.here_limit[idx]))
				break ;
			if (line && !_limit_quoted(token->addr_2))
				line = _xpd_str(data, line);
			if (line)
				ft_dprintf((*cmd)->redirs.here_fd, "%s\n", line);
			if (!line)
			{
				ft_dprintf(2,
					"bash: warning: here-document delimited by end-of-file (wanted `%s')\n",
					(*cmd)->redirs.here_limit[idx]);
				break ;
			}
			free(line);
			line = NULL;
		}
		free(line);
		close((*cmd)->redirs.here_fd);
	}
	(*cmd)->redirs.here_idx++;
	(*cmd)->redirs.here_fd = 1;
	if (inside || (!inside && !(*cmd)->redirs.here_inside))
	{
		if (inside)
			(*cmd)->redirs.here_inside = true;
		(*cmd)->redirs.here_name = path_name;
		(*cmd)->redirs.in_name = path_name;
	}
	return (_SUCCESS);
}

int	_pars_redirs(t_pdata data, t_ppncmd cmd, t_ppnlst token, bool inside)
{
	if (!inside && !_tok_id((*token)->x, _TYP_REDIRS)
		&& !_tok_id((*token)->prev->x, _TYP_REDIRS))
		return (_err_print(_ERR_TOKEN, (*token)->addr_1, true, 1));
	if ((*token)->x == 'H' && _pars_heredoc(data, cmd, (*token)->next, inside))
		return (_FAILURE);
	else if ((*token)->x == '<' && _pars_redir_in(cmd, (*token)->next))
		return (_FAILURE);
	else if ((*token)->x == '>' && _pars_redir_outt(cmd, (*token)->next,
			inside))
		return (_FAILURE);
	else if ((*token)->x == 'N' && _pars_redir_outa(cmd, (*token)->next,
			inside))
		return (_FAILURE);
	(*token) = (*token)->next->next;
	return (_SUCCESS);
}
