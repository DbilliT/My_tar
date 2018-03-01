#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include "archive.h"
#include "get_next_line.h"

int	strclen(char *str, int del)
{
  int	i;

  if (str == NULL)
    return (0);
  i = 0;
  while (str[i] != del && str[i] != '\0')
    i = i + 1;
  return (i);
}

void	write_content(int fd, int ffd)
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
	{
	  if (str[0] == '\0' || strclen(str, 3) != 0)
	    {
	      write(ffd, str, strclen(str, 3));
	      if (strclen(str, 3) == strclen(str, 0))
		write(ffd, "\n", 1);
	    }
	  free(str);
	}
    }
}

void	create_file(int fd, char *name, t_flags *flags)
{
  int	ffd;
  char	*mode;
  char	*tmp;

  if (flags->verbose)
    printf("-> %s\n", name);
  if ((ffd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 33188)) == -1)
    return;
  if ((tmp = get_next_line(fd)) != NULL)
    free(tmp);
  mode = get_next_line(fd);
  if ((tmp = get_next_line(fd)) != NULL)
    free(tmp);
  write_content(fd, ffd);
  if (flags->permission && mode != NULL)
    fchmod(ffd, atoi(mode));
  if (mode != NULL)
    free(mode);
  close(ffd);
}

void	create_directory(int fd, char *name, t_flags *flags)
{
  char	*tmp;

  if (flags->verbose)
    printf("-> %s\n", name);
  mkdir(name, 164333);
  if ((tmp = get_next_line(fd)) != NULL)
    free(tmp);
  if ((tmp = get_next_line(fd)) != NULL)
    free(tmp);
  if ((tmp = get_next_line(fd)) != NULL)
    free(tmp);
  if ((tmp = get_next_line(fd)) != NULL)
    free(tmp);
}

void	create_files(char *archive, t_flags *flags)
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
	    create_directory(fd, str, flags);
	  else
	    create_file(fd, str, flags);
	}
      free(str);
      str = get_next_line(fd);
    }
}
