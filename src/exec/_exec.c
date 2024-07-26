/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:53:33 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/26 19:20:23 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int _exec_process(t_pdata data, t_pbt_op node)
{
	// _infile_process(data, node);

	// _loop_process(data, node);

	// _outfile_process(data, node);
}

int _exec(t_pdata data, t_pbt_op tree)
{
	if (!tree)
		return (EXIT_SUCCESS);
	_path_resolver(data, tree);
	_exec_process(data, tree);
	if (tree->left)
		_exec(data, tree->left);
	if (tree->right)
		_exec(data, tree->right);
	return (EXIT_SUCCESS);
}
