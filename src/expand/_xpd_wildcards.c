/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _xpd_wildcards.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:38:12 by moha              #+#    #+#             */
/*   Updated: 2024/08/31 12:47:02 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_check_patterns(t_pnlst token, char **patt)
{
	char	*tmp;
	int		i;

	tmp = token->addr_1;
	i = 0;
	while (patt[i])
	{
		tmp = ft_strnstr(tmp, patt[i], ft_strlen(tmp));
		if (!tmp)
			return (false);
		i++;
	}
	return (true);
}

int	_xpd_wildcards_filter(t_ppadlst match_list, char **patterns)
{
	t_pnlst	tmp;

	tmp = (*match_list)->d_top;
	while (tmp)
	{
		if (!_check_patterns(tmp, patterns))
		{
			tmp->flag = true;
			_dlst_pop_in(match_list, &tmp);
			if (*match_list)
				tmp = (*match_list)->d_top;
			continue ;
		}
		tmp = tmp->next;
	}
	ft_free_arr(patterns);
	return (_SUCCESS);
}

int	_xpd_merge_list(t_ppnlst token, t_ppadlst match_list)
{
	t_pnlst		tmp;
	t_ppnlst	to_remove;

	to_remove = token;
	tmp = (*match_list)->d_top;
	while (tmp)
	{
		_dlst_push_in(&(*token)->manager, *token, ft_strdup(tmp->addr_1), NULL);
		token = &(*token)->next;
		tmp = tmp->next;
	}
	_dlst_pop_in(&(*token)->manager, to_remove);
	_dlst_clear(match_list);
	return (_SUCCESS);
}
int	_xpd_wildcards_proc(t_ppnlst token, t_ppadlst match_list)
{
	char	**patterns;

	patterns = ft_split((*token)->addr_1, '*');
	if (!patterns)
		return (_xpd_merge_list(token, match_list));
	_xpd_wildcards_filter(match_list, patterns);
	if (!match_list)
		return (_SUCCESS);
	if (_xpd_merge_list(token, match_list))
		return (_FAILURE);
	return (_SUCCESS);
}

int	_xpd_wildcards(t_ppnlst token)
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
		if (entry->d_name[0] == '.')
		{
			entry = readdir(cwd_dir);
			continue ;
		}
		_dlst_push_back(&match_list, ft_strdup(entry->d_name), NULL, 0);
		entry = readdir(cwd_dir);
	}
	closedir(cwd_dir);
	if (_xpd_wildcards_proc(token, &match_list))
		return (_FAILURE);
	return (_SUCCESS);
}
