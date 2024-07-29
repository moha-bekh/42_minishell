/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parsing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:43:02 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/29 19:44:36 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_count_arg(t_ptok token)
{
	t_ptok	tmp;
	int		i;

	tmp = token;
	i = 0;
	while (tmp && tmp->type == _LITERAL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	_pars_redir(t_pcmd cmd, t_ptok token)
{
	(void)cmd;
	printf("is redir: %c\n", token->type);
	return (EXIT_SUCCESS);
}

int	_pars_pipe(t_pcmd cmd, t_ptok token)
{
	(void)cmd;
	(void)token;
	return (EXIT_SUCCESS);
}

int	_pars_args(t_pcmd cmd, t_ptok token)
{
	int	i;

	if (!cmd || !token)
		return (EXIT_FAILURE);
	i = _count_arg(token);
	if (!i)
		return (EXIT_SUCCESS);
	if (_alloc((void **)&cmd->cmd_a, sizeof(char *) * (i + 1)) || !cmd->cmd_a)
		return (EXIT_ERROR);
	i = 0;
	while (token && token->type == _LITERAL)
	{
		cmd->cmd_a[i++] = ft_strdup(token->value);
		token = token->next;
	}
	cmd->cmd_a[i] = NULL;
	return (EXIT_SUCCESS);
}

int	_pars_process(t_pbt_op tree, t_ptok token)
{
	t_ptok	tmp;
	t_pcmd	tmp_cmd;

	if (!tree || !token)
		return (EXIT_SUCCESS);
	tree->cmd = _cmd_push_back(tree->cmd, token, NULL);
	tmp = token;
	while (tmp && !_tok_is(_TREE_SEP, tmp->type))
	{
		if (tmp->type == _PIPE)
			tree->cmd = _cmd_push_back(tree->cmd, tmp->next, NULL);
		tmp = tmp->next;
	}
	_cmd_print(tree->cmd);
	tmp_cmd = tree->cmd->c_top;
	while (tmp_cmd)
	{
		_pars_args(tmp_cmd, tmp_cmd->token);
		tmp_cmd = tmp_cmd->next;
	}
	return (EXIT_SUCCESS);
}

int	_parsing(t_pbt_op tree)
{
	if (!tree)
		return (EXIT_SUCCESS);
	_pars_process(tree, tree->token);
	if (tree->left)
		_parsing(tree->left);
	if (tree->right)
		_parsing(tree->right);
	return (EXIT_SUCCESS);
}
