/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _wildcards.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:38:12 by moha              #+#    #+#             */
/*   Updated: 2024/08/27 17:38:20 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_expand_list_to_tokens(t_ppnlst token, t_ppadlst match_list)
{
	t_pnlst		tmp;
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

int	_expand_wildcards_all(t_ppadlst match_list)
{
	t_pnlst	tmp;
	char	*str;

	tmp = (*match_list)->d_top;
	while (tmp)
	{
		str = (char *)tmp->addr_1;
		if (str[0] == '.')
		{
			_dlst_pop_in(match_list, &tmp);
			tmp = (*match_list)->d_top;
		}
		tmp = tmp->next;
	}
	return (_SUCCESS);
}

int	_expand_wildcards_filter(t_ppnlst token, t_ppadlst match_list,
		char **patterns)
{
	t_pnlst	tmp;
	char	*str;
	int		i;

	free((*token)->addr_1);
	(*token)->addr_1 = NULL;
	i = -1;
	while (patterns[++i])
	{
		tmp = (*match_list)->d_top;
		while (tmp)
		{
			str = (char *)tmp->addr_1;
			if (str[0] == '.' || !ft_strnstr(str, patterns[i], ft_strlen(str)))
			{
				_dlst_pop_in(match_list, &tmp);
				tmp = (*match_list)->d_top;
			}
			tmp = tmp->next;
		}
	}
	ft_free_arr(patterns);
	return (_SUCCESS);
}

int	_expand_wildcards_proc(t_ppnlst token, t_ppadlst match_list)
{
	char	**patterns;

	patterns = ft_split((char *)(*token)->addr_1, '*');
	if (*patterns)
	{
		if (!patterns[1] && patterns[0][0] == '.')
			return (_SUCCESS);
		_expand_wildcards_filter(token, match_list, patterns);
	}
	else
		_expand_wildcards_all(match_list);
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
	if (_expand_wildcards_proc(token, &match_list))
		return (_FAILURE);
	return (_SUCCESS);
}
