/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 06:00:00 by moha              #+#    #+#             */
/*   Updated: 2024/09/25 17:42:11 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_set_shell(t_pdata data)
{
	int i;

	open("/dev/stdin", O_RDWR);
	open("/dev/stdout", O_RDWR);
	open("/dev/stderr", O_RDWR);
	i = 2;
	while (++i < 6)
		close(i);
	if (isatty(STDIN_FILENO))
	{
		tcgetattr(STDIN_FILENO, &data->shell.org_term);
		data->shell.new_term = data->shell.org_term;
		data->shell.new_term.c_lflag &= (ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &data->shell.new_term);
	}
	else
	{
		tcgetattr(STDIN_FILENO, &data->shell.org_term);
		data->shell.new_term = data->shell.org_term;
		data->shell.new_term.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &data->shell.new_term);
	}
	return (_SUCCESS);
}

int	main(int ac, char **av, char **ev)
{
	static t_data	data;

	_set_shell(&data);
	if (_data_init(&data, ac, av, ev))
		return (_data_clear(&data), _FAILURE);
	while (true)
	{
		data.prompt = readline("minishell$ ");
		if (!data.prompt)
			return (printf("exit\n"), _data_clear(&data));
		add_history(data.prompt);
		if (_tok_list(&data) && !_data_structs_clear(&data))
			continue ;
		_tree_builder(&data.tree, data.tokens->d_top);
		if (_exec(&data, &data.tree) && !_data_structs_clear(&data))
			continue ;
		_data_structs_clear(&data);
	}
	return (_data_clear(&data), _SUCCESS);
}
