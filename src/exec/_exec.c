/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:53:33 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/30 18:50:22 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_is_builtin(t_pdata data, char *str)
{
	int	i;

	if (!data || !str)
		return (_ERROR);
	i = 0;
	while (data->built_in[i])
	{
		if (!ft_strcmp(data->built_in[i], str))
			return (_IS);
		i++;
	}
	return (_NOT);
}

int	_resolve_path(t_pdata data, t_pbt_op node)
{
	t_pcmd	tmp;

	tmp = node->cmd->c_top;
	while (tmp)
	{
		if (tmp->cmd_a && !_is_builtin(data, tmp->cmd_a[0]))
			_acces_path(data, tmp->cmd_a[0]);
		tmp = tmp->next;
	}
	return (_SUCCESS);
}

int	_path_resolver(t_pdata data)
{
	if (!data || !data->tree)
		return (_ERROR);
	_resolve_path(data, data->tree);
	if (data->tree->left)
		_path_resolver(data->tree->left);
	if (data->tree->right)
		_path_resolver(data->tree->right);
	return (_SUCCESS);
}

int	_exec_process(t_pdata data)
{
	// _infile_process(data, node);
	// _loop_process(data, node);
	// _outfile_process(data, node);
	return (_SUCCESS);
}

int	_execution(t_pdata data)
{
	if (!data || !data->tree)
		return (_ERROR);
	_path_resolver(data);
	_exec_process(data);
	if (data->tree->left)
		_exec(data);
	if (data->tree->right)
		_exec(data);
	return (_SUCCESS);
}
