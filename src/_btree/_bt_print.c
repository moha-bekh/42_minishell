/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bt_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:28:49 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/31 11:55:29 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_node_print_tokens(t_pnlst tokens)
{
	t_pnlst	tmp;

	tmp = tokens;
	if (tmp->x == _AND || tmp->x == _OR || tmp->x == '(')
		printf("( %s )", (char *)tmp->addr_1);
	else
	{
		while (tmp && !_tok_id(tmp->x, _TYP_SEP))
		{
			printf("%s ", (char *)tmp->addr_1);
			tmp = tmp->next;
		}
	}
	printf("\n");
}

void	_bt_print(t_pbtree node, int i)
{
	int	tab;

	(void)tab;
	if (!node)
		return ;
	tab = 0;
	if (node->root)
	{
		while (tab++ < i)
			printf("\t");
		if (node->root->left == node)
			printf("left: ");
		else if (node->root->right == node)
			printf("right: ");
		// else
		// 	printf("root: ");
		_node_print_tokens(node->token);
		_cmd_print_all(node->cmd_line);
	}
	else
	{
		while (tab++ < i)
			printf("\t");
		if (node->token)
			printf("root: ( %s )\n", (char *)node->token->addr_1);
		_cmd_print_all(node->cmd_line);
	}
	if (node->left)
		_bt_print(node->left, i + 1);
	if (node->right)
		_bt_print(node->right, i + 1);
}

// void	_print_tokens(t_ptok tok)
// {
// 	t_ptok	tmp;

// 	tmp = tok;
// 	if (tmp->type == _AND || tmp->type == _OR)
// 		printf("( %s )", tmp->value);
// 	else
// 	{
// 		printf("toks: ");
// 		while (tmp && !_tok_is(_TYP_SEP, tmp->type))
// 		{
// 			printf("( %s )", tmp->value);
// 			tmp = tmp->next;
// 		}
// 	}
// 	printf("\n");
// }

// void	_bt_print(t_pbt_op tree, bool prefix, int i)
// {
// 	int	tab;

// 	tab = 0;
// 	if (!tree)
// 		return ;
// 	if (tree->root)
// 	{
// 		while (tab++ < i)
// 			printf("\t");
// 		_print_tokens(tree->token);
// 		// _cmd_print(tree->cmd);
// 	}
// 	else
// 	{
// 		while (tab++ < i)
// 			printf("\t");
// 		printf("root: ( %s )\n", tree->token->value);
// 		// _cmd_print(tree->cmd);
// 	}
// 	if (prefix)
// 	{
// 		if (tree->left)
// 			_op_bt_print(tree->left, prefix, i + 1);
// 		if (tree->right)
// 			_op_bt_print(tree->right, prefix, i + 1);
// 	}
// 	else
// 	{
// 		if (tree->right)
// 			_op_bt_print(tree->right, prefix, i + 1);
// 		if (tree->left)
// 			_op_bt_print(tree->left, prefix, i + 1);
// 	}
// 	return ;
// }
