/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _op_bt_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:28:49 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/07 15:42:37 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void _print_tokens(t_ptok tok)
{
	t_ptok	tmp;

	tmp = tok;
	if (tmp->type == _AND || tmp->type == _OR)
		printf("( %s )", tmp->value);
	else
	{
		printf("toks: ");
		while (tmp && !_tok_is(_TYP_SEP, tmp->type))
		{
			printf("( %s )", tmp->value);
			tmp = tmp->next;
		}
	}
	printf("\n");
}

void	_op_bt_print(t_pbt_op tree, bool prefix, int i)
{
	int		tab;

	tab = 0;
	if (!tree)
		return ;
	if (tree->root)
	{
		while (tab++ < i)
			printf("\t");
		// _print_tokens(tree->token);
		_cmd_print(tree->cmd);
	}
	else
	{
		while (tab++ < i)
			printf("\t");
		printf("root: ( %s )\n", tree->token->value);
		_cmd_print(tree->cmd);
	}
	if (prefix)
	{
		if (tree->left)
			_op_bt_print(tree->left, prefix, i + 1);
		if (tree->right)
			_op_bt_print(tree->right, prefix, i + 1);
	}
	else
	{
		if (tree->right)
			_op_bt_print(tree->right, prefix, i + 1);
		if (tree->left)
			_op_bt_print(tree->left, prefix, i + 1);
	}
	return ;
}
