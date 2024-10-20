/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _resolve_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:19:04 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/21 00:15:35 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int _path_incwd(t_pdata data, t_ppncmd cmd, char **paths)
{
	char *tmp;

	tmp = ft_strjoin("./", (*cmd)->args[0]);
	if (!tmp)
		return (ft_free_arr(paths), _FAILURE);
	if (!access(tmp, F_OK))
	{
		if (!access(tmp, X_OK))
			(*cmd)->path = tmp;
		else
		{
			free(tmp);
			ft_free_arr(paths);
			_err_print(_ERR_PERM, (*cmd)->args[0], true, 126);
			return (_data_clear_exit(data, 126));
		}
	}
	return (_SUCCESS);
}

char *_find_path_(t_ppncmd cmd, char **paths)
{
	char *path;
	char *tmp;
	int i;

	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (ft_free_arr(paths), NULL);
		path = ft_strjoin(tmp, (*cmd)->args[0]);
		if (!path)
			return (free(tmp), ft_free_arr(paths), NULL);
		free(tmp);
		if (!access(path, F_OK))
			return (ft_free_arr(paths), path);
		free(path);
		path = NULL;
	}
	return (ft_free_arr(paths), NULL);
}

int _get_paths_(t_pdata data, char ***paths)
{
	char *tmp;

	*paths = NULL;
	tmp = _get_path(data);
	if (tmp)
	{
		*paths = ft_split(tmp, ':');
		if (!*paths)
			return (_FAILURE);
	}
	else if (!tmp && data->args._hard_path)
	{
		*paths = ft_split(data->args._hard_path, ':');
		if (!*paths)
			return (_FAILURE);
	}
	return (_SUCCESS);
}

int _try_n_set_path(t_ppncmd cmd, char *path)
{
	if (access(path, F_OK))
	{
		_err_print(_ERR_NO_FILE, path, true, 127);
		return (_FAILURE);
	}
	if (access(path, X_OK))
	{
		_err_print(_ERR_PERM, path, true, 126);
		return (_FAILURE);
	}
	(*cmd)->path = ft_strdup(path);
	if (!(*cmd)->path)
		return (_FAILURE);
	return (_SUCCESS);
}

int _resolve_path(t_pdata data, t_ppncmd cmd)
{
	char **paths;
	char *tmp;

	paths = NULL;
	if (ft_strchr((*cmd)->args[0], '/'))
		return (_try_n_set_path(cmd, (*cmd)->args[0]));
	if (_get_paths_(data, &paths))
		return (_FAILURE);
	if (!paths)
	{
		_err_print(_ERR_NO_FILE, (*cmd)->args[0], true, 127);
		return (_data_clear_exit(data, 127));
	}
	tmp = _find_path_(cmd, paths);
	if (!tmp)
		return (_FAILURE);
	if (_try_n_set_path(cmd, tmp))
		return (free(tmp), _FAILURE);
	free(tmp);
	if (!(*cmd)->path && _path_incwd(data, cmd, paths))
		return (_FAILURE);
	return (_SUCCESS);
}
