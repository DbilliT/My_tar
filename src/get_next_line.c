#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int	clen(const char *str, const char delimiter)
{
  int	i;

  if (str == NULL)
    return (0);
  i = 0;
  while (str[i] != delimiter && str[i] != '\0')
    i = i + 1;
  return (i);
}

char    *my_strncat(char *dest, const char *src, int nb)
{
  int   i;
  int   j;

  i = 0;
  j = 0;
  if (dest == NULL)
    return ((char *)src);
  if (src == NULL)
    return (dest);
  while (dest[i] != '\0')
    i = i + 1;
  while (j < nb && src[j] != '\0')
    {
      dest[i + j] = src[j];
      j = j + 1;
    }
  dest[i + j] = '\0';
  return (dest);
}

char	*my_strndup(const char *src, int size)
{
  char	*rt;

  if (src == NULL)
    return (NULL);
  if ((rt = malloc((size + 1) * sizeof(char))) == NULL)
    return (NULL);
  rt[0] = '\0';
  rt = my_strncat(rt, src, size);
  return (rt);
}

char	*concatenate(char *str1, char *str2)
{
  char	*rt;

  if (str1 == NULL)
    return (my_strndup(str2, clen(str2, 0)));
  if (str2 == NULL)
    return (str1);
  rt = malloc((clen(str1, 0) + clen(str2, 0) + 1) * sizeof(char));
  if (rt == NULL)
    {
      free(str1);
      return (NULL);
    }
  rt[0] = '\0';
  rt = my_strncat(rt, str1, clen(str1, 0));
  rt = my_strncat(rt, str2, clen(str2, 0));
  free(str1);
  return (rt);
}

char		*get_next_line(const int fd)
{
  static char	*mem = NULL;
  char		*returnstr;
  char		buffer[READ_SIZE + 1];
  int		ret;

  while (clen(mem, 10) == clen(mem, 0))
    {
      if ((ret = read(fd, buffer, READ_SIZE)) == -1)
	return (NULL);
      if (ret == 0)
	{
	  returnstr = my_strndup(mem, clen(mem, 10));
	  mem = NULL;
	  return (returnstr);
	}
      buffer[ret] = '\0';
      mem = concatenate(mem, buffer);
    }
  returnstr = my_strndup(mem, clen(mem, 10));
  mem = my_strndup(mem + clen(mem, 10) + 1, clen(mem, 0) - clen(mem, 10) - 1);
  if (mem[0] == '\0')
    mem = NULL;
  return (returnstr);
}
