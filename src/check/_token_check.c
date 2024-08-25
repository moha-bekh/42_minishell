/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _token_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:18:25 by moha              #+#    #+#             */
/*   Updated: 2024/08/21 17:02:52 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	_tok_stx_err(char a, int n)
// {
// 	char	x;
// 	int		i;

// 	if (a == 'A')
// 		x = '&';
// 	else if (a == 'O' || a == 'P')
// 		x = '|';
// 	else
// 		x = a;
// 	i = -1;
// 	ft_putstr_fd(_STX_ERR, STDERR_FILENO);
// 	while (++i < n)
// 		ft_putchar_fd(x, STDERR_FILENO);
// 	ft_putstr_fd("'\n", STDERR_FILENO);
// 	return (_FAILURE);
// }

// int	_tok_stx_close_err(char a)
// {
// 	ft_putstr_fd(_STX_ERR_CLOSE, STDERR_FILENO);
// 	ft_putchar_fd(a, STDERR_FILENO);
// 	ft_putstr_fd("' must be closed\n", STDERR_FILENO);
// 	return (_FAILURE);
// }

// int	_token_check(t_pdata data)
// {
// 	char	top;
// 	char	bot;

// 	if (!data || !data->tokens)
// 		return (_SUCCESS);
// 	top = data->tokens->d_top->x;
// 	bot = data->tokens->d_bot->x;
// 	if (top == _AND || top == _OR)
// 		return (ft_dprintf(STDERR_FILENO, _BASH_ERR_TOKEN_2, top));
// 	else if (top == _PIPE)
// 		return (ft_dprintf(STDERR_FILENO, _BASH_ERR_TOKEN_1, top));
// 	if (bot == _AND || bot == _OR)
// 		return (ft_dprintf(STDERR_FILENO, _BASH_ERR_TOKEN_2, top));
// 	else if (bot == _PIPE)
// 		return (ft_dprintf(STDERR_FILENO, _BASH_ERR_TOKEN_1, top));
// 	if (bot == _HERE_DOC || bot == _REDIR_OUTA || bot == '>' || bot == '<')
// 		return (ft_dprintf(STDERR_FILENO, _BASH_ERR_REDIR), _FAILURE);
// 	return (_SUCCESS);
// }
