/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _xpd_wildcards.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:38:12 by moha              #+#    #+#             */
/*   Updated: 2024/09/01 02:16:16 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_check_patterns(t_pnlst token, char **patt)
{
	char	*tmp;
	int		len;
	int		i;

	tmp = (char *)token->addr_1;
	i = 0;
	while (patt[i])
	{
		len = ft_strlen(tmp);
		tmp = ft_strnstr(tmp, patt[i], len - 1);
		if (!tmp)
			return (false);
		i++;
	}
	return (true);
}

int	_xpd_wildcards_filter(t_ppadlst list, char **patterns)
{
	t_pnlst	tmp;

	tmp = (*list)->d_top;
	while (tmp)
	{
		if (!_check_patterns(tmp, patterns))
		{
			_dlst_pop_in(list, &tmp);
			if (*list)
				tmp = (*list)->d_top;
			else
				break ;
		}
		else
			tmp = tmp->next;
	}
	ft_free_arr(patterns);
	return (_SUCCESS);
}

int	_xpd_merge_list(t_ppnlst token, t_ppadlst list)
{
	t_pnlst		tmp;
	t_ppnlst	to_remove;

	to_remove = token;
	tmp = (*list)->d_top;
	while (tmp)
	{
		_dlst_push_in(&(*token)->manager, *token, tmp->addr_1, NULL);
		tmp->addr_1 = NULL;
		token = &(*token)->next;
		tmp = tmp->next;
	}
	if (list)
		_dlst_pop_in(&(*token)->manager, to_remove);
	_dlst_clear(list);
	return (_SUCCESS);
}

int	_xpd_right_border(t_ppnlst token, t_ppadlst list)
{
	t_pnlst	tmp;
	char	*str;
	char	*rts;

	str = (*token)->addr_1;
	tmp = (*list)->d_top;
	while (tmp)
	{
		rts = tmp->addr_1;
		if (str[ft_strlen(str) - 1] != rts[ft_strlen(rts) - 1])
		{
			_dlst_pop_in(list, &tmp);
			if (*list)
				tmp = (*list)->d_top;
			else
				break ;
		}
		else
			tmp = tmp->next;
	}
	return (_SUCCESS);
}
int	_xpd_left_border(t_ppnlst token, t_ppadlst list)
{
	t_pnlst	tmp;
	char	*str;
	char	*rts;

	str = (*token)->addr_1;
	tmp = (*list)->d_top;
	while (tmp)
	{
		rts = tmp->addr_1;
		if (str[0] != rts[0])
		{
			_dlst_pop_in(list, &tmp);
			if (*list)
				tmp = (*list)->d_top;
			else
				break ;
		}
		else
			tmp = tmp->next;
	}
	return (_SUCCESS);
}

int	_xpd_wildcards_proc(t_ppnlst token, t_ppadlst list)
{
	char	*tmp;
	char	**patterns;

	tmp = (*token)->addr_1;
	if (tmp[0] != '*')
		return (_xpd_left_border(token, list));
	if (tmp[ft_strlen(tmp) - 1] != '*')
		return (_xpd_right_border(token, list));
	patterns = ft_split((*token)->addr_1, '*');
	if (!*patterns)
		return (_xpd_merge_list(token, list));
	_xpd_wildcards_filter(list, patterns);
	if (!*list)
		return (_SUCCESS);
	return (_xpd_merge_list(token, list));
}

int	_xpd_wildcards(t_pdata data, t_ppnlst token)
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
		entry = readdir(cwd_dir);
	}
	closedir(cwd_dir);
	if (_xpd_wildcards_proc(token, &data->xpd))
		return (_FAILURE);
	return (_SUCCESS);
}
