/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:11:53 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/30 22:54:34 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_some_utils(t_pdata data, char *input)
{
	if (!*input)
		return (_IS);
	if (!ft_strncmp(input, "\n", 1))
		return (_IS);
	if (!ft_strncmp(input, "clear", 5))
	{
		system("clear");
		return (_IS);
	}
	if (!ft_strncmp(input, "env ", 4))
	{
		_env(data);
		return (_IS);
	}
	return (_NOT);
}

int	main(int ac, char **av, char **ev)
{
	t_data	data;
	int		i;

	i = 0;
	if (_data_init(&data, ac, av, ev))
		return (_FAILURE);
	while (1)
	{
		printf(CYAN "-------------------------------------- PROMPT --------------------------------------" RESET "\n");
		data.input = readline(">$ ");
		if (!data.input || !ft_strncmp(data.input, "exit", 4))
			return (_data_cleaner(&data), _FAILURE);
		add_history(data.input);
		if (_some_utils(&data, data.input))
			continue ;
		if (_tok_process(data.input, &data.tok))
			continue ;
		_expand_tokens(&data);
		data.tree = _tree_process(&data);
		_parsing(data.tree);
		_execution(&data, data.tree);
		_op_bt_print(data.tree, true, i);
		data.tree = _op_bt_clear(data.tree);
		data.tok = _tok_clear(data.tok);
	}
	return (_data_cleaner(&data), _SUCCESS);
}

// int	main(void)
// {
// 	t_pbt_op	tree_1;
// 	t_pbt_op	tree_2;
// 	u_padll		scop;

// 	tree_1 = NULL;
// 	tree_2 = NULL;
// 	scop = NULL;

// 	tree_1 = _op_bt_push_right(tree_1, _op_bt_create('1', NULL));
// 	tree_2 = _op_bt_push_root(tree_2, _op_bt_create('2', NULL));
// 	scop = _scp_push_back(scop, tree_1);
// 	scop = _scp_push_back(scop, tree_2);
// 	printf("scp top value = %c\n", scop->s_top->ptr_op->type);
// 	printf("scp bot value = %c\n", scop->s_bot->ptr_op->type);

// 	scop = _scp_pop_back(scop);
// 	printf("scp top value = %c\n", scop->s_bot->ptr_op->type);

// 	(void)tree_1;
// 	(void)tree_2;
// 	return (0);
// }

// int main(void)
// {
// 	t_pbt_op tree;
// 	t_pbt_op scop_1;
// 	t_pbt_op scop_2;
// 	t_pbt_op scop_3;

// 	scop_1 = NULL;
// 	scop_2 = NULL;
// 	scop_3 = NULL;
// 	tree = NULL;

// 	tree = _op_bt_push_right(tree, _op_bt_create('X', NULL));
// 	tree = _op_bt_push_root(tree, _op_bt_create('&', NULL));
// 	tree = _op_bt_push_right(tree, _op_bt_create('Y', NULL));
// 	tree = _op_bt_push_root(tree, _op_bt_create('|', NULL));

// 	scop_1 = tree;
// 	tree = NULL;
// 	tree = _op_bt_push_right(tree, _op_bt_create('Z', NULL));
// 	tree = _op_bt_push_root(tree, _op_bt_create('&', NULL));
// 	tree = _op_bt_push_right(tree, _op_bt_create('A', NULL));
// 	tree = _op_bt_push_root(tree, _op_bt_create('&', NULL));

// 	scop_2 = tree;
// 	tree = NULL;

// 	tree = _op_bt_push_right(tree, _op_bt_create('M', NULL));
// 	tree = _op_bt_push_root(tree, _op_bt_create('|', NULL));
// 	tree = _op_bt_push_right(tree, _op_bt_create('N', NULL));

// 	scop_2->right = tree;
// 	tree->root = scop_2;
// 	tree = scop_2;

// 	tree = _op_bt_push_root(tree, _op_bt_create('|', NULL));
// 	tree = _op_bt_push_right(tree, _op_bt_create('O', NULL));

// 	scop_1->right = tree;
// 	tree->root = scop_1;
// 	tree = scop_1;

// 	tree = _op_bt_push_root(tree, _op_bt_create('|', NULL));
// 	tree = _op_bt_push_right(tree, _op_bt_create('B', NULL));

// 	_op_bt_print(tree, true);

// 	_op_bt_clear(tree);
// 	(void)scop_1;
// 	(void)scop_2;
// 	(void)scop_3;
// 	return (_SUCCESS);
// }

// {
//// DATA INIT TEST
// 	printf("data->ac = %d\n", data.ac);
// 	while (data.av[++i])
// 		printf("data->av[%d] = %s\n", i, data.av[i]);
// 	i = -1;
// 	while (data.env.ev[++i])
// 		printf("data->env.ev[%d] = %s\n", i, data.env.ev[i]);
// }