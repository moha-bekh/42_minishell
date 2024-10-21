/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 06:00:00 by moha              #+#    #+#             */
/*   Updated: 2024/10/21 14:08:22 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_stdio_init(void)
{
	int	fd;

	fd = open("/dev/stdin", O_RDWR);
	if (fd == -1)
		return (_FAILURE);
	fd = open("/dev/stdout", O_RDWR);
	if (fd == -1)
		return (_FAILURE);
	fd = open("/dev/stderr", O_RDWR);
	if (fd == -1)
		return (_FAILURE);
	fd = 2;
	while (++fd < 6)
		close(fd);
	return (_SUCCESS);
}

int	_shell_init(t_pdata data)
{
	if (isatty(STDIN_FILENO))
	{
		if (tcgetattr(STDIN_FILENO, &data->shell.org_term) == -1)
			return (_FAILURE);
		data->shell.new_term = data->shell.org_term;
		data->shell.new_term.c_lflag |= (ICANON | ECHO | ECHOE
				| ECHOK | ISIG | IEXTEN);
		data->shell.new_term.c_lflag &= ~(ECHONL | ECHOPRT | ECHOKE);
		if (tcsetattr(STDIN_FILENO, TCSANOW, &data->shell.new_term) == -1)
			return (_FAILURE);
		rl_outstream = stderr;
	}
	else
		rl_outstream = stdin;
	return (_SUCCESS);
}

void	_canonical_mode(t_pdata data)
{
	while (true)
	{
		data->prompt = readline("minishell$ ");
		if (!data->prompt)
			return (write(1, "exit\n", 5), (void)_data_clear_exit(data, -1));
		add_history(data->prompt);
		if (_atol(data))
		{
			_data_structs_clear(data);
			continue ;
		}
		_tree_builder(&data->tree, data->tokens->d_top);
		if (_exec(data, &data->tree))
		{
			_data_structs_clear(data);
			continue ;
		}
		_data_structs_clear(data);
	}
	_data_clear(data);
}

void	_non_canonical_mode(t_pdata data)
{
	while (true)
	{
		data->prompt = readline(NULL);
		if (!data->prompt)
			return ((void)_data_clear_exit(data, -1));
		if (_atol(data))
		{
			_data_structs_clear(data);
			continue ;
		}
		_tree_builder(&data->tree, data->tokens->d_top);
		if (_exec(data, &data->tree))
		{
			_data_structs_clear(data);
			continue ;
		}
		_data_structs_clear(data);
	}
	_data_clear(data);
}

int	main(int ac, char **av, char **ev)
{
	if (_stdio_init() || _shell_init(_get_data()) || _sig_init(_get_data()))
		return (_FAILURE);
	if (_data_init(_get_data(), ac, av, ev))
		return (_data_clear(_get_data()), _FAILURE);
	if (isatty(STDIN_FILENO))
		_canonical_mode(_get_data());
	else
		_non_canonical_mode(_get_data());
	return (_SUCCESS);
}
