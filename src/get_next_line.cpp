/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas <khatlas@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:13:07 by khatlas           #+#    #+#             */
/*   Updated: 2022/05/08 15:32:44 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.hpp"

static char	*store_append(char *store, char *buff)
{
	char	*temp;

	if (store == NULL)
		return (ft_strdup(buff));
	else
	{
		temp = store;
		store = ft_strjoin(store, buff);
		free (temp);
		return (store);
	}
}

static char	*generate_strings(char *store, int len, char **out)
{
	char	*temp;

	if (store[len] == '\n')
	{
		temp = store;
		*out = ft_substr(store, 0, len + 1);
		store = ft_strdup(store + len + 1);
		free (temp);
		return (store);
	}
	else
	{
		*out = ft_strdup(store);
		free(store);
		return (NULL);
	}
}

static char	*ft_strchr(const char *str, int c)
{
	c = c % 128;
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == c)
			return ((char *) str);
		str++;
	}
	if (c == 0)
		return ((char *) str);
	return (NULL);
}

static int	check_null(char *buffer, int len, char **store)
{
	if (*buffer == '\0')
		return (1);
	if (*store)
	{
		if (**store == '\0' && len == 0)
		{
			free (*store);
			*store = NULL;
			return (1);
		}
	}
	else if (len == 0)
	{
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_static	ctnr;
	char			*out;
	int				len;

	out = NULL;
	len = 1;
	if (fd < 0 || BUFFER_SIZE < 1 || fd > OPEN_MAX)
		return (NULL);
	while (len > 0 && !(ft_strchr(ctnr.store, '\n')))
	{
		len = read (fd, ctnr.buff, BUFFER_SIZE);
		if (len == -1 || check_null(ctnr.buff, len, &(ctnr.store)))
			return (NULL);
		(ctnr.buff)[len] = '\0';
		ctnr.store = store_append(ctnr.store, ctnr.buff);
	}
	len = 0;
	while ((ctnr.store)[len] != '\n' && (ctnr.store)[len] != '\0')
		len++;
	ctnr.store = generate_strings(ctnr.store, len, &out);
	return (out);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int		fd;
// 	char	*ln;
// 	int		i;
// 	FILE	*read_txt;

// 	read_txt = fopen("read.txt", "w+");
// 	fprintf(read_txt, "asdf\nqwer\nzxcv\npok\n\n\n\n");
// 	fclose(read_txt);
// 	fd = open("read.txt", O_RDONLY);
// 	i = 0;
// 	while (i < 7)
// 	{
// 		ln = get_next_line(fd);
// 		printf("%s", ln);
// 		free (ln);
// 		i++;
// 	}
// 	close (fd);
// 	// system("leaks a.out");
// 	return (0);
// }
