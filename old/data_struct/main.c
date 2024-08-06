/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:08:25 by moha              #+#    #+#             */
/*   Updated: 2024/07/18 23:19:02 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

int	main(void)
{
	t_pbt_tok	tree;

	// tree = _tok_bt_join(_tok_bt_create(NULL, '6'), _tok_bt_create(NULL, '2'),
			// _tok_bt_create(NULL, '4'));
	// tree->left = _tok_bt_join(tree->left, _tok_bt_create(NULL, '8'),
			// _tok_bt_create(NULL, '3'));
	// tree->right = _tok_bt_join(tree->right, _tok_bt_create(NULL, '5'),
			// _tok_bt_create(NULL, '7'));
	tree = _tok_bt_push(NULL, _tok_bt_create(NULL, '6'), true);
	tree = _tok_bt_push(tree, _tok_bt_create(NULL, '2'), true);
	tree = _tok_bt_push(tree, _tok_bt_create(NULL, '4'), false);
	tree = _tok_bt_push(tree, _tok_bt_create(NULL, '8'), true);
	printf("====================================\n");
	_tok_bt_print(tree, true);
	printf("====================================\n");
	_tok_bt_clear(tree);
	return (0);
}
