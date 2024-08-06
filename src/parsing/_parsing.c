/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parsing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:43:02 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/06 08:05:29 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_pars_redirs(t_pcmd cmd, t_ptok token)
{
	t_ptok	tmp;

	if (!cmd || !token)
		return ;
	tmp = token;
	while (tmp && tmp->type != _PIPE && !_tok_is(_TYP_SEP, tmp->type))
	{
		if (tmp->type == 'H')
			cmd->redir.here_name = get_random_name();
		if (tmp->type == '<')
			cmd->redir.in_name = tmp->next->value;
		else if (tmp->type == '>')
		{
			cmd->redir.out_name = tmp->next->value;
			cmd->redir.trunc = true;
		}
		else if (tmp->type == 'N')
		{
			cmd->redir.out_name = tmp->next->value;
			cmd->redir.trunc = false;
		}
		tmp = tmp->next;
	}
}

void	_pars_pipe(t_pbt_op node, t_ptok token)
{
	t_ptok	tmp;

	if (!node || !token)
		return ;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == _PIPE)
			node->cmd = _cmd_push_back(node->cmd, tmp->next, NULL);
		tmp = tmp->next;
	}
	return ;
}

int	_pars_args(t_pcmd cmd, t_ptok token)
{
	int	i;

	if (!cmd || !token)
		return (_FAILURE);
	i = _count_arg(token);
	if (!i)
		return (_SUCCESS);
	if (_alloc((void **)&cmd->cmd_arg, sizeof(char *) * (i + 1)) || !cmd->cmd_arg)
		return (_ALLOC);
	i = 0;
	while (token && token->type != _PIPE && !_tok_is(_TYP_SEP, token->type))
	{
		if (_tok_is(_TYP_REDIRS, token->type))
		{
			_pars_redirs(cmd, token);
			token = token->next->next;
			continue ;
		}
		cmd->cmd_arg[i++] = ft_strdup(token->value);
		token = token->next;
	}
	cmd->cmd_arg[i] = NULL;
	return (_SUCCESS);
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
		_pars_args(tmp, tmp->token);
		tmp = tmp->next;
	}
	return (_SUCCESS);
}

int	_parsing(t_pbt_op tree)
{
	if (!tree)
		return (_FAILURE);
	_pars_process(tree, tree->token);
	if (tree->left)
		_parsing(tree->left);
	if (tree->right)
		_parsing(tree->right);
	return (_SUCCESS);
}
