/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _xpd_wildcards.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:38:12 by moha              #+#    #+#             */
/*   Updated: 2024/10/22 11:57:13 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_xpd_wildcards_filter(t_ppadlst list, char **patterns)
{
	t_pnlst	tmp;

	tmp = (*list)->d_top;
	while (tmp)
	{
		if (!_check_patterns(tmp, patterns))
		{
			free(tmp->addr_1);
			tmp->addr_1 = ft_strdup("");
		}
		tmp = tmp->next;
	}
	return (_SUCCESS);
}

int	_xpd_merge_string(t_ppnlst token, t_ppadlst list)
{
	char	*tmp;
	t_pnlst	node;

	node = (*list)->d_top;
	free((*token)->addr_1);
	(*token)->addr_1 = ft_strdup(" ");
	while (node)
	{
		tmp = ft_strjoin((*token)->addr_1, node->addr_1);
		if (!tmp)
			return (_FAILURE);
		free((*token)->addr_1);
		(*token)->addr_1 = tmp;
		tmp = ft_strjoin((*token)->addr_1, " ");
		if (!tmp)
			return (_FAILURE);
		free((*token)->addr_1);
		(*token)->addr_1 = tmp;
		node = node->next;
	}
	return (_SUCCESS);
}

int	_xpd_merge_list(t_ppnlst token, t_ppadlst list)
{
	t_pnlst	tmp;
	char	*str;

	free((*token)->addr_1);
	(*token)->addr_1 = NULL;
	tmp = (*list)->d_top;
	while (tmp)
	{
		if (!tmp->addr_1)
			tmp = tmp->next;
		str = ft_strdup(tmp->addr_1);
		if (!str)
			return (_FAILURE);
		_dlst_push_after(&(*token)->manager, *token, str, NULL);
		token = &(*token)->next;
		tmp = tmp->next;
	}
	_dlst_clear(list);
	return (_SUCCESS);
}

int	_xpd_wildcards_proc(t_ppnlst token, t_ppadlst list, bool to_str)
{
	char	**patterns;
	char	*str;

	if (_xpd_full_asterix((*token)->addr_1))
	{
		if (!to_str)
			return (_xpd_merge_string(token, list));
		else
			_xpd_merge_list(token, list);
		return (_dlst_clear(list), _SUCCESS);
	}
	str = (*token)->addr_1;
	if (str[0] != '*')
		_xpd_left_border(token, list);
	if (str[ft_strlen(str) - 1] != '*')
		_xpd_right_border(token, list);
	patterns = ft_split((*token)->addr_1, '*');
	if (*list)
		_xpd_wildcards_filter(list, patterns);
	ft_free_arr(patterns);
	if (!*list)
		return (_SUCCESS);
	if (!to_str)
		return (_xpd_merge_string(token, list));
	return (_xpd_merge_list(token, list));
}

int	_xpd_wildcards(t_pdata data, t_ppnlst token, bool to_str)
{
	struct dirent	*entry;
	char			*cwd_name;
	DIR				*cwd_dir;

	data->xpd = NULL;
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
		_dlst_push_back(&data->xpd, ft_strdup(entry->d_name), NULL, 0);
		if (!data->xpd->d_bot->addr_1)
			return (_FAILURE);
		entry = readdir(cwd_dir);
	}
	closedir(cwd_dir);
	if (data->xpd && _xpd_wildcards_proc(token, &data->xpd, to_str))
		return (_FAILURE);
	return (_SUCCESS);
}
