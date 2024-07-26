/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:47:06 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/26 16:34:37 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd, t_list **lst)
{
	char			*line;

	if (fd < 0 || BF <= 0)
		return (NULL);
	line = NULL;
	read_and_stock(fd, lst);
	if (!(*lst))
		return (NULL);
	extract_line((*lst), &line);
	if (!line)
		return (free_list((*lst)), NULL);
	if (!clean_list(lst))
		return (ft_free(line), NULL);
	if (line[0] == '\0')
	{
		free_list((*lst));
		ft_free(line);
		return (NULL);
	}
	return (line);
}

void	read_and_stock(int fd, t_list **lst)
{
	char	*buf;
	int		rd;

	rd = 1;
	while (!is_new_line(*lst) && rd != 0)
	{
		buf = ft_calloc((BF + 1), sizeof(char));
		if (!buf)
			return ;
		rd = (int)read(fd, buf, BF);
		if ((!*lst && rd == 0) || rd == -1)
			return (ft_free(buf));
		buf[rd] = '\0';
		add_to_list(lst, buf, rd);
		ft_free(buf);
	}
}

void	add_to_list(t_list **lst, char *buf, int rd)
{
	t_list	*new;
	t_list	*last;
	int		i;

	new = ft_calloc(1, sizeof(t_list));
	if (!new)
		return ;
	new->value = ft_calloc((rd + 1), sizeof(char));
	if (!new->value)
		return (ft_free(new), ft_free(buf));
	i = 0;
	while (buf[i] && i < rd)
	{
		new->value[i] = buf[i];
		i++;
	}
	new->value[i] = '\0';
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = get_last_node(*lst);
	last->next = new;
}

void	extract_line(t_list *lst, char **line)
{
	int	i;
	int	j;

	if (!lst)
		return ;
	generate_line(lst, line);
	if (!*line)
		return ;
	j = 0;
	while (lst)
	{
		i = 0;
		while (lst->value[i])
		{
			if (lst->value[i] == '\n')
			{
				(*line)[j++] = lst->value[i];
				break ;
			}
			(*line)[j++] = lst->value[i++];
		}
		lst = lst->next;
	}
	(*line)[j] = '\0';
}

bool	clean_list(t_list **lst)
{
	t_list	*clean;
	t_list	*last;
	int		i;
	int		j;

	clean = ft_calloc(1, sizeof(t_list));
	if (!clean)
		return (false);
	last = get_last_node(*lst);
	if (!last)
		return (free_list(*lst), free_list(clean), false);
	i = 0;
	while (last->value[i] && last->value[i] != '\n')
		i++;
	if (last->value && last->value[i] == '\n')
		i++;
	clean->value = ft_calloc(((ft_strlen(last->value) - i) + 1), sizeof(char));
	if (!clean->value)
		return (free_list(*lst), free_list(clean), false);
	j = 0;
	while (last->value[i])
		clean->value[j++] = last->value[i++];
	clean->value[j] = '\0';
	free_list(*lst);
	return (*lst = clean, true);
}
/* 
int main(void)
{
	// t_list *lst = NULL;

	// lst = ft_calloc(sizeof(t_list), 1);
	// if (!lst)
		// return (0);

	int fd = open("test.txt", O_RDONLY);
	char *line;
	
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%s\n", line);
		ft_free(line);
	}
	close(fd);
	return (0);
}
 */