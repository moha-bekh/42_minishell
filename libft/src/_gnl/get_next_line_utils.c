/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:47:02 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/28 12:58:05 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

int	is_new_line(t_list *line_list)
{
	t_list	*current;
	int		i;

	if (!line_list)
		return (0);
	current = get_last_node(line_list);
	i = 0;
	while (current->value[i])
	{
		if (current->value[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list	*get_last_node(t_list *line_list)
{
	t_list	*current;

	current = line_list;
	while (current && current->next)
		current = current->next;
	return (current);
}

void	generate_line(t_list *line_list, char **line)
{
	int	i;
	int	len;

	len = 0;
	while (line_list)
	{
		i = 0;
		while (line_list->value[i])
		{
			if (line_list->value[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		line_list = line_list->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

void	free_list(t_list *line_list)
{
	t_list	*current;
	t_list	*next;

	current = line_list;
	while (current)
	{
		free(current->value);
		next = current->next;
		free(current);
		current = next;
	}
}
