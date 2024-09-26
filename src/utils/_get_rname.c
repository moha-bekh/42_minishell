/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _get_rname.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 02:32:54 by oek               #+#    #+#             */
/*   Updated: 2024/09/26 02:43:39 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*_get_rname(void)
{
	int				fd;
	unsigned char	*buf;
	int				i;

	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (_alloc((void **)&buf, 11))
		return (NULL);
	read(fd, buf, 10);
	close(fd);
	i = -1;
	while (buf[++i])
		buf[i] = (buf[i] % 26) + 97;
	return ((char *)buf);
}
