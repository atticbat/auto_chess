#ifndef CONVERSION_FUNCTIONS_HPP
# define CONVERSION_FUNCTIONS_HPP

# include <string.h>

void        ft_itoa(int num, char *buffer);
char	    **ft_split(char const *s, char c);
size_t		ft_strlcpy(char *dst, const char *src, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t n);
int			ft_atoi(const char *str);

#endif