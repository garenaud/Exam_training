/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:23:59 by grenaud-          #+#    #+#             */
/*   Updated: 2022/12/17 17:24:02 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
	int	fd;

	fd = open("Cookie.txt", O_RDONLY);
	if (fd == -1)
	{
		write(1, "FILE Error\n", 13);
		return (1);
	}
	printf("--------------------------- 1\n");
	printf("%s", get_next_line(fd));
	printf("--------------------------- 2\n");
	printf("%s", get_next_line(fd));
	printf("--------------------------- 3\n");
	printf("%s", get_next_line(fd));
	printf("--------------------------- 4\n");
	printf("%s", get_next_line(fd));
	printf("--------------------------- 5\n");
	printf("%s", get_next_line(fd));
	printf("--------------------------- 6\n");
	printf("%s", get_next_line(fd));
	printf("--------------------------- 7\n");
	printf("%s", get_next_line(fd));
	printf("\n");
	return (0);
}