/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _resolve_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:19:04 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/21 10:51:13 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_path_incwd(t_pdata data, t_ppncmd cmd, char **paths)
{
	char	*tmp;

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
			_data_clear_exit(data, 126);
		}
	}
	free(tmp);
	return (_SUCCESS);
}

char	*_find_path_(t_ppncmd cmd, char **paths)
{
	char	*path;
	char	*tmp;
	int		i;

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

int	_try_n_set_path(t_ppncmd cmd, char *path)
{
	if (access(path, F_OK))
	{
		_err_print(_ERR_NO_FILE, path, true, 127);
		_data_clear_exit(_get_data(), 127);
	}
	if (access(path, X_OK))
	{
		_err_print(_ERR_PERM, path, true, 126);
		_data_clear_exit(_get_data(), 126);
	}
	(*cmd)->path = ft_strdup(path);
	if (!(*cmd)->path)
		return (_FAILURE);
	return (_SUCCESS);
}

int	_path_finder(t_pdata data, t_ppncmd cmd, char **paths)
{
	char	*tmp;

	tmp = NULL;
	tmp = _find_path_(cmd, paths);
	if (!tmp)
	{
		if (_path_incwd(data, cmd, paths))
			return (_FAILURE);
		else
		{
			(*cmd)->path = ft_strdup((*cmd)->args[0]);
			if (!(*cmd)->path)
				return (_FAILURE);
		}
	}
	else
	{
		if (_try_n_set_path(cmd, tmp))
			return (free(tmp), _FAILURE);
		free(tmp);
	}
	return (_SUCCESS);
}

int	_resolve_path(t_pdata data, t_ppncmd cmd)
{
	char	**paths;

	if (ft_strchr((*cmd)->args[0], '/'))
		return (_try_n_set_path(cmd, (*cmd)->args[0]));
	paths = NULL;
	if (_get_paths_(data, &paths))
		return (_FAILURE);
	if (!paths)
	{
		_err_print(_ERR_NO_FILE, (*cmd)->args[0], true, 127);
		return (_data_clear_exit(data, 127));
	}
	if (_path_finder(data, cmd, paths))
		return (_FAILURE);
	return (_SUCCESS);
}
