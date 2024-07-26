/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parsing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:43:02 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/26 18:43:22 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_count_arg(t_ptok token)
{
	t_ptok	tmp;
	int		i;

	tmp = token;
	i = 0;
	while (tmp && tmp->type == _LITERAL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	_pars_process(t_pbt_op node)
{
	t_ptok	tmp_tok;
	char	**cmd_a;
	int		i;

	cmd_a = NULL;
	i = _count_arg(node->token);
	if (!i)
		return (EXIT_SUCCESS);
	if (_alloc((void **)&cmd_a, sizeof(char *) * (i + 1)) || !cmd_a)
		return (EXIT_ERROR);
	tmp_tok = node->token;
	i = -1;
	while (tmp_tok && tmp_tok->type == _LITERAL)
	{
		cmd_a[++i] = ft_strdup(tmp_tok->value);
		tmp_tok = tmp_tok->next;
	}
	cmd_a[++i] = NULL;
	node->cmd_a = cmd_a;
	return (EXIT_SUCCESS);
}

int	_parsing(t_pbt_op tree)
{
	if (!tree)
		return (EXIT_SUCCESS);
	_pars_process(tree);
	if (tree->left)
		_parsing(tree->left);
	if (tree->right)
		_parsing(tree->right);
	return (EXIT_SUCCESS);
}
