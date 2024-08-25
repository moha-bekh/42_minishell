/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parsing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:43:02 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/16 07:53:01 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_pars_args(t_pcmd cmd, t_ptok token)
{
	int	i;

	if (!cmd || !token)
		return (_FAILURE);
	i = _count_arg(token);
	if (i && _alloc((void **)&cmd->cmd_arg, sizeof(char *) * (i + 1)))
		return (_ALLOC);
	i = 0;
	while (token && token->type != _PIPE && !_tok_is(_TYP_SEP, token->type))
	{
		if (_tok_is(_TYP_REDIRS, token->type))
		{
			if (_pars_redirs(cmd, token))
				return (_FAILURE);
			token = token->next->next;
			continue ;
		}
		cmd->cmd_arg[i++] = ft_strdup(token->value);
		token = token->next;
	}
	if (cmd->cmd_arg)
		cmd->cmd_arg[i] = NULL;
	return (_SUCCESS);
}

void	_pars_pipe(t_pbt_op node, t_ptok token)
{
	t_ptok	tmp;

	if (!node || !token)
		return ;
	tmp = token;
	while (tmp && !_tok_is(_TYP_SEP, tmp->type))
	{
		if (tmp->type == _PIPE)
			node->cmd = _cmd_push_back(node->cmd, tmp->next, NULL);
		tmp = tmp->next;
	}
	return ;
}

int	_pars_process(t_pbt_op tree_node, t_ptok token)
{
	t_pcmd	tmp;

	if (!tree_node || !token)
		return (_FAILURE);
	tree_node->cmd = _cmd_push_back(tree_node->cmd, token, NULL);
	_pars_pipe(tree_node, token);
	tmp = tree_node->cmd->c_top;
	while (tmp)
	{
		if (_pars_args(tmp, tmp->token))
			return (_FAILURE);
		tmp = tmp->next;
	}
	return (_SUCCESS);
}

int	_parsing(t_pdata data, t_pbt_op tree)
{
	if (!tree)
		return (_FAILURE);
	if (_pars_process(tree, tree->token))
	{
		data->_errno = 1;
		return (_FAILURE);
	}
	if (tree->left)
		_parsing(data, tree->left);
	if (tree->right)
		_parsing(data, tree->right);
	return (_SUCCESS);
}
