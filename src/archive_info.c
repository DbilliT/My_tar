#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include "archive.h"
#include "get_next_line.h"

void    skip_content(int fd)
{
  int	eof;
  char	*str;

  eof = 0;
  while (!eof)
    {
      str = get_next_line(fd);
      if (strclen(str, 3) != strclen(str, 0) || str == NULL)
	eof = 1;
      if (str != NULL)
	free(str);
    }
}

void    show_file(int fd, char *name, t_flags *flags)
{
  char	*size;
  char	*permission;
  char	*date;

  size = get_next_line(fd);
  permission = get_next_line(fd);
  date = get_next_line(fd);
  if (!flags->verbose)
    printf("%s\n", name);
  else
    printf("%s> Size: %s | Permission: %s | Date: %s\n", name,
	   size, permission, date);
  skip_content(fd);
}

void    show_directory(int fd, char *name, t_flags *flags)
{
  char	*size;
  char	*permission;
  char	*date;

  size = get_next_line(fd);
  permission = get_next_line(fd);
  date = get_next_line(fd);
  if (!flags->verbose)
    printf("%s\n", name);
  else
    printf("%s> Size: %s | Permission: %s | Date: %s\n", name,
	   size, permission, date);
  get_next_line(fd);
}

void    archive_info(char *archive, t_flags *flags)
{
  int	fd;
  char	*str;

  if ((fd = open(archive, O_RDONLY)) == -1)
    return;
  str = get_next_line(fd);
  while (str != NULL)
    {
      if (strlen(str) > 0)
	{
	  if (str[strlen(str) - 1] == '/')
	    show_directory(fd, str, flags);
	  else
	    show_file(fd, str, flags);
	}
      free(str);
      str = get_next_line(fd);
    }
}
