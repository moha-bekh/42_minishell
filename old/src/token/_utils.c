/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:18:25 by moha              #+#    #+#             */
/*   Updated: 2024/08/07 15:35:06 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_tok_is(char *str, char a)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == a)
			return (_IS);
	return (_NOT);
}

int	_tok_stx_err(char a, int n)
{
	char	x;
	int		i;

	if (a == 'A')
		x = '&';
	else if (a == 'O' || a == 'P')
		x = '|';
	else
		x = a;
	i = -1;
	ft_putstr_fd(_STX_ERR, STDERR_FILENO);
	while (++i < n)
		ft_putchar_fd(x, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (_SYNTAX_ERR);
}

int	_tok_stx_close_err(char a)
{
	ft_putstr_fd(_STX_ERR_CLOSE, STDERR_FILENO);
	ft_putchar_fd(a, STDERR_FILENO);
	ft_putstr_fd("' must be closed\n", STDERR_FILENO);
	return (_SYNTAX_ERR);
}

int	_tok_check(t_pdata data)
{
	char	top;
	char	bot;

	if (!data || !data->tok)
		return (_SUCCESS);
	top = data->tok->t_top->type;
	bot = data->tok->t_bot->type;
	if (top == _AND || top == _OR)
		return (_tok_stx_err(top, 2));
	else if (top == _PIPE)
		return (_tok_stx_err(top, 1));
	if (bot == _AND || bot == _OR)
		return (_tok_stx_err(bot, 2));
	else if (bot == _PIPE)
		return (_tok_stx_err(top, 1));
	if (bot == _HERE_DOC || bot == _REDIR_OUTA || bot == '>' || bot == '<')
		return (ft_putstr_fd(_STX_ERR_REDIR, STDERR_FILENO), _FAILURE);
	return (_SUCCESS);
}
