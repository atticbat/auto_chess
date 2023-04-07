#include "get_next_line.hpp"

static size_t ft_strlen(const char *str) {
  size_t i;

  i = 0;
  while (str[i] != '\0') {
    i++;
  }
  return (i);
}

static void *ft_memcpy(void *dst, const void *src, size_t n) {
  char *dstptr;
  const char *srcptr;

  if (!dst && !src)
    return (NULL);
  dstptr = (char *)dst;
  srcptr = (const char *)src;
  while (n) {
    *dstptr = *srcptr;
    dstptr++;
    srcptr++;
    n--;
  }
  return (dst);
}

char *ft_strjoin(char const *s1, char const *s2) {
  unsigned int len1;
  unsigned int len2;
  unsigned int to_malloc;
  char *ptr;

  if (s1 == NULL || s2 == NULL)
    return (NULL);
  len1 = ft_strlen(s1);
  len2 = ft_strlen(s2);
  to_malloc = len1 + len2 + 1;
  if (s1[0] == '\0' && s2[0] == '\0')
    to_malloc++;
  ptr = (char *)malloc((to_malloc) * sizeof(char));
  if (!ptr)
    return (NULL);
  ft_memcpy(ptr, s1, len1);
  ft_memcpy(ptr + len1, s2, len2);
  ptr[len1 + len2] = '\0';
  return (ptr);
}

char *ft_strdup(const char *str) {
  size_t l;
  char *ptr;
  size_t i;

  if (!str)
    return (NULL);
  l = ft_strlen(str);
  ptr = (char *)malloc(sizeof(char) * (l + 1));
  if (!ptr)
    return (NULL);
  i = 0;
  while (i < l) {
    ptr[i] = str[i];
    i++;
  }
  ptr[i] = '\0';
  return (ptr);
}

char *ft_substr(char const *s, unsigned int start, size_t len) {
  char *ptr;
  size_t i;

  if (!s)
    return (NULL);
  if (ft_strlen(s) < start) {
    ptr = (char *)malloc(sizeof(char));
    if (!ptr)
      return (NULL);
    *ptr = '\0';
    return (ptr);
  }
  if (ft_strlen(s) - start > len)
    i = len + 1;
  else
    i = ft_strlen(s) - start + 2;
  ptr = (char *)malloc((i) * sizeof(char));
  if (!ptr)
    return (NULL);
  ft_memcpy(ptr, s + start, i - 1);
  ptr[i - 1] = '\0';
  return (ptr);
}
