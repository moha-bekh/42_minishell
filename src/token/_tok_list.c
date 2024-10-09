/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tok_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:24:25 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/09 17:24:16 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_quote_proc(t_pdata data, int *i)
{
	char	*str;
	char	*tmp;
	char	type_quote;
	int		j;

	type_quote = data->prompt[*i];
	j = *i;
	*i += 1;
	while (data->prompt[*i] && data->prompt[*i] != type_quote)
		*i += 1;
	(void)tmp;
	if (!data->prompt[*i])
		return (_err_print(_ERR_CLOSE, &type_quote, false, 2));
	if (data->tokens && data->tokens->d_bot->flag && data->tokens->d_bot->prev  && data->tokens->d_bot->prev->x == 'H')
	{
		str = ft_substr(data->prompt, j + 1, (*i - j - 1));
		tmp = ft_strjoin(data->tokens->d_bot->addr_1, str);
		free(str);
		free(data->tokens->d_bot->addr_1);
		data->tokens->d_bot->addr_1 = tmp;
		data->tokens->d_bot->x = type_quote;
	}
	else
	{
		str = ft_substr(data->prompt, j + 1, (*i - j - 1));
		if (!str)
			return (_FAILURE);
		_dlst_push_back(&data->tokens, str, NULL, type_quote);
	}
	*i += 1;
	if (data->prompt[*i] && !ft_isspace(data->prompt[*i]))
		data->tokens->d_bot->flag = true;
	else
		data->tokens->d_bot->flag = false;
	return (_SUCCESS);
}

int	_tok_word(t_pdata data, int *i)
{
	char	*str;
	char	*tmp;
	int		j;

	j = *i;
	while (data->prompt[*i] && !ft_isspace(data->prompt[*i])
		&& !_tok_id(data->prompt[*i], _TOKENS))
		*i += 1;
	if (data->tokens && data->tokens->d_bot->flag && data->tokens->d_bot->prev && data->tokens->d_bot->prev->x == 'H')
	{
		str = ft_substr(data->prompt, j, (*i - j));
		tmp = ft_strjoin(data->tokens->d_bot->addr_1, str);
		free(str);
		free(data->tokens->d_bot->addr_1);
		data->tokens->d_bot->addr_1 = tmp;
	}
	else
	{
		str = ft_substr(data->prompt, j, (*i - j));
		if (!str)
			return (_FAILURE);
		_dlst_push_back(&data->tokens, str, NULL, _WORD);
		if (!data->tokens->d_bot->addr_1)
			return (_FAILURE);
	}
	if (data->prompt[*i] && !ft_isspace(data->prompt[*i])
		&& _tok_id(data->prompt[*i], _JOINERS))
		data->tokens->d_bot->flag = true;
	else
		data->tokens->d_bot->flag = false;
	return (_SUCCESS);
}

int	_first_tok(t_pdata data, int *i)
{
	_dlst_push_back(&data->tokens, NULL, NULL, _WORD);
	if (data->prompt[*i] && _tok_id(data->prompt[*i], _TOKENS))
	{
		if (_tok_proc(data, i))
			return (_FAILURE);
	}
	else if (data->prompt[*i] && !ft_isspace(data->prompt[*i]))
	{
		if (_tok_word(data, i))
			return (_FAILURE);
	}
	else if (data->prompt[*i])
		*i += 1;
	if (_check_top(data))
		return (_FAILURE);
	return (_SUCCESS);
}

void	_hndl_hd_sigint(int sig)
{
	t_pdata	data;

	(void)sig;
	data = _get_data();
	*g_ptr_errno = 130;
	write(STDOUT_FILENO, "\n", 1);
	_data_clear(data);
}

int	_hd_fill(t_pdata data, t_pnlst token)
{
	int		fd;
	char	*line;
	pid_t	pid;

	line = NULL;
	pid = fork();
	if (pid == 0)
	{
		data->shell.s_sigint.sa_handler = _hndl_hd_sigint;
		sigaction(SIGINT, &data->shell.s_sigint, NULL);

		fd = open(token->addr_1, O_RDWR | O_CREAT | O_APPEND, 0644);
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
		free(line);
		close(fd);
		if (data->_errno == 130)
		{
			_data_clear(data);
			exit(130);
		}
		_data_clear(data);
		exit(0);
	}
	else
	{
		token = token->next;
		data->shell.s_sigint.sa_handler = SIG_IGN;
		sigaction(SIGINT, &data->shell.s_sigint, NULL);
		waitpid(pid, &data->_errno, 0);
		if (WIFEXITED(data->_errno))
			data->_errno = WEXITSTATUS(data->_errno);
		else if (WIFSIGNALED(data->_errno))
			data->_errno = WTERMSIG(data->_errno) + 128;
		data->shell.s_sigint.sa_handler = _hndl_sigint;
		sigaction(SIGINT, &data->shell.s_sigint, NULL);
		if (data->_errno == 130)
			return (_FAILURE);
	}
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

int	_tok_list(t_pdata data)
{
	int	i;

	i = 0;
	if (!data->prompt)
		return (_FAILURE);
	if (_first_tok(data, &i))
		return (_FAILURE);
	while (data->prompt[i] && data->prompt[i] != '\n')
	{
		if (data->prompt[i] && _tok_id(data->prompt[i], _TOKENS))
		{
			if (_tok_proc(data, &i))
				return (_FAILURE);
		}
		else if (data->prompt[i] && !ft_isspace(data->prompt[i]))
		{
			if (_tok_word(data, &i))
				return (_FAILURE);
		}
		else if (data->prompt[i])
			i++;
	}
	if (_check_bot(data))
		return (_FAILURE);
	if (_here_doc_filler(data))
		return (_FAILURE);
	return (_SUCCESS);
}
