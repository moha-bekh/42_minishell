/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 06:00:00 by moha              #+#    #+#             */
/*   Updated: 2024/09/26 19:43:28 by mbekheir         ###   ########.fr       */
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
		data->shell.new_term.c_lflag &= (ICANON | ECHO);
		if (tcsetattr(STDIN_FILENO, TCSANOW, &data->shell.new_term) == -1)
			return (_FAILURE);
	}
	return (_SUCCESS);
}

int	main(int ac, char **av, char **ev)
{
	static t_data	data;

	if (_stdio_init() || _shell_init(&data) || _signals_init(&data))
		return (perror("shell"), _FAILURE);
	if (_data_init(&data, ac, av, ev))
		return (perror("data"), _data_clear(&data), _FAILURE);
	while (true)
	{
		data.prompt = readline("minishell$ ");
		if (!data.prompt)
			return (write(1, "exit\n", 5), _data_clear(&data));
		add_history(data.prompt);
		if (_tok_list(&data) && !_data_structs_clear(&data))
			continue ;
		// _dlst_print_tokens(data.tokens);
		_tree_builder(&data.tree, data.tokens->d_top);
		if (_exec(&data, &data.tree) && !_data_structs_clear(&data))
			continue ;
		_data_structs_clear(&data);
	}
	return (_data_clear(&data), _SUCCESS);
}
