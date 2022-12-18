#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

size_t	ft_strlen(const char *s)
{
	size_t i = 0;
	while(s && s[i])
		i++;
	return(i);
}

char *ft_strjoin(char *left_str, char *buff)
{
	size_t i;
	size_t j;
	char *str;
	if(!left_str)
	{
		left_str = (char *)malloc(1 * sizeof(char));
		left_str[0] = '\0';
	}
	if (!left_str || !buff)
		return(NULL);
	str = malloc(sizeof(char) * ((ft_strlen(left_str) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (left_str)
		while(left_str[++i] != '\0')
			str[i] = left_str[i];
	while(buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(left_str) + ft_strlen(buff)] = '\0';
	free(left_str);
	return(str);
}

char	*ft_strchr(char *s, int c)
{
	int i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while(s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_get_start(char *raw_line)
{
	int i = 0;
	int j = 0;
	char *str;
	while(raw_line[i] && raw_line[i] != '\n')
		i++;
	if(!raw_line[i])
	{
		free(raw_line);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(raw_line) - i + 1));
	if (!str)
		return(NULL);
	i++;
	while(raw_line[i])
		str[j++] = raw_line[i++];
	str[j] = '\0';
	free(raw_line);
	return(str);
}

char	*ft_get_line(char *raw_line)
{
	int i = 0;
	char *str;
	if (!raw_line[i])
		return (NULL);
	while(raw_line[i] && raw_line[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while(raw_line[i] && raw_line[i] != '\n')
	{
		str[i] = raw_line[i];
		i++;
	}
	if (raw_line[i] == '\n')
	{
		str[i] = raw_line[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_get_raw_line(int fd, char *raw_line)
{
	char *buff;
	int bytes = 1;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return(NULL);
	while (!ft_strchr(raw_line, '\n') && bytes != 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if(bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[bytes] = '\0';
		raw_line = ft_strjoin(raw_line, buff);
	}
	free(buff);
	return (raw_line);
}

char 	*get_next_line(int fd)
{
	char *line;
	static char *raw_line;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	raw_line = ft_get_raw_line(fd, raw_line);
	if (!raw_line)
		return(NULL);
	line = ft_get_line(raw_line);
	raw_line = ft_get_start(raw_line);
	return(line);
}
