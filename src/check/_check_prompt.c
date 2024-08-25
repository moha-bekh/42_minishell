/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _check_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:03:59 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/24 03:03:34 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	_check_start_n_end(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (!str[i])
// 		return (0);
// 	while (ft_isspace(str[i]))
// 		i++;
// 	if (str[i] && _token_id(str[i], _STX_ERR_START))
// 	{
// 		if (str[i + 1] && str[i] == str[i + 1])
// 			return (ft_dprintf(2, _BASH_ERR_TOKEN_2, str[i], str[i]), 1);
// 		else
// 			return (ft_dprintf(2, _BASH_ERR_TOKEN_1, str[i]), 1);
// 	}
// 	i = ft_strlen(str) - 1;
// 	while (ft_isspace(str[i]))
// 		i--;
// 	if (str[i] && _token_id(str[i], _STX_ERR_END))
// 	{
// 		if ((str[i - 1] != '|') || (str[i - 1] == '|' && str[i - 2] != '|'))
// 			return (ft_dprintf(2, _BASH_ERR_NEWLINE, str[i]), 1);
// 	}
// 	return (0);
// }

// int	_check_parentheses(char *str)
// {
// 	int	i;
// 	int	x;
// 	int	y;

// 	x = 0;
// 	y = 0;
// 	i = -1;
// 	while (str[++i] && str[i] != '\n')
// 	{
// 		if (str[i] == '(')
// 			x++;
// 		if (str[i] == ')')
// 			y++;
// 	}
// 	if (x > y)
// 		return (ft_dprintf(STDERR_FILENO, _BASH_ERR_CLOSE, '('), _FAILURE);
// 	if (x < y)
// 		return (ft_dprintf(STDERR_FILENO, _BASH_ERR_CLOSE, ')'), _FAILURE);
// 	return (_SUCCESS);
// }

// int	_check_quotes(char *str)
// {
// 	int		i;
// 	char	x;

// 	i = -1;
// 	while (str[++i] && str[i] != '\n')
// 	{
// 		if (str[i] == '\'' || str[i] == '"')
// 		{
// 			x = str[i++];
// 			while (str[i] && str[i] != x && str[i] != '\n')
// 				i++;
// 			if (str[i] != x)
// 				return (ft_dprintf(2, _BASH_ERR_CLOSE, x), _FAILURE);
// 		}
// 	}
// 	return (_SUCCESS);
// }

// int	_check_and(t_pdata data, int *i)
// {
// 	char	*str;
// 	int		x;

// 	str = data->prompt;
// 	if (!str[*i + 1] || str[*i + 1] != '&')
// 		return (ft_dprintf(2, _BASH_ERR_TOKEN_1, '&'), 1);
// 	if (!str[*i - 1])
// 		return (ft_dprintf(2, _BASH_ERR_TOKEN_2, '&', '&'), 1);
// 	x = 1;
// 	while (str[++*i] == '&')
// 		x++;
// 	if (x == 3)
// 		return (ft_dprintf(2, _BASH_ERR_TOKEN_1, '&'), 1);
// 	if (x > 3)
// 		return (ft_dprintf(2, _BASH_ERR_TOKEN_2, '&', '&'), 1);
// 	if (x == 2 && _token_id(str[*i], _STX_ERR_OP))
// 		return (ft_dprintf(2, _BASH_ERR_TOKEN_1, str[*i]), 1);
// 	return (_SUCCESS);
// }

// int	_check_or_n_pipe(t_pdata data, int *i)
// {
// 	char	*str;
// 	int		x;

// 	str = data->prompt;
// 	if (!str[*i - 1] && (!str[*i + 1] || str[*i + 1] != '|'))
// 		return (ft_dprintf(2, _BASH_ERR_TOKEN_1, '|'), 1);
// 	if (!str[*i - 1])
// 		return (ft_dprintf(2, _BASH_ERR_TOKEN_2, '|', '|'), 1);
// 	x = 1;
// 	while (str[++*i] == '|')
// 		x++;
// 	if (x == 3)
// 		return (ft_dprintf(2, _BASH_ERR_TOKEN_1, '|'), 1);
// 	if (x > 3)
// 		return (ft_dprintf(2, _BASH_ERR_TOKEN_2, '|', '|'), 1);
// 	if (x == 2 && _token_id(str[*i], _STX_ERR_OP))
// 		return (ft_dprintf(2, _BASH_ERR_TOKEN_1, str[*i]), 1);
// 	return (_SUCCESS);
// }

// int _check_redir_out(t_pdata data, int *i)
// {
// 	char *str;
// 	int x;

// 	str = data->prompt;
// 	x = 1;
// 	while (str[++*i] == '>')
// 		x++;
// 	if (x == 1 && _token_id(str[*i], _STX_ERR_REDIR_OUTT))
// 		return (ft_dprintf(2, _BASH_ERR_TOKEN_1, str[*i]), 1);
// 	if (x == 2 && _token_id(str[*i], _STX_ERR_REDIR_OUTA))
// 		return (ft_dprintf(2, _BASH_ERR_TOKEN_1, str[*i]), 1);
// 	if (x == 3)
// 		return (ft_dprintf(2, _BASH_ERR_TOKEN_1, '>'), 1);
// 	if (x > 3)
// 		return (ft_dprintf(2, _BASH_ERR_TOKEN_2, '>', '>'), 1);
// 	return (_SUCCESS);
// }

// int _check_redir_in(t_pdata data, int *i)
// {
// 	char *str;
// 	int x;

// 	str = data->prompt;
// 	x = 1;
// 	while (str[++*i] == '<')
// 		x++;
// 	if (x == 1 && _token_id(str[*i], _STX_ERR_REDIR_IN))
// 		return (ft_dprintf(2, _BASH_ERR_TOKEN_1, str[*i]), 1);
// 	if (x == 2 && _token_id(str[*i], _STX_ERR_HERE_DOC))
// 		return (ft_dprintf(2, _BASH_ERR_TOKEN_1, str[*i]), 1);
// 	if (x == 3 || x == 4)
// 		return (ft_dprintf(2, _BASH_ERR_TOKEN_1, '<'), 1);
// 	if (x == 5)
// 		return (ft_dprintf(2, _BASH_ERR_TOKEN_2, '<', '<'), 1);
// 	if (x > 5)
// 		return (ft_dprintf(2, _BASH_ERR_TOKEN_3, '<', '<', '<'), 1);
// 	return (_SUCCESS);
// }

int	_scope_check(t_pdata data, int *i)
{
	char	open;
	char	close;

	open = data->prompt[*i];
	if (open == '(')
		close = ')';
	else
		close = open;
	while (data->prompt[++*i] && data->prompt[*i] != '\n')
	{
		if (data->prompt[*i] == close)
			return (_SUCCESS);
	}
	return (ft_dprintf(STDERR_FILENO, _BASH_ERR_CLOSE, open), _FAILURE);
}

// int	_check_prompt(t_pdata data)
// {
// 	char	*str;
// 	int		i;

// 	str = data->prompt;
// 	i = 0;
// 	while (str[i] && str[i] != '\n')
// 	{
// 		if (str[i] == '\'' || str[i] == '"')
// 			if (_check_quotes(str))
// 				return (_FAILURE);
// 		if (str[i] == '&' && _check_and(data, &i))
// 			return (_FAILURE);
// 		else if (str[i] == '|' && _check_or_n_pipe(data, &i))
// 			return (_FAILURE);
// 		else if (_token_id(str[i], _SCOPES) && _scope_check(data, &i))
// 			return (_FAILURE);
// 		else if (str[i] == '<' && _check_redir_in(data, &i))
// 			return (_FAILURE);
// 		else if (str[i] == '>' && _check_redir_out(data, &i))
// 			return (_FAILURE);
// 		else if (str[i])
// 			i++;
// 	}
// 	if (_check_start_n_end(str) || _check_parentheses(str))
// 		return (_FAILURE);
// 	return (_SUCCESS);
// }
