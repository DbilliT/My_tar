#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "archive.h"

void	create_data(int fdtar, t_linked *list)
{
  char	buffer[1024];
  char	separator[2];
  int	ret;

  separator[0] = 3;
  separator[1] = '\n';
  write(fdtar, list->header->name, strlen(list->header->name));
  write(fdtar, "\n", 1);
  write(fdtar, list->header->size, strlen(list->header->size));
  write(fdtar, "\n", 1);
  write(fdtar, list->header->mode, strlen(list->header->mode));
  write(fdtar, "\n", 1);
  write(fdtar, list->header->time, strlen(list->header->time));
  write(fdtar, "\n", 1);
  while ((ret = read(list->fd, buffer, 1024)) > 0)
    write(fdtar, buffer, ret);
  close(list->fd);
  write(fdtar, separator, 2);
}

void	create_archive(t_linked *list, char *file)
{
  int	fdtar;
  char	tmp[10];

  srand(time(NULL));
  sprintf(tmp, "%d", rand());
  if ((fdtar = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 33188)) == -1)
    {
      printf("Archive failed to open\n");
      return;
    }
  while (list != NULL)
    {
      create_data(fdtar, list);
      list = list->next;
    }
  close(fdtar);
  rename(tmp, file);
}
