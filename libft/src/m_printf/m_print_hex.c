/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_print_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:27:21 by moha              #+#    #+#             */
/*   Updated: 2024/05/29 14:38:16 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	m_put_hex(int fd, unsigned int unbr, const char format, int *len)
{
	if (unbr >= 16)
	{
		m_put_hex(fd, (unbr / 16), format, len);
		m_put_hex(fd, (unbr % 16), format, len);
	}
	else
	{
		if (unbr <= 9)
			m_print_char(fd, (unbr + '0'), len);
		else
		{
			if (format == 'x')
				m_print_char(fd, ((unbr - 10) + 'a'), len);
			else if (format == 'X')
				m_print_char(fd, ((unbr - 10) + 'A'), len);
		}
	}
	return ;
}

void	m_print_hex(int fd, unsigned int unbr, const char format, int *len)
{
	if (!unbr)
		m_print_char(fd, '0', len);
	else
		m_put_hex(fd, unbr, format, len);
	return ;
}

void	m_put_ptr(int fd, unsigned long long ptr, int *len)
{
	if (ptr >= 16)
	{
		m_put_ptr(fd, (ptr / 16), len);
		m_put_ptr(fd, (ptr % 16), len);
	}
	else
	{
		if (ptr <= 9)
			m_print_char(fd, (ptr + '0'), len);
		else
			m_print_char(fd, ((ptr - 10) + 'a'), len);
	}
	return ;
}

void	m_print_ptr(int fd, unsigned long long ptr, int *len)
{
	if (!ptr)
		m_print_str(fd, "(nil)", len);
	else
	{
		m_print_str(fd, "0x", len);
		m_put_ptr(fd, ptr, len);
	}
	return ;
}
