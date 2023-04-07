#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10

typedef struct s_static {
  char *store;
  char buff[BUFFER_SIZE + 1];
} t_static;

char *get_next_line(int fd);
char *ft_strdup(const char *str);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_substr(char const *s, unsigned int start, size_t len);

#endif
