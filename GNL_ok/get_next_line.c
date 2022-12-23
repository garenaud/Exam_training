/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creyt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:50:10 by creyt             #+#    #+#             */
/*   Updated: 2022/11/08 15:33:35 by creyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_init(int fd, t_gnl *gnl)
{
	gnl->pos = 0;
	gnl->fd = fd;
	gnl->maxbuf = read(fd, gnl->backup, BUFFER_SIZE);
	if (gnl->maxbuf <= 0)
		return (0);
	else
		return (1);
}

char	ft_check_read(t_gnl *gnl)
{
	char	c;

	if (gnl->pos >= gnl->maxbuf)
	{
		gnl->pos = 0;
		gnl->maxbuf = read(gnl->fd, gnl->backup, BUFFER_SIZE);
		if (gnl->maxbuf <= 0)
			return (0);
	}
	c = gnl->backup[gnl->pos];
	gnl->pos++;
	return (c);
}

int	ft_len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_join(char *s1, char c)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = ft_len(s1);
	str = (char *)malloc((len + 2) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	if (s1)
		free(s1);
	return (str);
}

char	*get_next_line(int fd)
{
	static t_gnl	gnl = {.fd = -1};
	char			*str;
	char			c;

	str = NULL;
	if (gnl.fd != fd)
	{
		if (!ft_init(fd, &gnl))
			return (0);
	}
	c = ft_check_read(&gnl);
	while (c)
	{
		str = ft_join(str, c);
		if (c == '\n')
			return (str);
		c = ft_check_read(&gnl);
	}
	return (str);
}

int	main()
{
	int	fd = open("test.txt", O_RDONLY);
	int	i = 10;

	while (i-- > 0)
		printf("%s", get_next_line(fd));
}

