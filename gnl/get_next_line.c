/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:22:09 by grenaud-          #+#    #+#             */
/*   Updated: 2022/12/17 17:22:12 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int ft_init(int fd, t_read_info *buff)
{
	buff->fd = fd;
	buff->max = read(buff->fd, buff->data, BUFFER_SIZE);
	if (buff->max < 0)
		return (0);
	buff->pos = 0;
	return (1);
}

int ft_single(t_read_info *buff, char *res)
{
	*res = '\0';
	if (buff->pos >= buff->max)
	{
		buff->max = read(buff->fd, buff->data, BUFFER_SIZE);
		if (buff->max <= 0)
			return (0);
		buff->pos = 0;
	}
	*res = buff->data[buff->pos];
	buff->pos++;
	return (1);
}

char *ft_strjoin(char *s, char c)
{
	int i = 0, len = -1;
	char *line;

	while(s && s[++len]);
	line = malloc(len +2);
	if (!line)
		return (0);
	while(s && i < len)
	{
		line[i] = s[i];
		i++;
	}
	line[i] = c;
	line[++i] = '\0';
	free(s);
	return (line);
}

char *get_next_line(int fd)
{
	static t_read_info  read_info ={.fd = -1};
	char c, *line = 0;

	if (fd != read_info.fd)
	{
		if (!ft_init(fd, &read_info))
			return (0);
	}
	while(ft_single(&read_info, &c))
	{
		line = ft_strjoin(line, c);
		if (c == '\n')
			break;
	}
	return (line);
}