/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 06:00:00 by moha              #+#    #+#             */
/*   Updated: 2024/08/27 16:48:03 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int main(void)
// {

// 	t_padlst dll = NULL;

// 	_dlst_push_back(&dll, ft_strdup("1"), NULL, 0);
// 	_dlst_push_back(&dll, ft_strdup("2"), NULL, 0);
// 	_dlst_push_back(&dll, ft_strdup("3"), NULL, 0);

// 	_dlst_push_in(&dll, dll->d_bot, ft_strdup("0"), NULL);

// 	_dlst_print_builtins(dll);

// 	_dlst_clear(&dll);
// 	return (0);
// }

int	_expand_list_to_tokens(t_ppnlst token, t_ppadlst match_list)
{
	t_pnlst	tmp;
	t_ppnlst	to_remove;

	to_remove = token;
	tmp = (*match_list)->d_top;
	while (tmp)
	{
		_dlst_push_in(&(*token)->manager, *token,
			ft_strdup((char *)tmp->addr_1), NULL);
		token = &(*token)->next;
		tmp = tmp->next;
	}
	_dlst_pop_in(&(*token)->manager, to_remove);
	_dlst_clear(match_list);
	return (_SUCCESS);
}

int	_expand_wildcards_filter(t_ppnlst token, t_ppadlst match_list)
{
	char	**patterns;
	t_pnlst	tmp;
	int		i;

	patterns = ft_split((char *)(*token)->addr_1, '*');
	printf("ptr patterns 0: %p\n", patterns[0]);
	printf("ptr patterns 1: %p\n", patterns[1]);
	free((*token)->addr_1);
	(*token)->addr_1 = NULL;
	i = -1;
	while (patterns[++i])
	{
		tmp = (*match_list)->d_top;
		while (tmp)
		{
			if (!ft_strnstr((char *)tmp->addr_1, patterns[i],
					ft_strlen((char *)tmp->addr_1)))
			{
				_dlst_pop_in(match_list, &tmp);
				tmp = (*match_list)->d_top;
			}
			tmp = tmp->next;
		}
	}
	ft_free_arr(patterns);
	if (_expand_list_to_tokens(token, match_list))
		return (_FAILURE);
	return (_SUCCESS);
}

int	_expand_wildcards(t_ppnlst token)
{
	t_padlst		match_list;
	struct dirent	*entry;
	char			*cwd_name;
	DIR				*cwd_dir;

	match_list = NULL;
	cwd_name = getcwd(NULL, 0);
	cwd_dir = opendir(cwd_name);
	free(cwd_name);
	entry = readdir(cwd_dir);
	while (entry)
	{
		_dlst_push_back(&match_list, ft_strdup(entry->d_name), NULL, 0);
		entry = readdir(cwd_dir);
	}
	closedir(cwd_dir);
	if (_expand_wildcards_filter(token, &match_list))
		return (_FAILURE);
	return (_SUCCESS);
}

int	_expand_line(t_ppnlst tokens)
{
	t_pnlst	tmp;

	tmp = *tokens;
	while (tmp && tmp->x != _PIPE && !_token_id(tmp->x, _TYP_SEP))
	{
		if (tmp->x == '*' && _expand_wildcards(&tmp))
			return (_FAILURE);
		tmp = tmp->next;
	}
	return (_SUCCESS);
}

int	main(int ac, char **av, char **ev)
{
	static t_data	data;

	if (_data_init(&data, ac, av, ev) || _set_signals(&data))
		return (_data_clear(&data), _FAILURE);
	while (1)
	{
		data.prompt = readline(">$ ");
		if ((!data.prompt || !data.prompt[0]) && !_data_structs_clear(&data))
			continue ;
		add_history(data.prompt);
		if (_token_list(&data) && !_data_structs_clear(&data))
			continue ;
		_dlst_print_tokens(data.tokens);
		// _tree_builder(&data.tree, data.tokens->d_top);
		// if (_exec(&data, &data.tree) && !_data_structs_clear(&data))
		// 	continue ;
		// _dlst_print_tokens(data.tokens);
		// _bt_print(data.tree, 0);
		_data_structs_clear(&data);
	}
	return (_data_clear(&data), _SUCCESS);
}
