/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parsing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:43:02 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/30 11:05:32 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	_count_arg(t_ptok token)
{
	t_ptok	tmp;
	int		i;

	if (!token)
		return (_EMPTY);
	tmp = token;
	i = 0;
	while (tmp && tmp->type != _PIPE && !_tok_is(_TYPE_SEP, tmp->type))
	{
		if (_tok_is(_TYPE_REDIRS, tmp->type))
		{
			tmp = tmp->next->next;
			continue ;
		}
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	_pars_redirs(t_pcmd cmd, t_ptok token)
{
	t_ptok	tmp;

	if (!cmd || !token)
		return ;
	tmp = token;
	while (tmp && tmp->type != _PIPE && !_tok_is(_TYPE_SEP, tmp->type))
	{
		// if (tmp->type == 'H')
		// 	_pars_here_doc(cmd, token);
		// else if (tmp->type == '<')
		// 	_pars_redir_in(cmd, token);
		// else if (tmp->type == '>')
		// 	_pars_redir_outt(cmd, token);
		// else if (tmp->type == 'N')
		// 	_pars_redir_outa(cmd, token);
		tmp = tmp->next;
	}
}

int	_pars_args(t_pcmd cmd, t_ptok token)
{
	int	i;

	if (!cmd || !token)
		return (_EMPTY);
	i = _count_arg(token);
	if (!i)
		return (_SUCCESS);
	if (_alloc((void **)&cmd->cmd_a, sizeof(char *) * (i + 1)) || !cmd->cmd_a)
		return (_ALLOC);
	i = 0;
	while (token && token->type != _PIPE && !_tok_is(_TYPE_SEP, token->type))
	{
		if (_tok_is(_TYPE_REDIRS, token->type))
		{
			_pars_redirs(cmd, token);
			token = token->next->next;
			continue ;
		}
		cmd->cmd_a[i++] = ft_strdup(token->value);
		token = token->next;
	}
	cmd->cmd_a[i] = NULL;
	return (_SUCCESS);
}

int	_pars_process(t_pbt_op tree_node, t_ptok token)
{
	t_pcmd	tmp;

	if (!tree_node || !token)
		return (_EMPTY);
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
		return (_EMPTY);
	_pars_process(tree, tree->token);
	if (tree->left)
		_parsing(tree->left);
	if (tree->right)
		_parsing(tree->right);
	return (_SUCCESS);
}
