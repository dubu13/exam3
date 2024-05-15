#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define	BUFFER_SIZE 42
#endif

int	ft_strlen(const char *str)
{
	int len = 0;

	while (str[len])
		len++;
	return (len);
}

void	ft_strcpy(char *dst, const char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

char	*ft_strdup(const char *src)
{
	char	*dst = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dst)
		return (NULL);
	ft_strcpy(dst, src);
	return (dst);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (NULL);
	char	*new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	int		s1_len = ft_strlen(s1);
	if (!new)
		return (NULL);
	ft_strcpy(new, s1);
	ft_strcpy(new + s1_len, s2);
	free(s1);
	return (new);
}

char	*ft_strchr(char *str, char target)
{
	while (*str)
	{
		if (*str == (char)target)
			return ((char *)str);
		str++;
	}
	return (NULL);
}
char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char	*line;
	char	*new_line;
	int		r_byte = 0;
	int		len = 0;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = ft_strdup(buff);
	while (!(new_line = ft_strchr(line, '\n')) && (r_byte = read(fd, buff, BUFFER_SIZE)))
	{
		buff[r_byte] = '\0';
		line = ft_strjoin(line, buff);
	}
	if (line[0] == '\0')
		return (free(line), NULL);
	if (new_line != NULL)
	{
		len = new_line - line + 1;
		ft_strcpy(buff, new_line + 1);
	}
	else
	{
		len = ft_strlen(line);
		buff[0] = '\0';
	}
	line[len] = '\0';
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("test.txt", O_RDONLY);

// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("Line read: %s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }