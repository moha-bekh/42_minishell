/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:47:06 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/28 12:51:23 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static t_list	*line_list;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	read_and_stock(fd, &line_list);
	if (!line_list)
		return (NULL);
	extract_line(line_list, &line);
	if (!line)
		return (free_list(line_list), NULL);
	clean_list(&line_list);
	if (line[0] == '\0')
	{
		free_list(line_list);
		line_list = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	read_and_stock(int fd, t_list **line_list)
{
	char	*buf;
	int		readed;

	readed = 1;
	while (!is_new_line(*line_list) && readed != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return ;
		readed = (int)read(fd, buf, BUFFER_SIZE);
		if ((!*line_list && readed == 0) || readed == -1)
			return (free(buf), (void)0);
		buf[readed] = '\0';
		add_to_list(line_list, buf, readed);
		free(buf);
	}
}

void	add_to_list(t_list **line_list, char *buf, int readed)
{
	t_list	*new_node;
	t_list	*last_node;
	int		i;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->value = malloc(sizeof(char) * (readed + 1));
	if (!new_node->value)
		return ;
	i = 0;
	while (buf[i] && i < readed)
	{
		new_node->value[i] = buf[i];
		i++;
	}
	new_node->value[i] = '\0';
	if (!*line_list)
	{
		*line_list = new_node;
		return ;
	}
	last_node = get_last_node(*line_list);
	last_node->next = new_node;
}

void	extract_line(t_list *line_list, char **line)
{
	int	i;
	int	j;

	if (!line_list)
		return ;
	generate_line(line_list, line);
	if (!*line)
		return ;
	j = 0;
	while (line_list)
	{
		i = 0;
		while (line_list->value[i])
		{
			if (line_list->value[i] == '\n')
			{
				(*line)[j++] = line_list->value[i];
				break ;
			}
			(*line)[j++] = line_list->value[i++];
		}
		line_list = line_list->next;
	}
	(*line)[j] = 0;
}

void	clean_list(t_list **line_list)
{
	t_list	*clean_node;
	t_list	*last_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_list));
	if (!line_list || !clean_node)
		return ;
	clean_node->next = NULL;
	last_node = get_last_node(*line_list);
	i = 0;
	while (last_node->value[i] && last_node->value[i] != '\n')
		i++;
	if (last_node->value && last_node->value[i] == '\n')
		i++;
	clean_node->value = malloc(sizeof(char) * ((ft_strlen(last_node->value)
					- i) + 1));
	if (!clean_node->value)
		return ;
	j = 0;
	while (last_node->value[i])
		clean_node->value[j++] = last_node->value[i++];
	clean_node->value[j] = '\0';
	free_list(*line_list);
	*line_list = clean_node;
}
