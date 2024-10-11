/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bt_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:28:49 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/26 02:42:50 by oek              ###   ########.fr       */
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
